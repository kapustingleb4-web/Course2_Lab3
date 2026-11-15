package structures

import "strings"

// ---------------- Односвязный список ----------------

type fNode struct {
	data string
	next *fNode
}

// ForwardList - односвязный список (head + tail).
type ForwardList struct {
	head, tail *fNode
	size       int
}

func (l *ForwardList) findNode(val string) *fNode {
	for cur := l.head; cur != nil; cur = cur.next {
		if cur.data == val {
			return cur
		}
	}
	return nil
}

func (l *ForwardList) PushFront(val string) {
	l.head = &fNode{val, l.head}
	if l.tail == nil {
		l.tail = l.head
	}
	l.size++
}

func (l *ForwardList) PushBack(val string) {
	n := &fNode{data: val}
	if l.tail != nil {
		l.tail.next = n
	} else {
		l.head = n
	}
	l.tail = n
	l.size++
}

func (l *ForwardList) InsertBefore(target, val string) bool {
	if l.head == nil {
		return false
	}
	if l.head.data == target {
		l.PushFront(val)
		return true
	}
	prev := l.head
	for prev.next != nil && prev.next.data != target {
		prev = prev.next
	}
	if prev.next == nil {
		return false
	}
	prev.next = &fNode{val, prev.next}
	l.size++
	return true
}

func (l *ForwardList) InsertAfter(target, val string) bool {
	cur := l.findNode(target)
	if cur == nil {
		return false
	}
	cur.next = &fNode{val, cur.next}
	if cur == l.tail {
		l.tail = cur.next
	}
	l.size++
	return true
}

func (l *ForwardList) PopFront() error {
	if l.head == nil {
		return ErrEmpty
	}
	l.head = l.head.next
	if l.head == nil {
		l.tail = nil
	}
	l.size--
	return nil
}

func (l *ForwardList) PopBack() error {
	if l.head == nil {
		return ErrEmpty
	}
	if l.head == l.tail {
		return l.PopFront()
	}
	prev := l.head
	for prev.next != l.tail { // предпоследний - O(n)
		prev = prev.next
	}
	prev.next = nil
	l.tail = prev
	l.size--
	return nil
}

func (l *ForwardList) RemoveByValue(val string) bool {
	if l.head == nil {
		return false
	}
	if l.head.data == val {
		_ = l.PopFront()
		return true
	}
	prev := l.head
	for prev.next != nil && prev.next.data != val {
		prev = prev.next
	}
	if prev.next == nil {
		return false
	}
	if prev.next == l.tail {
		l.tail = prev
	}
	prev.next = prev.next.next
	l.size--
	return true
}

func (l *ForwardList) RemoveBefore(target string) bool {
	if l.head == nil || l.head.data == target {
		return false
	}
	if l.head.next != nil && l.head.next.data == target {
		_ = l.PopFront()
		return true
	}
	pp := l.head
	for pp.next != nil && pp.next.next != nil && pp.next.next.data != target {
		pp = pp.next
	}
	if pp.next == nil || pp.next.next == nil {
		return false
	}
	pp.next = pp.next.next
	l.size--
	return true
}

func (l *ForwardList) RemoveAfter(target string) bool {
	cur := l.findNode(target)
	if cur == nil || cur.next == nil {
		return false
	}
	if cur.next == l.tail {
		l.tail = cur
	}
	cur.next = cur.next.next
	l.size--
	return true
}

func (l *ForwardList) Find(val string) int {
	i := 0
	for cur := l.head; cur != nil; cur, i = cur.next, i+1 {
		if cur.data == val {
			return i
		}
	}
	return -1
}

func (l *ForwardList) GetData() []string {
	var res []string
	for cur := l.head; cur != nil; cur = cur.next {
		res = append(res, cur.data)
	}
	return res
}

func (l *ForwardList) Size() int        { return l.size }
func (l *ForwardList) IsEmpty() bool    { return l.size == 0 }
func (l *ForwardList) Clear()           { l.head, l.tail, l.size = nil, nil, 0 }
func (l *ForwardList) TypeName() string { return "ForwardList" }
func (l *ForwardList) String() string   { return "[" + strings.Join(l.GetData(), " -> ") + "]" }

func (l *ForwardList) setData(items []string) {
	l.Clear()
	for _, s := range items {
		l.PushBack(s)
	}
}

func (l *ForwardList) SaveBinary(f string) error { return saveBinary(f, l.TypeName(), l.GetData()) }
func (l *ForwardList) SaveText(f string) error   { return saveText(f, l.TypeName(), l.GetData()) }

func (l *ForwardList) LoadBinary(f string) error {
	items, err := loadBinary[string](f, l.TypeName())
	if err == nil {
		l.setData(items)
	}
	return err
}

