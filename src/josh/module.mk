SRC += src/josh/josh.cpp
MODULES := src/josh/tmp
include $(patsubst %, %/module.mk, $(MODULES))
