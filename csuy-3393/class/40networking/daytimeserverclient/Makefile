FLAGS = -Wall -O1 -std=c99  -D _POSIX_C_SOURCE=200112L

all: daytimetcpcli daytimetcpsrv

daytimetcpcli: daytimetcpcli.c
	gcc daytimetcpcli.c ${FLAGS} -o daytimetcpcli

daytimetcpsrv: daytimetcpsrv.c
	gcc daytimetcpsrv.c ${FLAGS} -o daytimetcpsrv

clean:
	rm -f daytimetcpcli daytimetcpsrv
