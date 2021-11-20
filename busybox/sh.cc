// TODO include

enum { EXEC = 1, REDIR, PIPE, LIST, BACK };

#define MAXARGS 10
struct CMD;
struct ExecCMD;
struct PipeCMD;
struct RedirCMD;
struct ListCMD;
struct BackCMD;
int fork_panic_on_failure();
void panic(char *);
CMD *parseCMD(char *);

struct CMD {
    int type;
    CMD(int n)
        : type(n) {}

    void run();
};

struct ExecCMD : CMD {
    char *argv[MAXARGS];
    char *eargv[MAXARGS];

    ExecCMD()
        : CMD(EXEC) {}

    static CMD *create() {
        CMD *cmd = malloc(sizeof(CMD));
        memset(cmd, 0, sizeof(CMD));
        cmd->type = EXEC;
        return (CMD *)cmd;
    }

    void run() {
        if (argv[0] == 0)
            exit();
        exec(argv[0], argv);
        printf(2, "exec %s failed\n", argv[0]);
    }
};

struct PipeCMD : CMD {
    CMD *left;
    CMD *right;

    void run() {
        int p[2];
        if (pipe(p) < 0) {
            painc("pipe");
        }
        if (fork_panic_on_failure() == 0) {
            close(1);
            dup(p[1]);
            close(p[0]);
            close(p[1]);
            left->run();
        }
        if (fork_panic_on_failure() == 0) {
            close(0);
            dup(p[0]);
            close(p[0]);
            close(p[1]);
            right.run();
        }
        close(p[0]);
        close(p[1]);
        wait();
        wait();
    }
};

struct RedirCMD : CMD {
    CMD *cmd;
    char *file;
    char *efile;
    int mode;
    int fd;

    RedirCMD()
        : CMD(REDIR) {}

    void run() {
        close(fd);
        if (open(file, mode) < 0) {
            printf(2, "open %s failed\n", file);
            exit();
        }
    }
};

struct ListCMD : CMD {
    CMD *left;
    CMD *right;
    ListCMD()
        : CMD(LIST) {}

    void run() {
        if (fork_panic_on_failure() == 0)
            left->run();
        wait();
        right->run();
    }
};

struct BackCMD : CMD {
    CMD *cmd;

    BackCMD()
        : CMD(BACK) {}

    void run() {
        if (fork_panic_on_failure() == 0) {
            cmd->run();
        }
    }
};

void CMD::run() {
    switch (type) {
    default:
        painc("run cmd error");
    case EXEC:
        static_cast<ExecCMD *>(this)->run();
        break;
    case REDIR:
        static_cast<RedirCMD *>(this)->run();
        break;
    case PIPE:
        static_cast<PipeCMD *>(this)->run();
        break;
    case LIST:
        static_cast<ListCMD *>(this)->run();
        break;
    case BACK:
        static_cast<BackCMD *>(this)->run();
        break;
    }
}

int get_cmd(char *buf, int nbuf) {
    printf(2, "$ ");
    memset(buf, 0, nbuf);
    gets(buf, nbuf);
    if (buf[0] == 0) // EOF
        return -1;
    return 0;
}

int cd(char *dirname) {
    if (chdir(buf) < 0)
        printf(2, "cannot cd %s\n", buf);
}

int main(int argc, char *argv[]) {
    static char buf[100];
    int fd;

    while ((fd = open("console", O_RDWR)) >= 0) { // open 3 fds.
        if (fd >= 3) {
            close(fd);
            break;
        }
    }

    while (get_cmd(buf, sizeof(buf)) >= 0) { // repl.
        // cd needs to built in because it modiyf the same thread.
        if (buf[0] == 'c' && buf[1] == 'd' && buf[2] == ' ') {
            buf[strlen(buf) - 1] = '\0';
            cd(buf + 3);
            continue;
        }

        if (fork_panic_on_failure() == 0)
            parseCMD(buf)->run();
        wait();
    }

    exit();
}

void painc(char *s) {
    printf(2, "%s\n", s);
    exit();
}

int fork_panic_on_failure() {
    int pid;

    pid = fork();
    if (pid == -1)
        painc("fork");
    return pid;
}
