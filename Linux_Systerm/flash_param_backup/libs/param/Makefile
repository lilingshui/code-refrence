##################################################
#
#  Makefile
#
#  email: pengshuiming@wasion.com
#
#  Copyright(c) 2021 wasion
#  All rights reserved.
#
##################################################

LIBSO = libparam.so
SOURCES = $(wildcard ./src/*.c)
OBJS = $(SOURCES:%.c=%.o)

CC = $(HOST)gcc
CPPFLAGS = -Wall -g -fPIC -D_REENTRANT -Wno-unknown-pragmas -Wno-format -Werror
INCLUDE_DIR = -I ./inc

all:$(LIBSO)
	$(HOST)strip $(LIBSO)
	@chmod 755 $(LIBSO)
	@if [ ! -d $(TOPDIR)/bin/lib ]; then \
	mkdir $(TOPDIR)/bin/lib; \
	fi
	@mv $(LIBSO) $(TOPDIR)/bin/lib/
	@echo "$(LIBSO) has been compiled successfully!!!"

$(LIBSO):$(OBJS)
	$(CC) -shared -o $@ $(OBJS)

$(OBJS): %.o : %.c
	$(CC) $(CPPFLAGS) -c $< -o $@ $(INCLUDE_DIR)

clean:
	@rm -f src/*.o src/*~ *.o
	@rm -f $(TOPDIR)/bin/lib/$(LIBSO)
