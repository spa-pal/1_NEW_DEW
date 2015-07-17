#include "bldFlags.h"
#include <style.h>      /* definitions for programming style */
#include <string.h>
#include <nethw.h>
#include <kernel.h>
#include <io.h>
#include <globals.h>
#include <WiFi.h>
#include <setpar.h>
#include <netdrv.h>

	/* keep in sync with setpar.c */
#define DEFAULT2FACTORY 0
#define DEFAULT2MENU    1

extern NET_HW_T nethw;
extern BYTE scr_unit[];
extern WORD radio_fw_rev;

WiFiCfg_t WiFiCfg;
const struct Country_t Country[COUNTRIES] = {'U','S',1,11, 'F','R',10,13, 'J','P',1,14, 'O','T',1,13,
    'S','P',10,11, 'C','A',1,11};

void put_hex8s(char *buf, int len);
void GetKey(int keylen);


// Option selection lists
SelectionList_t SelList_Netmode = { "Network mode", "", 0, 1, "Wired Only", "Wireless Only" };
SelectionList_t SelList_Topology = { "Topology", "", 0, 1, "Infrastructure", "Ad-Hoc" };
SelectionList_t SelList_Security_AdHoc = { "Security suite", "", 0, 1, "none", "WEP" };
#ifdef MARVELL
SelectionList_t SelList_Security_Infra = { "Security suite", "", 0, 3, "none", "WEP", "WPA", "WPA2/802.11i" };
#else
SelectionList_t SelList_Security_Infra = { "Security suite", "", 0, 2, "none", "WEP", "WPA" };
#endif
SelectionList_t SelList_Authentication_WEP = { "Authentication", "", 0, 1, "open/none", "shared" };
SelectionList_t SelList_Authentication_80211i = { "Authentication", "", 1, 2, "PSK", "PEAP" };
SelectionList_t SelList_Authentication = { "Authentication", "", 0, 2, "open/none", "PSK", "PEAP" };
SelectionList_t SelList_Enc_WEP = { "Encryption", "", 1, 2, "WEP64", "WEP128" };
//SelectionList_t SelList_Enc_WPA_Group = { "Group (multicast) encryption", "", 1, 3, "WEP64", "WEP128", "TKIP" };
SelectionList_t SelList_Enc_WPA = { "Encryption", "", 0, 1, "TKIP", "TKIP+WEP" };
SelectionList_t SelList_Enc_80211i_Pair = { "Pairwise (unicast) encryption", "", 3, 4, "TKIP", "CCMP" };
SelectionList_t SelList_Enc_80211i_Group = { "Group (multicast) encryption", "", 1, 4, "WEP64", "WEP128", "TKIP", "CCMP" };
SelectionList_t SelList_Enc_80211i = { "Encryption", "", 0, 4, "CCMP", "CCMP+TKIP", "CCMP+WEP", "TKIP", "TKIP+WEP" };
SelectionList_t SelList_TX_Auto = { "TX Data rate", "", 0, 1, "fixed", "auto fallback" };
#ifdef MARVELL
SelectionList_t SelList_TX_DataRate = { "TX Data rate", " Mbps", 0, 7, "1", "2", "5.5", "11", "18", "24", "36", "54" };
#else
SelectionList_t SelList_TX_DataRate = { "TX Data rate", " Mbps", 0, 7, "1", "2", "5.5", "11" };
#endif
//SelectionList_t SelList_TX_Power = { "TX Power level", " dBm", 0, 3, "6", "9", "12", "15" };



static BYTE Setup8[252];
extern BYTE SetupOEM[];
extern BYTE S_tmp[];

#define Tmp_WiFiCfg   (*(WiFiCfg_t *)Setup8)


void defaultWiFiSettings(int type, int intf)
{
  if(type==DEFAULT2FACTORY)
  {
    memset(&Tmp_WiFiCfg, 0, sizeof(Tmp_WiFiCfg));
    if (intf == 2)
      Tmp_WiFiCfg.enabled = TRUE;
    strcpy(Tmp_WiFiCfg.ssid, "LTRX_IBSS");
    Tmp_WiFiCfg.ibss = TRUE;
    Tmp_WiFiCfg.ibss_channel = 11;
//    Tmp_WiFiCfg.country = us;
//  Tmp_WiFiCfg.authentication = open;  // implied in memset
//    Tmp_WiFiCfg.p_encryption = wep64;
//    memcpy(&(Tmp_WiFiCfg.key), nethw.hw_addr+1, 5);
//  Tmp_WiFiCfg.displaykey = 0;
  }
  Tmp_WiFiCfg.datarate = 3;
  Tmp_WiFiCfg.autorate = TRUE;
  Tmp_WiFiCfg.power_level = 3;
  Tmp_WiFiCfg.power_management = 0;

}


