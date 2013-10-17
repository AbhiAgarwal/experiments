package main

import (
    "github.com/sfreiberg/gotwilio"
    "github.com/hoisie/web"
    "strconv"
    "io"
    "bytes"
    )

var m map[string]int

func main() {
        web.Get("/(.*)", hello)
        web.Run("0.0.0.0:9999")
}

func hello(ctx *web.Context, val string) {

	for k, v := range ctx.Params {
	        if(k=="sms") {
	            m[v] += 1
	        }
	    }
	var buf bytes.Buffer
	for k, v := range m {
		c := k +  " " + strconv.Itoa(v) + "\n"
	}
	buf.WriteString(c)
	io.Copy(ctx, &buf)
}