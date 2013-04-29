package main

import (
	"fmt"
)

func sum(a []int, c chan int, number int) {
    sum := 0
    for _, v := range a {
    	fmt.Println("Adding", v, "to" , sum, "for", number)
        sum += v
        fmt.Println("Sum is now", sum, "of", number)
    }
    c <- sum // send sum to c
}

func main () {
	a := []int{7, 2, 8, -9, 4, 0}
	c := make(chan int)
	d := make(chan int)
	go sum(a[:len(a)/2], c, 1)
	go sum(a[len(a)/2:], d, 2)
	x, y := <- c, <- d

	fmt.Println(x,"+", y,"=", x + y)
}