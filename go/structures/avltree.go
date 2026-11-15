package structures

import (
	"fmt"
	"strings"
)

// Traversal - вид обхода дерева.
type Traversal int

const (
	InOrder Traversal = iota
	PreOrder
	PostOrder
	BFS
)

type avlNode struct {
	key         int
	left, right *avlNode
	height      int
}

// AVLTree - сбалансированное двоичное дерево поиска (вариант 2 ЛР1).
type AVLTree struct {
	root *avlNode
	size int
}

func h(n *avlNode) int {
	if n == nil {
		return 0
	}
	return n.height
}

func upd(n *avlNode)    { n.height = 1 + max(h(n.left), h(n.right)) }
func bf(n *avlNode) int { return h(n.left) - h(n.right) }

func rotR(y *avlNode) *avlNode {
	x := y.left
	y.left, x.right = x.right, y
	upd(y)
	upd(x)
	return x
}

func rotL(x *avlNode) *avlNode {
	y := x.right
	x.right, y.left = y.left, x
	upd(x)
	upd(y)
	return y
}

func rebalance(n *avlNode) *avlNode {
	upd(n)
	switch b := bf(n); {
	case b > 1:
		if bf(n.left) < 0 { // LR
			n.left = rotL(n.left)
		}
		return rotR(n) // LL
	case b < -1:
		if bf(n.right) > 0 { // RL
			n.right = rotR(n.right)
		}
		return rotL(n) // RR
	}
	return n
}

func insertNode(n *avlNode, key int, ok *bool) *avlNode {
	if n == nil {
		*ok = true
		return &avlNode{key: key, height: 1}
	}
	switch {
	case key < n.key:
		n.left = insertNode(n.left, key, ok)
	case key > n.key:
		n.right = insertNode(n.right, key, ok)
	default:
		return n
	}
	return rebalance(n)
}

// insertPlain - без балансировки, для загрузки прямого обхода (форма сохраняется)
func insertPlain(n *avlNode, key int) *avlNode {
	if n == nil {
		return &avlNode{key: key, height: 1}
	}
	if key < n.key {
		n.left = insertPlain(n.left, key)
	} else if key > n.key {
		n.right = insertPlain(n.right, key)
	}
	upd(n)
	return n
}

func removeMin(n *avlNode) (rest, min *avlNode) {
	if n.left == nil {
		return n.right, n
	}
	n.left, min = removeMin(n.left)
	return rebalance(n), min
}

func removeNode(n *avlNode, key int, ok *bool) *avlNode {
	if n == nil {
		return nil
	}
	switch {
	case key < n.key:
		n.left = removeNode(n.left, key, ok)
	case key > n.key:
		n.right = removeNode(n.right, key, ok)
	default:
		*ok = true
		if n.right == nil {
			return n.left
		}
		rest, m := removeMin(n.right) // два ребёнка: минимум правого поддерева
		m.left, m.right = n.left, rest
		return rebalance(m)
	}
	return rebalance(n)
}

func (t *AVLTree) Insert(key int) bool {
	ok := false
	t.root = insertNode(t.root, key, &ok)
	if ok {
		t.size++
	}
	return ok
}

func (t *AVLTree) Remove(key int) bool {
	ok := false
	t.root = removeNode(t.root, key, &ok)
	if ok {
		t.size--
	}
	return ok
}

func (t *AVLTree) Find(key int) bool {
	for cur := t.root; cur != nil; {
		if key == cur.key {
			return true
		}
		if key < cur.key {
			cur = cur.left
		} else {
			cur = cur.right
		}
	}
	return false
}

func (t *AVLTree) Height() int { return h(t.root) }

func checkBalanced(n *avlNode) int {
	if n == nil {
		return 0
	}
	l, r := checkBalanced(n.left), checkBalanced(n.right)
	if l < 0 || r < 0 || l-r > 1 || r-l > 1 {
		return -1
	}
	return 1 + max(l, r)
}

func (t *AVLTree) IsBalanced() bool { return checkBalanced(t.root) >= 0 }

func collect(n *avlNode, order Traversal, out *[]int) {
	if n == nil {
		return
	}
	if order == PreOrder {
		*out = append(*out, n.key)
	}
	collect(n.left, order, out)
	if order == InOrder {
		*out = append(*out, n.key)
	}
	collect(n.right, order, out)
	if order == PostOrder {
		*out = append(*out, n.key)
	}
}

func (t *AVLTree) Traverse(order Traversal) []int {
	out := []int{}
	if order != BFS {
		collect(t.root, order, &out)
		return out
	}
	var level []*avlNode
	if t.root != nil {
		level = append(level, t.root)
	}
	for len(level) > 0 {
		var next []*avlNode
		for _, n := range level {
			out = append(out, n.key)
			if n.left != nil {
				next = append(next, n.left)
			}
			if n.right != nil {
				next = append(next, n.right)
			}
		}
		level = next
	}
	return out
}

func (t *AVLTree) Size() int        { return t.size }
func (t *AVLTree) IsEmpty() bool    { return t.size == 0 }
func (t *AVLTree) Clear()           { t.root, t.size = nil, 0 }
func (t *AVLTree) TypeName() string { return "AVLTree" }

func (t *AVLTree) String() string {
	var s []string
	for _, v := range t.Traverse(InOrder) {
		s = append(s, fmt.Sprint(v))
	}
	return "[" + strings.Join(s, ", ") + "]"
}

func (t *AVLTree) setPreorder(keys []int) {
	t.Clear()
	for _, k := range keys {
		if !t.Find(k) {
			t.size++
		}
		t.root = insertPlain(t.root, k)
	}
}

func (t *AVLTree) SaveBinary(f string) error {
	return saveBinary(f, t.TypeName(), t.Traverse(PreOrder))
}
func (t *AVLTree) SaveText(f string) error { return saveText(f, t.TypeName(), t.Traverse(PreOrder)) }

func (t *AVLTree) LoadBinary(f string) error {
	keys, err := loadBinary[int](f, t.TypeName())
	if err == nil {
		t.setPreorder(keys)
	}
	return err
}

func (t *AVLTree) LoadText(f string) error {
	keys, err := loadText[int](f, t.TypeName())
	if err == nil {
		t.setPreorder(keys)
	}
	return err
}
