package main

import ("net/http")

func main() {
    http.HandleFunc("/hello", func(w http.ResponseWriter, req *http.Request) {
        w.Write([]byte("What the hell!!"))
    })

    http.ListenAndServe(":8820", nil)
}