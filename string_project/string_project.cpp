// string_project.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int find_value(char *ptr, char* target, int target_len, const char* key)
{
	int place = 0;
	ptr = (char*)strstr(ptr, key);
	if (ptr == NULL)
	{
		printf("[%s:%d] Not found key(%s)\n", __FILE__, __LINE__, key);
		return -1;
	}
	ptr = strstr(ptr, "\"");
	printf("[%s:%d] ptr =>> %s\n", __FILE__, __LINE__, ptr);
	if (*ptr == '\"') {
		ptr++;
		while (*ptr && *ptr != '\"') {
			if (*ptr == '\\') {
				if (!ptr[1])
					break;
				ptr += 2;
			}
			else {
				place++;
				if (place >= target_len)
				{
					*target = 0;
					while (*ptr != '\"')
					{
						place++;
						ptr++;
					}
					printf("Smaller target(%d) than value (%s:%d)\n", target_len, key, place);
					return 0;
				}
				*target = *ptr;
				ptr++;
				target++;
			}
			printf("[%s:%d] ptr =>> %s\n", __FILE__, __LINE__, ptr);
		}
	}
	*target = 0;
	return 1;
}

int main() {
	char search = 's';
	const char* searchs = "s";
	char str[] = "This is a sample string";
	char* pch;
	printf("Looking for the %s character in \"%s\"...\n", searchs, str);

	pch = strstr(str, searchs);

	while (pch != NULL) {
		printf("strstr found at %d(%s)\n", pch - str + 1, pch);
		pch = strstr(pch + strlen (searchs), searchs);
	}

	printf ("\n\n");
	printf("Looking for the %c character in \"%s\"...\n", search, str);
	pch = strchr(str, search);

	while (pch != NULL) {
		printf("strchr found at %d(%s)\n", pch - str + 1, pch);
		pch = strchr(pch + 1, search);
	}

	const char* test = "WWW - Authenticate: Digest realm = \"AXIS_WS_ACCC8E18B499\", nonce = \"LIikbJCGBQA=6ad7acd11c5085b56d2521074feeaceeb4d0532a\", algorithm = MD5, qop = \"auth\"";
	const char* search_test = "realm";
	char* ptr = (char*)test;
	char target[20];
	int target_len = sizeof(target);

	if (0 >= find_value(ptr, target, target_len, search_test))
	{
		printf("Failed to find value (%s)\n", search_test);
	}

	printf("[%s:%d] target = %s", __FILE__, __LINE__, target);

	return 0;
}
// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
