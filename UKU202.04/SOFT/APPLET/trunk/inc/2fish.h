#define BYTE unsigned char
#define DWORD unsigned long

#define MAXKEYSIZE		(MAXKEYCOLUMNS*4)


enum cr_mode { cr_ofb=0, cr_cfb_e=1, cr_cfb_d=2 };



#define BLOCKCOLUMNS		4
#define MAXKEYCOLUMNS	   	8
#define TF_ROUNDS		16
#define tf_key_struct cr_keyStruct

#ifdef TF_CRYP_C
const int cr_keyLengths[3] = { 128, 192, 256 };
#else
extern const int cr_keyLengths[3];

#define CR_KEY_INIT(a, b, c)   					tf_key_prep(a, b, c)
#define CR_CIPHER_INIT()
#define CR_BLOCK_ENCRYPT_ECB(a, b, c, d)     	tf_block_encrypt(NULL, a, b, c, d)
#define CR_BLOCK_DECRYPT_ECB(a, b, c, d)  		tf_block_decrypt(NULL, a, b, c, d)
#define CR_BLOCK_ENCRYPT_CBC(a, b, c, d, e)     tf_block_encrypt( b, a, c, d, e)
#define CR_BLOCK_DECRYPT_CBC(a, b, c, d, e)  	tf_block_decrypt( b, a, c, d, e)
#define CR_BYTE_ENCRYPT_OFB(a, b, c, d, e, f)	tf_byte_stream(b, a, c, d, e, f, cr_ofb)
#define CR_BYTE_DECRYPT_OFB(a, b, c, d, e, f)	tf_byte_stream(b, a, c, d, e, f, cr_ofb) // encrypt for decrypt not a typo.
#define CR_BYTE_ENCRYPT_CFB(a, b, c, d, e, f)	tf_byte_stream(b, a, c, d, e, f, cr_cfb_e)
#define CR_BYTE_DECRYPT_CFB(a, b, c, d, e, f)	tf_byte_stream(b, a, c, d, e, f, cr_cfb_d)

#endif

typedef BYTE cr_block[BLOCKCOLUMNS*4];
#define  tf_block     cr_block

typedef struct {
  enum tf_keylen keyLen;
  DWORD sboxKeys[4];
  struct {
    tf_block InputWhiten;
    tf_block OutputWhiten;
    DWORD RoundSubKeys[2*TF_ROUNDS];
  } subKeys;
} cr_keyStruct;


void pascal tf_key_prep(tf_key_struct *keystr, void *key, enum tf_keylen keyLen);

void pascal tf_block_encrypt(tf_block *tmpb, tf_key_struct *keystr, tf_block *input,
int nBlocks, tf_block *output);

void pascal tf_block_decrypt(tf_block *tmpb, tf_key_struct *keystr, tf_block *input,
int nBlocks, tf_block *output);

void pascal tf_byte_stream(tf_block *tmpb, tf_key_struct *keystr, BYTE *input,
int nBytes, BYTE *output, BYTE *pstat, enum tf_stream_mode mode);



