# Based on the paper "Recrusive Make Considered Harmful" by Peter Miller
# http://miller.emu.id.au/pmiller/books/rmch/

MODULES := src/josh
VPATH := src/josh

CPPFLAGS += -Iinclude/ 

LIBS :=

SRC := 

OUT := bin/josh

include $(patsubst %, %/module.mk, $(MODULES))

TOLOAD := $(patsubst %, -l%, $(LIBS))

OBJ := $(patsubst %.cpp, %.o, $(filter %.cpp, $(SRC))) 

$(OUT): $(OBJ)
	@$(CXX) $(CPPFLAGS) -o $@ $(OBJ) $(TOLOAD)

clean: 
	rm -f $(OBJ) $(OBJ:.o=.d)  $(OUT)

%.d: %.cpp
	$(CXX) -MM -MG $(CPPFLAGS) $^  | sed -e 's@^\(.*\)\.o:@\1.d \1.o:@' > $@

-include $(OBJ:.o=.d)

