# the compiler to use in compilation
# CXX=g++

# the various build directories
OMNI_DIR=/code/Zeriph/omni
OMNI_SDIR=$(OMNI_DIR)/source
OMNI_ODIR=$(OMNI_DIR)/build/obj
# Omni framework source files
OMNI_SRC=application.cpp\
	argparser.cpp\
	basic_thread.cpp\
	binary_semaphore.cpp\
	conditional.cpp\
	framework.cpp\
	mutex.cpp\
	runnable.cpp\
	semaphore.cpp\
	thread.cpp\
	threadpool.cpp\
	timer.cpp
# translate the source to obj files
OMNI_O=$(OMNI_SRC:%.cpp=$(OMNI_ODIR)/%.o)
OMNI_LIB=$(OMNI_DIR)/build/bin/libomni.a

# OMNI_FLAGS are the default flags for compilation
OMNI_FLAGS=-pthread -rt -O3 -DNDEBUG -D_CONSOLE 
# Various compilation flags for Omni that can be used (optional)
OMNI_EX=-fexceptions
OMNI_NOTHROW=-fno-exceptions -DOMNI_NO_THROW
OMNI_UNICODE=-D_UNICODE -DUNICODE
OMNI_DEBUG=-ggdb -DOMNI_SHOW_DEBUG_ERR -DOMNI_SHOW_DEBUG_FILE -DOMNI_SHOW_DEBUG_FUNC -DOMNI_SHOW_DEBUG_LINE -DOMNI_SHOW_DEBUG=1
OMNI_HEAVY=-DOMNI_DISPOSE_EVENT -DOMNI_OBJECT_NAME -DOMNI_TYPE_INFO
OMNI_SAFE=-DOMNI_SAFE_FRAMEWORK
OMNI_NP=-DOMNI_NON_PORTABLE
# generic default flags (pthread/execptions/unicode)
OMNI_DEF=$(OMNI_FLAGS) $(OMNI_EX) $(OMNI_UNICODE)
OMNI_DEF_EX=$(OMNI_FLAGS) $(OMNI_UNICODE) $(OMNI_NOTHROW)

# DEV_NOTE: target-specific-variables's aren't on all platforms/versions of make. While not
# typically advised to build anything this way (i.e. $(MAKE) OMNI_FLAGS="$(OMNI_FLAGS) ..."),
# it is portable enough and you (the user of this Makefile) can adjust as necessary.

# These build targets are only a subset of the ways to build the Omni framework
# and a number of flags can be defined to customize the way Omni operates.

# if make is called with no targets, then this is the default (base Omni with Unicode)
all: unicode

# if this target is specified, then all options (except debug) are enabled
full:
	$(MAKE) OMNI_FLAGS="$(OMNI_DEF) $(OMNI_HEAVY) $(OMNI_SAFE) $(OMNI_NP)" libomni

full_debug:
	$(MAKE) OMNI_FLAGS="$(OMNI_DEF) $(OMNI_HEAVY) $(OMNI_SAFE) $(OMNI_NP) $(OMNI_DEBUG)" libomni

# default build with omni::string_t == std::wstring
unicode:
	$(MAKE) OMNI_FLAGS="$(OMNI_DEF)" libomni

# build with omni::string_t == std::string
ansi:
	$(MAKE) OMNI_FLAGS="$(OMNI_FLAGS) $(OMNI_EX)" libomni

# a basic debug build of the Omni framework (debug level = 1)
debug:
	$(MAKE) OMNI_FLAGS="$(OMNI_DEF) $(OMNI_DEBUG)" libomni

debug_ansi:
	$(MAKE) OMNI_FLAGS="$(OMNI_FLAGS) $(OMNI_EX) $(OMNI_DEBUG)" libomni

# Classes in the framework will have additional helper members (hash/etc.)
heavy:
	$(MAKE) OMNI_FLAGS="$(OMNI_DEF) $(OMNI_HEAVY)" libomni

# Classes in the framework will be thread safe
thread_safe:
	$(MAKE) OMNI_FLAGS="$(OMNI_DEF) $(OMNI_SAFE)" libomni

# Non-portable code (like thread::set_priority) will be enabled in the framework
nonportable:
	$(MAKE) OMNI_FLAGS="$(OMNI_DEF) $(OMNI_NP)" libomni

# throw omni::exception, and try..catch will not be used
nothrow:
	$(MAKE) OMNI_FLAGS="$(OMNI_DEF_EX)" libomni

# std::terminate will be called instead of throw omni::exception, and try..catch will not be used
terminate:
	$(MAKE) OMNI_FLAGS="$(OMNI_DEF_EX) -DOMNI_TERMINATE" libomni

# Main build: build source files then call ar to build the lib
libomni: $(OMNI_SRC)
	ar rvs $(OMNI_LIB) $(OMNI_O)

# Source build: compiles the source files to object files (no link, just compile)
$(OMNI_SRC):
	$(CXX) -I$(OMNI_SDIR) $(OMNI_FLAGS) -c $(OMNI_SDIR)/$@ -o $(OMNI_ODIR)/$(@:%.cpp=%.o)

# make clean -> deletes the lib and obj files
clean:
	rm -rf $(OMNI_ODIR)/*.o $(OMNI_LIB)
