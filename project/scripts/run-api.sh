#!/usr/bin/env bash

set -e

export APP_SECRET=$(dd if=/dev/urandom bs=128 count=1 status=none | base64 | tr -d '\n')

uwsgi uwsgi.ini
