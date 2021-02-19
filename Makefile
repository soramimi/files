

all: files


files: main.o joinpath.o
	g++ -O2 $^ -o $@
	strip $@

clean:
	rm -f *.o
	rm -f files

install: files
	install -m 755 files /usr/local/bin/
