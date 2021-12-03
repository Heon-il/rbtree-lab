#include "rbtree.h"
#include <stdlib.h>
#include <stdio.h> // 나중에 삭제



void left_rotation(rbtree *t, node_t *x){
  node_t *y = x->right;
  x->right = y->left;

  if (y->left !=t->nil)
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

  if (y->parent = t->nil) t->root = x;
  else if (y->parent->left ==y) y->parent->left = x; 
  else y->parent->right = x;
  
  x->right = y;
  y->parent = x;
}


void insert_fixup(rbtree *t, node_t *p){
  
}



// root -> left -> right
void postorder(rbtree *t, node_t *p){
  if (p==t->nil)
    return;
  printf("%d  ", p->key);
  postorder(t, p->left);
  postorder(t, p->right);
  
}

// left -> root -> right
void inorder(rbtree *t, node_t *p){
  if (p==t->nil)
    return;
  inorder(t, p->left);
  printf("%d  ", p->key);
  inorder(t, p->right);
}

// left -> right -> root
void preorder(rbtree *t, node_t *p){
  if (p==t->nil)
    return;
  preorder(t, p->left);
  preorder(t, p->right);
  printf("%d  ", p->key);
}

/* 위에는 내가 필요에 의해 구현 한 것 들*/

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  node_t* dummy_node = (node_t*)calloc(1, sizeof(node_t)); 
  p->root = dummy_node;
  p->nil = dummy_node;
  return p;
}

void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory
  free(t);
}

// key 추가
node_t *rbtree_insert(rbtree *t, const key_t key) {

  node_t *next, *cur;

  if (rbtree_find(t, key) == t->nil){

    // 노드 생성
    node_t* node = (node_t*)calloc(1, sizeof(node_t));
    node -> left = t -> nil; 
    node -> right = t -> nil;
    node->key = key;

    // BST insert
    cur = t->nil; // 삽입될 노드의 부모 노드
    next = t->root;
    while (next != t->nil){
      cur = next;
      next = (key < next->key ) ? next->left : next->right;
    }

    node->parent = cur;
    if (cur==t->nil){ // 빈 트리
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


    // insert_fixup
    
  }

  else{
    // multiset
  }

  return t->root;
}


node_t *rbtree_find(const rbtree *t, const key_t key) {

  // 트리가 없는 경우
  // 어떻게 처리를 해야할지?

  node_t *cur = t->root;
  while (cur->key != key && cur != t->nil){
    cur = (cur->key<key) ? cur = cur->left: cur->right;
  }

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
  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  return 0;
}



int main(){

  rbtree *t = new_rbtree();
  rbtree_insert(t, 11);
  rbtree_insert(t, 12);
  rbtree_insert(t, 9);
  rbtree_insert(t, 8);
  rbtree_insert(t, 10);



  return 0;
}