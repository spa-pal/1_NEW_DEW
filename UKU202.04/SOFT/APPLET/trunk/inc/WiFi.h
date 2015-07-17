/*******************************************************************
 *
 *    DESCRIPTION:
 *
 *    AUTHOR: Pietje Bel
 *
 *    HISTORY:
 *
 *******************************************************************/
#ifndef COUNTRIES

/** include files **/

/** local definitions **/
extern int NW_DRV;

#define COUNTRIES 6
#ifdef MARVELL
#define WIFI_DATARATES 8
#else
#define WIFI_DATARATES 4
#endif

enum authentication_options  { open, shared, PEAP, TTLS, TLS, LEAP, EAP_FAST };
enum security_options  { no_sec, wep, wpa, ieee802_11i };
enum encryption_options   {no_enc, wep64, wep128, TKIP, CCMP, WRAP  };
enum keytype_options { hex, passphrase };


/** default settings **/

/** external functions **/
/** external data **/

/** internal functions **/

/** public data **/
enum country_options  {us, fr, jp, ot, sp, ca };
// Configuration
#define SSIDMAXLEN 32
typedef struct  {
// 0
  unsigned enabled:1;
  unsigned power_level:2;
  unsigned datarate:3;
  unsigned autorate:1;
  unsigned power_management:1;
// 1
//  unsigned ibss_creation_enabled:1;
  unsigned ibss:1;
  unsigned country:3;
  unsigned ibss_channel:4;
// 2
  unsigned security:2;
  unsigned authentication:3;
  unsigned p_encryption:3;
//3
  char ssid[SSIDMAXLEN+1];
// 36
  char ibssid[SSIDMAXLEN+1];
// 69
  BYTE g_encryption;
// 70
  BYTE keylen;
// 71
  unsigned keytype:2;
// 72
  BYTE TXkeyInd;
// 73
  char spacer[60];
// 133
  union {
    BYTE key[32];
    char passphrase[64];  // 63 chars and a terminator
  };
// 165
  } WiFiCfg_t;

typedef struct Country_t {
  char abbreviation[2];
  unsigned lowest_channel:4;
  unsigned highest_channel:4;
  };

extern WiFiCfg_t WiFiCfg;
extern const struct Country_t Country[COUNTRIES];
/** private data **/

/** public functions **/
void defaultWiFiSettings(int type, int intf);
void saveWiFiSettings(void);
void loadWiFiSettings(void);
void EnterWiFiSettings(void);
void ShowWiFiSettings(void);

/** private functions **/


typedef struct  {
  unsigned char Key[32];
  int Length;
  int Index;
  int Type;
  BYTE Tx;
  BYTE RSC[8];
//  BYTE Address[6];
  } KeyIdentifier;



#define WPA_IE_LEN  34

typedef struct {
  BYTE sta_wpa_ie_len;
  BYTE STA_WPA_IE[WPA_IE_LEN];
  BYTE ap_wpa_ie_len;
  BYTE AP_WPA_IE[WPA_IE_LEN];
  BYTE bssid[6];
} AssociationInfo_t;

#define SCANRESULTSSIZE 1024

typedef struct {
  char ssid[SSIDMAXLEN+1];
  BYTE *results;
//  BYTE results[SCANRESULTSSIZE];
  BYTE no_of_sets;
  } ScanResults_t;

#ifdef SelectionList_t_defined

extern SelectionList_t SelList_Netmode;
extern SelectionList_t SelList_Topology;
extern SelectionList_t SelList_Security_AdHoc;
extern SelectionList_t SelList_Security_Infra;
extern SelectionList_t SelList_Authentication;
extern SelectionList_t SelList_Authentication_WEP;
extern SelectionList_t SelList_Authentication_80211i;
extern SelectionList_t SelList_Enc_WEP;
extern SelectionList_t SelList_Enc_WPA;
//extern SelectionList_t SelList_Enc_WPA_Group;
extern SelectionList_t SelList_Enc_80211i;
extern SelectionList_t SelList_Enc_80211i_Pair;
extern SelectionList_t SelList_Enc_80211i_Group;
extern SelectionList_t SelList_TX_Auto;
extern SelectionList_t SelList_TX_DataRate;
//extern SelectionList_t SelList_TX_Power = { "TX Power level", " dBm", 0, 3, "6", "9", "12", "15" };
#endif

#endif

