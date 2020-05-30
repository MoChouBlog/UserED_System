
#include <stdint.h>
#include <string.h>
//message为明文，len为明文长度，
//output为明文的MD5值（固定128位）
void md5 (const char *message, long len, char *output);
