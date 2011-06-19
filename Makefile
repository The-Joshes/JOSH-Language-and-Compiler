MODULES := src/josh

CPPFLAGS += $(patsubst %, -I%, $(MODULES))
CPPFLAGS += -Iinclude/

LIBS :=

SRC := 

BIN := bin/

include $(patsubst %, %/module.mk, $(MODULES))

OBJ := \
    $(patsubst %.cpp, %.o,   \
    $(filter %.cpp, $(SRC))) \
    $(patsubst %.y, %.o,   \
    $(filter %.y, $(SRC)))

josh: $(OBJ)
	$(CXX) $(CPPFLAGS) -o $(BIN)/$@ $(OBJ) $(LIBS)

%.d: %.cpp
	./depend.sh `dirname $*.cpp` $(CFLAGS) $*.cpp > $@
