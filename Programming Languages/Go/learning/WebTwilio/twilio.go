package main

import (
    "github.com/sfreiberg/gotwilio"
    "github.com/hoisie/web"
)

func main() {
	web.Get("/(.*)", hello)
    web.Run("0.0.0.0:9999")
}

func hello(ctx *web.Context, val string) { 
    for k, v := range ctx.Params {
        	if(k=="sms") {
        		twilio(v)
        	}
    }
}   

func twilio(tos string) {
    accountSid := ""
    authToken := ""
    twilio := gotwilio.NewTwilioClient(accountSid, authToken)

    from := "+"
    to := "+1" + tos
    message := "Hello World!"
    twilio.SendSMS(from, to, message, "", "")
}
