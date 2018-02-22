package main


import (
	"log"
	"net/http"
)


func main() {
	port := ":8080"
	log.Println("Serving on", port)
	log.Fatal(http.ListenAndServe(port, newRouter()))
}
