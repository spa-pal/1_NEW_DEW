
#define MAXKEYSIZE		(MAXKEYCOLUMNS*4)
#define BLOCKSIZE 		(BLOCKCOLUMNS<<2)


#define BLOCKCOLUMNS  4
#define MAXKEYCOLUMNS	   	8
#define MAXROUNDS	   	14

typedef BYTE cr_block[BLOCKSIZE];
typedef BYTE cr_blockMultiDim[BLOCKCOLUMNS][4];
typedef struct { 
	BYTE keyColumns;			
	BYTE blockColumns;		 
	BYTE rounds;
	cr_blockMultiDim roundKeys[MAXROUNDS+1];
	} cr_keyStruct;


#ifdef KAT_MCT
void rijndaelEncryptRound ( cr_keyStruct *keyStr, cr_block a, int rds);
void rijndaelDecryptRound ( cr_keyStruct *keyStr, cr_block a, int rds);
#define rijndaelEncrypt(a, b)	 rijndaelEncryptRound(a, b, rounds)
#define rijndaelDecrypt(a, b)	 rijndaelDecryptRound(a, b, 0)
#endif

#ifdef PC				 // define PC when running tests on a PC
#define ENCRYPT_MODE_ECB
#define ENCRYPT_MODE_OFB
#endif
#define ENCRYPT_MODE_CBC
#define ENCRYPT_MODE_CFB



void aes_key_init( cr_keyStruct *keyStr, BYTE *key, int keyLen);
void aes_cipher_init(void);

#define CR_CIPHER_INIT()   				aes_cipher_init()
#define CR_KEY_INIT(a, b, c)   			aes_key_init(a, b, c)

#ifdef ENCRYPT_MODE_ECB
void aes_block_encrypt_ECB(cr_keyStruct *keyStr, cr_block *plainText,
int nBlocks, cr_block *cipherText);

void aes_block_decrypt_ECB(cr_keyStruct *keyStr, cr_block *cipherText,
int nBlocks, cr_block *plainText);

#define CR_BLOCK_ENCRYPT_ECB(a, b, c, d)     	aes_block_encrypt_ECB(a, b, c, d)		
#define CR_BLOCK_DECRYPT_ECB(a, b, c, d)  		aes_block_decrypt_ECB(a, b, c, d)
#endif

#ifdef ENCRYPT_MODE_CBC
void aes_block_encrypt_CBC(cr_keyStruct *keyStr, cr_block *initVec, cr_block *plainText,
int nBlocks, cr_block *cipherText);

void aes_block_decrypt_CBC(cr_keyStruct *keyStr, cr_block *initVec, cr_block *cipherText,
int nBlocks, cr_block *plainText);

#define CR_BLOCK_ENCRYPT_CBC(a, b, c, d, e)     aes_block_encrypt_CBC(a, b, c, d, e)
#define CR_BLOCK_DECRYPT_CBC(a, b, c, d, e)  	aes_block_decrypt_CBC(a, b, c, d, e)
#endif

void aes_byte_encrypt(cr_keyStruct *keyStr, cr_block *initVec, BYTE *plainText,
int nBytes, BYTE *cipherText, BYTE *left, enum cr_mode mode);


#ifdef ENCRYPT_MODE_OFB
#define CR_BYTE_ENCRYPT_OFB(a, b, c, d, e, f)	aes_byte_encrypt(a, b, c, d, e, f, 0)
#define CR_BYTE_DECRYPT_OFB(a, b, c, d, e, f)	aes_byte_encrypt(a, b, c, d, e, f, 0) 
#endif
#ifdef ENCRYPT_MODE_CFB
#define CR_BYTE_ENCRYPT_CFB(a, b, c, d, e, f)	aes_byte_encrypt(a, b, c, d, e, f, 1)
#define CR_BYTE_DECRYPT_CFB(a, b, c, d, e, f)	aes_byte_encrypt(a, b, c, d, e, f, 2)
#endif
