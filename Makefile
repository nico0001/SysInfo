CFLAGS=-g -Wall -Werror

all: tests lib_tar.o

lib_tar.o: lib_tar.c lib_tar.h

tests: tests.c lib_tar.o

clean:
	rm -f lib_tar.o tests soumission.tar

submit: all
	tar --posix --pax-option delete=".*" --pax-option delete="*time*" --no-xattrs --no-acl --no-selinux -c *.h *.c Makefile > soumission.tar

run: all
	ln -s lib_tar.c testlink.c

	mkdir testdir
	ln -s testdir testdirlink.c
	echo "test">>testdir/test.txt
	mkdir testdir/dir2
	echo "test">>testdir/dir2/test.txt
	mkdir testdir/dir2/dir3

	mkdir testdir2
	echo "test">>testdir2/test.txt
	mkdir testdir2/dir2

	tar --posix --pax-option delete=".*" --pax-option delete="*time*" --no-xattrs --no-acl --no-selinux -c *.h *.c testdir Makefile > soumission.tar
	rm -r testdir
	rm -r testdir2
	rm testlink.c
	rm testdirlink.c
	./tests soumission.tar