package structures

import (
	"os"
	"path/filepath"
	"testing"

	"github.com/stretchr/testify/assert"
	"github.com/stretchr/testify/require"
)

func TestMyArray(t *testing.T) {
	a := &MyArray{}
	assert.True(t, a.IsEmpty())
	for _, s := range []string{"a", "c"} {
		a.PushBack(s)
	}
	require.NoError(t, a.InsertAt(1, "b"))
	require.NoError(t, a.InsertAt(0, "start"))
	assert.Equal(t, "[start, a, b, c]", a.String())
	v, err := a.Get(2)
	require.NoError(t, err)
	assert.Equal(t, "b", v)
	require.NoError(t, a.UpdateAt(0, "zero"))
	require.NoError(t, a.RemoveAt(0))
	assert.Equal(t, 1, a.Find("b"))
	assert.Equal(t, -1, a.Find("zzz"))
	assert.ErrorIs(t, a.InsertAt(10, "x"), ErrOutOfRange)
	assert.ErrorIs(t, a.RemoveAt(-1), ErrOutOfRange)
	assert.ErrorIs(t, a.UpdateAt(10, "x"), ErrOutOfRange)
	_, err = a.Get(10)
	assert.ErrorIs(t, err, ErrOutOfRange)
	assert.Equal(t, 3, a.Size())
	assert.Equal(t, "MyArray", a.TypeName())
	a.Clear()
	assert.True(t, a.IsEmpty())
}

func TestStackQueue(t *testing.T) {
	s := &MyStack{}
	_, err := s.Pop()
	assert.ErrorIs(t, err, ErrEmpty)
	_, err = s.Peek()
	assert.ErrorIs(t, err, ErrEmpty)
	s.Push("1")
	s.Push("2")
	s.Push("3")
	top, _ := s.Peek()
	assert.Equal(t, "3", top)
	assert.Equal(t, "top> [3, 2, 1]", s.String())
	v, _ := s.Pop()
	assert.Equal(t, "3", v)
	assert.Equal(t, "MyStack", s.TypeName())

	q := &MyQueue{}
	_, err = q.Pop()
	assert.ErrorIs(t, err, ErrEmpty)
	_, err = q.Front()
	assert.ErrorIs(t, err, ErrEmpty)
	q.Push("a")
	q.Push("b")
	f, _ := q.Front()
	assert.Equal(t, "a", f)
	assert.Equal(t, "front> [a, b] <back", q.String())
	v, _ = q.Pop()
	assert.Equal(t, "a", v)
	assert.Equal(t, "MyQueue", q.TypeName())
}

func TestForwardList(t *testing.T) {
	l := &ForwardList{}
	assert.False(t, l.InsertBefore("x", "y"))
	assert.False(t, l.RemoveByValue("x"))
	assert.False(t, l.RemoveBefore("x"))
	l.PushBack("b")
	l.PushFront("a")
	assert.True(t, l.InsertAfter("b", "d"))
	assert.True(t, l.InsertBefore("d", "c"))
	assert.True(t, l.InsertBefore("a", "start"))
	assert.False(t, l.InsertBefore("zzz", "x"))
	assert.False(t, l.InsertAfter("zzz", "x"))
	assert.Equal(t, "[start -> a -> b -> c -> d]", l.String())
	assert.Equal(t, 3, l.Find("c"))
	assert.Equal(t, -1, l.Find("zzz"))
	require.NoError(t, l.PopFront())
	require.NoError(t, l.PopBack())
	assert.True(t, l.RemoveBefore("c")) // b
	assert.True(t, l.RemoveAfter("a"))  // c (хвост)
	assert.False(t, l.RemoveAfter("a"))
	assert.False(t, l.RemoveBefore("a"))
	l.PushBack("x")
	l.PushBack("y")
	l.PushBack("z")
	assert.True(t, l.RemoveBefore("z")) // y, не голова
	assert.False(t, l.RemoveBefore("nope"))
	assert.True(t, l.RemoveByValue("z")) // хвост
	assert.True(t, l.RemoveByValue("a")) // голова
	assert.False(t, l.RemoveByValue("q"))
	assert.Equal(t, "[x]", l.String())
	require.NoError(t, l.PopBack())
	assert.ErrorIs(t, l.PopBack(), ErrEmpty)
	assert.ErrorIs(t, l.PopFront(), ErrEmpty)
	assert.True(t, l.IsEmpty())
	assert.Equal(t, "ForwardList", l.TypeName())
}

