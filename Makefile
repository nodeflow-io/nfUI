# Attempt to load a config.make file.
# If none is found, project defaults in config.project.make will be used.
ifneq ($(wildcard config.make),)
	include config.make
endif

# make sure the the OF_ROOT location is defined
ifndef OF_ROOT
	OF_ROOT=$(realpath ../../..)
endif

# add our own directories
PROJECT_INCLUDE_CFLAGS += -I$(CURDIR)/src/API
PROJECT_INCLUDE_CFLAGS += -I$(CURDIR)/src/UI-Components

$(info PROJECT_INCLUDE_CFLAGS is $(PROJECT_INCLUDE_CFLAGS))


# call the project makefile!
include $(OF_ROOT)/libs/openFrameworksCompiled/project/makefileCommon/compile.project.mk
