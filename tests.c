#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "lib_tar.h"

/**
 * You are free to use this file to write tests for your implementation
 */

void debug_dump(const uint8_t *bytes, size_t len) {
    for (int i = 0; i < len;) {
        printf("%04x:  ", (int) i);

        for (int j = 0; j < 16 && i + j < len; j++) {
            printf("%02x ", bytes[i + j]);
        }
        printf("\t");
        for (int j = 0; j < 16 && i < len; j++, i++) {
            printf("%c ", bytes[i]);
        }
        printf("\n");
    }
}

int main(int argc, char **argv) {
    printf("#### TESTS ####\n");
    if (argc < 2) {
        printf("Usage: %s tar_file\n", argv[0]);
        return -1;
    }

    int fd = open(argv[1] , O_RDONLY);
    if (fd == -1) {
        perror("open(tar_file)");
        return -1;
    }
    //Check archive
    int ret = check_archive(fd);
    printf("check_archive returned %d\n", ret);

    //exists
    char* p1 = "te.c";
    int ret1 = exists(fd, p1);
    printf("exists1 of '%s' returned %d\n", p1, ret1);

    char* p2 = "lib_tar.c";
    int ret2 = exists(fd, p2);
    printf("exists2 of '%s' returned %d\n", p2, ret2);

    //is_file
    char* file = "tests.c";
    int ret3 = is_file(fd, file);
    printf("is_file of '%s' returned %d\n", file, ret3);

    char* file1 = "testdir/";
    int ret4 = is_file(fd, file1);
    printf("is_file of '%s' returned %d\n", file1, ret4);

    char* file2 = "abc.c";
    int ret5 = is_file(fd, file2);
    printf("is_file of '%s' returned %d\n", file2, ret5);

    //is_dir
    char* dir = "testdir/";
    int ret6 = is_dir(fd, dir);
    printf("is_dir of '%s' returned %d\n", dir, ret6);

    char* dir1 = "lib_tar.c";
    int ret7 = is_dir(fd, dir1);
    printf("is_dir of '%s' returned %d\n", dir1, ret7);

    char* dir2 = "notthere/";
    int ret8 = is_dir(fd, dir2);
    printf("is_dir of '%s' returned %d\n", dir2, ret8);

    //is_symlink
    char* s = "testlink.c";
    int ret9 = is_symlink(fd, s);
    printf("is_symlink of '%s' returned %d\n", s, ret9);

    char* s1 = "lib_tar.c";
    int ret10 = is_symlink(fd, s1);
    printf("is_symlink of '%s' returned %d\n", s1, ret10);

    char* s2 = "testdir/";
    int ret11 = is_symlink(fd, s2);
    printf("is_symlink of '%s' returned %d\n", s2, ret11);

    // list()
    size_t* psize, size;
    size = 2;
    char* buf[512];
    psize  = &size;
    ssize_t ret12 = list(fd, s2, buf, psize);
    printf("list returned %ld\n", ret12);
    printf("no_entries = %ld\n", *psize);
    

    char* s3 = "testdirlink.c";
    size_t* psize1, size1;
    size1 = 9;
    char* buf1[512];
    psize1  = &size1;
    ssize_t ret13 = list(fd, s3, buf1, psize1);
    printf("list returned %ld\n", ret13);
    printf("no_entries = %ld\n", *psize1);

    // read_file()
    uint8_t buf3[50];
    size_t* psize2, size2;
    size2 = 50;
    psize2  = &size2;
    ssize_t ret14 = read_file(fd, file, 0, buf3, psize2);
    printf("read_file returned %ld\n", ret14);
    printf("len = %ld\n", *psize2);
    //debug_dump(buf3, size2);

    uint8_t buf4[8191];
    size_t* psize3, size3;
    size3 = 8191;
    psize3  = &size3;
    ssize_t ret15 = read_file(fd, s, 500, buf4, psize3);
    printf("read_file returned %ld\n", ret15);
    printf("len = %ld\n", *psize3);
    //debug_dump(buf4, size3);
    return 0;
}