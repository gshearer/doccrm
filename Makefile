CC = gcc
LD = $(CC)
LIBS = -lfcgi -lpq
CFLAGS = -O3 -Wall -pipe
LDFLAGS = -s

# Do not modify anything below this point
#############################################################################

OBJS = main.o parse.o misc.o html.o db.o

all:	doccrm.fcgi

doccrm.fcgi: $(OBJS)
	$(LD) $(LDFLAGS) -o doccrm.fcgi $(OBJS) $(LIBS)

main.o:     common.h main.h main.c

parse.o:    common.h parse.h parse.c

misc.o:     common.h misc.h misc.c

html.o:     common.h html.h html.c

db.o:       common.h db.h db.c

clean:
	rm -f $(OBJS) a.out core doccrm.fcgi
