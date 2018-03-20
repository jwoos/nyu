# Go version 1.9.4
# Alpine version 3.7
FROM golang:1.9.4-alpine3.7

EXPOSE 8080

ENTRYPOINT []
CMD $GOPATH/bin/cwc-go

ENV SRC_PATH=/go/src/cs3083-project

RUN mkdir -p $SRC_PATH

COPY . $SRC_PATH

WORKDIR $SRC_PATH

RUN go install . && rm -rf $SRC_PATH

WORKDIR $GOPATH/bin
