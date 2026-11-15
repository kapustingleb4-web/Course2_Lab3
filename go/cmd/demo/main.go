// ЛР3 (Go): демонстрация структур, полиморфизма через интерфейс и сериализации.
package main

import (
	"fmt"
	"os"

	"lab3/structures"
)

func main() {
	arr := &structures.MyArray{}
	for _, s := range []string{"10", "20", "30"} {
		arr.PushBack(s)
	}
	_ = arr.InsertAt(1, "15")

	fl := &structures.ForwardList{}
	fl.PushBack("b")
	fl.PushFront("a")
	fl.InsertAfter("b", "c")

	dl := &structures.DoublyList{}
	for _, s := range []string{"1", "2", "3"} {
		dl.PushBack(s)
	}

	st := &structures.MyStack{}
	st.Push("x")
	st.Push("y")

	q := &structures.MyQueue{}
	q.Push("first")
	q.Push("second")

	ht := structures.NewHashTable()
	ht.Put("one", "1")
	ht.Put("two", "2")

	tree := &structures.AVLTree{}
	for _, v := range []int{7, 3, 2, 1, 9, 5, 4, 6, 8} {
		tree.Insert(v)
	}

	// полиморфизм: все структуры через интерфейс Container
	for _, c := range []structures.Container{arr, fl, dl, st, q, ht, tree} {
		fmt.Printf("%s (size %d): %s\n", c.TypeName(), c.Size(), c.String())
	}
	fmt.Println("Дерево BFS:", tree.Traverse(structures.BFS), "высота", tree.Height(), "сбалансировано:", tree.IsBalanced())

	if err := tree.SaveText("tree.json"); err != nil {
		fmt.Fprintln(os.Stderr, err)
	}
	if err := ht.SaveBinary("table.gob"); err != nil {
		fmt.Fprintln(os.Stderr, err)
	}
	tree2, ht2 := &structures.AVLTree{}, structures.NewHashTable()
	_ = tree2.LoadText("tree.json")
	_ = ht2.LoadBinary("table.gob")
	fmt.Println("Загружено из tree.json (BFS):", tree2.Traverse(structures.BFS))
	fmt.Println("Загружено из table.gob:", ht2.String())
}