void saveWiFiSettings(void)
{
  EE_Write(Setup8,1024,126);
  EE_Write(Setup8+126,1152,126);
}



void loadWiFiSettings(void)
{
  if(EE_Read(Setup8,1024,126) || EE_Read(Setup8+126,1152,126))
  {
    defaultWiFiSettings(DEFAULT2FACTORY, WIRELESS_ENABLED);
    saveWiFiSettings();
  }
  Tmp_WiFiCfg.country =  SetupOEM[10];
  memcpy(&WiFiCfg, Setup8, sizeof(WiFiCfg));
}



void EnterWiFiSettings(void)
{
  WORD Tmp;

  putcrlf();
  if (!Tmp_WiFiCfg.enabled)
  {
    printf("WLAN is disabled\r\n");
    return;
  }

  Tmp_WiFiCfg.ibss = SelectFromList(&SelList_Topology, (WORD)Tmp_WiFiCfg.ibss);

  printf("Network name (SSID)", Tmp_WiFiCfg.ssid);
  getstrt(Tmp_WiFiCfg.ssid, SSIDMAXLEN+1);
  strcpy(Tmp_WiFiCfg.ibssid,Tmp_WiFiCfg.ssid);

  if(Tmp_WiFiCfg.ibss)
  {
    Tmp_WiFiCfg.ibss_channel = SelectFromRange("Channel", Country[Tmp_WiFiCfg.country].lowest_channel,
       Country[Tmp_WiFiCfg.country].highest_channel, Tmp_WiFiCfg.ibss_channel);
  }

  Tmp_WiFiCfg.security = SelectFromList(Tmp_WiFiCfg.ibss?&SelList_Security_AdHoc:&SelList_Security_Infra, Tmp_WiFiCfg.security);

  switch(Tmp_WiFiCfg.security)
  {
    case no_sec:
    {
      Tmp_WiFiCfg.p_encryption = no_enc;
      Tmp_WiFiCfg.authentication = open;
      break;
    }
    case wep:
    {
      {
        Tmp_WiFiCfg.authentication = SelectFromList(&SelList_Authentication_WEP, Tmp_WiFiCfg.authentication);
      }
      Tmp_WiFiCfg.p_encryption = SelectFromList(&SelList_Enc_WEP, Tmp_WiFiCfg.p_encryption);
      GetKey((Tmp_WiFiCfg.p_encryption==wep64)?5:13);
      Tmp_WiFiCfg.TXkeyInd = SelectFromRange("TX Key index", 1, 4, Tmp_WiFiCfg.TXkeyInd+1) - 1;
      break;
    }
    case wpa:
    {
      Tmp_WiFiCfg.authentication = shared;
      GetKey(32);
      Tmp_WiFiCfg.p_encryption = TKIP;
      Tmp_WiFiCfg.g_encryption = (SelectFromList(&SelList_Enc_WPA, (Tmp_WiFiCfg.g_encryption==TKIP)?0:1)==0)?TKIP:wep64;
      break;
    }
#ifdef MARVELL
    case ieee802_11i:
    {
#ifdef EAP_AUTH_ENABLED
      Tmp_WiFiCfg.authentication = SelectFromList(&SelList_Authentication_80211i, Tmp_WiFiCfg.authentication);
#else
      Tmp_WiFiCfg.authentication = shared;
#endif

      if(Tmp_WiFiCfg.authentication == shared) GetKey(32);
      else
      {
      }

      if(Tmp_WiFiCfg.p_encryption==CCMP)
      {
        Tmp = 0;
        if(Tmp_WiFiCfg.g_encryption==TKIP) Tmp = 1;
        if((Tmp_WiFiCfg.g_encryption==wep64) || (Tmp_WiFiCfg.g_encryption==wep128)) Tmp = 2;
      }
      else
      {
        Tmp = 3;
        if((Tmp_WiFiCfg.g_encryption==wep64) || (Tmp_WiFiCfg.g_encryption==wep128)) Tmp = 4;
      }

      Tmp = SelectFromList(&SelList_Enc_80211i, Tmp);

      switch(Tmp)
      {
        case 0:
          Tmp_WiFiCfg.p_encryption = CCMP;
          Tmp_WiFiCfg.g_encryption = CCMP;
          break;
        case 1:
          Tmp_WiFiCfg.p_encryption = CCMP;
          Tmp_WiFiCfg.g_encryption = TKIP;
          break;
        case 2:
          Tmp_WiFiCfg.p_encryption = CCMP;
          Tmp_WiFiCfg.g_encryption = wep64;
          break;
        case 3:
          Tmp_WiFiCfg.p_encryption = TKIP;
          Tmp_WiFiCfg.g_encryption = TKIP;
          break;
        case 4:
          Tmp_WiFiCfg.p_encryption = TKIP;
          Tmp_WiFiCfg.g_encryption = wep64;
          break;
      }

      break;
    }
#endif


  }

  Tmp_WiFiCfg.autorate = SelectFromList(&SelList_TX_Auto, Tmp_WiFiCfg.autorate);
  Tmp_WiFiCfg.datarate = SelectFromList(&SelList_TX_DataRate, Tmp_WiFiCfg.datarate);

  if(!Tmp_WiFiCfg.ibss)
  {
    printf("Enable power management");
    Tmp_WiFiCfg.power_management = getynt(Tmp_WiFiCfg.power_management);
  }

}


