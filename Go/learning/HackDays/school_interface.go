package main

import (
	"fmt"
	"log"
	"net/http"
)
type Student struct {
	Name string
}
func main () {

	a := Student {
		Name: "Abhi",
	}

	http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
		fmt.Fprintf(w, a.Name)
	})

	log.Fatal(http.ListenAndServe(":8080",nil))
}