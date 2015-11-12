package main

import "fmt"

func connectToDB () {
    fmt.Println( "ok, connected to db" )
}

func disconnectFromDB (v int) {
    fmt.Println(v+v)
}

func doDBOperations() {
     connectToDB()
     fmt.Println("Defering the database disconnect.")
     defer disconnectFromDB(1) //function called here with defer
     fmt.Println("Doing some DB operations ...")
     fmt.Println("Oops! some crash or network error ...")
     fmt.Println("Returning from function here!")
     return //terminate the program

     // deferred function executed here just before actually returning, even if there is a return or abnormal termination before
}

func main() {
    doDBOperations()
}