FROM nginx:mainline-alpine

RUN apk add --no-cache \
	bash

COPY nginx.conf /opt/
COPY scripts/wait-for-it.sh /opt/
COPY static /opt/static

CMD ["./opt/wait-for-it.sh", "api:9000", "--", "nginx", "-c", "/opt/nginx.conf", "-g", "daemon off;"]
