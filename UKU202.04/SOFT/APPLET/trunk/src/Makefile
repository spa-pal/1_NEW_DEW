# Please remove the # below and define BCBIN to be the path to the Borland bin directory	 
BCBIN=c:\bc5													
!if !$d(BCBIN) 													
!error Please define BCBIN in the Makefile!						
!endif																
MAKE = $(BCBIN)\make												

fpt.rom: *.c *.h 						
 $(MAKE) -fMakefile1 -DBCBIN=$(BCBIN) -DPROD=fpt -DKEY=FX -DCFLAG=MODS_FPT -DCFLAG1=-zC_TXT1		

fpts.rom: *.c *.h						
 $(MAKE) -fMakefile1 -DBCBIN=$(BCBIN) -DPROD=fpts -DKEY=FX -DCFLAG=MODS_FPT			

xpt.rom: *.c *.h 						
 $(MAKE) -fMakefile1 -DBCBIN=$(BCBIN) -DPROD=xpt -DKEY=X4 -DCFLAG=MODS_XPT -DCFLAG1=-zC_TXT1		

xpts.rom: *.c *.h						
 $(MAKE) -fMakefile1 -DBCBIN=$(BCBIN) -DPROD=xpts -DKEY=X4 -DCFLAG=MODS_XPT			

xptex.rom: *.c *.h 						
 $(MAKE) -fMakefile1 -DBCBIN=$(BCBIN) -DPROD=xptex -DKEY=X5 -DCFLAG=MODS_XPTEX -DCFLAG1=-zC_TXT1		

xptexs.rom: *.c *.h						
 $(MAKE) -fMakefile1 -DBCBIN=$(BCBIN) -DPROD=xptexs -DKEY=X5 -DCFLAG=MODS_XPTEX			

m100.rom: *.c *.h 						
 $(MAKE) -fMakefile1 -DBCBIN=$(BCBIN) -DPROD=m100 -DKEY=4M -DCFLAG=MODS_M100 -DCFLAG1=-zC_TXT1		

m100s.rom: *.c *.h						
 $(MAKE) -fMakefile1 -DBCBIN=$(BCBIN) -DPROD=m100s -DKEY=4M -DCFLAG=MODS_M100			

sds1101.rom: *.c *.h 						
 $(MAKE) -fMakefile1 -DBCBIN=$(BCBIN) -DPROD=sds1101 -DKEY=D3 -DCFLAG=MODS_SDS1101 -DCFLAG1=-zC_TXT1		

sds1101s.rom: *.c *.h						
 $(MAKE) -fMakefile1 -DBCBIN=$(BCBIN) -DPROD=sds1101s -DKEY=D3 -DCFLAG=MODS_SDS1101			

sds2101.rom: *.c *.h 						
 $(MAKE) -fMakefile1 -DBCBIN=$(BCBIN) -DPROD=sds2101 -DKEY=D4 -DCFLAG=MODS_SDS2101 -DCFLAG1=-zC_TXT1		

sds2101s.rom: *.c *.h						
 $(MAKE) -fMakefile1 -DBCBIN=$(BCBIN) -DPROD=sds2101s -DKEY=D4 -DCFLAG=MODS_SDS2101			

mpt_bg.rom: *.c *.h 						
 $(MAKE) -fMakefile1 -DBCBIN=$(BCBIN) -DPROD=mpt_bg -DKEY=W8 -DCFLAG=MODS_WIMINUS -DCFLAG1=-zC_TXT1		


wpt_mrv.rom: *.c *.h 						
 $(MAKE) -fMakefile1 -DBCBIN=$(BCBIN) -DPROD=wpt_mrv -DKEY=W6 -DCFLAG=MODS_WPT_MRV -DCFLAG1=-zC_TXT1		


wbx_mrv.rom: *.c *.h 						
 $(MAKE) -fMakefile1 -DBCBIN=$(BCBIN) -DPROD=wbx_mrv -DKEY=W7 -DCFLAG=MODS_WBX_MRV -DCFLAG1=-zC_TXT1		


uds1100.rom: *.c *.h 						
 $(MAKE) -fMakefile1 -DBCBIN=$(BCBIN) -DPROD=uds1100 -DKEY=U3 -DCFLAG=MODS_UDS1100 -DCFLAG1=-zC_TXT1		

uds1100s.rom: *.c *.h						
 $(MAKE) -fMakefile1 -DBCBIN=$(BCBIN) -DPROD=uds1100s -DKEY=U3 -DCFLAG=MODS_UDS1100			

