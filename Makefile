CFLAGS=-g -Wall -Werror

all: tests lib_tar.o

lib_tar.o: lib_tar.c lib_tar.h

tests: tests.c lib_tar.o

clean:
	rm -f lib_tar.o tests soumission.tar

submit: all
	ln -s lib_tar.c testlink.c
	mkdir testdir
	tar --posix --pax-option delete=".*" --pax-option delete="*time*" --no-xattrs --no-acl --no-selinux -c *.h *.c testdir Makefile > soumission.tar
	rm -r testdir
	rm testlink.c