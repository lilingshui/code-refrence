# xml util
#
# yuweifeng@wasion.com
#

LIBSRC	= xmlutil
LIBBIN	= lib$(LIBSRC).so

DEMO	= demo
CONFIG = create_config_file

DESTDIR	?=
prefix	?= /usr
incdir	= $(prefix)/include
libdir  = $(prefix)/lib

INSTALL		:= /usr/bin/install -c
INSTALL_PROGRAM	:= $(INSTALL) -m 755
INSTALL_STRIP_PROGRAM	:=
RM		:= rm -f


CC	= $(CROSS_COMPILE)gcc
STRIP	= $(CROSS_COMPILE)strip

CFLAGS	= -Os -Wall
CFLAGS	+= -I$(incdir)/libxml2

LDFLAGS += -L$(libdir) -lxml2

# Program
$(LIBBIN): $(LIBSRC).o
	$(CC) $(LDFLAGS) -fPIC -shared -o $@ $^

$(DEMO): $(DEMO).o
	$(CC) $(LDFLAGS) -l$(LIBSRC) -o $@ $^
	
$(CONFIG): $(CONFIG).o
	$(CC) $(LDFLAGS) -l$(LIBSRC) -o $@ $^

# Object
$(LIBSRC).o: $(LIBSRC).c
	$(CC) $(CFLAGS) -c $< -o $@

$(DEMO).o: $(DEMO).c
	$(CC) $(CFLAGS) -I$(incdir) -c $< -o $@

$(CONFIG).o: $(CONFIG).c
	$(CC) $(CFLAGS) -I$(incdir) -c $< -o $@
	
# Commands
all: $(LIBBIN) strip install $(DEMO) $(CONFIG)

distclean: clean uninstall

strip:
	$(STRIP) $(LIBBIN)

clean:
	$(RM) *.o $(LIBBIN) $(DEMO) $(CONFIG)

install: $(LIBBIN)
	$(INSTALL) $(LIBBIN) $(libdir)
	$(INSTALL) $(LIBSRC).h $(incdir)
	$(INSTALL_PROGRAM) $(LIBBIN) $(DESTDIR)

uninstall:
	$(RM) $(DESTDIR)/$(LIBBIN)  $(DEMO) $(CONFIG)
