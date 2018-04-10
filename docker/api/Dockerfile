FROM python:3-alpine3.6

COPY requirements.txt /opt/

RUN apk add --no-cache \
		alpine-sdk \
		bash \
		build-base \
		ca-certificates \
		curl \
		libffi-dev \
		linux-headers \
		musl \
		openssl \
		openssl-dev \
		python3-dev \
		zlib-dev

RUN pip3 install -r /opt/requirements.txt --use-wheel --no-cache-dir

COPY . /opt

WORKDIR /opt

ENTRYPOINT []
CMD /opt/scripts/wait-for-it.sh db:3306 -- uwsgi uwsgi.ini
