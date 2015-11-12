package main

import (
    "github.com/sfreiberg/gotwilio"
)

func main() {
    accountSid := ""
    authToken := ""
    twilio := gotwilio.NewTwilioClient(accountSid, authToken)

    from := "+"
    to := "+"
    message := "Hello World!"
    twilio.SendSMS(from, to, message, "", "")
}
