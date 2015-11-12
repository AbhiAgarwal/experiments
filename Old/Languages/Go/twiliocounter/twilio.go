package main

import (
    "github.com/sfreiberg/gotwilio"
    "net/http"
    "fmt"
)

func twilio() {
    accountSid := ""
    authToken := ""
    twilio := gotwilio.NewTwilioClient(accountSid, authToken)

    from := "+1"
    to := "+1"
    message := "user connected!"
    twilio.SendSMS(from, to, message, "", "")
}

func handler(w http.ResponseWriter, r *http.Request) { 
    twilio() // Calls everytime someone makes a request,
    // Work in progress to add the count
    fmt.Fprintf(w, "Hello world from my Go program!")
}
func main() {
    http.HandleFunc("/", handler)
    http.ListenAndServe("localhost:8080", nil)
}
