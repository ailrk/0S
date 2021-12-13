#pragma once

// system call numbers

enum {
    SYSCALL_FORK = 1,
    SYSCALL_EXIT = 2,
    SYSCALL_WAIT = 3,
    SYSCALL_PIPE = 4,
    SYSCALL_READ = 5,
    SYSCALL_KILL = 6,
    SYSCALL_EXEC = 7,
    SYSCALL_FSTAT = 8,
    SYSCALL_CHDIR = 9,
    SYSCALL_DUP = 10,
    SYSCALL_GETPID = 11,
    SYSCALL_SBRK = 12,
    SYSCALL_SLEEP = 13,
    SYSCALL_UPTIME = 14,
    SYSCALL_OPEN = 15,
    SYSCALL_WRITE = 16,
    SYSCALL_MKNOD = 17,
    SYSCALL_UNLINK = 18,
    SYSCALL_LINK = 19,
    SYSCALL_MKDIR = 20,
    SYSCALL_CLOSE = 21,
};

int argint(int, int *);
int argptr(int, char **, int);
int argstr(int, char **);
int fetchint(unsigned int, char *);
int fetchstr(unsigned int, char **);
void syscall();
