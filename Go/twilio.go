package main

import (
    "github.com/sfreiberg/gotwilio"
    "net/http"
    "fmt"
)

func twilio() {
    accountSid := "ACd44100ff63d9f063b149272c1c9b8f64"
    authToken := "372306737e389b83729d9d7f5c0fe1e2"
    twilio := gotwilio.NewTwilioClient(accountSid, authToken)

    from := "+14423337001"
    to := "+13474593725"
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
    http.ListenAndServe("localhost:80", nil)
}
