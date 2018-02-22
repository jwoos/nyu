package main


import (
	"database/sql"
	"log"

	"github.com/go-sql-driver/mysql"
)


func newDatabase() *sql.DB {
	// TODO read from config
	username := "user"
	password := "password"
	net := "tcp"
	address := "localhost:3306"
	name := "feedback"

	config := mysql.NewConfig()

	config.User = username
	config.Passwd = password
	config.Net = net
	config.Addr = address
	config.DBName = name

	dsn := config.FormatDSN()

	db, err := sql.Open("mysql", dsn)
	if err != nil {
		log.Fatal(err)
	}

	return db
}
