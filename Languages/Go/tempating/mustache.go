package main

import (
	"github.com/hoisie/mustache"
	"github.com/hoisie/web"
	"fmt"
)

// http://mustache.github.io/mustache.5.html

type Content struct {
    Title string
    Content string    
}

func home() string {
	c := Content{
		"Hello",
		"My name is abhi",
	}
	return mustache.RenderFile(
		"template/layout.html", 
		map[string]string {
		"title": c.Title, "content": c.Content,
		},
		nil,
	)
}

func server(ctx *web.Context) string {
    return fmt.Sprintf("%v\n", ctx.Server.Config)
}

func main() {
    web.Get("/", home)
    web.Get("/server", server)
    web.Run("0.0.0.0:9999")
}