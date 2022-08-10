#include <stdio.h>
#include <string.h>

#include "binascii.h"

int main(void) {
    unsigned char hello[] = "hello";
    char hex[sizeof(hello) * 2 + 1];
    memset(hex, 0, sizeof(hex));
    // bzero(hex, sizeof(hex));         According to some blogs, bzero is deprecated, use memset instead.

    binascii_hexlify(hello, sizeof(hello), hex);
    printf("hexlify: %s\n", hex);

    memset(hello, 0, sizeof(hello));
    // bzero(hello, sizeof(hello));
    binascii_unhexlify(hex, sizeof(hex), hello);
    printf("unhexlify: %s\n", hello);

    return 0;
}
