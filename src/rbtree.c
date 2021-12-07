#include "rbtree.h"
#include <stdlib.h>
#include <stdio.h> // 나중에 삭제


int bst_erase(rbtree *t, node_t* z){
  // 루트를 삭제 할 때에는 t의 root를 NULL로 만들어 줘야 한다.
  if (z->left == NULL){
    bst_transplant(t,z, z->right);

  }
  else if (z->right ==NULL){
    bst_transplant(t,z,z->left);
  }
  else{
    node_t *y = successor(t, z);
    // z가 y의 부모가 아닌 경우
    if(y->parent != z){
      bst_transplant(t, y, y->right);
      y->right = z->right;
      y->right->parent = y;
    }
    else{
      bst_transplant(t, z, y);
      y->left = z->left;
      y->left->parent = y;
    }
  }
  free(z);
  return 0;
}

// 노드 u가 루트인 subtree를 노드 v가 루트인 subtree로 교체할 때, 
void bst_transplant(rbtree* t, node_t* u, node_t* v){
  // u가 전체 tree의 루트인 경우
  if (u->parent == NULL)
    t->root = v;

  // u가 왼쪽 자식 인 경우
  else if (u == u->parent->left)
    u->parent->left= v;
  else
    u->parent->right = v; 
  
  if (v!=NULL)
    v->parent = u->parent;
}

void rbtree_transplant(rbtree* t, node_t* u, node_t* v){
  if (u->parent == NULL)
    t->root = v;
  else if (u==u->parent->left)
    u->parent->left =v;
  else
    u->parent->right = v;
  
  if(v!=NULL)
    v->parent = u->parent;
}


node_t *successor(rbtree *t , node_t *x){
  // right subtree
  if (x->right!=NULL){
    // right subtree의 max
    x = x->right;
    while(x->left!=NULL)
      x = x->left;
    return x;
  }

  else{
    // North - West
    node_t* y  = x->parent;
    while (y!=NULL && x == y->right){
      x = y;
      y = y->parent;
    }
  return y;
  }
}

node_t *predecessor(rbtree *t, node_t *x){
  // left subtree
  if (x->left != NULL){
    // left subtree의 max
    x = x->left;
    while (x->right!=NULL)
      x = x->right;
    return x;
  }

  else{
    // North - East
    node_t* y = x->parent;
    while (y!=NULL && x == y->left){
      x = y;
      y = y->parent;
    }
    return y;
  }
}

void left_rotation(rbtree *t, node_t *x){
  node_t *y = x->right;
  x->right = y->left;

  if (y->left !=NULL)
    y->left->parent = x;

  y->parent = x->parent;

  if (x->parent==NULL) t->root = y;
  else if (x == x->parent->left) x->parent->left = y;
  else x->parent->right = y; 
  
  y->left = x;
  x->parent = y;
}

void right_rotation(rbtree *t, node_t *y){
  node_t *x = y->left;
  y->left = x->right;

  if (x->right != NULL)
    x->right->parent = y;

  x->parent = y->parent;

  if (y->parent == NULL) t->root = x;
  else if (y->parent->left == y) y->parent->left = x; 
  else y->parent->right = x;
  
  x->right = y;
  y->parent = x;
}


void insert_fixup(rbtree *t, node_t *z){
  while (z->parent->color == RBTREE_RED){
    // 부모가 조부모의 왼쪽 자식인 경우
    if (z->parent == z->parent->parent->left){
      node_t *y = z->parent->parent->right; // 삼촌노드
      if (y == NULL || y->color ==RBTREE_BLACK){
        if(z == z->parent->right){
          z = z->parent;
          left_rotation(t, z);
        }
        z->parent->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        right_rotation(t, z->parent->parent);
      }

      else if (y->color == RBTREE_RED){
        // 삼촌의 색이 빨간색인 경우 -> color flipping
        z->parent->color = RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        z->parent ->parent ->color = RBTREE_RED;
        z = z->parent->parent; // 조부모를 다시 노드로 설정하여 insert_fixup을 반복
        if (z==t->root)
          break;
      }
    }

    // 부모가 조부모의 오른쪽 자식인 경우
    else{
      node_t *y = z->parent->parent->left; // 삼촌 노드
      if (y==NULL || y->color ==RBTREE_BLACK){
          if(z== z->parent->left){
          z = z ->parent;
          right_rotation(t,z);
        }
        z->parent->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        left_rotation(t, z->parent->parent); //탈출 조건은 없어도 되는건가?
      }
      else if (y->color ==RBTREE_RED){ // 삼촌 노드의 색이 빨간색인 경우 
        z->parent->color = RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        z->parent ->parent ->color = RBTREE_RED;
        z = z->parent->parent; // 조부모를 다시 노드로 설정하여 insert_fixup을 반복
        if (z==t->root)
          break;
      }
    }
  }
  t->root->color = RBTREE_BLACK;
}