func (l *ForwardList) LoadText(f string) error {
	items, err := loadText[string](f, l.TypeName())
	if err == nil {
		l.setData(items)
	}
	return err
}

// ---------------- Двусвязный список ----------------

type dNode struct {
	data       string
	prev, next *dNode
}

// DoublyList - двусвязный список.
type DoublyList struct {
	head, tail *dNode
	size       int
}

func (l *DoublyList) findNode(val string) *dNode {
	for cur := l.head; cur != nil; cur = cur.next {
		if cur.data == val {
			return cur
		}
	}
	return nil
}

func (l *DoublyList) unlink(n *dNode) { // O(1)
	if n.prev != nil {
		n.prev.next = n.next
	} else {
		l.head = n.next
	}
	if n.next != nil {
		n.next.prev = n.prev
	} else {
		l.tail = n.prev
	}
	l.size--
}

func (l *DoublyList) PushFront(val string) {
	n := &dNode{data: val, next: l.head}
	if l.head != nil {
		l.head.prev = n
	} else {
		l.tail = n
	}
	l.head = n
	l.size++
}

func (l *DoublyList) PushBack(val string) {
	n := &dNode{data: val, prev: l.tail}
	if l.tail != nil {
		l.tail.next = n
	} else {
		l.head = n
	}
	l.tail = n
	l.size++
}

func (l *DoublyList) InsertBefore(target, val string) bool {
	t := l.findNode(target)
	if t == nil {
		return false
	}
	if t == l.head {
		l.PushFront(val)
		return true
	}
	n := &dNode{data: val, prev: t.prev, next: t}
	t.prev.next = n
	t.prev = n
	l.size++
	return true
}

func (l *DoublyList) InsertAfter(target, val string) bool {
	t := l.findNode(target)
	if t == nil {
		return false
	}
	if t == l.tail {
		l.PushBack(val)
		return true
	}
	n := &dNode{data: val, prev: t, next: t.next}
	t.next.prev = n
	t.next = n
	l.size++
	return true
}

func (l *DoublyList) PopFront() error {
	if l.head == nil {
		return ErrEmpty
	}
	l.unlink(l.head)
	return nil
}

func (l *DoublyList) PopBack() error {
	if l.tail == nil {
		return ErrEmpty
	}
	l.unlink(l.tail)
	return nil
}

func (l *DoublyList) RemoveByValue(val string) bool {
	if t := l.findNode(val); t != nil {
		l.unlink(t)
		return true
	}
	return false
}

func (l *DoublyList) RemoveBefore(target string) bool {
	if t := l.findNode(target); t != nil && t.prev != nil {
		l.unlink(t.prev)
		return true
	}
	return false
}

func (l *DoublyList) RemoveAfter(target string) bool {
	if t := l.findNode(target); t != nil && t.next != nil {
		l.unlink(t.next)
		return true
	}
	return false
}

func (l *DoublyList) Find(val string) int {
	i := 0
	for cur := l.head; cur != nil; cur, i = cur.next, i+1 {
		if cur.data == val {
			return i
		}
	}
	return -1
}

func (l *DoublyList) GetData() []string {
	var res []string
	for cur := l.head; cur != nil; cur = cur.next {
		res = append(res, cur.data)
	}
	return res
}

// ReverseString - чтение назад по ссылкам prev
func (l *DoublyList) ReverseString() string {
	var res []string
	for cur := l.tail; cur != nil; cur = cur.prev {
		res = append(res, cur.data)
	}
	return "[" + strings.Join(res, " <-> ") + "]"
}

func (l *DoublyList) Size() int        { return l.size }
func (l *DoublyList) IsEmpty() bool    { return l.size == 0 }
func (l *DoublyList) Clear()           { l.head, l.tail, l.size = nil, nil, 0 }
func (l *DoublyList) TypeName() string { return "DoublyList" }
func (l *DoublyList) String() string   { return "[" + strings.Join(l.GetData(), " <-> ") + "]" }

func (l *DoublyList) setData(items []string) {
	l.Clear()
	for _, s := range items {
		l.PushBack(s)
	}
}

func (l *DoublyList) SaveBinary(f string) error { return saveBinary(f, l.TypeName(), l.GetData()) }
func (l *DoublyList) SaveText(f string) error   { return saveText(f, l.TypeName(), l.GetData()) }

func (l *DoublyList) LoadBinary(f string) error {
	items, err := loadBinary[string](f, l.TypeName())
	if err == nil {
		l.setData(items)
	}
	return err
}

func (l *DoublyList) LoadText(f string) error {
	items, err := loadText[string](f, l.TypeName())
	if err == nil {
		l.setData(items)
	}
	return err
}
