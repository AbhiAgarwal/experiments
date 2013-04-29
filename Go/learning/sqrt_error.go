package main

import (
    "fmt"
    "errors"
    "math"
)

//name the return variables - by default it will have 'zero-ed' values i.e. numbers are 0, string is empty, etc.
func MySqrt2(f float64) (ret float64, err error) {
    if (f < 0) {
        //then you can use those variables in code
        ret = float64(math.NaN())
        err = errors.New("I won't be able to do a sqrt of negative number!")
    } else {
        ret = math.Sqrt(f)
        err = errors.New("")
        //err is not assigned, so it gets default value nil
    }
    //automatically return the named return variables ret and err
    return
}

func main() { 
    fmt.Println(MySqrt2(1))
}