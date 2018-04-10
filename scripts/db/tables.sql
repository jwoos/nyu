CREATE TABLE levels (
	id INT,
	name TINYTEXT,
	description TINYTEXT,

	PRIMARY KEY(id)
);

CREATE TABLE accounts (
	id INT,
	level_id INT,
	email TEXT, -- sha256
	username CHAR(64), -- sha256
	salt TINYTEXT,
	password BINARY(60), -- bcrypt
	created DATETIME,
	updated DATETIME,

	PRIMARY KEY(id),
	FOREIGN KEY(level_id) REFERENCES levels(id)
);

CREATE TABLE professors  (
	id INT,
	account_id INT,
	first_name TINYTEXT,
	last_name TINYTEXT,
	created DATETIME,
	updated DATETIME,

	PRIMARY KEY(id),
	FOREIGN KEY(account_id) REFERENCES accounts(id)
);

CREATE TABLE students (
	id INT,
	account_id INT,
	university_number CHAR(64), -- sha256
	created DATETIME,
	updated DATETIME,

	PRIMARY KEY(id),
	FOREIGN KEY(account_id) REFERENCES accounts(id)
);

CREATE TABLE courses (
	id INT,
	name TINYTEXT,
	description TEXT,
	professor_id INT,
	created DATETIME,
	updated DATETIME,

	PRIMARY KEY(id),
	FOREIGN KEY(professor_id) REFERENCES professors(id)
);

CREATE TABLE enrollments (
	id INT,
	student_id INT,
	course_id INT,
	year INT,
	semester INT,
	section VARCHAR(16),
	created DATETIME,
	updated DATETIME,

	PRIMARY KEY(id),
	FOREIGN KEY(student_id) REFERENCES students(id),
	FOREIGN KEY(course_id) REFERENCES courses(id)
);

CREATE TABLE evaluations (
	id INT,
	enrollment_id INT,
	name TEXT,
	comments TEXT,
	percentage INT,
	rating INT,
	created DATETIME,
	updated DATETIME,

	PRIMARY KEY(id),
	FOREIGN KEY(enrollment_id) REFERENCES enrollments(id)
);
