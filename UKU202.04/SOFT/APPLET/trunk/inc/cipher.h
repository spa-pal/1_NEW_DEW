#include <rijndael.h>

/*

typedef struct {
  void (*encrypt_block)();
  void (*decrypt_block)();
  void *KeyStruct;
  BYTE BlockLen;
} CipherContext_t;

enum cr_mode { cr_ofb=0, cr_cfb_e=1, cr_cfb_d=2 };


#define CFB_encrypt(CipherContext, initVec, input, nBytes, output, left)    \
    byte_encrypt(CipherContext, initVec, input, nBytes, output, left, cr_cfb_e)


// do we need to switch input, output to make it more in line with the block encrypt functions?
!#define CFB_decrypt(CipherContext, initVec, input, nBytes, output, left)    \
    byte_encrypt(CipherContext, initVec, input, nBytes, output, left, cr_cfb_d)

#define OFB_encrypt(CipherContext, initVec, input, nBytes, output, left)    \
    byte_encrypt(CipherContext, initVec, input, nBytes, output, left, cr_ofb)


// do we need to switch input, output to make it more in line with the block encrypt functions?
!#define OFB_decrypt(CipherContext, initVec, input, nBytes, output, left)    \
    byte_encrypt(CipherContext, initVec, input, nBytes, output, left, cr_ofb)


void byte_encrypt(CipherContext_t *CipherContext, BYTE *initVec, BYTE *input,
  int nBytes, BYTE *output, BYTE *left, enum cr_mode mode);


void ECB_encrypt(CipherContext_t *CipherContext, BYTE *plainText, int nBlocks, BYTE *cipherText);
void ECB_decrypt(CipherContext_t *CipherContext, BYTE *plainText, int nBlocks, BYTE *cipherText);
void CBC_encrypt(CipherContext_t *CipherContext, BYTE *initVec, BYTE *plainText, int nBlocks, BYTE *cipherText);
void CBC_decrypt(CipherContext_t *CipherContext, BYTE *initVec, BYTE *plainText, int nBlocks, BYTE *cipherText);

*/


#if DEBUG_CIPHER
  BYTE KEK[16] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf };
  BYTE plain[16] = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff };
  BYTE cipher[24];
#endif  
/*
      aes_wrap(KEK, 128, plain, 2, cipher);
            
      aes_unwrap(KEK, 128, cipher, 3, plain);      
*/


#define aes_wrap(a,b,c,d,e) Wrap(a,b,c,d,e)
#define aes_unwrap(a,b,c,d,e) UnWrap(a,b,e,d,c)

WORD Wrap(BYTE *KEK, int KEKLen, BYTE *PlainText, WORD NoBlocks, BYTE *CipherText);
BOOL UnWrap(BYTE *KEK, int KEKLen, BYTE *PlainText, WORD NoBlocks, BYTE *CipherText);




