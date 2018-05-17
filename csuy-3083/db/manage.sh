#!/usr/bin/env bash

NAME='csuy3083'

if [[ $1 == 'build' ]]; then
	docker build -t 'csuy3083:1' .
elif [[ $1 == 'run' ]]; then
	docker run -it --name=$NAME --rm -p 3306:3306 csuy3083:1
elif [[ $1 == 'rund' ]]; then
	docker run -it --name=$NAME --rm -d -p 3306:3306 csuy3083:1
elif [[ $1 == 'kill' ]]; then
	docker kill csuy3083
elif [[ $1 == 'import' ]]; then
	docker exec -it $NAME /opt/import.sh
elif [[ $1 == 'shell' ]]; then
	docker exec -it $NAME bash
elif [[ $1 == 'sqlshell' ]]; then
	docker exec -it $NAME mysql -u root -p
fi
