# This makefile is based on https://gist.github.com/maxtruxa/4b3929e118914ccef057f8a05c614b0f
# ... and mangled by PG1003

SRCDIR = tests

# source files
SRCS := $(shell find $(SRCDIR) -type f -name '*.cpp')

# intermediate directory for generated dependency and object files
OBJDIR := obj

# object files, auto generated from source files
OBJS := $(patsubst %,$(OBJDIR)/%.o,$(basename $(SRCS)))
# dependency files, auto generated from source files
DEPS := $(patsubst %,$(OBJDIR)/%.d,$(basename $(SRCS)))

# compilers (at least gcc and clang) don't create the subdirectories automatically
$(shell mkdir -p $(dir $(OBJS)) >/dev/null)

# C++ compiler
CXX := g++
# linker
LD := g++

# C++ flags
CXXFLAGS := -std=c++14
# C/C++ flags
CPPFLAGS := -Wall -Wextra -Wpedantic -O3
# Extra include directories
INCLUDES = -I "./src"
# linker flags
LDFLAGS :=
# linker flags: libraries to link (e.g. -lfoo)
LDLIBS :=
# flags required for dependency generation; passed to compilers
DEPFLAGS = -MT $@ -MD -MP -MF $*.d

# compile C++ source files
COMPILE.cc = $(CXX) $(DEPFLAGS) $(CXXFLAGS) $(CPPFLAGS) $(INCLUDES) -c -o $@
# link object files to binary
LINK.o = $(LD) $(LDFLAGS) $(LDLIBS) -o $@

.PHONY: all
all: test

.PHONY: clean
clean:
	$(RM) -r $(OBJDIR)

.PHONY: test
test: $(OBJDIR)/$(SRCDIR)/test

$(OBJDIR)/$(SRCDIR): $(OBJS)
	$(LINK.o) $^

.PHONY: run_tests
run_tests: test
	@echo "Running tests..."
	@cd $(OBJDIR)/$(SRCDIR); ./test && : || { echo ">>> Generic tests failed!"; exit 1; }
	@echo "...tests completed"
	@echo "      _"
	@echo "     /(|"
	@echo "    (  :"
	@echo "   __\  \  _____"
	@echo " (____)  '|"
	@echo "(____)|   |"
	@echo " (____).__|"
	@echo "  (___)__.|_____"
# https://asciiart.website/index.php?art=people/body%20parts/hand%20gestures


$(OBJS): $(SRCS)
$(OBJS): $(SRCS) $(DEPS)
	$(COMPILE.cc) $<

.PRECIOUS: $(OBJDIR)/%.d
$(OBJDIR)/%.d: ;

-include $(DEPS) 
