// Package structures - классы (структуры с методами) ЛР3: массив, списки, стек, очередь,
// хеш-таблица, АВЛ-дерево. Поля с маленькой буквы не видны снаружи пакета (инкапсуляция).
package structures

import (
	"encoding/gob"
	"encoding/json"
	"errors"
	"fmt"
	"os"
)

// Container - общий интерфейс всех структур (в Go интерфейс реализуется неявно).
type Container interface {
	Size() int
	IsEmpty() bool
	Clear()
	String() string
	TypeName() string
	SaveBinary(filename string) error
	LoadBinary(filename string) error
	SaveText(filename string) error
	LoadText(filename string) error
}

var (
	ErrEmpty      = errors.New("structure is empty")
	ErrOutOfRange = errors.New("index out of range")
	ErrNotFound   = errors.New("not found")
)

// file - общий формат файла: имя типа + элементы
type file[T any] struct {
	Type  string `json:"type"`
	Items []T    `json:"items"`
}

func saveBinary[T any](filename, typ string, items []T) error {
	f, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer f.Close()
	return gob.NewEncoder(f).Encode(file[T]{typ, items})
}

func loadBinary[T any](filename, typ string) ([]T, error) {
	f, err := os.Open(filename)
	if err != nil {
		return nil, err
	}
	defer f.Close()
	var d file[T]
	if err := gob.NewDecoder(f).Decode(&d); err != nil {
		return nil, fmt.Errorf("binary decode: %w", err)
	}
	if d.Type != typ {
		return nil, fmt.Errorf("type mismatch: expected %s, got %s", typ, d.Type)
	}
	return d.Items, nil
}

func saveText[T any](filename, typ string, items []T) error {
	data, err := json.MarshalIndent(file[T]{typ, items}, "", "    ")
	if err != nil {
		return err
	}
	return os.WriteFile(filename, data, 0644)
}

func loadText[T any](filename, typ string) ([]T, error) {
	data, err := os.ReadFile(filename)
	if err != nil {
		return nil, err
	}
	var d file[T]
	if err := json.Unmarshal(data, &d); err != nil {
		return nil, fmt.Errorf("text decode: %w", err)
	}
	if d.Type != typ {
		return nil, fmt.Errorf("type mismatch: expected %s, got %s", typ, d.Type)
	}
	return d.Items, nil
}
