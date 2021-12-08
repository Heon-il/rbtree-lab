# Red-Black Tree

## 사전 필요 지식 
- C언어 동적 할당, 포인터 등
- Binary Search Tree

## 학습 목적
- C언어에 대한 기본 이해(동적할당, 포인터, struct 등)
- Insert, Delete Case에 대한 정확한 이해
- C언어를 이용한 구현

## 구현 방식
- Sentinel(경계조건)을 이용한 Red-Black Tree 구현
- CLRS book에서 제공하는 pseudo code

## Key Point
- 일반화된 상황을 통해 각 Case들이 결국 RB Tree의 균형을 맞추게 만든다는 것을 이해
- `Black Height` - Red Black Tree에서 균형을 유지하기 위한 Rotation과 Color-Flipping --> **각 case들에서 일반화된 상황에서 각 노드들의 Black Height를 고려하면서 case를 따지면 이해하기 쉬움**
- `이중 흑색 노드` : 이중 흑색 노드의 발생 상황과 이중 흑색 노드가 의미하는 바, 이중 흑색 노드가 발생하는 정확한 상황 -- *RB Tree에서 만들어지는 이중 흑색 노드는 항상 여러개의 Black Height를 가지지 않게 된다는 것도 이해*


## Insert Case 
1) 먼저, BST의 insert의 과정을 따름.
2) insert 하는 노드는 red로 가정하고 넣음
3) red로 가정하고 insert된 노드의 parent가 red인 경우 RB Tree의 특성을 유지하기 못하기 때문에 fixup 진행
4) fixup

### insert-fixup case
용어 
```
z : inserted node
w : uncle
p : parent
```
*케이스들은 좌우로 대칭이기 때문에 p나 z가 left child인 경우에 대해서만 이야기함*

#### case 1) uncle(red)
```
p.color = BLACK
w.color = BLACK
p.p.color = RED
```
p.p가 루트 인경우 마지막에 p.color = RED
(p.p가 루트였다면 p.p에 대한 side tree(?), sibling tree(?) 가 없기 때문에 black height를 해치지 않는다.)

(side tree, sibling tree..? 적절한 용어가 생각나지 않음)

#### case 2) uncle(black) - triangle
**case 3)로 변환이 되고 case 3)에서 다시 진행하여 균형을 맞추게 된다.**
```
z = z.p
left_rotate(z)
```

#### case 3) uncle(black) - linear
```
z.p.color = BLACK
z.p.p.color = RED
right_rotate(z.p.p)
```




# Red-Black Tree 구현

Balanced search tree로 많이 쓰이는 Red-black tree (이하 RB tree)를 C 언어로 구현해 보는 과제입니다.
구현하는 추상 자료형(abstract data type)은 ordered set, multiset 입니다.

## 구현 범위
다음 기능들을 수행할 수 있도록 RB tree를 구현합니다.

- tree = `new_tree()`: RB tree 구조체 생성 - 구현되어 있음
- `delete_tree(tree)`: RB tree 구조체가 차지했던 메모리 반환

- `tree_insert(tree, key)`: key 추가
- ptr = `tree_find(tree, key)`
    - RB tree내에 해당 key가 있는지 탐색하여 있으면 해당 node pointer 반환
    - 없으면 NIL 반환
- `tree_erase(tree, ptr)`: ptr로 지정된 node 삭제 및 메모리 반환
- ptr = `tree_min(tree)`: RB tree 중 최소 값을 가진 node pointer 반환
- ptr = `tree_max(tree)`: 최대값을 가진 node pointer 반환

- `tree_to_array(tree, array, n)`
  - RB tree의 내용을 *key 순서대로* 주어진 array로 변환
  - array의 크기는 n으로 주어지며 tree의 크기가 n 보다 큰 경우에는 순서대로 n개 까지만 변환

## 구현 규칙
- `src/rbtree.c` 이외에는 수정하지 않고 test를 통과해야 합니다.

## 과제의 의도 (Motivation)

- 복잡한 자료구조(data structure)를 구현해 봄으로써 자신감 상승
- C 언어, 특히 포인터(pointer)와 malloc, free 등의 system call에 익숙해짐.
- 동적 메모리 할당(dynamic memory allocation)을 직접 사용해 봄으로써 동적 메모리 할당의 필요성 체감 및 data segment에 대한 이해도 상승
- 고급 언어에서 기본으로 제공되는 자료구조가 세부적으로는 어떻게 구현되어 있는지 경험함으로써 고급 언어 사용시에도 효율성 고려

## 참고문헌
- [위키백과: 레드-블랙 트리](https://ko.wikipedia.org/wiki/%EB%A0%88%EB%93%9C-%EB%B8%94%EB%9E%99_%ED%8A%B8%EB%A6%AC)
([영어](https://en.wikipedia.org/wiki/Red%E2%80%93black_tree))
- CLRS book (Introduction to Algorithms) 13장 레드 블랙 트리
- [Wikipedia:균형 이진 트리의 구현 방법들](https://en.wikipedia.org/wiki/Self-balancing_binary_search_tree#Implementations)
