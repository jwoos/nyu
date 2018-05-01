# CS3083 Project
Yining Wang, Mohammad Rafi, Lyu Longtao, Johnson Mei, Jun Woo Shin

## Running
You will need to have Docker and docker-compose installed.

1. Go to the root of the project and run `docker-compose build`
2. Run `docker-compose up api`
	- This will bring up the application
	- `localhost:8080` for the frontend and `localhost:9000` for the backend

There are four test accounts two students and two professors. The usernames are: `student1@test.site`, `student2@test.site`, `professor1@test.site`, and `professor2@test.site`. The passwords are all `password`.

## Files
- `db/`
	- This directory has all the files to set up the database and load mock data. The MySQL container will automatically load these files.
- `docker/`
	- All the necessary Docker files
	- `api` for the backend
	- `db` for MySQL
	- `nginx` for a web server and reverse proxy
- `scripts/`
	- utility scripts
- `src`
	- the backend
	- `views` has all the API endpoints defined with all the logic
	- `auth` is a wrapper for jwt
	- `password` is a wrapper for bcrypt
	- `db` is to connect to the database
	- `main` sets everything up and establishes the endpoints
- `static`
	- the frontend
	- divided into sections
	- `index.html` is the login
	- respective view for student and professor in the directories
	- `assets` has all the scripts and stylesheets including vendors
- `docker-compose.yaml`
	- determines the Docker compose services
- `nginx.conf`
	- nginx configuration
- `requirements.txt`
	- for install Python requirements
- `uwsgi.ini`
	- uwsgi configuration
