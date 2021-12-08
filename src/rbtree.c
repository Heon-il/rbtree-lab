#include "rbtree.h"

#include <stdlib.h>

/* 따로 구현한 부분 */
void delete_node_all(rbtree* t, node_t* p){
  if (p==t->nil)
    return;
  delete_node_all(t, p->left);
  delete_node_all(t, p->right);
  free(p);
}

void left_rotation(rbtree* t, node_t*x){
  node_t *y = x->right;
  x->right = y->left;

  if (y->left != t->nil)
    y->left->parent = x;

  y->parent = x->parent;

  if (x->parent==t->nil) t->root = y;
  else if (x == x->parent->left) x->parent->left = y;
  else x->parent->right = y; 
  
  y->left = x;
  x->parent = y;
}

void right_rotation(rbtree *t, node_t *y){
  node_t *x = y->left;
  y->left = x->right;

  if (x->right != t->nil)
    x->right->parent = y;

  x->parent = y->parent;

  if (y->parent == t->nil) t->root = x;
  else if (y == y->parent->right) y->parent->right = x; 
  else y->parent->left = x;
  
  x->right = y;
  y->parent = x;
}


void insert_fixup(rbtree* t, node_t *z){

  while (z->parent->color == RBTREE_RED){ // insert_fixup에서 에러가 났다.
    // z is left child
    if(z->parent == z->parent->parent->left){
      node_t* y = z->parent->parent->right; // uncle
      
      // case 1) uncle(red)
      if (y->color == RBTREE_RED){
        z->parent->color = RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        z = z->parent->parent;
      }
      else{
        // case 2) uncle(black) + triangle
        if(z==z->parent->right){
          z = z->parent;
          left_rotation(t, z);
        }
        // case 3) uncle(black) + linear
        z->parent->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        right_rotation(t, z->parent->parent);
      } 
    }

    // z is right child
    else{
      node_t *y = z->parent->parent->left; // uncle

      // case 1) uncle(red)
      if (y->color == RBTREE_RED){
        z->parent->color = RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        z = z->parent->parent;
      }
      else{
        // case 2) uncle(black) + triangle
        if(z==z->parent->left){
          z = z->parent;
          right_rotation(t, z);
        }

        // case 3) uncle(black) + linear
        z->parent->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        left_rotation(t, z->parent->parent);
      }
    }
  }
  t->root->color = RBTREE_BLACK;
}

void rb_transplant(rbtree* t, node_t* u, node_t* v){
  if(u->parent == t->nil)
    t->root = v;
  else if(u == u->parent->left)
    u->parent->left = v;
  else
    u->parent->right = v;
  v->parent = u->parent;
}

node_t* tree_min(rbtree* t, node_t* p){
  while(p->left != t->nil)
    p = p->left;
  return p;
}


void delete_fixup(rbtree* t, node_t* x){
  while(x!=t->root && x->color == RBTREE_BLACK){
    // x is left child
    if (x== x->parent->left){
      node_t* w = x->parent->right; // sibling

      // case change)
      if (w->color == RBTREE_RED){
        w->color = RBTREE_BLACK;
        x->parent->color = RBTREE_RED;
        left_rotation(t, x->parent);
        w = x->parent->right;
      }
      
      // case 1)
      if (w->left->color == RBTREE_BLACK && w->right->color ==RBTREE_BLACK){
        w->color = RBTREE_RED;
        x = x->parent;
      }
      else{
        // case 2)
        if (w->right->color == RBTREE_BLACK){
          w->left->color = RBTREE_BLACK;
          w->color = RBTREE_RED;
          right_rotation(t, w);
          w = x->parent->right;
        }

        // case 3)
        w->color = x->parent->color;
        x->parent->color = RBTREE_BLACK;
        w->right->color = RBTREE_BLACK;
        left_rotation(t, x->parent);
        x = t->root;
      }
    }

    // x is right child
    else{
      node_t* w = x->parent->left; // sibling

      // case change)
      if (w->color == RBTREE_RED){
        w->color = RBTREE_BLACK;
        x->parent->color = RBTREE_RED;
        right_rotation(t, x->parent);
        w = x->parent->left;
      }

      // case 1)
      if (w->left->color == RBTREE_BLACK && w->right->color ==RBTREE_BLACK){
        w->color = RBTREE_RED;
        x = x->parent;
      }

      else{
        // case 2)
        if (w->left->color == RBTREE_BLACK){
          w->right->color = RBTREE_BLACK;
          w->color = RBTREE_RED;
          left_rotation(t, w);
          w = x->parent->left;
        }

        // case 3)
        w->color = x->parent->color;
        x->parent->color = RBTREE_BLACK;
        w->left->color = RBTREE_BLACK;
        right_rotation(t, x->parent);
        x = t->root;
      }
    }
  }

  x->color = RBTREE_BLACK;
}


