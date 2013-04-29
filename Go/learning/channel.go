package main                                                                                                                                                           

import (
    "fmt"
    "time"
    "strconv"
)

func makeCakeAndSend(cs chan string, cs2 chan string) {
    for i := 1; i<=3; i++ {
        cakeName := "Strawberry Cake " + strconv.Itoa(i)
        fmt.Println("Making a cake and sending ...", cakeName)
        cs <- cakeName //send a strawberry cake
        hello := ("Hello World " + strconv.Itoa(i))
        cs2 <- hello
    }   
}

func receiveCakeAndPack(cs chan string, cs2 chan string) {
    for i := 1; i<=3; i++ {
        s := <-cs //get whatever cake is on the channel
        t := <-cs2
        fmt.Println("Packing received cake: ", s)
        fmt.Println(t)
    }   
}

func main() {
    cs := make(chan string)
    cs2 := make(chan string)
    go makeCakeAndSend(cs, cs2)
    go receiveCakeAndPack(cs, cs2)

    //sleep for a while so that the program doesn’t exit immediately
    time.Sleep(1 * 1e9)
}