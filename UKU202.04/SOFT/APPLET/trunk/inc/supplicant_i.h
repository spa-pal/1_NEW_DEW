/*                                               
 * Copyright (c) 2004, Lantronix Inc. All rights reserved.
 *
 * File: supplicant_i.h
 *
 * Purpose: Common definitions across supplicant modules.
 *          
 * Created By: Vishal Kakkad
 *
 * History:
 *     09/24/2004	VMK		Initial Creation
 * 
 */

#ifndef SUPPLICANT_I_H
#define SUPPLICANT_I_H

/****************************************************************************
 *
 *                                 CONSTANTS
 *
 ****************************************************************************/
typedef enum {
  EVENT_ASSOC, 
  EVENT_DISASSOC, 
  EVENT_MIC_FAILURE,
  EVENT_BSSID_SELECTED
} supplicant_event_type;

/****************************************************************************
 *                                                                            
 *                               MACROS
 *                                                                            
 ****************************************************************************/
#define ETH_ADDR_LEN   6
#define SSIDMAXLEN     32

//#define MAX_IE_LEN  34    // limitation imposed currently by the Agere Firmware
#define MAX_IE_LEN  64
#define PMKID_LEN   16

#define PMK_LEN             32
#define NONCE_LEN           32
#define REPLAY_COUNTER_LEN  8

#define CIPHER_NONE   0x01
#define CIPHER_WEP40  0x02
#define CIPHER_WEP104 0x04
#define CIPHER_TKIP   0x08
#define CIPHER_CCMP   0x10
#define CIPHER_WRAP   0x20

#define KEY_MGMT_NONE   0x01
#define KEY_MGMT_PSK    0x02
#define KEY_MGMT_802_1X 0x04



/****************************************************************************
 *
 *                               DATA STRUCTURES
 *
 ****************************************************************************/
struct wpa_ie_data {
	WORD proto;
	WORD pairwise_cipher;
	WORD group_cipher;
	WORD key_mgmt;
	WORD capabilities;
  //WORD num_pmkid;
  //BYTE *pmkid;
};

struct wpa_ptk {
	BYTE mic_key[16];  /* EAPOL-Key MIC Key (MK) */
	BYTE encr_key[16]; /* EAPOL-Key Encryption Key (EK) */
	BYTE tk1[16];      /* Temporal Key 1 (TK1) */
	union {
		BYTE tk2[16];    /* Temporal Key 2 (TK2) */
		struct {         /* the references to the direction are from the Supplicant side. */
			BYTE rx_mic_key[8];
			BYTE tx_mic_key[8];
		} auth;
	} u;
};

/*
 * To be extended when we add RSN preauthentication support
 */
struct pmksa_cache {
  BYTE pmkid[PMKID_LEN];
  BYTE pmk[PMK_LEN];
  BYTE pmk_len;
  //int lifetime;
  //int akmp;
  BYTE auth_addr[ETH_ADDR_LEN];
  //BYTE bssid[ETH_ADDR_LEN];
};

/*
 * create a union based on what kind of data we expect to be reported in
 * events from the network driver.
 */
typedef union supplicant_event_data {
   struct {
      BOOL unicast;
   } michael_mic_failure;
   struct {
      BYTE *req_ie; 
      BYTE *resp_ie;
      WORD req_ie_len; 
      WORD resp_ie_len;
      BYTE *bssid;
   } assoc_ie_info;
   BOOL success;   
} supplicant_event_data_t;

/*-------------------------------------------------
  Runtime configuration information read from 
  WiFiCfg and also dynamically generated.
  -------------------------------------------------*/ 
struct ssid_config {
  BYTE ssid[SSIDMAXLEN+1];
  BYTE psk[PMK_LEN];
  BOOL psk_isset;
  /* bit encoded fields of config options of which one gets selected at assoc time */
  BYTE sec_proto;
  BYTE pairwise_cipher;
  BYTE group_cipher;
  BYTE key_mgmt;
  /* eap method specific config info */
  
};

/*-------------------------------------------------
            Supplicant Work Area 
  -------------------------------------------------*/ 
struct supplicant_wa {

  struct ssid_config conf;          /* runtime configuration */
  
  struct eapol_fsm *eapol_sm;       /* eapol state machine reference. */
  DWORD eapol_timer;
  WORD eapol_timer_period;
  WORD eapol_received;
  
  BYTE bssid[ETH_ADDR_LEN];         /* bssid of the station to which associated */

  /* EAPOL Key Exchange related variables */
  BOOL renew_snonce;
	BYTE snonce[NONCE_LEN];
  BYTE anonce[NONCE_LEN];           /* ANonce from the last 1/4 msg */
	
  /* Key management related variables */
  BYTE rx_replay_counter[REPLAY_COUNTER_LEN];
	BOOL rx_replay_counter_set;
  BYTE request_counter[REPLAY_COUNTER_LEN];
  
  BYTE pmk[PMK_LEN];
  BYTE pmk_len;
 
  struct wpa_ptk ptk;               /* temporal keys for data */
  BOOL ptk_set; 
  /* used mainly for first EAPOL-KEY message. to prevent attackers 
   * from changing PTK on supplicant
   */
  struct wpa_ptk tptk; 
  BOOL tptk_set;
 
  /* configuration information after association (current selection) */
  BYTE proto;
  BYTE pairwise_cipher;
  BYTE group_cipher;
  BYTE key_mgmt;
  
  /* Information Elements stored for easy reference */
  BYTE *assoc_wpa_ie;
  WORD assoc_wpa_ie_len;
  
  BYTE *ap_wpa_ie;
  WORD ap_wpa_ie_len;
   
  /* MIC Failure Related variable */
  BOOL countermeasures;
  DWORD countermeasures_timer;
  DWORD last_michael_mic_error;
  
  /* Global */
  //BOOL reassociate;
  BYTE supp_state;
  WORD portNum;     /* interface no. of this instance.*/  
};

/****************************************************************************
 *                                                                            
 *                               PROTOTYPES
 *                                                                            
 ****************************************************************************/

/* Exported Functions */
//void supplicant_eapol_input(void *ctx, BYTE *buf, WORD len);

//void hexdump(const char *title, const BYTE *buf, WORD len);
BOOL supplicant_sigEvent(supplicant_event_type event, supplicant_event_data_t *data);


#endif