uds2100.rom: *.c *.h 						
 $(MAKE) -fMakefile1 -DBCBIN=$(BCBIN) -DPROD=uds2100 -DKEY=U4 -DCFLAG=MODS_UDS2100 -DCFLAG1=-zC_TXT1		

uds2100s.rom: *.c *.h						
 $(MAKE) -fMakefile1 -DBCBIN=$(BCBIN) -DPROD=uds2100s -DKEY=U4 -DCFLAG=MODS_UDS2100			

drig.rom: *.c *.h 						
 $(MAKE) -fMakefile1 -DBCBIN=$(BCBIN) -DPROD=drig -DKEY=R1 -DCFLAG=MODS_DRIG -DCFLAG1=-zC_TXT1		

drigs.rom: *.c *.h						
 $(MAKE) -fMakefile1 -DBCBIN=$(BCBIN) -DPROD=drigs -DKEY=R1 -DCFLAG=MODS_DRIG			

dr_mrv.rom: *.c *.h 						
 $(MAKE) -fMakefile1 -DBCBIN=$(BCBIN) -DPROD=dr_mrv -DKEY=R2 -DCFLAG=MODS_DR_MRV -DCFLAG1=-zC_TXT1		


sauber: 									
 $(MAKE) clean 							

cln_all_s: clean_xpt clean_xptex clean_m100 clean_uds1100 clean_uds2100 clean_sds1101 clean_sds2101  clean_wpt_mrv clean_mpt_bg clean_wbx_mrv clean_drig clean_dr_mrv clean_fpt		
cln_all_l: clean_xpts clean_xptexs clean_m100s clean_uds1100s clean_uds2100s clean_sds1101s clean_sds2101s  clean_drigs clean_fpts 	
clean: cln_all_s cln_all_l			 		

clean_m100:					 				
 $(MAKE) -fMakefile1 -DPROD=m100    clean	

clean_xpt:					 				
 $(MAKE) -fMakefile1 -DPROD=xpt     clean	

clean_xptex:					 				
 $(MAKE) -fMakefile1 -DPROD=xptex   clean		

clean_wpt_mrv: 								
 $(MAKE) -fMakefile1 -DPROD=wpt_mrv clean	

clean_mpt_bg: 								
 $(MAKE) -fMakefile1 -DPROD=mpt_bg clean	

clean_wbx_mrv:					 				
 $(MAKE) -fMakefile1 -DPROD=wbx_mrv clean	

clean_uds1100:					 				
 $(MAKE) -fMakefile1 -DPROD=uds1100 clean		

clean_uds2100:					 				
 $(MAKE) -fMakefile1 -DPROD=uds2100 clean		

clean_sds1101:					 				
 $(MAKE) -fMakefile1 -DPROD=sds1101 clean		

clean_sds2101:					 				
 $(MAKE) -fMakefile1 -DPROD=sds2101 clean		

clean_drig:					 				
 $(MAKE) -fMakefile1 -DPROD=drig clean		

clean_dr_mrv:					 				
 $(MAKE) -fMakefile1 -DPROD=dr_mrv clean			

clean_fpt:					 					
 $(MAKE) -fMakefile1 -DPROD=fpt clean			

clean_m100s:					 				
 $(MAKE) -fMakefile1 -DPROD=m100s    clean	

clean_xpts:					 				
 $(MAKE) -fMakefile1 -DPROD=xpts     clean	

clean_xptexs:					 				
 $(MAKE) -fMakefile1 -DPROD=xptexs   clean		

clean_uds1100s:					 				
 $(MAKE) -fMakefile1 -DPROD=uds1100s clean		

clean_uds2100s:					 				
 $(MAKE) -fMakefile1 -DPROD=uds2100s clean		

clean_sds1101s:					 				
 $(MAKE) -fMakefile1 -DPROD=sds1101s clean		

clean_sds2101s:					 				
 $(MAKE) -fMakefile1 -DPROD=sds2101s clean		

clean_drigs:					 				
 $(MAKE) -fMakefile1 -DPROD=drigs clean		

clean_fpts:					 					
 $(MAKE) -fMakefile1 -DPROD=fpts clean			

all_s:  fpts.rom xpts.rom xptexs.rom m100s.rom sds1101s.rom sds2101s.rom uds1100s.rom uds2100s.rom drigs.rom 							
all_l:  fpt.rom xpt.rom xptex.rom m100.rom sds1101.rom sds2101.rom mpt_bg.rom wpt_mrv.rom wbx_mrv.rom uds1100.rom uds2100.rom drig.rom dr_mrv.rom 							
all: all_s all_l 							
