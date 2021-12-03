#include "rbtree.h"
#include <stdlib.h>


/* 
  rotation이 필요할 것 같기는 한데 rbtree.c 이외에는 수정하지 않고
  test를 통과해야하기 때문에 rotation 함수를 만들고 나서 사용을 하되 
  그 부분에 다 넣어줘야 할 것 같다.

*/


void left_rotation(rbtree* t){
  return;
}
void right_rotation(rbtree* t){
  return;
}




// RB Tree 구조체 생성 - 구현이 되어 있음
// -- 하나의 노드를 의미하는 것 같다.
rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  p->root = NULL;
  // nil을 어떻게 처리해야하는가
  return p;
}

// 구조체가 차지 했던 메모리 반환
// -- free를 하면 구조체 메모리 반환된다.
void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory
  free(t);
}

// key 추가
node_t *rbtree_insert(rbtree *t, const key_t key) {

  

  // 첫 삽입시
  if (t->root == NULL){
    // 노드 생성
    node_t* node = (node_t*)calloc(1, sizeof(node_t));
    node -> color = color_t.RBTREE_BLACK;
    node -> key = key;
    node -> parent = node;
    node -> left = t -> nil;
    node -> right = t -> nil;
    return t->root;
  }

  // root 로 부터 시작해야 한다.
  // 바로 삽입을 할 수 가 없고 key값들을 비교하면서 
  // 삽입할 곳을 가리킬 포인터들이 필요하다.
  node_t *cur, *next;
  cur = t->root;



  





  return t->root;
}


// -- NIL을 하나의 마지막 노드로 처리 할 수 있어서 탐색이 끝나고 나면 자연스럽게 NIL이 반환될 것 같다.
node_t *rbtree_find(const rbtree *t, const key_t key) {
  // TODO: implement find
  return t->root;
}


// 최소값을 가진 node pointer 반환
node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
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
