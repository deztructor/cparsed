export ROOTDIR:=$(CURDIR)

SOURCES=templates.c nl.c parsed.c actions.c main.c
OBJS=$(SOURCES:.c=.o)
TARGET:=parsed-test

DEFINES:= -DDEBUG -D_BSD_SOURCE -D_XOPEN_SOURCE=700 -D_GNU_SOURCE
CFLAGS=-g -Wall $(DEFINES) $(INCLUDES)
C_COMPILE=$(CC) $(DEFS) $(CFLAGS)
C_LINK=$(CC) $(CFLAGS) $(LDFLAGS) -L.

includes = $(wildcard $(ROOTDIR)*.h)

C_DEPENDENCIES=-Wp,-MD,.deps/$(*F).P
DEP_FILES=$(patsubst %.o,.deps/%.P,$(OBJS))
DEPS_MAGIC := $(shell mkdir .deps > /dev/null 2>&1 || :)
-include $(DEP_FILES)

LDDEPS=

all: $(TARGET)

%.o: %.c $(includes)
	@echo '$(C_COMPILE) -o $@ -c $<'; \
	$(C_COMPILE) $(C_DEPENDENCIES) -o $@ -c $<

clean:
	rm -rf $(TARGET) *.o .deps/

.PHONY: clean

$(TARGET): $(OBJS) $(LIBS)
	$(C_LINK) -o $@ $^ $(LDDEPS)
