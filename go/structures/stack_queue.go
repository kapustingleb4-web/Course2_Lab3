package structures

import "strings"

// MyStack - стек (LIFO), встраивает MyArray (аналог наследования в C++).
type MyStack struct {
	MyArray
}

func (s *MyStack) Push(val string) { s.PushBack(val) }

func (s *MyStack) Pop() (string, error) {
	if s.size == 0 {
		return "", ErrEmpty
	}
	s.size--
	return s.data[s.size], nil
}

func (s *MyStack) Peek() (string, error) {
	if s.size == 0 {
		return "", ErrEmpty
	}
	return s.data[s.size-1], nil
}

func (s *MyStack) TypeName() string { return "MyStack" }

func (s *MyStack) String() string {
	items := s.GetData()
	for i, j := 0, len(items)-1; i < j; i, j = i+1, j-1 {
		items[i], items[j] = items[j], items[i]
	}
	return "top> [" + strings.Join(items, ", ") + "]"
}

func (s *MyStack) SaveBinary(f string) error { return saveBinary(f, s.TypeName(), s.GetData()) }
func (s *MyStack) SaveText(f string) error   { return saveText(f, s.TypeName(), s.GetData()) }

func (s *MyStack) LoadBinary(f string) error {
	items, err := loadBinary[string](f, s.TypeName())
	if err == nil {
		s.setData(items)
	}
	return err
}

func (s *MyStack) LoadText(f string) error {
	items, err := loadText[string](f, s.TypeName())
	if err == nil {
		s.setData(items)
	}
	return err
}

// MyQueue - очередь (FIFO), встраивает MyArray: добавление в конец, извлечение из начала.
type MyQueue struct {
	MyArray
}

func (q *MyQueue) Push(val string) { q.PushBack(val) }

func (q *MyQueue) Pop() (string, error) {
	if q.size == 0 {
		return "", ErrEmpty
	}
	v := q.data[0]
	_ = q.RemoveAt(0) // O(n): сдвиг
	return v, nil
}

func (q *MyQueue) Front() (string, error) {
	if q.size == 0 {
		return "", ErrEmpty
	}
	return q.data[0], nil
}

func (q *MyQueue) TypeName() string { return "MyQueue" }
func (q *MyQueue) String() string   { return "front> [" + strings.Join(q.GetData(), ", ") + "] <back" }

func (q *MyQueue) SaveBinary(f string) error { return saveBinary(f, q.TypeName(), q.GetData()) }
func (q *MyQueue) SaveText(f string) error   { return saveText(f, q.TypeName(), q.GetData()) }

func (q *MyQueue) LoadBinary(f string) error {
	items, err := loadBinary[string](f, q.TypeName())
	if err == nil {
		q.setData(items)
	}
	return err
}

func (q *MyQueue) LoadText(f string) error {
	items, err := loadText[string](f, q.TypeName())
	if err == nil {
		q.setData(items)
	}
	return err
}
