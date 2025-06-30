#include <iostream>
#include <cstdio>
#include <climits>
#include <string.h>
#include <stdint.h>

class HexDump
{
public:
    HexDump()
    {

    }

    ~HexDump()
    {

    }

    void hexdump(char *s, size_t size, const char* msg)
    {
        char buf[16]; // 4 hex data and '\0'
        char pbuf[8]; // printable character buffer
        char *p = &buf[0];
        char *q = &pbuf[0];
        size_t nwritten;

        memset(buf, 0, sizeof(buf));
        memset(pbuf, 0, sizeof(pbuf));

        if(msg)
        {
            printf("%s\n", msg);
        }

        printf("== hexdump (%d) ==\n", size);

        for(size_t i = 0; i < size; ++i)
        {
            nwritten = sprintf(p, "%02x ", (uint8_t)s[i]);
            if(isprint((int)s[i]))
            {
                sprintf(q, "%c", (uint8_t)s[i]);
            }
            else
            {
                sprintf(q, ".");
            }

            if((i != 0) && (((i + 1) % 4) == 0))
            {
                printf("%-12s %s\n", buf, pbuf);
                memset(buf, 0, sizeof(buf));
                memset(pbuf, 0, sizeof(pbuf));
                p = &buf[0];
                q = &pbuf[0];
            }
            else
            {
                p += nwritten;
                q++;
        }
            }

        if (buf[0] != '\0')
        {
            printf("%-12s %s\n", buf, pbuf);
        }
    }
};


int main(int argc, char** argv)
{
    enum
    {
        TEST_SIZE = 2,
    };
    HexDump hexDump;
    char test[4 * TEST_SIZE];

    for(int i = 0;i < 4 * TEST_SIZE;i += 4)
    {
        test[i] = i & 0xff;
        test[i + 1] = (i + 4) & 0xff;
        test[i + 2] = (i + 8) & 0xff;
        test[i + 3] = (i + 12) & 0xff;
        printf("[%s:%d] test [%d] = %d(/%d)\n", __FILE__, __LINE__, i, test[i], i & 0xff);
        printf("[%s:%d] test [%d] = %d(/%d)\n", __FILE__, __LINE__, i + 1, test[i + 1], (i + 4) & 0xff);
        printf("[%s:%d] test [%d] = %d(/%d)\n", __FILE__, __LINE__, i + 2, test[i + 2], (i + 8) & 0xff);
        printf("[%s:%d] test [%d] = %d(/%d)\n", __FILE__, __LINE__, i + 3, test[i + 3], (i + 12) & 0xff);
    }
    for(int i = 0;i < 4 * TEST_SIZE;i++)
    {
        printf("[%s:%d] test [%d] = %d\n", __FILE__, __LINE__, i, test[i]);
    }

    hexDump.hexdump(test, 4 * TEST_SIZE, "test");

    return 0;
}