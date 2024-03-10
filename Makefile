gen:
	bison -d src/core/parser.y
	flex src/core/lexer.l
	mv lex.yy.c src/
	mv parser.tab.* src/

all: gen
	mkdir -p build && cd build && cmake ../ && cmake --build .

test:
	ls ./build/hawk || (echo "no binary found"; exit 1)
	rm -f tests/test.check
	./build/hawk ./tests/test.code ./tests/test.in > tests/test.check
	(diff ./tests/test.exp tests/test.check && echo "Test passed") || (echo "test failed"; exit 1)

clean:
	rm -f src/lex.yy.c src/parser.tab.c src/parser.tab.h
	rm -rf build
	rm -f tests/test.check
