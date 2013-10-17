package main

import "fmt"

func main() {
    s1 := "abcd"
    s2 := "abc"
    switch s1 { 
    case s2: fmt.Println("the two strings are equal")
    default: fmt.Println("the two strings are NOT equal")  //since nothing else matches, the default block is executed
    }
}