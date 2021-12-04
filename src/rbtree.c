#include "rbtree.h"
#include <stdlib.h>
#include <stdio.h> // 나중에 삭제

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
  if (p==t->nil)
    return;
  printf("key : %d color : %d, ", p->key, p->color);
  postorder(t, p->left);
  postorder(t, p->right);
  
}

// left -> root -> right
void inorder(rbtree *t, node_t *p){
  if (p==t->nil)
    return;
  inorder(t, p->left);
  printf("key : %d color : %d, ", p->key, p->color);
  inorder(t, p->right);
}

// left -> right -> root
void preorder(rbtree *t, node_t *p){
  if (p==t->nil)
    return;
  preorder(t, p->left);
  preorder(t, p->right);
  printf("key : %d color : %d, ", p->key, p->color);
}

/* 위에는 내가 필요에 의해 구현 한 것 들*/

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  p->root = NULL;
  p->nil = NULL;
  return p;
}

void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory
  free(t);
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


// 최소값을 가진 node pointer 반환
node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
  // 맨 왼쪽 거를 반환하면 된다.
  return t->root;
}

// 최대값을 가진 node pointer 반환
node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
  return t->root;
}


// p로 지정된 node 삭제 및 메모리 반환
int rbtree_erase(rbtree *t, node_t *p) {
  // TODO: implement erase
  // rbtree_erase(t, rbtree_find(t,key)); 이런식으로 쓸 수 있을 듯
  // 
  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  return 0;
}
