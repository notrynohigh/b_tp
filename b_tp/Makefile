.PHONY: clean

NDKROOT=/opt/android/ndk

PLATFORM=$(NDKROOT)/platforms/android-14/arch-arm

CROSS_COMPILE=$(NDKROOT)/toolchains/arm-linux-androideabi-4.6/prebuilt/linux-x86/bin/arm-linux-androideabi-

CC=$(CROSS_COMPILE)gcc

AR=$(CROSS_COMPILE)ar

LD=$(CROSS_COMPILE)ld

CFLAGS = -I$(PWD) -I$(PLATFORM)/usr/include -Wall -O2 -fPIC -DANDROID -DHAVE_PTHREAD -mfpu=neon -mfloat-abi=softfp

LDFLAGS =

TARGET = libmath.a

SRCS = $(wildcard *.c)

OBJS = $(SRCS:.c=.o)

all: $(OBJS)

        $(AR) -rc $(TARGET) $(OBJS)

clean:

        rm -f *.o *.a *.so
