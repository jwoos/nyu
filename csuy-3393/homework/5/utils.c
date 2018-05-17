#include "utils.h"


void println(char* fmt, ...) {
	va_list args;

	va_start(args, fmt);
	vprintf(fmt, args);
	va_end(args);

	printf("\n");
}
