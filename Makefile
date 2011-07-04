CFLAGS = -Iinclude
LFLAGS = 

EXECS = bin/josh
OBJS = src/josh/main.o src/josh/ast/ast.o src/josh/ir/ir.o src/josh/token/token.o src/josh/system/system.o

all: $(EXECS)

bin/josh: $(OBJS)
	g++ $(LFLAGS) $(OBJS) -o $@

.cpp.o: 
	g++ -c $(CFLAGS) $< -o $@

src/josh/main.o: src/josh/main.cpp include/josh/ast/ast.h include/josh/ir/ir.h include/josh/token/token.h
src/josh/ast/ast.o: src/josh/ast/ast.cpp include/josh/ast/ast.h
src/josh/ir/ir.o: src/josh/ir/ir.cpp include/josh/ir/ir.h
src/josh/token/token.o: src/josh/token/token.cpp include/josh/token/token.h
src/josh/system/system.o: src/josh/system/system.cpp include/josh/system/system.h

clean:
	rm -rf $(EXECS) $(OBJS)
