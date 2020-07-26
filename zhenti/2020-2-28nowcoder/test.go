package main

import (
	"fmt"
	"os"
)

func main() {
	var a, b, c = true, 123, "string"
	s := []int{1, 2, 3}
	fmt.Printf("%v, %v, %v, %v", a, b, c, s)
	if f, err := os.Open("coin.cpp"); err != nil {
		f.Close()
		return
	}
	//err := fmt.Errorf("aaa")
	//f, _ := os.Open("coin.cpp")
	var x *int = nil

}
