LIB = libfossa.so
PROG = restful_server
SOURCES = $(PROG).c 
CFLAGS = -W -Wall $(CFLAGS_EXTRA)
CFLAGS = -L. -lfossa $(LDFLAGS_EXTRA)

ifeq ($(SSL), openssl)
	CFLAGS += -DNS_ENABLE_SSL -lssl -lcrypto
endif

all: $(LIB)

$(LIB): fossa.c
	$(CC) -shared -fPIC fossa.c -o libfossa.so

#$(PROG): $(SOURCES)
#	$(CC) $(SOURCES) -o $@ $(CFLAGS) $(LDFLAGS)

clean:
	rm -rf *.gc* *.dSYM *.exe *.obj *.o a.out $(PROG)
