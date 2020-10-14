#include "jansson.h"
#include <stdio.h>
#include <string.h>

int test_file_write(const char *filename, char *data)
{
	/* file write / read test code */
	FILE *fp = NULL;

	fp = fopen(filename, "w");
	fwrite(data, 1, strlen(data) + 1, fp);
	fclose(fp);
	fp = NULL;

	return 0;
}

int test_file_read(const char *filename)
{
	FILE *fp = NULL;
	char buffer[1024];

	fp = fopen(filename, "r");
	fread(buffer, 1, sizeof(buffer), fp);
	printf("[%s:%d] buffer = %s\n", __FILE__, __LINE__, buffer);
	fclose(fp);
	fp = NULL;

	return 0;
}

int test_json(json_t *result)
{
	/* jansson test code */
	enum
	{
		INPUT_SIZE = 5
	};
	const char *testInputKey[INPUT_SIZE] = {"admin", "test1", "test2", "test3", "test4"};
	int testInputValue[INPUT_SIZE] = {1, 4, 1, 2, 0};
	int i;

	for (i = 0; i < INPUT_SIZE; i++)
	{
		json_object_set_new(result, testInputKey[i], json_integer(testInputValue[i]));
	}
	printf("[%s:%d] result = %s\n", __FILE__, __LINE__, json_dumps(result, JSON_ENCODE_ANY));

	return 0;
}

int main(int argc, char **argv)
{
	const char *txtFilename = "test.txt";
	const char *jsonFilename = "test.json";

	char buffer[1024];

	/* test file write */
	snprintf(buffer, sizeof(buffer), "%s\0", "hello file write test!!!!");
	test_file_write(txtFilename, buffer);

	/* test file write */
	memset(buffer, 0, sizeof(buffer));
	test_file_read(txtFilename);

	/* test fill json type */
	json_t *result = json_object();
	test_json(result);

	/* test file write json data */
	memset(buffer, 0, sizeof(buffer));
	snprintf(buffer, sizeof(buffer), "%s\0", json_dumps(result, JSON_ENCODE_ANY));
	printf("[%s:%d] buffer = %s\n", __FILE__, __LINE__, buffer);
	test_file_write(jsonFilename, buffer);

	/* test file read json data */
	memset(buffer, 0, sizeof(buffer));
	test_file_read(jsonFilename);

	return 0;
}