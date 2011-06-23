# Based on the paper "Recrusive Make Considered Harmful" by Peter Miller
# http://miller.emu.id.au/pmiller/books/rmch/

MODULES := src/josh

CPPFLAGS += -Iinclude/ 

LIBS :=

SRC := 

OUT := bin/josh

include $(patsubst %, %/module.mk, $(MODULES))

TOLOAD := $(patsubst %, -l%, $(LIBS))

%.d: %.cpp
	./depend.sh `dirname $*.cpp` $(CPPFLAGS) $*.cpp > $@

OBJ := $(patsubst %.cpp, %.o, $(filter %.cpp, $(SRC))) 

$(OUT): $(OBJ)
	$(CXX) $(CPPFLAGS) -o $@ $(OBJ) $(TOLOAD)

.PHONY: clean
clean: 
	rm -f $(OBJ) $(OUT)
