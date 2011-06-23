SRC += josh.cpp
MODULES := src/josh/tmp
VPATH += $(MODULES)
include $(patsubst %, %/module.mk, $(MODULES))
