#ifndef SHA1_H
#define SHA1_H

#include <style.h>

#define size_t unsigned int

#define SHA1_MAC_LEN 20

/* adapted from Hyperion source */
typedef struct {
  unsigned long v[5];
  struct { unsigned long hi; unsigned long lo; } n;
  unsigned char buf[64];
  int ncached;
} SHA1_CTX;

//void SHA1Init(SHA1_CTX *context);
//void SHA1Update(SHA1_CTX *context, unsigned char *data, DWORD len);
//void SHA1Final(unsigned char digest[20], SHA1_CTX* context);
//void SHA1Transform(DWORD state[5], unsigned char buffer[64]);

void sha1_mac(unsigned char *key, unsigned int key_len,
	      unsigned char *data, unsigned int data_len,
	      unsigned char *mac);
void hmac_sha1_vector(unsigned char *key, unsigned int key_len,
		      size_t num_elem, unsigned char *addr[],
		      unsigned int *len, unsigned char *mac);
void hmac_sha1(unsigned char *key, unsigned int key_len,
	       unsigned char *data, unsigned int data_len,
	       unsigned char *mac);
void sha1_prf(unsigned char *key, unsigned int key_len,
	      char *label, unsigned char *data, unsigned int data_len,
	      unsigned char *buf, size_t buf_len);
void pbkdf2_sha1(char *passphrase, char *ssid, size_t ssid_len, int iterations,
		 unsigned char *buf, size_t buflen);

#endif /* SHA1_H */
