# tools
CC ?= cc
PKG_CONFIG ?= pkg-config

# install dirs
PREFIX ?= /usr/local
DESTDIR ?=
BIN := musu
MAN := musu.1
MAN_DIR := $(PREFIX)/share/man/man1
ASSET_DIR := $(PREFIX)/share/musu
# layout
SRC_DIR := ./
OBJ_DIR := obj/

SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))
DEP := $(OBJ:.o=.d)

# flags
CPPFLAGS ?= -Isrc -D_FORTIFY_SOURCE=2

# compile flags + warnings, hardening
CFLAGS ?= -std=c99 -Os -pipe \
		  -Wall -Wextra -Wformat=2 -Werror=format-security \
		  -Wshadow -Wpointer-arith -Wmissing-prototypes \
		  -Wstrict-prototypes -Wundef -Wvla \
		  -fno-common -fno-strict-aliasing \
		  -fstack-protector-strong -fPIE \
		  -ffunction-sections -fdata-sections \
		  -fno-unwind-tables -fno-asynchronous-unwind-tables -fno-ident

# linker
LDFLAGS ?= -Wl,-Os -pie -Wl,--as-needed -Wl,--gc-sections -Wl,-s

# libraries
CFLAGS += $(shell $(PKG_CONFIG) --cflags x11 xft fontconfig)
LDLIBS += $(shell $(PKG_CONFIG) --libs x11 xft fontconfig) -lXpm -lXext

.PHONY: all clean install uninstall clangd
.SUFFIXES:

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -c -o $@ $<

-include $(DEP)

$(OBJ_DIR):
	@mkdir -p $@

clean:
	@rm -rf $(OBJ_DIR) $(BIN)

install: all
	@echo "installing $(BIN) to $(DESTDIR)$(PREFIX)/bin..."
	@mkdir -p "$(DESTDIR)$(PREFIX)/bin"
	@install -m 755 $(BIN) "$(DESTDIR)$(PREFIX)/bin/$(BIN)"
	@echo "installing assets to $(DESTDIR)$(ASSET_DIR)..."
	mkdir -p "$(DESTDIR)$(ASSET_DIR)"
	@install -d $(DESTDIR)$(ASSET_DIR)
	@cp -r pets $(DESTDIR)$(ASSET_DIR)/
	@echo "installing man page to $(DESTDIR)$(MAN_DIR)..."
	@mkdir -p "$(DESTDIR)$(MAN_DIR)"
	@install -m 644 $(MAN) "$(DESTDIR)$(MAN_DIR)/"
	@echo "installation complete :)"

uninstall:
	@echo "uninstalling $(BIN) from $(DESTDIR)$(PREFIX)/bin..."
	@rm -f "$(DESTDIR)$(PREFIX)/bin/$(BIN)"
	@echo "uninstalling man page from $(DESTDIR)$(MAN_DIR)..."
	@rm -f "$(DESTDIR)$(MAN_DIR)/$(MAN)"
	@echo "uninstallation complete :)"

# dev tools
clangd:
	@echo "generating compile_flags.txt"
	@rm -f compile_flags.txt
	@for flag in $(CPPFLAGS) $(CFLAGS); do echo $$flag >> compile_flags.txt; done
