#include "lib_tar.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/**
 * Checks whether the archive is valid.
 *
 * Each non-null header of a valid archive has:
 *  - a magic value of "ustar" and a null,
 *  - a version value of "00" and no null,
 *  - a correct checksum
 *
 * @param tar_fd A file descriptor pointing to the start of a file supposed to contain a tar archive.
 *
 * @return a zero or positive value if the archive is valid, representing the number of headers in the archive,
 *         -1 if the archive contains a header with an invalid magic value,
 *         -2 if the archive contains a header with an invalid version value,
 *         -3 if the archive contains a header with an invalid checksum value
 */
int check_archive(int tar_fd) {
    int rep = 0;
    int off_set = 0;
    char buf[512];
    pread(tar_fd, buf, 512, 0);
    tar_header_t* header = (tar_header_t*) buf;
    while(strcmp(header->name,"")){
        rep++;
        if(strcmp(header->magic, "ustar")){
            return -1;
        }
        if(memcmp(header->version, TVERSION, TVERSLEN)){
            return -2;
        }
        uint sum = 0;
        for (int i = 0; i <512; i++){
            if(i<=148 || i > 156){
                sum += (uint) *(buf+i);
            }
            else{
                sum += (uint) ' ';
            }
        }
        if(TAR_INT(header->chksum)!=sum){
            return -3;
        }
        int file_size = (TAR_INT(header->size)/512 + ((TAR_INT(header->size)%512>0)?1:0)) * 512;
        off_set += 512 + file_size;
        pread(tar_fd, buf, 512, off_set);
    }
    return rep;
}

/**
 * Checks whether an entry exists in the archive.
 *
 * @param tar_fd A file descriptor pointing to the start of a tar archive file.
 * @param path A path to an entry in the archive.
 *
 * @return zero if no entry at the given path exists in the archive,
 *         any other value otherwise.
 */
int exists(int tar_fd, char *path) {
    char buf[512];
    read(tar_fd, buf, 512);
    int off_set = 0;
    tar_header_t* header = (tar_header_t*) buf;
    while(strcmp(header->name,"")){
        if(!strcmp(header->name, path)){
            return 1;
        }
        int file_size = (TAR_INT(header->size)/512 + ((TAR_INT(header->size)%512>0)?1:0)) * 512;
        off_set += 512+file_size;
        pread(tar_fd, buf, 512, off_set);
    }
    return 0;
}

/**
 * Checks whether an entry exists in the archive and is a directory.
 *
 * @param tar_fd A file descriptor pointing to the start of a tar archive file.
 * @param path A path to an entry in the archive.
 *
 * @return zero if no entry at the given path exists in the archive or the entry is not a directory,
 *         any other value otherwise.
 */
int is_dir(int tar_fd, char *path) {
    char buf[512];
    read(tar_fd, buf, 512);
    int off_set = 0;
    tar_header_t* header = (tar_header_t*) buf;
    while(strcmp(header->name,path)){
        int file_size = (TAR_INT(header->size)/512 + ((TAR_INT(header->size)%512>0)?1:0)) * 512;
        off_set += 512+file_size;
        pread(tar_fd, buf, 512, off_set);
        if(!strcmp(header->name, "")){
            return 0;
        }
    }
    if(header->typeflag == DIRTYPE){
        return 1;
    }
    return 0;
}

/**
 * Checks whether an entry exists in the archive and is a file.
 *
 * @param tar_fd A file descriptor pointing to the start of a tar archive file.
 * @param path A path to an entry in the archive.
 *
 * @return zero if no entry at the given path exists in the archive or the entry is not a file,
 *         any other value otherwise.
 */
int is_file(int tar_fd, char *path) {
    int off_set = 0;
    char buf[512];
    pread(tar_fd, buf, 512, 0);
    tar_header_t* header = (tar_header_t*) buf;
    while(strcmp(header->name,path)){
        int file_size = (TAR_INT(header->size)/512 + ((TAR_INT(header->size)%512>0)?1:0)) * 512;
        off_set += 512 + file_size;
        pread(tar_fd, buf, 512, off_set);
        if(!strcmp(header->name, "")){
            return 0;
        }
    }
    if(header->typeflag == REGTYPE || header->typeflag == AREGTYPE || header->typeflag == LNKTYPE){
        return 1;
    }
    return 0;
}

/**
 * Checks whether an entry exists in the archive and is a symlink.
 *
 * @param tar_fd A file descriptor pointing to the start of a tar archive file.
 * @param path A path to an entry in the archive.
 * @return zero if no entry at the given path exists in the archive or the entry is not symlink,
 *         any other value otherwise.
 */
int is_symlink(int tar_fd, char *path) {
    char buf[512];
    read(tar_fd, buf, 512);
    int off_set = 0;
    tar_header_t* header = (tar_header_t*) buf;
    while(strcmp(header->name,path)){
        int file_size = (TAR_INT(header->size)/512 + ((TAR_INT(header->size)%512>0)?1:0)) * 512;
        off_set += 512+file_size;
        pread(tar_fd, buf, 512, off_set);
        if(!strcmp(header->name, "")){
            return 0;
        }
    }
    if(header->typeflag == SYMTYPE){
        return 1;
    }
    return 0;
}


/**
 * Lists the entries at a given path in the archive.
 *
 * @param tar_fd A file descriptor pointing to the start of a tar archive file.
 * @param path A path to an entry in the archive. If the entry is a symlink, it must be resolved to its linked-to entry.
 * @param entries An array of char arrays, each one is long enough to contain a tar entry
 * @param no_entries An in-out argument.
 *                   The caller set it to the number of entry in entries.
 *                   The callee set it to the number of entry listed.
 *
 * @return zero if no directory at the given path exists in the archive,
 *         any other value otherwise.
 */
int list(int tar_fd, char *path, char **entries, size_t *no_entries) {
    return 0;
}

/**
 * Reads a file at a given path in the archive.
 *
 * @param tar_fd A file descriptor pointing to the start of a tar archive file.
 * @param path A path to an entry in the archive to read from.  If the entry is a symlink, it must be resolved to its linked-to entry.
 * @param offset An offset in the file from which to start reading from, zero indicates the start of the file.
 * @param dest A destination buffer to read the given file into.
 * @param len An in-out argument.
 *            The caller set it to the size of dest.
 *            The callee set it to the number of bytes written to dest.
 *
 * @return -1 if no entry at the given path exists in the archive or the entry is not a file,
 *         -2 if the offset is outside the file total length,
 *         zero if the file was read in its entirety into the destination buffer,
 *         a positive value if the file was partially read, representing the remaining bytes left to be read.
 *
 */
ssize_t read_file(int tar_fd, char *path, size_t offset, uint8_t *dest, size_t *len) {
    return 0;
}