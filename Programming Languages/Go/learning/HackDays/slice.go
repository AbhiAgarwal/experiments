package main

import (
	"fmt"
)

func main (){

	x := []string{"Лайка", "Белка", "Стрелка"}
	s := x[:]
	fmt.Println(s)
	fmt.Println(cap(s))
	fmt.Println(len(s))
	fmt.Println(s[2])

}