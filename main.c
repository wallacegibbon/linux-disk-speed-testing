/// Compiling this file with the `_GNU_SOURCE` macro defined: gcc -D_GNU_SOURCE filename.c
/// You need to install the following library to run this project:
///     https://github.com/wallacegibbon/commandline-argument-parser

#include <assert.h>
#include <cmd_argument_parser.h>
#include <errno.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

struct testing_data {
	const char *target_file;
	size_t lines_to_print;
	size_t line_size;
	int do_sync;
	/// the content of the buffer does not matter.
	char *buffer;
};

int testing_data_initialize(struct testing_data *self) {
	self->buffer = malloc(self->line_size);
	if (self->buffer == NULL)
		return 0;

	memset(self->buffer, 'a', self->line_size);
	return 1;
}

void testing_data_cleanup(struct testing_data *self) {
	free(self->buffer);
}

void testing_data_show_info(struct testing_data *self, int elapsed_clock, const char *tag) {
	float tmp;
	tmp = self->lines_to_print * ((double)CLOCKS_PER_SEC / elapsed_clock);
	printf("[%10s]", tag);
	printf("line size:%8ld, ", self->line_size);
	printf("lines per second:%10.0f, ", tmp);
	printf("speed:%10.2f MiB/s, ", tmp * self->line_size / 1024 / 1024);
	printf("sync:%d\n", self->do_sync);
}

void test_1(struct testing_data *self, char **error) {
	int fd;
	size_t i, a, b;
	float tmp;

	*error = NULL;

	/// opening this file with `O_DIRECT` flag causes `Invalid argument` error.
	// fd = open(self->target_file, O_WRONLY | O_CREAT | O_DIRECT, S_IRUSR | S_IWUSR);
	fd = open(self->target_file, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	if (fd == -1) {
		*error = strerror(errno);
		goto end;
	}

	a = clock();
	for (i = 0; i < self->lines_to_print; i++) {
		if (write(fd, self->buffer, self->line_size) == -1) {
			*error = strerror(errno);
			goto end;
		}
	}

	if (self->do_sync)
		assert(!fsync(fd));

	b = clock();
	testing_data_show_info(self, b - a, "write");

end:
	close(fd);
}

void test_2(struct testing_data *self, char **error) {
	FILE *fp;
	size_t i, a, b;
	float tmp;

	*error = NULL;

	fp = fopen(self->target_file, "wb");

	a = clock();
	for (i = 0; i < self->lines_to_print; i++)
		assert(fwrite(self->buffer, 1, self->line_size, fp) == self->line_size);

	if (self->do_sync) {
		assert(!fflush(fp));
		assert(!fsync(fileno(fp)));
	}

	b = clock();
	testing_data_show_info(self, b - a, "fwrite");

	fclose(fp);
}

int main(int argc, const char **argv) {
	struct cmd_argument_parser parser;
	struct testing_data testing;
	size_t lines_to_print, line_size;
	const char *filename;
	char *error;

	cmd_argument_parser_prepare(&parser, argc - 1, argv + 1);

	testing.target_file = cmd_argument_parser_get(&parser, "file", "disk-testing-data.txt");
	testing.lines_to_print = atoi(cmd_argument_parser_get(&parser, "lines", "1000000"));
	testing.line_size = atoi(cmd_argument_parser_get(&parser, "line_size", "128"));
	testing.do_sync = cmd_argument_parser_has(&parser, "sync");

	testing_data_initialize(&testing);

	test_1(&testing, &error);
	if (error != NULL) {
		fprintf(stderr, "test 1 error: %s\n", error);
		return 2;
	}

	test_2(&testing, &error);
	if (error != NULL) {
		fprintf(stderr, "test 2 error: %s\n", error);
		return 3;
	}

	cmd_argument_parser_cleanup(&parser);
	testing_data_cleanup(&testing);

	return 0;
}
