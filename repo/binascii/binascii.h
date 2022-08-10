#ifndef __BINASCII_H__
#define __BINASCII_H__

enum {BINASCII_OK = 0};

#define BINASCII_HEXLIFY_OUT_SIZE(s)	((s) * 2)
#define BINASCII_UNHEXLIFY_OUT_SIZE(s)	((s) / 2)


int binascii_hexlify(const unsigned char *in, const int inlen, char *out);

int binascii_unhexlify(const char *in, const int inlen, unsigned char *out);

#endif /* _BINASCII_H__ */

