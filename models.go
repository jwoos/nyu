package main

import (
	"github.com/jinzhu/gorm"
	"github.com/go-sql-driver/mysql"
)

type Privilege struct {
	gorm.Model

	id int `Form:"PRIMARY_KEY"`
	name string `gorm:"size:255"`
	description string `gorm:"size:255"`
}
