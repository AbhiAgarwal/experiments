package main

import(
	"fmt"
)

func main() {
	fmt.Println("Enter one number")
    var i int
    fmt.Scan(&i)
    fmt.Println("Enter another number")
    var j int
    fmt.Scan(&j)
    sum, product, minus1, minus2 := calc(i, j)
    fmt.Println("Sum", sum, "Product", product, "N1-N2", minus1,  "N2-N1", minus2)
}

func calc(a, b int) (int, int, int, int) {

	return a+b, a*b, a-b, b-a

}