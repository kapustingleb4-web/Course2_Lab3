package structures

import "strings"

type hNode struct {
	key, value string
	next       *hNode
}

// MyHashTable - хеш-таблица (метод цепочек), удвоение при заполнении > 0.75.
type MyHashTable struct {
	buckets []*hNode
	size    int
}

func NewHashTable() *MyHashTable { return &MyHashTable{buckets: make([]*hNode, 16)} }

func (h *MyHashTable) index(key string) int {
	var v uint64 = 5381 // djb2
	for i := 0; i < len(key); i++ {
		v = v*33 + uint64(key[i])
	}
	return int(v % uint64(len(h.buckets)))
}

func (h *MyHashTable) rehash() {
	old := h.buckets
	h.buckets = make([]*hNode, len(old)*2)
	for _, cur := range old {
		for cur != nil {
			next := cur.next
			i := h.index(cur.key)
			cur.next = h.buckets[i]
			h.buckets[i] = cur
			cur = next
		}
	}
}

func (h *MyHashTable) Put(key, value string) {
	i := h.index(key)
	for cur := h.buckets[i]; cur != nil; cur = cur.next {
		if cur.key == key {
			cur.value = value
			return
		}
	}
	h.buckets[i] = &hNode{key, value, h.buckets[i]}
	h.size++
	if h.size*4 > len(h.buckets)*3 {
		h.rehash()
	}
}

func (h *MyHashTable) Get(key string) (string, error) {
	for cur := h.buckets[h.index(key)]; cur != nil; cur = cur.next {
		if cur.key == key {
			return cur.value, nil
		}
	}
	return "", ErrNotFound
}

func (h *MyHashTable) Contains(key string) bool {
	_, err := h.Get(key)
	return err == nil
}

func (h *MyHashTable) Remove(key string) bool {
	i := h.index(key)
	var prev *hNode
	for cur := h.buckets[i]; cur != nil; prev, cur = cur, cur.next {
		if cur.key == key {
			if prev != nil {
				prev.next = cur.next
			} else {
				h.buckets[i] = cur.next
			}
			h.size--
			return true
		}
	}
	return false
}

func (h *MyHashTable) Capacity() int { return len(h.buckets) }

// pairs - ключи и значения подряд: k1, v1, k2, v2, ...
func (h *MyHashTable) pairs() []string {
	var res []string
	for _, cur := range h.buckets {
		for ; cur != nil; cur = cur.next {
			res = append(res, cur.key, cur.value)
		}
	}
	return res
}

func (h *MyHashTable) Size() int        { return h.size }
func (h *MyHashTable) IsEmpty() bool    { return h.size == 0 }
func (h *MyHashTable) Clear()           { h.buckets, h.size = make([]*hNode, 16), 0 }
func (h *MyHashTable) TypeName() string { return "MyHashTable" }

func (h *MyHashTable) String() string {
	p := h.pairs()
	var items []string
	for i := 0; i < len(p); i += 2 {
		items = append(items, p[i]+": "+p[i+1])
	}
	return "{" + strings.Join(items, ", ") + "}"
}

func (h *MyHashTable) setPairs(p []string) {
	h.Clear()
	for i := 0; i+1 < len(p); i += 2 {
		h.Put(p[i], p[i+1])
	}
}

func (h *MyHashTable) SaveBinary(f string) error { return saveBinary(f, h.TypeName(), h.pairs()) }
func (h *MyHashTable) SaveText(f string) error   { return saveText(f, h.TypeName(), h.pairs()) }

func (h *MyHashTable) LoadBinary(f string) error {
	p, err := loadBinary[string](f, h.TypeName())
	if err == nil {
		h.setPairs(p)
	}
	return err
}

func (h *MyHashTable) LoadText(f string) error {
	p, err := loadText[string](f, h.TypeName())
	if err == nil {
		h.setPairs(p)
	}
	return err
}
