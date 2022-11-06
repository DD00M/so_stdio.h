#include <unistd.h>
#include <fcntl.h>  /* open, O_RDONLY */
#include <errno.h>  /* errno, perror */
#include <stdlib.h> /* exit */
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/errno.h>
#include "so_stdio.h"

//#include <stdio.h>

SO_FILE *so_fopen(const char *pathname, const char *mode)
{
    //write(1, "FLAG1\n", 7);
    if (strcmp(mode, "r") == 0)
    {
        SO_FILE *fp = (SO_FILE *)malloc(sizeof(SO_FILE));
        struct stat st;
        stat(pathname, &st);
        fp->so_sizeFile = st.st_size;
        fp->firstIndex = 0;
        if (fp == NULL)
        {
            perror("bad alloc\n");
            fp->isERR = 222;
            exit(-1);
        }
        int fd = open(pathname, O_RDONLY);
        if (fd == -1)
        {
            perror("File does not exist!\n");
            fp->isERR = 333;
            return NULL;
        }
        else
        {
            fp->buffer_index = 0;
            fp->so_fd = fd;
            fp->off_written = 0;
            fp->cursor = 0;
            //write(1, "FLAG2\n", 7);
            fp->buffer = (char *)malloc(BUFSIZE * sizeof(char));
            //int position = fseek(fd, 0, SEEK_SET);

            //fp->so_start_offset = position;
            //write(1, "FLAG3\n", 7);
            fp->mode = "r";

            return fp;
        }
    }
    else if (strcmp(mode, "r+") == 0)
    {
        SO_FILE *fp;
        struct stat st;
        stat(pathname, &st);
        fp->so_sizeFile = st.st_size;
        fp = (SO_FILE *)malloc(sizeof(SO_FILE));
        fp->firstIndex = 0;
        fp->buffer_index = 0;
        int fd = open(pathname, O_RDWR);
        if (fd == -1)
        {
            perror("File does not exist!\n");
            fp->isERR = 333;
            return NULL;
        }
        else
        {
            fp->mode = "r+";
            fp->so_fd = fd;
            fp->cursor = 0;
            fp->buffer = (char *)malloc(BUFSIZE * sizeof(char));
            //int position = fseek(fd, 0, SEEK_SET);
            //fp->so_start_offset = position;
            fp->off_written = 0;
            return fp;
        }
    }
    else if (strcmp(mode, "w") == 0)
    {

        SO_FILE *fp;
        fp = (SO_FILE *)malloc(sizeof(SO_FILE));
        // write(1, "FLAG3\n", 7);
        struct stat st;
        stat(pathname, &st);
        fp->so_sizeFile = st.st_size;
        fp->buffer_index = 0;
        fp->firstIndex = 0;
        if (access(pathname, F_OK) == 0)
        {
            //write(1, "FLAG1\n", 7);
            int fd = open(pathname, O_WRONLY | O_TRUNC, 0);
            if (fd == -1)
            {
                perror("File does not be opened for W operation!\n");
                fp->isERR = 444;
                return NULL;
            }
            else
            {
                fp->mode = "w";
                fp->so_fd = fd;
                fp->off_written = 0;
                //int position = fseek(fd, 0, SEEK_SET);
                fp->buffer = (char *)malloc(BUFSIZE * sizeof(char));

                //fp->so_start_offset = position;
                return fp;
            }
        }
        else
        {
            int fd = open(pathname, O_WRONLY | O_CREAT, 0644);
            if (fd == -1)
            {
                perror("File does not opened!\n");
                fp->isERR = 333;
                return NULL;
            }
            else
            {
                fp->mode = "w";
                fp->so_fd = fd;
                fp->cursor = 0;
                //int position = fseek(fd, 0, SEEK_SET);
                //fp->so_start_offset = position;
                fp->off_written = 0;
                fp->buffer = (char *)malloc(BUFSIZE * sizeof(char));
                return fp;
            }
        }
    }
    else if (strcmp(mode, "w+") == 0)
    {
        SO_FILE *fp;
        fp = (SO_FILE *)malloc(sizeof(SO_FILE));
        struct stat st;
        stat(pathname, &st);
        fp->firstIndex = 0;
        fp->so_sizeFile = st.st_size;
        fp->buffer_index = 0;
        if (access(pathname, F_OK) == 0)
        {
            int fd = open(pathname, O_RDWR | O_TRUNC, 0);
            if (fd == -1)
            {
                perror("File does not be opened for W operation!\n");
                fp->isERR = 444;
                return NULL;
            }
            else
            {
                fp->mode = "w";
                fp->so_fd = fd;
                fp->cursor = 0;
                //int position = fseek(fd, 0, SEEK_SET);
                fp->buffer = (char *)malloc(BUFSIZE * sizeof(char));
                //fp->so_start_offset = position;
                fp->off_written = 0;
                return fp;
            }
        }
        else
        {
            int fd = open(pathname, O_RDWR | O_CREAT, 0644);
            if (fd == -1)
            {
                perror("File does not opened!\n");
                fp->isERR = 333;
                return NULL;
            }
            else
            {
                fp->mode = "w";
                fp->so_fd = fd;
                fp->cursor = 0;
                //int position = fseek(fd, 0, SEEK_SET);
                fp->buffer = (char *)malloc(BUFSIZE * sizeof(char));
                //fp->so_start_offset = position;
                fp->off_written = 0;
                return fp;
            }
        }
    }
    else if (strcmp(mode, "a") == 0)
    {
        SO_FILE *fp;
        fp = (SO_FILE *)malloc(sizeof(SO_FILE));
        struct stat st;
        stat(pathname, &st);
        fp->firstIndex = 0;
        fp->so_sizeFile = st.st_size;
        fp->buffer_index = 0;
        if (access(pathname, F_OK) == 0)
        {
            int fd = open(pathname, O_APPEND);
            if (fd == -1)
            {
                perror("File does not be opened for W operation!\n");
                fp->isERR = 444;
                return NULL;
            }
            else
            {
                fp->mode = "a";
                fp->so_fd = fd;
                fp->cursor = 0;
                //int position = fseek(fd, 0, SEEK_SET);
                fp->buffer = (char *)malloc(BUFSIZE * sizeof(char));
                //fp->so_start_offset = position;
                fp->off_written = 0;
                return fp;
            }
        }
        else
        {
            int fd = open(pathname, O_APPEND | O_RDWR | O_CREAT, 0644);
            if (fd == -1)
            {
                perror("File does not opened!\n");
                fp->isERR = 333;
                return NULL;
            }
            else
            {
                fp->mode = "a";
                fp->so_fd = fd;
                fp->cursor = 0;
                //int position = fseek(fd, 0, SEEK_SET);
                fp->buffer = (char *)malloc(BUFSIZE * sizeof(char));
                //fp->so_start_offset = position;
                fp->off_written = 0;
                return fp;
            }
        }
    }
    else if (strcmp(mode, "a+") == 0)
    {
        SO_FILE *fp;
        fp = (SO_FILE *)malloc(sizeof(SO_FILE));
        struct stat st;
        stat(pathname, &st);
        fp->firstIndex = 0;
        fp->so_sizeFile = st.st_size;
        fp->buffer_index = 0;
        if (access(pathname, F_OK) == 0)
        {
            int fd = open(pathname, O_APPEND);
            if (fd == -1)
            {
                perror("File does not be opened for W operation!\n");
                fp->isERR = 444;
                return NULL;
            }
            else
            {
                fp->mode = "a";
                fp->off_written = 0;
                fp->so_fd = fd;
                fp->cursor = 0;
                //int position = fseek(fd, 0, SEEK_SET);
                fp->buffer = (char *)malloc(BUFSIZE * sizeof(char));
                //fp->so_start_offset = position;
                return fp;
            }
        }
        else
        {
            int fd = open(pathname, O_APPEND | O_CREAT, 0644);
            if (fd == -1)
            {
                perror("File does not opened!\n");
                fp->isERR = 333;
                return NULL;
            }
            else
            {
                fp->mode = "a";
                fp->so_fd = fd;
                fp->off_written = 0;
                fp->cursor = 0;
                //int position = fseek(fd, 0, SEEK_SET);
                fp->buffer = (char *)malloc(BUFSIZE * sizeof(char));
                //fp->so_start_offset = position;
                return fp;
            }
        }
    }
}