// root -> left -> right
void postorder(rbtree *t, node_t *p){
  if (p==NULL)
    return;
  printf("key : %d color : %d, ", p->key, p->color);
  postorder(t, p->left);
  postorder(t, p->right);
  
}

// left -> root -> right
void inorder(rbtree *t, node_t *p){
  if (p==NULL)
    return;
  inorder(t, p->left);
  printf("key : %d color : %d, ", p->key, p->color);
  inorder(t, p->right);
}

// left -> right -> root
void preorder(rbtree *t, node_t *p){
  if (p==NULL)
    return;
  preorder(t, p->left);
  preorder(t, p->right);
  printf("key : %d color : %d, ", p->key, p->color);
}


void delete_node_all(node_t* p){
  if (p==NULL)
    return;
  delete_node_all(p->left);
  delete_node_all(p->right);
  free(p);
}

/* 위에는 내가 필요에 의해 구현 한 것 들*/

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  p->root = NULL;
  p->nil = NULL;

  return p;
}

void delete_rbtree(rbtree *t) {
  delete_node_all(t->root);
  free(t);
  t=NULL;
}

// key 추가
node_t *rbtree_insert(rbtree *t, const key_t key) {
  node_t *next, *cur;
  // 첫 insert
  if (t->root == NULL){
    node_t* node = (node_t*)calloc(1, sizeof(node_t));
    node->key = key;
    node->color = RBTREE_BLACK;
    node->parent = NULL;
    node -> left = NULL; 
    node -> right = NULL;
    t->root = node;
    return t->root;
  }

  // 노드 생성
  node_t* node = (node_t*)calloc(1, sizeof(node_t));
  node -> left = NULL; 
  node -> right = NULL;
  node->key = key;

  // BST insert
  cur = NULL; // 삽입될 노드의 부모 노드
  next = t->root;
  while (next != NULL){
    cur = next;
    next = (key < next->key ) ? next->left : next->right;
  }

  node->parent = cur;
  if (cur==NULL){ // 빈 트리
    node -> color = RBTREE_BLACK; 
    t->root = node;
  }
  else if (cur->key > key){
    node -> color = RBTREE_RED; 
    cur->left = node;
  }
  else{
    node -> color = RBTREE_RED; 
    cur->right = node;
  }

  insert_fixup(t, node);

  return t->root;
}


node_t *rbtree_find(const rbtree *t, const key_t key) {

  node_t *cur = t->root;
  while (cur->key !=key && cur!=NULL){
    if (key < cur->key){
      cur = cur->left;
      if (cur==NULL)
        return NULL;
    }
    else{
      cur = cur->right;
      if(cur==NULL)
        return NULL;
    }
  }
  
  // 위에서는 잘되는데 왜 오류가 나는지 모르겠다.
  // while (cur->key != key && cur != t->nil){
  //   cur = (cur->key<key) ? cur = cur->left: cur->right;
  // }
  
  return cur; 
}


node_t *rbtree_min(const rbtree *t) {
  node_t *x = t->root;
  if (x==NULL){
    // No node
    return x;
  }
  while (x->left!=NULL)
    x = x->left;
  return x;
}

node_t *rbtree_max(const rbtree *t) {
  node_t *x = t->root;
  if (x==NULL){
    // No node
    return x;
  }

  while (x->right !=NULL)
    x = x->right;
  return x;
}




