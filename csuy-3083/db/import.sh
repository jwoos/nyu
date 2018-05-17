#!/usr/bin/env bash

FILES=(
	'employees-mysql.sql'
	'patient-mysql.sql'
	'restaurant-mysql.sql'
)

for FILE in "${FILES[@]}"; do
	mysql --user=root --password=${MYSQL_ROOT_PASSWORD} < /opt/$FILE
done
