# O (Output) is the build directory
ifeq ($O,)
O = .
endif
# V (Verbosity) is 0 (quiet) or 1 (verbose)
ifeq ($V,0)
override V =
endif

# files
INC = roxml.h
SRC_LIB = roxml.c
SRC_BIN = roxml-parser.c
SRC_TST = xshell.c
DEPS = $(patsubst %.c, $O/%.d, $(SRC_LIB) $(SRC_BIN) $(SRC_TST))
OBJS = $(OBJ_LIB) $(OBJ_TST) $(OBJ_BIN)
OBJ_LIB = $(SRC_LIB:%.c=$O/%.o)
OBJ_BIN = $(SRC_BIN:%.c=$O/%.o)
OBJ_TST = $(SRC_TST:%.c=$O/%.o)
TARGETS = $(TARGET_SLIB) $(TARGET_LIB) $(TARGET_BIN) $(TARGET_TST)
TARGET_SLIB = $O/libroxml.a
TARGET_LIB = $O/libroxml.so
TARGET_BIN = $O/roxml
TARGET_TST = $O/xshell

# options
override CPPFLAGS +=
override CFLAGS += -Wall -Wextra -Werror
override LDFLAGS +=

# first rule (default)
all:

# dependencies
ifeq ($(or \
	$(findstring doxy, $(MAKECMDGOALS)), \
	$(findstring clean, $(MAKECMDGOALS)), \
	$(findstring mrproper, $(MAKECMDGOALS)), \
	$(findstring uninstall, $(MAKECMDGOALS)) \
),)
-include $(DEPS)
endif

# rules verbosity
define ECHO_DO
@ $(if $V, echo $2, $(if $(strip $1), echo $1))
@ $2
endef

# rules

$O:
	$(call ECHO_DO, '  MKDIR   $@', \
	mkdir -p $O )

$O/%.d: $(notdir %.c) | $O
	$(call ECHO_DO, '  DEP     $(notdir $@)', \
	$(CC) -MM -MT '$@ $O/$*.o' $(CPPFLAGS) $< -MF $@ || rm -f $@ )

$O/%.o: $(notdir %.c)
	$(call ECHO_DO, '  CC      $(notdir $@)', \
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $< -o $@ )

$(TARGET_SLIB): $(OBJ_LIB)
	$(call ECHO_DO, '  AR      $(notdir $@)', \
	$(AR) rc $@ $^ )

$(TARGET_LIB): $(OBJ_LIB)
	$(call ECHO_DO, '  LD      $(notdir $@)', \
	$(CC) -shared $(LDFLAGS) $^ -o $@ )

$(TARGET_BIN): $(OBJ_BIN)
$(TARGET_TST): $(OBJ_TST)
$(TARGET_BIN) $(TARGET_TST): | $(if $(filter -static, $(LDFLAGS)), $(TARGET_SLIB), $(TARGET_LIB))
	$(call ECHO_DO, '  LD      $(notdir $@)', \
	$(CC) $(LDFLAGS) $^ -L$O -lroxml -o $@ )

.PHONY: all
all: $(TARGET_SLIB) $(if $(filter -static, $(LDFLAGS)), , $(TARGET_LIB)) $(TARGET_BIN) $(TARGET_TST)

.PHONY: doxy
doxy: doxy.cfg
	$(call ECHO_DO, '  DOXYGEN', \
	doxygen $< )

.PHONY: clean
clean:
	$(call ECHO_DO, '  RM      deps objs libs bins', \
	- rm -f $(DEPS) $(OBJS) $(TARGETS) )

.PHONY: mrproper
mrproper: clean
	$(call ECHO_DO, '  RM      docs', \
	- rm -fr docs )
	$(call ECHO_DO, '  CLEAN   debian', \
	- fakeroot $(MAKE) -f $(abspath debian/rules) clean )

.PHONY: install
install: $(TARGETS) doxy
	install -D $(TARGET_SLIB) $(DESTDIR)/usr/lib
	install -D $(TARGET_LIB) $(DESTDIR)/usr/lib
	install -D $(TARGET_TST) $(DESTDIR)/usr/bin
	install -D $(TARGET_BIN) $(DESTDIR)/usr/bin
	install -D $(INC) $(DESTDIR)/usr/include
	install -D libroxml.pc $(DESTDIR)/usr/lib/pkgconfig
	install -D docs/html $(DESTDIR)/usr/share/doc/libroxml

.PHONY: uninstall
uninstall:
	- rm -f $(DESTDIR)/usr/lib/pkgconfig/libroxml.pc
	- rm -f $(DESTDIR)/usr/lib/$(TARGET_SLIB)
	- rm -f $(DESTDIR)/usr/lib/$(TARGET_LIB)
	- rm -f $(DESTDIR)/usr/bin/$(TARGET_TST)
	- rm -f $(DESTDIR)/usr/bin/$(TARGET_BIN)
	- rm -f $(DESTDIR)/usr/include/$(INC)
	- rm -fr $(DESTDIR)/usr/share/doc/libroxml