key_t *inorder(const rbtree* t, node_t* p, key_t *arr){
  if (p==t->nil){
    return arr;
  }
  arr = inorder(t, p->left, arr);
  *arr = p->key;
  arr += 1;
  arr = inorder(t, p->right, arr);
  return arr;
}

/*      */


rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  // dummy node를 가리키도록 한다.
  node_t* dummy_node = (node_t*)calloc(1, sizeof(node_t));
  dummy_node->color = RBTREE_BLACK;
  p->root = dummy_node;
  p->nil = dummy_node;
  return p;
}


void delete_rbtree(rbtree *t) {
  // 따로 구현하기
  delete_node_all(t, t->root);
  free(t->nil); t->nil = NULL; // nil node 해제
  free(t); t=NULL;
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  node_t *y = t->nil;
  node_t *x = t->root;

  // 삽입할 노드 생성
  node_t* node = (node_t*)calloc(1, sizeof(node_t));
  node->key = key;
  node->left = t->nil;
  node->right = t->nil;
  node->color = RBTREE_RED;

  while (x != t->nil){
    y = x;
    x = (key < x->key) ? x->left : x->right;
  }

  node->parent = y;
  if(y==t->nil){
    t->root = node;
    node->color = RBTREE_BLACK;
  }
  else if(key<y->key)
    y->left = node;
  else
    y->right = node;

  insert_fixup(t, node);

  return t->root;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  // 못찾은 경우 NULL을 return 하도록 해야 한다.
  node_t* cur = t->root;

  while (cur->key != key && cur!=t->nil)
    cur = (key < cur->key) ? cur->left : cur->right;
  
  if (cur==t->nil)
    return NULL; // wrong key 인경우 assert(q==NULL)을 통과해야 한다.
  else
    return cur;
}

node_t *rbtree_min(const rbtree *t) {
  node_t *cur = t->root;
  while(cur->left != t->nil)
    cur = cur->left;
  return cur;
}

node_t *rbtree_max(const rbtree *t) {
  node_t *cur = t->root;
  while(cur->right != t->nil)
    cur = cur->right;
  return cur;
}

int rbtree_erase(rbtree *t, node_t *p) {
  node_t* y = p;
  color_t y_original_color = y->color;
  node_t* x; // 이중 블랙 노드 가능성이 생기는 노드

  // case 1) Left child : nil
  if(p->left == t->nil){
    x = p->right;
    rb_transplant(t, p, p->right);
  }
  // case 2) Right child : nil
  else if (p->right ==t->nil){
    x = p->left;
    rb_transplant(t, p, p->left);
  }

  // case 3) All Subtree
  else{
    y = tree_min(t, p->right);
    y_original_color = y->color;
    x = y->right;
    if (y->parent == p){
      x->parent = y;
    }
    else{
      rb_transplant(t, y, y->right);
      y->right = p->right;
      y->right->parent = y;
    }
    rb_transplant(t, p, y);
    y->left = p->left;
    y->left->parent = y;
    y->color = p->color;
  }

  if (y_original_color == RBTREE_BLACK)
    delete_fixup(t, x);
  
  free(p); p=NULL;
  return 0;
}


int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  inorder(t, t->root, arr);
  return 0;
}