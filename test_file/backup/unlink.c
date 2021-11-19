#include <stdio.h>

int main(void)
{
	//const char* file = "/mnt/ipm/setup/setup.ini";
	const char* file = "mzf_table";
	char buf[64];
	printf ("BEFORE unlink\n");
	unlink (file);
	//snprintf (buf, sizeof(buf), "rm %s", file);
	//system(buf);
	printf ("AFTER unlink buf = %s;%s\n", buf, file);

	return 0;
}
