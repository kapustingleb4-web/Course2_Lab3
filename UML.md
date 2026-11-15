# UML-диаграммы классов

Диаграммы в формате Mermaid: открываются на GitHub или в https://mermaid.live.

## C++

```mermaid
classDiagram
    class Container {
        <<abstract>>
        +getSize() int*
        +isEmpty() bool
        +clear()*
        +toString() string*
        +typeName() string*
        +saveBinary(filename)*
        +loadBinary(filename)*
        +saveText(filename)*
        +loadText(filename)*
    }
    class MyArray {
        #string* data
        #int size
        #int capacity
        #resize(newCapacity)
        +push_back(val)
        +insert_at(index, val)
        +remove_at(index)
        +update_at(index, val)
        +get(index) string
        +find(val) int
    }
    class MyStack {
        +push(val)
        +pop() string
        +peek() string
    }
    class MyQueue {
        +push(val)
        +pop() string
        +front() string
    }
    class ForwardList {
        -Node* head
        -Node* tail
        -int size
        +push_front(val)
        +push_back(val)
        +insert_before(target, val) bool
        +insert_after(target, val) bool
        +pop_front()
        +pop_back()
        +remove_by_value(val) bool
        +remove_before(target) bool
        +remove_after(target) bool
        +find(val) int
    }
    class DoublyList {
        -Node* head
        -Node* tail
        -int size
        -unlink(Node*)
        +push_front(val)
        +push_back(val)
        +insert_before(target, val) bool
        +insert_after(target, val) bool
        +pop_front()
        +pop_back()
        +toReverseString() string
    }
    class MyHashTable {
        -Node** buckets
        -int capacity
        -int size
        -hash(key) int
        -rehash()
        +put(key, value)
        +get(key) string
        +contains(key) bool
        +remove(key) bool
    }
    class AVLTree {
        -Node* root
        -int size
        -balance(Node*) Node*
        -rightRotate(Node*) Node*
        -leftRotate(Node*) Node*
        +insert(key) bool
        +remove(key) bool
        +find(key) bool
        +traverse(Traversal) vector~int~
        +isBalanced() bool
    }
    class Serializer {
        <<namespace>>
        +saveStringsBinary()
        +loadStringsBinary()
        +saveStringsText()
        +loadStringsText()
    }
    Container <|-- MyArray
    MyArray <|-- MyStack
    MyArray <|-- MyQueue
    Container <|-- ForwardList
    Container <|-- DoublyList
    Container <|-- MyHashTable
    Container <|-- AVLTree
    MyArray ..> Serializer : использует
    ForwardList ..> Serializer
    DoublyList ..> Serializer
    MyHashTable ..> Serializer
    AVLTree ..> Serializer
```

## Go

```mermaid
classDiagram
    class Container {
        <<interface>>
        +Size() int
        +IsEmpty() bool
        +Clear()
        +String() string
        +TypeName() string
        +SaveBinary(filename) error
        +LoadBinary(filename) error
        +SaveText(filename) error
        +LoadText(filename) error
    }
    class MyArray {
        -data []string
        -size int
        -capacity int
        +PushBack(val)
        +InsertAt(index, val) error
        +RemoveAt(index) error
        +Get(index) (string, error)
    }
    class MyStack {
        +Push(val)
        +Pop() (string, error)
        +Peek() (string, error)
    }
    class MyQueue {
        +Push(val)
        +Pop() (string, error)
        +Front() (string, error)
    }
    class ForwardList {
        -head *fNode
        -tail *fNode
        -size int
    }
    class DoublyList {
        -head *dNode
        -tail *dNode
        -size int
        +ReverseString() string
    }
    class MyHashTable {
        -buckets []*hNode
        -size int
        +Put(key, value)
        +Get(key) (string, error)
    }
    class AVLTree {
        -root *avlNode
        -size int
        +Insert(key) bool
        +Remove(key) bool
        +Traverse(order) []int
    }
    Container <|.. MyArray
    Container <|.. MyStack
    Container <|.. MyQueue
    Container <|.. ForwardList
    Container <|.. DoublyList
    Container <|.. MyHashTable
    Container <|.. AVLTree
    MyStack *-- MyArray : встраивание
    MyQueue *-- MyArray : встраивание
```

Обозначения: сплошная линия с треугольником — наследование, пунктир с треугольником — реализация
интерфейса, ромб — встраивание (композиция), пунктирная стрелка — зависимость.
