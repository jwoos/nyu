FROM python:3-alpine3.6

COPY requirements.txt /opt/

RUN apk add --no-cache \
	alpine-sdk \
	linux-headers \
	python3-dev \
	bash

RUN pip3 install -r /opt/requirements.txt --use-wheel --no-cache-dir

COPY . /opt

WORKDIR /opt

ENTRYPOINT []
CMD uwsgi uwsgi.ini
