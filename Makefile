all: test

test: install
	cd bin; \
	LD_LIBRARY_PATH=.; \
	./main Composant1 10 10; \
	./main Composant2 10 10;

install:
	cd main && ${MAKE} install

clean:
	cd main && ${MAKE} clean
