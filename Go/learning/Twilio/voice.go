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
    callbackParams := gotwilio.NewCallbackParameters("http://example.com")
    twilio.CallWithUrlCallbacks(from, to, callbackParams)
}
