package main

import "fmt"

func main() {
    j := 4
    switch {
    case (j%2 == 0): fmt.Println(j, "is even")
    case (j%2 != 0): fmt.Println(j, "is odd")
    default: fmt.Println(j, "is not an integer between 0 and 9")
    }

}