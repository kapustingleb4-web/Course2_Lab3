package structures

import (
	"fmt"
	"strconv"
	"testing"
)

var sizes = []int{100, 1000, 10000}

func BenchmarkArrayPushBack(b *testing.B) {
	for i := 0; i < b.N; i++ {
		a := &MyArray{}
		for j := 0; j < 1000; j++ {
			a.PushBack("x")
		}
	}
}

func BenchmarkArrayInsertFront(b *testing.B) { // O(n) на вставку
	for _, n := range sizes {
		b.Run(fmt.Sprint(n), func(b *testing.B) {
			a := &MyArray{}
			for j := 0; j < n; j++ {
				a.PushBack("x")
			}
			for i := 0; i < b.N; i++ {
				_ = a.InsertAt(0, "y")
				_ = a.RemoveAt(0)
			}
		})
	}
}

func BenchmarkDoublyListFind(b *testing.B) { // O(n)
	for _, n := range sizes {
		b.Run(fmt.Sprint(n), func(b *testing.B) {
			l := &DoublyList{}
			for j := 0; j < n; j++ {
				l.PushBack(strconv.Itoa(j))
			}
			last := strconv.Itoa(n - 1)
			for i := 0; i < b.N; i++ {
				l.Find(last)
			}
		})
	}
}

func BenchmarkStackPushPop(b *testing.B) { // O(1)
	s := &MyStack{}
	for i := 0; i < b.N; i++ {
		s.Push("x")
		_, _ = s.Pop()
	}
}

func BenchmarkHashTableGet(b *testing.B) { // O(1) в среднем
	for _, n := range sizes {
		b.Run(fmt.Sprint(n), func(b *testing.B) {
			h := NewHashTable()
			for j := 0; j < n; j++ {
				h.Put(strconv.Itoa(j), "v")
			}
			for i := 0; i < b.N; i++ {
				_, _ = h.Get(strconv.Itoa(i % n))
			}
		})
	}
}

func BenchmarkAVLFind(b *testing.B) { // O(log n)
	for _, n := range sizes {
		b.Run(fmt.Sprint(n), func(b *testing.B) {
			t := &AVLTree{}
			for j := 0; j < n; j++ {
				t.Insert(j)
			}
			for i := 0; i < b.N; i++ {
				t.Find(i % n)
			}
		})
	}
}