// p로 지정된 node 삭제 및 메모리 반환
int rbtree_erase(rbtree *t, node_t *p) {

  // tree자체가 만들어지지 않았거나 트리에 아무 값도 없을 때
  if (t==NULL || t->root==NULL){
    return -1;
  }
  // 삭제하려는 노드가 존재하지 않는 경우
  if (p==NULL){
    // 예외처리를 배워서 해두면 좋을 것 같음
    return -1;
  }

  node_t* y = p;
  color_t y_original_color = y->color;
  node_t* x;

  node_t* tmp; // parent
  if (p->left ==NULL){ // NULL과 동일
    x = p->right;
    tmp = p->parent;
    rbtree_transplant(t, p, p->right);
  }
  else if (p->right == NULL){
    x = p->left;
    tmp = p->parent;
    rbtree_transplant(t, p, p->left);
  }

  else{
    // y는 무조건 NULL이 아니다.
    y = successor(t, p);
    x = y->right; 
    y_original_color = y->color;

    if (y->parent == p && x!=NULL){
      x->parent = y;
      tmp = y ;
    }
    else if (y->parent == p && x==NULL){
      tmp = y;
    }
    else{
      // 바꾸기 전에 
      tmp = y->parent; // 이게 나중에 x의 parent가 된다.
      rbtree_transplant(t, y, y->right);
      y->right = p->right;
      y->right->parent = y;
    }

    rbtree_transplant(t, p, y);
    y->left = p->left;
    y->left->parent = y;
    y->color = p->color; // 대체된 노드는 
  }


  // case 1, 2 의 경우 x가 NULL이라면 x의 parent는 p->parent가 된다.
  // case 3에서 x가 null이라면 y
  if (y_original_color == RBTREE_BLACK){
    rb_delete_fixup(t, x, tmp);
  }

  free(p);
  
  return 0;
}

// x를 시작으로 계속해서 fixup해 나가는 것.
void rb_delete_fixup(rbtree* t, node_t* x, node_t* p){
  while(1){
    if (x==t->root)
      break;
    if (x!=NULL && x->color == RBTREE_RED){
      break;
    }
    // 왼쪽 자식인 경우
    if (x==p->left){
      node_t* w = p->right; // sibling

      // case change
      if (w->color == RBTREE_RED){
        w->color = RBTREE_BLACK;
        p->color = RBTREE_RED;
        left_rotation(t, p);
        w = p->right;
      }

      // case 1) sibling의 자식이 모두 검정
      if((w->left->color == RBTREE_BLACK || w->left == NULL) && (w->right->color == RBTREE_BLACK || w->right == NULL)){
        w->color = RBTREE_RED;
        x = p;
        // my code
        if (x!= t->root)
          p = x->parent->parent;
        // 부모로 전달했을 때 부모가 이중 흑색이 되면 부모로 다시 검색
        // 전달 한 부모가 이중 흑색이 아니면 탈출

      }
      // case 2) sibling의 자식의 왼쪽은 빨강, 오른쪽은 검정
      else if (w->right->color == RBTREE_BLACK || w->right == NULL){
        w->color = RBTREE_RED;
        if (w->left!=NULL)
          w->left->color = RBTREE_BLACK;
        right_rotation(t, w);
        w = p->right;
      }

      // case 3) sibling의 자식의 오른쪽이 빨강 -- case2)는  case3)가 해결시켜준다.
      else{
        // else를 안해된다 --> case2)에서 case3)로 넘어오기 때문에
        
        w->color = p->color;
        p->color = RBTREE_BLACK;
        w->right->color = RBTREE_BLACK;
        left_rotation(t,p);
        x = t->root; 
        // case 3)는 언제나 균형을 이루게 한다.
        // 탈출
      }
    }

    // 오른쪽 자식인 경우
    else{
      node_t* w = p->left;

      // case change
      if (w->color == RBTREE_RED){
        w->color = RBTREE_BLACK;
        p->color = RBTREE_RED;
        right_rotation(t, p);
        w = p->right;
      }

      // case 1)
      if((w->left->color == RBTREE_BLACK || w->left == NULL) && (w->right->color == RBTREE_BLACK || w->right == NULL)){
        w->color = RBTREE_RED;
        x = p;
        // my code
        if (x!= t->root)
          p = x->parent->parent;
      }

      else if (w->left->color == RBTREE_BLACK || w->left == NULL){
        w->color = RBTREE_RED;
        if (w->right!=NULL)
          w->right->color = RBTREE_BLACK;
        left_rotation(t, w);
        w = p->left;
      }
      else{
        w->color = p->color;
        p->color = RBTREE_BLACK;
        w->left->color = RBTREE_BLACK;
        right_rotation(t,p);
        x = t->root; 
      }
    }
  }
  
  if (x!=NULL){
    x->color = RBTREE_BLACK;
  }
  
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  return 0;
}