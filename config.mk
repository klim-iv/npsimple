# npsimple version
VERSION = 0.3

# Customize below to fit your system
ifeq (${shell uname}, Darwin)
	CPPFLAGS = -DVERSION=\"${VERSION}\" -DWEBKIT_DARWIN_SDK
	LDFLAGS = -dynamiclib #-framework Carbon -framework CoreFoundation -framework WebKit
else
	INCS = -I./npapi
	CPPFLAGS = -DVERSION=\"${VERSION}\" -DNATIVE
endif

CFLAGS = -g -Wall -O2 ${INCS} ${CPPFLAGS}

# compiler and linker
ifeq (${HOST},)
	CC = cc
else
	ifeq (${CROSSTOOLS},)
		CROSSTOOLS := "/opt/arm-2010q1"
	endif
	CC = ${CROSSTOOLS}/bin/arm-none-linux-gnueabi-gcc
endif
