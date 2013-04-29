package main

import (
    "code.google.com/p/go-tour/wc"
    "strings"
)
func WordCount(s string) map[string]int {
    
    m := make(map[string]int)
    
    a := strings.Fields(s)
        
    for i:= 0; i<len(a); i++{
        m[a[i]] += 1   
    }
    return m
}
func main() {
    wc.Test(WordCount)
}
