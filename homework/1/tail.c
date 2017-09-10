#include "types.h"
#include "user.h"


void tail(int fd, char* name) {
	int linesSize = 10;
	int bufferSize = 512;

	char** lines = malloc(sizeof(char*) * linesSize);
	int* sizes = malloc(sizeof(int) * linesSize);
	lines[0] = malloc(sizeof(char) * bufferSize);
	char buffer[bufferSize];

	int bytesRead;
	int lineIndex = 0;
	int charIndex = 0;

	while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0) {
		for (int i = 0; i < bytesRead; i++) {
			// exceeded current buffer size
			if (charIndex == bufferSize - 1) {
				int oldBufferSize = bufferSize;
				bufferSize *= 2;
				char* temp = malloc(sizeof(char) * bufferSize);

				for (int j = 0; j < oldBufferSize; j++) {
					temp[j] = lines[lineIndex][j];
				}

				free(lines[lineIndex]);
				lines[lineIndex] = temp;
			}

			// put it in lines
			lines[lineIndex][charIndex] = buffer[i];

			// new line
			if (buffer[i] == '\n') {
				// exceeded current lines size
				if (lineIndex == linesSize - 1) {
					int oldLinesSize = linesSize;
					linesSize *= 2;
					char** tempLines = malloc(sizeof(char*) * linesSize);
					int* tempSizes = malloc(sizeof(int) * linesSize);

					for (int j = 0; j < oldLinesSize; j++) {
						tempLines[j] = lines[j];
						tempSizes[j] = sizes[j];
					}

					free(lines);
					free(sizes);

					lines = tempLines;
					sizes = tempSizes;
				}

				sizes[i] = charIndex + 1;
				lineIndex += 1;
				charIndex = 0;
				bufferSize = 512;

				lines[lineIndex] = malloc(sizeof(char) * bufferSize);
			}

			// separate index to keep track of line
			charIndex += 1;
		}
	}

	if (bytesRead < 0) {
		printf(1, "tail: read error\n");
		exit();
	}

	int startIndex = lineIndex - 10;;
	if (startIndex < 0) {
		startIndex = 0;
	}

	for (int i = startIndex; i <= lineIndex; i++) {
		write(1, lines[i], sizes[i]);
	}

	for (int i = 0; i <= lineIndex; i++) {
		free(lines[i]);
	}

	free(lines);
	free(sizes);
}

int main(int argc, char* argv[]) {
	int fd = 0;

	if (argc <= 1) {
		tail(fd, "");
	} else {
		fd = open(argv[1], 0);

		if (fd < 0) {
			printf(1, "tail: cannot open %s\n", argv[1]);
			exit();
		}

		tail(fd, argv[1]);
		close(fd);
	}
	exit();
}
