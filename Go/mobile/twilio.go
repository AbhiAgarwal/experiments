package main

import (
    "github.com/sfreiberg/gotwilio"
    "net/http"
    "fmt"
)

func twilio(message_s string) {
    accountSid := ""
    authToken := ""
    twilio := gotwilio.NewTwilioClient(accountSid, authToken)

    from := "+"
    to := "+"
    message := message_s
    twilio.SendSMS(from, to, message, "", "")
}

func main_handler(w http.ResponseWriter, r *http.Request) { 
    remPartOfURL := r.URL.Path[len("/"):]
    //twilio("On Main Page") // Calls everytime someone makes a request,
    // Work in progress to add the count
    fmt.Fprintf(w, "Hello world from %s ", (remPartOfURL))
}

func main() {
    http.HandleFunc("/", main_handler)
    http.ListenAndServe("localhost:8080", nil)
}
