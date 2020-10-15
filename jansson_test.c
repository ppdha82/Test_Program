#include "jansson.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int make_sample_json(json_t *result)
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

json_t* load_json_data_from(const char* filename)
{
	json_error_t error;

	json_t *jData = json_load_file(filename, JSON_DECODE_ANY, &error);
	printf("[%s:%d] error = %d\n", __FILE__, __LINE__, json_error_code(&error));
	printf("[%s:%d] jData = %s\n", __FILE__, __LINE__, json_dumps(jData, JSON_ENCODE_ANY));

	return jData;
}

int write_text_by_json(const char *filename, json_t* writeData)
{
	json_dump_file(writeData, filename, JSON_ENCODE_ANY);
	return 0;
}

int add_json_data(json_t *jData, const char* key)
{
	int jSize = json_object_size(jData);
	if(jSize >= 16) {
		printf("[%s:%d] can't add any more\n", __FILE__, __LINE__);
		return -1;
	}

	json_t* jID;
	// avoid to duplicate key
	jID = json_object_get(jData, key);
	if(jID != NULL) {
		printf("[%s:%d] add already key(%s)\n", __FILE__, __LINE__, key);
		int value = json_integer_value(jID);
		value++;
		value %= 5;
		json_object_set(jData, key, json_integer(value));
	}
	else {
		json_object_set_new(jData, key, json_integer(0));
	}

	return 0;
}

int init_json_data(json_t *jData, const char* key)
{
	json_t* jID;
	// avoid to duplicate key
	jID = json_object_get(jData, key);
	if(jID != NULL) {
		printf("[%s:%d] add already key(%s)\n", __FILE__, __LINE__, key);
		int value = json_integer_value(jID);
		value++;
		value %= 5;
		json_object_set(jData, key, json_integer(value));
	}
	else {
		json_object_set_new(jData, key, json_integer(0));
	}

	return 0;
}

int remove_json_data(json_t *jData, const char* key)
{
	int jSize = json_object_size(jData);
	if(jSize <= 0) {
		printf("[%s:%d] can't remove any more\n", __FILE__, __LINE__);
		return -1;
	}

	json_t *jID;
	jID = json_object_get(jData, key);
	if(jID == NULL) {
		printf("[%s:%d] Not found key(%s)\n", __FILE__, __LINE__, key);

		return -1;
	}

	json_object_del(jData, key);
}

int main(int argc, char **argv)
{
	const char *jsonFilename = "test.json";

	if(access(jsonFilename, F_OK) != 0) {
		/* test fill json type */
		json_t *result = json_object();
		make_sample_json(result);

		/* test file write json data */
		write_text_by_json(jsonFilename, result);
	}

	/* load json data from file */
	json_t* jData = json_object();
	jData = load_json_data_from(jsonFilename);
	printf("[%s:%d] Alive Check (jData = %s)\n", __FILE__, __LINE__, json_dumps(jData, JSON_ENCODE_ANY));
	add_json_data(jData, "admin");
	printf("[%s:%d] Alive Check (jData = %s)\n", __FILE__, __LINE__, json_dumps(jData, JSON_ENCODE_ANY));
	remove_json_data(jData, "test1");
	printf("[%s:%d] Alive Check (jData = %s)\n", __FILE__, __LINE__, json_dumps(jData, JSON_ENCODE_ANY));
	add_json_data(jData, "test1");
	printf("[%s:%d] Alive Check (jData = %s)\n", __FILE__, __LINE__, json_dumps(jData, JSON_ENCODE_ANY));
	write_text_by_json(jsonFilename, jData);

	return 0;
}