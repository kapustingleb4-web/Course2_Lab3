package structures

import "strings"

// MyArray - динамический массив строк (ёмкость удваивается).
type MyArray struct {
	data     []string
	size     int
	capacity int
}

func (a *MyArray) resize(newCap int) {
	newData := make([]string, newCap)
	copy(newData, a.data[:a.size])
	a.data = newData
	a.capacity = newCap
}

func (a *MyArray) PushBack(val string) {
	if a.size == a.capacity {
		a.resize(max(2, a.capacity*2))
	}
	a.data[a.size] = val
	a.size++
}

func (a *MyArray) InsertAt(index int, val string) error {
	if index < 0 || index > a.size {
		return ErrOutOfRange
	}
	if a.size == a.capacity {
		a.resize(max(2, a.capacity*2))
	}
	copy(a.data[index+1:a.size+1], a.data[index:a.size])
	a.data[index] = val
	a.size++
	return nil
}

func (a *MyArray) RemoveAt(index int) error {
	if index < 0 || index >= a.size {
		return ErrOutOfRange
	}
	copy(a.data[index:], a.data[index+1:a.size])
	a.size--
	return nil
}

func (a *MyArray) UpdateAt(index int, val string) error {
	if index < 0 || index >= a.size {
		return ErrOutOfRange
	}
	a.data[index] = val
	return nil
}

func (a *MyArray) Get(index int) (string, error) {
	if index < 0 || index >= a.size {
		return "", ErrOutOfRange
	}
	return a.data[index], nil
}

func (a *MyArray) Find(val string) int {
	for i := 0; i < a.size; i++ {
		if a.data[i] == val {
			return i
		}
	}
	return -1
}

func (a *MyArray) GetData() []string { return append([]string{}, a.data[:a.size]...) }
func (a *MyArray) Size() int         { return a.size }
func (a *MyArray) IsEmpty() bool     { return a.size == 0 }
func (a *MyArray) Clear()            { a.data, a.size, a.capacity = nil, 0, 0 }
func (a *MyArray) TypeName() string  { return "MyArray" }
func (a *MyArray) String() string    { return "[" + strings.Join(a.GetData(), ", ") + "]" }

func (a *MyArray) setData(items []string) {
	a.Clear()
	for _, s := range items {
		a.PushBack(s)
	}
}

func (a *MyArray) SaveBinary(filename string) error {
	return saveBinary(filename, a.TypeName(), a.GetData())
}

func (a *MyArray) LoadBinary(filename string) error {
	items, err := loadBinary[string](filename, a.TypeName())
	if err == nil {
		a.setData(items)
	}
	return err
}

func (a *MyArray) SaveText(filename string) error {
	return saveText(filename, a.TypeName(), a.GetData())
}

func (a *MyArray) LoadText(filename string) error {
	items, err := loadText[string](filename, a.TypeName())
	if err == nil {
		a.setData(items)
	}
	return err
}
