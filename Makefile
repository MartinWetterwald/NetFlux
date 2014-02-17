THIS := $(lastword $(MAKEFILE_LIST))

LIBNAME = libnetflux.a
SRCDIR = src/
BUILDDIR = build/
BINDIR = $(BUILDDIR)bin/
OBJDIR = $(BUILDDIR)obj/
DEPDIR = $(BUILDDIR)dep/
LIB = $(BINDIR)$(LIBNAME)

CC = @clang++

CFLAGS = -std=c++03 -Weverything -Wno-padded
ifneq ($(MODE),release)
CFLAGS += -g -O0
else
CFLAGS += -Werror -g0 -O3
endif

AR = @ar rs

SRC = $(shell find $(SRCDIR) -iname "*.cpp")
OBJ = $(addprefix $(OBJDIR), $(notdir $(SRC:%.cpp=%.o)))

DEP = $(wildcard $(DEPDIR)*.d)

.PHONY: clean mrproper all

ifneq ($(words $(OBJ)),0)
$(LIB): $(OBJ)
	@mkdir -p $(BINDIR)
	@printf "%-13s <$@>...\n" "Building static library"
	$(AR) $@ $(OBJ) > /dev/null 2>&1
	@ln -sf $(LIB) $(LIBNAME)
else
$(LIB):
	$(error No source code found)
endif


$(OBJDIR)%.o: $(SRCDIR)%.cpp $(THIS)
	@mkdir -p $(DEPDIR)
	@mkdir -p $(OBJDIR)
	@printf "%-13s <$<>...\n" "Compiling"
	$(CC) $(CFLAGS) -o $@ -c -MMD -MF $(addprefix $(DEPDIR), $(notdir $(<:.cpp=.d))) $<

-include $(DEP)

all: mrproper $(LIB)

clean:
	@echo "Cleaning..."
	@rm -rf $(OBJDIR) $(DEPDIR)

mrproper:
	@echo "Cleaning everything..."
	@rm -rf $(BUILDDIR) $(LIBNAME)
