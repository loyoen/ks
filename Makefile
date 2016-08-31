#COMAKE2 edit-mode: -*- Makefile -*-
####################64Bit Mode####################
ifeq ($(shell uname -m),x86_64)
CC=gcc
CXX=g++
CXXFLAGS=-g \
  -pipe \
  -W \
  -Wall \
  -fPIC
CFLAGS=-g \
  -pipe \
  -W \
  -Wall \
  -fPIC
CPPFLAGS=-D_GNU_SOURCE \
  -D__STDC_LIMIT_MACROS \
  -DVERSION=\"1.9.8.7\"
INCPATH=
DEP_INCPATH=

#============ CCP vars ============
CCHECK=@ccheck.py
CCHECK_FLAGS=
PCLINT=@pclint
PCLINT_FLAGS=
CCP=@ccp.py
CCP_FLAGS=


#COMAKE UUID
COMAKE_MD5=ae20a5441ae04ae1c70212ac556c50fb  COMAKE


.PHONY:all
all:comake2_makefile_check ks src 
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mall[0m']"
	@echo "make all done"

.PHONY:comake2_makefile_check
comake2_makefile_check:
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mcomake2_makefile_check[0m']"
	#in case of error, update 'Makefile' by 'comake2'
	@echo "$(COMAKE_MD5)">comake2.md5
	@md5sum -c --status comake2.md5
	@rm -f comake2.md5

.PHONY:ccpclean
ccpclean:
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mccpclean[0m']"
	@echo "make ccpclean done"

.PHONY:clean
clean:ccpclean
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mclean[0m']"
	rm -rf ks
	rm -rf ./output/bin/ks
	$(MAKE) -C src clean

.PHONY:dist
dist:
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mdist[0m']"
	tar czvf output.tar.gz output
	@echo "make dist done"

.PHONY:distclean
distclean:clean
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mdistclean[0m']"
	rm -f output.tar.gz
	@echo "make distclean done"

.PHONY:love
love:
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mlove[0m']"
	@echo "make love done"

ks:
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mks[0m']"
	$(CXX)  -Xlinker "-("   -lpthread \
  -lcrypto \
  -lrt -Xlinker "-)" -o ks
	mkdir -p ./output/bin
	cp -f --link ks ./output/bin

.PHONY:src
src:
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40msrc[0m']"
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Entering directory:'[1;32;40msrc[0m']"
	$(MAKE) -C src
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Leaving directory:'[1;32;40msrc[0m']"

endif #ifeq ($(shell uname -m),x86_64)


