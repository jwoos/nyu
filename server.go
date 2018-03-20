package main


import (
	"net/http"

	"github.com/gorilla/mux"
)


func newRouter() *mux.Router {
	router := mux.NewRouter().StrictSlash(true)
	router.HandleFunc("/status", status).Methods("GET")

	return router
}

func status(w http.ResponseWriter, r *http.Request) {
	w.WriteHeader(http.StatusOK)
}
