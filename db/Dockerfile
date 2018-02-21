FROM mysql

ENV MYSQL_ROOT_PASSWORD=password
ENV MYSQL_DATABASE=db

EXPOSE 3306

#ENV MYSQL_USER=junwoo
#ENV MYSQL_PASSWORD=password

COPY employees-mysql.sql /opt
COPY patient-mysql.sql /opt
COPY restaurant-mysql.sql /opt

COPY import.sh /opt