void ShowWiFiSettings(void)
{
  WORD Tmp;
  printf("\n\r\n*** WLAN ");
  printf("\r\nWLAN: "); printf(Tmp_WiFiCfg.enabled?"enabled":"disabled");
  ShowFromList(&SelList_Topology, (WORD)Tmp_WiFiCfg.ibss);
  printf("\r\nNetwork name: %s", Tmp_WiFiCfg.ssid);
  printf("\r\nCountry: %c%c", Country[Tmp_WiFiCfg.country].abbreviation[0], Country[Tmp_WiFiCfg.country].abbreviation[1]);
  if(Tmp_WiFiCfg.ibss) printf("\r\nChannel: %d", Tmp_WiFiCfg.ibss_channel);
  ShowFromList(Tmp_WiFiCfg.ibss?&SelList_Security_AdHoc:&SelList_Security_Infra, Tmp_WiFiCfg.security);

  switch(Tmp_WiFiCfg.security)
  {
    case wep:

      {
        ShowFromList(&SelList_Authentication_WEP, Tmp_WiFiCfg.authentication);
      }

      ShowFromList(&SelList_Enc_WEP, Tmp_WiFiCfg.p_encryption);
      printf("\r\nTX Key index: %d", Tmp_WiFiCfg.TXkeyInd+1);


      break;
    case wpa:
      printf("\r\nAuthentication: PSK");
      ShowFromList(&SelList_Enc_WPA, (Tmp_WiFiCfg.g_encryption==TKIP)?0:1);
      break;
#ifdef MARVELL
    case ieee802_11i:
    {
      ShowFromList(&SelList_Authentication_80211i, Tmp_WiFiCfg.authentication);

      if(Tmp_WiFiCfg.p_encryption==CCMP)
      {
        Tmp = 0;
        if(Tmp_WiFiCfg.g_encryption==TKIP) Tmp = 1;
        if((Tmp_WiFiCfg.g_encryption==wep64) || (Tmp_WiFiCfg.g_encryption==wep128)) Tmp = 2;
      }
      else
      {
        Tmp = 3;
        if((Tmp_WiFiCfg.g_encryption==wep64) || (Tmp_WiFiCfg.g_encryption==wep128)) Tmp = 4;
      }

      ShowFromList(&SelList_Enc_80211i, Tmp);

      if(Tmp_WiFiCfg.authentication == PEAP)
      {

      }

      break;
    }
#endif
    default:
      break;
  }

    ShowFromList(&SelList_TX_DataRate, Tmp_WiFiCfg.datarate);
  printf(" %s",Tmp_WiFiCfg.autorate?"auto fallback":"fixed");
  printf("\r\nPower management: ");
  if(!Tmp_WiFiCfg.ibss)
  {
    printf((Tmp_WiFiCfg.power_management)?"enabled":"disabled");
  }
  else printf("not supported in adhoc mode");

}


