#include <stdio.h>
#include <string.h>

typedef unsigned int __u64;

enum {
	KB_DEPTH = 1,
	MB_DEPTH = 2,
	GB_DEPTH = 3,
};

const int KB = 1024;

void get_network_info(__u64* recv_size, __u64* send_size, int sz)
{
	char cmd[256], buf[1024];
	int i;
	memset(buf, 0, sizeof(buf));

#if __DUAL_LAN__
	int max_sz = 2;
#else
	int max_sz = 1;
#endif

	for (i = 0; i < max_sz; i++) {
		snprintf(cmd, sizeof(cmd), "eth%d", i);

		FILE* fp = fopen("/proc/net/dev", "rt");
		if (fp) {
			char* p;
			do {
				memset(buf, 0, sizeof(buf));
				p = fgets(buf, sizeof(buf), fp);
				if (p) {
					if (strstr(buf, cmd))
						break;
				}
			} while (p);

			fclose(fp);
		}

		if (strlen(buf)) {
			printf("[%s:%d] [%s]\n", __FILE__, __LINE__, buf);

			int token_pos = 0;
			char* delimit = " ";
			char *p_token = NULL, *save_ptr;
			p_token = strtok_r(buf, delimit, &save_ptr);
			while (p_token) {
				printf("[%s:%d] %d> %s\n", __FILE__, __LINE__, token_pos, p_token);

				if (token_pos == 1 && recv_size) {
					recv_size[i] = atoll(p_token);
					printf("[%s:%d] recv[%d] %llu\n", __FILE__, __LINE__, i, recv_size[i]);

				}
				else if (token_pos == 9 && send_size) {
					send_size[i] = atoll(p_token);
					printf("[%s:%d] send[%d] %llu\n", __FILE__, __LINE__, i, send_size[i]);
					break;
				}

				p_token = strtok_r(NULL, delimit, &save_ptr);
				token_pos++;
			}
		}
	}

	for (i = max_sz; i < sz; i++) {
		recv_size[i] = 0;
		send_size[i] = 0;
	}
}

int convert_to_human_readable (__u64 *dest, __u64 src, int depth)
{
	int ret = -1;
	if (dest == NULL) {
		printf ("[%s:%d] dest is NULL\n", __FILE__, __LINE__);
		return -1;
	}

	depth--;
	if (depth > 0) {
		if (src > KB) {
			*dest = src / KB;
		}
		else {
			return -2;
		}

		ret = convert_to_human_readable (dest, *dest, depth);
		if (ret == -2) {
			*dest = 0;
			return -2;
		}
	}

	return 0;
}

int get_net_traffic_info (__u64* recv, __u64* send)
{
	const char* path = "/sys/class/net/eth0/statistics";
	char path_file[128];
	// rx_bytes
	const char* menu[4] = { "rx_bytes", "rx_packets", "tx_bytes", "tx_packets" };
	int i = 0;
	char buf[128];

	for (i = 0;i < 4;i++) {
		memset (path_file, 0, sizeof (path_file));
		memset (buf, 0, sizeof (buf));
		snprintf (path_file, sizeof (path_file), "%s/%s", path, menu[i]);
		FILE* fp = fopen(path_file, "rt");
		if (fp) {
			memset(buf, 0, sizeof(buf));
			fgets(buf, sizeof(buf), fp);
			printf ("[%s:%d] [%s] buf = %s", __FILE__, __LINE__, menu[i], buf);
			if (i == 0 || i == 1) {
				*recv = atoi (buf);
				recv++;
			}
			else if (i == 2 || i == 3) {
				*send = atoi (buf);
				send++;
			}

			fclose(fp);
		}
	}
}

int main (int argc, char** argv)
{
	__u64 recv[2];
	__u64 send[2];
	__u64 a = 0;
	__u64 b = 0;
	__u64 aKB = 0;
	__u64 bKB = 0;
	__u64 aMB = 0;
	__u64 bMB = 0;
	__u64 aGB = 0;
	__u64 bGB = 0;

	get_network_info (&a, &b, 1);
	printf ("[%s:%d] a = %d; b = %d\n", __FILE__, __LINE__, a, b);
	convert_to_human_readable (&aKB, a, KB_DEPTH);
	convert_to_human_readable (&bKB, b, KB_DEPTH);

	convert_to_human_readable (&aMB, a, MB_DEPTH);
	convert_to_human_readable (&bMB, b, MB_DEPTH);

	convert_to_human_readable (&aGB, a, GB_DEPTH);
	convert_to_human_readable (&bGB, b, GB_DEPTH);
	printf ("[%s:%d] a = %dKB, b = %dKB\n", __FILE__, __LINE__, aKB, bKB);
	printf ("[%s:%d] a = %dMB, b = %dMB\n", __FILE__, __LINE__, aMB, bMB);
	printf ("[%s:%d] a = %dGB, b = %dGB\n", __FILE__, __LINE__, aGB, bGB);

	get_net_traffic_info (recv, send);
	printf ("[%s:%d] rx_bytes = %d; rx_packets = %d; tx_bytes = %d; tx_packets = %d\n", __FILE__, __LINE__, recv[0], recv[1], send[0], send[1]);
	return 0;
}