func TestDoublyList(t *testing.T) {
	l := &DoublyList{}
	l.PushBack("2")
	l.PushFront("1")
	l.PushBack("4")
	assert.True(t, l.InsertBefore("4", "3"))
	assert.True(t, l.InsertAfter("4", "5"))
	assert.True(t, l.InsertBefore("1", "0"))
	assert.True(t, l.InsertAfter("2", "2.5"))
	assert.False(t, l.InsertBefore("x", "y"))
	assert.False(t, l.InsertAfter("x", "y"))
	assert.Equal(t, "[0 <-> 1 <-> 2 <-> 2.5 <-> 3 <-> 4 <-> 5]", l.String())
	assert.Equal(t, "[5 <-> 4 <-> 3 <-> 2.5 <-> 2 <-> 1 <-> 0]", l.ReverseString())
	assert.Equal(t, 4, l.Find("3"))
	assert.Equal(t, -1, l.Find("x"))
	assert.True(t, l.RemoveByValue("2.5"))
	assert.False(t, l.RemoveByValue("2.5"))
	assert.True(t, l.RemoveBefore("2"))
	assert.True(t, l.RemoveAfter("4"))
	assert.False(t, l.RemoveBefore("0"))
	assert.False(t, l.RemoveAfter("4"))
	require.NoError(t, l.PopFront())
	require.NoError(t, l.PopBack())
	assert.Equal(t, "[2 <-> 3]", l.String())
	l.Clear()
	assert.ErrorIs(t, l.PopFront(), ErrEmpty)
	assert.ErrorIs(t, l.PopBack(), ErrEmpty)
	assert.True(t, l.IsEmpty())
	assert.Equal(t, "DoublyList", l.TypeName())
}

func TestHashTable(t *testing.T) {
	h := NewHashTable()
	for i := 0; i < 50; i++ {
		h.Put("k"+string(rune('A'+i)), "v")
	}
	assert.Equal(t, 50, h.Size())
	assert.Greater(t, h.Capacity(), 50)
	h.Put("kA", "new")
	v, err := h.Get("kA")
	require.NoError(t, err)
	assert.Equal(t, "new", v)
	_, err = h.Get("nope")
	assert.ErrorIs(t, err, ErrNotFound)
	assert.True(t, h.Contains("kB"))
	assert.True(t, h.Remove("kB"))
	assert.False(t, h.Remove("kB"))
	h.Clear()
	assert.True(t, h.IsEmpty())
	h.Put("a", "1")
	assert.Equal(t, "{a: 1}", h.String())
	assert.Equal(t, "MyHashTable", h.TypeName())
}

func TestAVLTree(t *testing.T) {
	tr := &AVLTree{}
	for _, v := range []int{7, 3, 2, 1, 9, 5, 4, 6, 8} {
		assert.True(t, tr.Insert(v))
	}
	assert.False(t, tr.Insert(5))
	assert.True(t, tr.IsBalanced())
	assert.Equal(t, []int{1, 2, 3, 4, 5, 6, 7, 8, 9}, tr.Traverse(InOrder))
	assert.Equal(t, []int{3, 2, 7, 1, 5, 9, 4, 6, 8}, tr.Traverse(BFS))
	assert.Equal(t, []int{3, 2, 1, 7, 5, 4, 6, 9, 8}, tr.Traverse(PreOrder))
	assert.Equal(t, []int{1, 2, 4, 6, 5, 8, 9, 7, 3}, tr.Traverse(PostOrder))
	assert.True(t, tr.Find(6))
	assert.False(t, tr.Find(100))
	assert.True(t, tr.Remove(3))
	assert.True(t, tr.Remove(1))
	assert.True(t, tr.Remove(2))
	assert.False(t, tr.Remove(42))
	assert.True(t, tr.IsBalanced())
	assert.Equal(t, "[4, 5, 6, 7, 8, 9]", tr.String())
	r := &AVLTree{}
	for v := 10; v > 0; v-- {
		r.Insert(v)
	}
	assert.True(t, r.IsBalanced())
	assert.LessOrEqual(t, r.Height(), 4)
	lr := &AVLTree{}
	for _, v := range []int{30, 10, 20} {
		lr.Insert(v)
	}
	assert.Equal(t, []int{20, 10, 30}, lr.Traverse(PreOrder))
	rl := &AVLTree{}
	for _, v := range []int{10, 30, 20} {
		rl.Insert(v)
	}
	assert.Equal(t, []int{20, 10, 30}, rl.Traverse(PreOrder))
	tr.Clear()
	assert.True(t, tr.IsEmpty())
	assert.Equal(t, "AVLTree", tr.TypeName())
}