void put_hex8s(char *buf, int len)
{
  WORD i;
  for (i=0;i<len;i++) printf("%2x ",*buf++);
}


void GetKey(int keylen)
{
  WORD j;
  printf("Display current key");
  if(getynt(0))
  {
    if(Tmp_WiFiCfg.keytype==hex) put_hex8s(Tmp_WiFiCfg.key, keylen);
    else putstr(Tmp_WiFiCfg.passphrase);
    putcrlf();
  }

  printf("Change Key");
  if(getynt(0))
  {
    Tmp_WiFiCfg.keytype = SelectFromRange("Key type 0=hex, 1=passphrase", 0, 1, Tmp_WiFiCfg.keytype);

    printf("Enter Key: ");
    Tmp_WiFiCfg.passphrase[0]=0;
    if(Tmp_WiFiCfg.keytype)
    {
//      getstrt(Tmp_WiFiCfg.passphrase,64);
      getstr(Tmp_WiFiCfg.passphrase,64);
//      if((strlen(Tmp_WiFiCfg.passphrase)<20) && (keylen==32))
      if(strlen(Tmp_WiFiCfg.passphrase)<20)
      {
        printf("It is strongly recommended to use a passphrase of 20 chars or more!\r\r\n\n");
      }
    }
    else
    {
      gethex8k(Tmp_WiFiCfg.key);
      for (j=1; j<keylen; j++)
      {
        putch('-');
        gethex8k(Tmp_WiFiCfg.key+j);
      }
      putcrlf();
    }
  }
}

/* Set/Show Function invoked from stdpar.h for determining network mode. */
int set_netmode()
{
  int i, k;

//  if (WIRED_WLAN_EN)
  {
    i = Tmp_WiFiCfg.enabled;
    putcrlf();
    i = SelectFromList(&SelList_Netmode, i);

    Tmp_WiFiCfg.enabled = i & 0x01;
  }
//  else
//  {
//    i = 1;
//    Tmp_WiFiCfg.enabled = 1;
//  }

  return i;
}


void show_netmode()
{
  int i;

  i = Tmp_WiFiCfg.enabled;
  ShowFromList(&SelList_Netmode, i);
}

WORD SelectFromList(SelectionList_t *List, WORD StoredSel)
{
  WORD CurSel, Option;

  if(StoredSel < List->LowestIndex) StoredSel = List->LowestIndex;
  if(StoredSel > List->HighestIndex) StoredSel = List->HighestIndex;
get_input:

  printf("%s: %d=%s", List->Title, List->LowestIndex, List->Options[0]);
  for(Option = List->LowestIndex + 1; Option <= List->HighestIndex; Option++)
  {
    printf(", %d=%s", Option, List->Options[Option-List->LowestIndex]);
  }
  putstr(List->Unit);
  CurSel = StoredSel;
  getint(0,&CurSel);
  putcrlf();
  if((CurSel<List->LowestIndex) || (CurSel>List->HighestIndex))
  {
    print_allowed(List->LowestIndex,List->HighestIndex);
    goto   get_input;
  }
  return CurSel;
}

void ShowFromList(SelectionList_t *List, WORD StoredSel)
{
  printf("\r\n%s: %s%s", List->Title, List->Options[StoredSel-List->LowestIndex], List->Unit);
}

WORD SelectFromRange(char *List, BYTE LowestAllowed, BYTE HighestAllowed, WORD StoredSel)
{
  WORD CurSel;

  if(StoredSel < LowestAllowed) StoredSel = LowestAllowed;
  if(StoredSel > HighestAllowed) StoredSel = HighestAllowed;
get_input:
  putstr(List);
  CurSel = StoredSel;
  getint(0,&CurSel);
  putcrlf();
  if((CurSel<LowestAllowed) || (CurSel>HighestAllowed))
  {
    print_allowed(LowestAllowed,HighestAllowed);
    goto   get_input;
  }
  return CurSel;
}

void print_allowed(int low, int high)
{
  printf("  Only %d - %d allowed!\r\n",low,high);
}
