/**********************************************************/
/* #define N0 for 83902 driver                            */
/* #define N1 for 89100 cirrus driver (never really used) */
/* #define N2 for realtek driver                          */
/* #define N3 for nic110 driver (100Mbit Mini only)       */
/* #define ND for DSTni driver                            */
/**********************************************************/
#ifndef BLDFLAGS_H
#define BLDFLAGS_H
#endif

#define CPK_VERSION 6500

#if defined(MODS_XPT) || defined(MODS_XPTEX)
#define ND
#define NANO
#define XPORT
#define BAUD_230K
#define CPCFG
#define WSET
#define PHY

#ifdef MODS_XPT
#define FW_TYP   "CPK6500_XPT"
#define FW_CHECK "X4"
#endif

#ifdef MODS_XPTEX
#define FW_TYP "CPK6500_XPTEX"
#define FW_CHECK "X5"
#define EX
#define BAUD_920K
#define VAR_CPUPERF
#endif
#endif


#ifdef MODS_M100
#define ND
#define M100
#define FW_TYP   "CPK6500_M100"
#define FW_CHECK "4M"
#define BAUD_230K
#define CPCFG
#define STATIC_CPCFG
#define WSET
#define PHY
#endif

#ifdef MODS_WIMINUS
#define ND
#define WF
#define NANO
#define WSET
#define MARVELL
#define FW_CHECK "W8"
#define BAUD_230K
#define CPCFG
#define EX
#define TXEN_HW_CTRL
#define VAR_CPUPERF
#define PHY
#define WIMINUS
#endif

#if defined(MODS_WPT_MRV)
#define ND
#define WF
#define NANO
#define WSET
#define FW_TYP      "CPK6500_WPT"
#define WPT
#define MARVELL
#define FW_CHECK "W6"
#define BAUD_230K
#define BAUD_920K
#define CPCFG
#define EX
#define TXEN_HW_CTRL
#define VAR_CPUPERF
#define PHY
#define WPT_CPS
#endif

#if defined(MODS_WBX_MRV)
#define ND
#define WF
#define NANO
#define WSET
#define FW_TYP      "CPK6500_WBX"
#define WBX
#define MARVELL
#define FW_CHECK "W7"
#define BAUD_230K
#define BAUD_920K
#define CPCFG
#define STATIC_CPCFG
#define EX
#define TXEN_HW_CTRL
#define VAR_CPUPERF
#define PHY
#endif

#if defined(MODS_VDS100) || defined(MODS_UDS1100) || defined(MODS_SDS1101)
#define EX
#define ND
#define WSET
#define BAUD_230K
#define CPCFG
#define STATIC_CPCFG
#define TXEN_HW_CTRL
#define FW_CHECK "U3"

#ifdef MODS_VDS100
#define FW_TYP   "CPK6500_VDS100"
#define VDS100
#endif

#ifdef MODS_UDS1100
#define FW_TYP   "CPK6500_UDS1100"
#define UDS1100
#define PHY
#endif

#ifdef MODS_SDS1101
#define FW_TYP   "CPK6500_SDS1101"
#define FW_CHECK "D3"
#define UDS1100
#define PHY
#endif
#endif

#ifdef MODS_FPT
#define ND
#define WPT_CPS
#define NANO
#define WSET
#define FW_TYP      "CPK6500_FPT"
#define FPT
#define FW_CHECK "FX"
#define BAUD_230K
#define BAUD_920K
#define CPCFG
#define EX
#define TXEN_HW_CTRL
#define VAR_CPUPERF
#define PHY
#endif


#if defined(MODS_UDS2100) || defined(MODS_SDS2101)
#define EX
#define ND
#define WSET
#define BAUD_230K
#define BAUD_920K
#define CPCFG
#define STATIC_CPCFG
#define TXEN_HW_CTRL
#define UDS2100
#define VAR_CPUPERF
#define PHY
#ifdef MODS_UDS2100
#define FW_CHECK "U4"
#endif
#ifdef MODS_SDS2101
#define FW_CHECK "D4"
#endif
#endif

#if defined(MODS_DRIG) || defined(MODS_DR_MRV)
#define ND
#define DRIG
#define WSET
#define BAUD_230K
#define CPCFG
#define STATIC_CPCFG
#define EX
#define TXEN_HW_CTRL

#ifdef MODS_DRIG
#define FW_TYP   "CPK6500_DRIG"
#define FW_CHECK "R1"
#endif

#ifdef MODS_DR_MRV
#define FW_TYP   "CPK6500_DRIGW"
#define FW_CHECK "R2"
#define WF
#define MARVELL
#endif

#endif










