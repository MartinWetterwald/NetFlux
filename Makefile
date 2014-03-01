THIS := $(lastword $(MAKEFILE_LIST))

rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

LIBNAME = libnetflux.a
SRCDIR = src/
BUILDDIR = build/
BINDIR = $(BUILDDIR)bin/
INCDIR = $(BUILDDIR)include/
OBJDIR = $(BUILDDIR)obj/
DEPDIR = $(BUILDDIR)dep/
LIB = $(BINDIR)$(LIBNAME)

CLANG = @clang++
GPP = @g++

COMMONFLAGS = -std=c++11
ifneq ($(MODE),release)
COMMONFLAGS += -DDEBUG -g -O0
else
COMMONFLAGS += -Werror -g0 -O3
endif
CLANGFLAGS = $(COMMONFLAGS) -Weverything -Wno-padded -Wno-disabled-macro-expansion -Wno-c++98-compat
GPPFLAGS = $(COMMONFLAGS) -Wall -Wextra -Weffc++ -Wno-error=effc++


AR = @ar rs

SRC =  $(call rwildcard,$(SRCDIR),*.cpp)
HPP =  $(call rwildcard,$(SRCDIR),*.hpp)
OBJ = $(addprefix $(OBJDIR), $(notdir $(SRC:%.cpp=%.o)))

DEP = $(wildcard $(DEPDIR)*.d)

.PHONY: clean mrproper all default
.SECONDEXPANSION:

default: $(LIB)
	@printf "%-13s <$(INCDIR)>...\n" "Generating"
	@mkdir -p $(INCDIR)
	@cd $(SRCDIR) && cp -u --parents -t ../$(INCDIR) $(HPP:$(SRCDIR)%=%)

ifneq ($(words $(OBJ)),0)
$(LIB): $(OBJ)
	@mkdir -p $(BINDIR)
	@printf "%-13s <$@>...\n" "Building lib"
	$(AR) $@ $(OBJ) > /dev/null 2>&1
	@ln -sf $(LIB) $(LIBNAME)
else
$(LIB):
	$(error No source code found)
endif


$(OBJDIR)%.o: $$(call rwildcard,$(SRCDIR),%.cpp) $(THIS)
	@mkdir -p $(DEPDIR)
	@mkdir -p $(OBJDIR)
ifeq ($(CC),g++)
	@printf "%-13s <$<>...\n" "Gplusplusing"
	$(GPP) $(GPPFLAGS) -o $@ -c -MMD -MF $(addprefix $(DEPDIR), $(notdir $(<:.cpp=.d))) $<
else
	@printf "%-13s <$<>...\n" "Clanging"
	$(CLANG) $(CLANGFLAGS) -o $@ -c -MMD -MF $(addprefix $(DEPDIR), $(notdir $(<:.cpp=.d))) $<
endif

-include $(DEP)

all: mrproper $(LIB)

clean:
	@echo "Cleaning..."
	@rm -rf $(OBJDIR) $(DEPDIR)

mrproper:
	@echo "Cleaning everything..."
	@rm -rf $(BUILDDIR) $(LIBNAME)