func TestPolymorphism(t *testing.T) {
	all := []Container{&MyArray{}, &MyStack{}, &MyQueue{}, &ForwardList{}, &DoublyList{}, NewHashTable(), &AVLTree{}}
	for _, c := range all {
		assert.True(t, c.IsEmpty(), c.TypeName())
	}
}

func TestSerialization(t *testing.T) {
	dir := t.TempDir()
	p := func(name string) string { return filepath.Join(dir, name) }

	a := &MyArray{}
	a.PushBack("hello world")
	a.PushBack("")
	s := &MyStack{}
	s.Push("bottom")
	s.Push("top")
	q := &MyQueue{}
	q.Push("1")
	fl := &ForwardList{}
	fl.PushBack("x")
	dl := &DoublyList{}
	dl.PushBack("y")
	h := NewHashTable()
	h.Put("k", "v")
	tr := &AVLTree{}
	for _, v := range []int{7, 3, 2, 1, 9, 5, 4, 6, 8} {
		tr.Insert(v)
	}

	type pair struct{ src, dst Container }
	cases := []pair{
		{a, &MyArray{}}, {s, &MyStack{}}, {q, &MyQueue{}}, {fl, &ForwardList{}},
		{dl, &DoublyList{}}, {h, NewHashTable()}, {tr, &AVLTree{}},
	}
	for _, c := range cases {
		bin, txt := p(c.src.TypeName()+".gob"), p(c.src.TypeName()+".json")
		require.NoError(t, c.src.SaveBinary(bin))
		require.NoError(t, c.src.SaveText(txt))
		require.NoError(t, c.dst.LoadBinary(bin))
		assert.Equal(t, c.src.String(), c.dst.String())
		c.dst.Clear()
		require.NoError(t, c.dst.LoadText(txt))
		assert.Equal(t, c.src.String(), c.dst.String())
	}
	tr2 := &AVLTree{}
	require.NoError(t, tr2.LoadBinary(p("AVLTree.gob")))
	assert.Equal(t, tr.Traverse(BFS), tr2.Traverse(BFS)) // форма дерева сохранилась
	assert.Equal(t, 9, tr2.Size())

	// ошибки: чужой тип, нет файла, испорченный файл, нельзя создать файл
	for _, c := range cases {
		other := p("MyArray.gob")
		otherTxt := p("MyArray.json")
		if c.src.TypeName() == "MyArray" {
			other, otherTxt = p("MyStack.gob"), p("MyStack.json")
		}
		assert.Error(t, c.dst.LoadBinary(other))
		assert.Error(t, c.dst.LoadText(otherTxt))
		assert.Error(t, c.dst.LoadBinary(p("none.gob")))
		assert.Error(t, c.dst.LoadText(p("none.json")))
		assert.Error(t, c.src.SaveBinary(filepath.Join(dir, "no", "dir.gob")))
	}
	require.NoError(t, os.WriteFile(p("bad"), []byte("{not json"), 0644))
	assert.Error(t, a.LoadBinary(p("bad")))
	assert.Error(t, a.LoadText(p("bad")))
}
