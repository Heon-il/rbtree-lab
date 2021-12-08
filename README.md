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
- `Black Height` - Red Black Tree에서 균형을 유지하기 위한 Rotation과 Color-Flipping --> **각 case들에서 일반화된 상황에서 각 노드들의 Black Height를 고려하면 아래에서의 case들은 모든 경우를 설명하고 결국 균형을 이루게 된다는 것을 알 수 있음**
- `이중 흑색 노드` : 이중 흑색 노드의 발생 상황과 이중 흑색 노드가 의미하는 바, 이중 흑색 노드가 발생하는 정확한 상황 -- *RB Tree에서 만들어지는 이중 흑색 노드는 항상 여러개의 Black Height를 가지지 않게 된다는 것도 이해*


## Insert Case 
1) 먼저, BST의 insert의 과정을 따름.
2) insert 하는 노드는 red로 가정하고 넣음
3) red로 가정하고 insert된 노드의 parent가 red인 경우 RB Tree의 특성을 유지하기 못하기 때문에 fixup 진행
4) fixup

## Insert Fixup
- ### 용어 
```
z : inserted node
w : uncle
p : parent
```
- *케이스들은 좌우로 대칭이기 때문에 p나 z가 left child인 경우에 대해서만 이야기함*

### case 1) uncle(red)
```
p.color = BLACK
w.color = BLACK
p.p.color = RED
```
균형을 이룸

cf)
p.p가 루트 인경우 마지막에 p.color = RED
(p.p가 루트였다면 p.p에 대한 side tree(?), sibling tree(?) 가 없기 때문에 black height를 해치지 않는다.)

(side tree, sibling tree..? 적절한 용어가 생각나지 않음)


### case 2) uncle(black) - triangle
```
z = z.p
left_rotate(z)
```
*case 3)로 변환이 되고 case 3)에서 다시 진행하여 균형을 맞추게 된다.**

### case 3) uncle(black) - linear
```
z.p.color = BLACK
z.p.p.color = RED
right_rotate(z.p.p)
```
균형을 이룸




## Delete 과정
1) 일반적인 BST delete 과정을 따름
2) 이중 흑색 노드 발생 여부에 따른 fixup 진행 
cf) 삭제할 노드가 Red인 경우 이중흑색노드가 발생하지 않는 것이 아님(오해하기 쉬움)
 - `삭제할 노드` 또는 `이동할 노드`에 대한 관리가 필요
 - 결론적으로는 Delete에서 case 1) case 2)는 삭제할 노드가 Red인 경우 문제 발생 X
 - case 3) 에서는 삭제할 노드 z의 successor 또는 predecessor의 노드가 Red일 경우 문제 발생 X

## Delete 

### 용어 정리
```
z : 삭제할 노드
w : sibling
p : parent
y : 삭제할 노드 또는 이동하는 노드(관리노드) - case 3)에서는 z의 successor가 된다.
x : BST deletion 완료 후 이중흑색이 발생할 '가능성'이 있는 노드
 - x가 FixUp의 인자로 들어오는 것.
```

### Case 1) 삭제할 노드 Z의 left child가 nil인 경우 
```
x = z.right
rb_transplant(z, z.right)
```
### Case 2) 삭제할 노드 Z의 right child가 nil인 경우
(Case 1 에서 else if로 넘어 오기 때문에 더 정확히는 right child는 nil이고 left child는 nil이 아닌 경우) 

```
x = z.left
rb_transplant(z, z.left)
```

### Case 3) 삭제할 노드 z의 양쪽 subtree가 존재하는 경우
```
y_origin_color = y.color
x = y.right
if y.p==z: // z와 붙어 있는 경우
  x.p = y // nil node 인 경우 임시적으로 부모를 설정해줄 수 있다. nil node의 강력함!!
else // 붙어 있는 경우
  rb_transplant(y, y.right)
  y.right = z.right
rb_transplant(z,y)
y.left = z.left
y.left.p = y
y.color = z.color
```

## Delete Fixup
위의 case들에 대해서 노드 x가 이중흑색노드가 발생이 된다면 fixup이 진행되는 것(pseudo코드상 y color가 black인 경우 이중 흑색노드가 생길 가능성이 있는 것이고 거기서 x 또한 black이라면 이중흑색노드가 발생하는 구조)
```
if y_origin_color == BLACK:
  RB_DELETE_FIXUP(x)
```




### Case Change) sibling(RED)
*sibling이 Black인 Case로 변경이 되고* Case1~3)의 과정을 통해 균형을 맞춤*
```
w.color = BLACK
x.p.color = RED
left_rotation(x.p)
w = w.p.right
```

### Case 1) sibling(BLACK), sibling.left(BLACK), sibling.right(BLACK)
```
w.color = RED
x = x.p // 부모가 red였으면 탈출, 부모가 black이면 다시 fixup 진행
```
두 가지의 결과가 나올 수 있다.
1) 부모가 red인 경우 균형이 맞춰진다. (자식으로 부터 흑색을 넘겨받느낟. 아래 '주의' 보기)
2) 부모가 black인 경우 부모가 균형을 깨트리는 이중 흑색노드가 된다. 그래서 다시 이중 흑색노드를 fix하는 과정을 밟게 된다.

주의) 부모가 빨간색인 경우 fixup함수 안의 while문은 진행하지 않고, x.color = BLACK 으로 흑색을 칠해 다시 균형을 맞추는 것(인터넷에 검색하면 부모에게 흑색을 넘긴다고 표현을 하는데 그 부분)
### Case 2) sibling(BLACK), sibling.left(RED), sibling.right(BLACK) 
```
w.left.color = BLACK
w.color = RED
right_rotate(w)
w = x.p.right
```
case 3로 바뀌게 되고 case 3에서 균형을 이룬다.

### Case 3) sibling(BLACK), sibling.right(RED)
```
w.color = x.p.color
x.p.color = BLACK
w.right.color = BLACK
left_rotate(x.p)
x=T.root // 탈출 조건
```
균형을 이루게 된다.



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
