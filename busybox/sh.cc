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

    PipeCMD(CMD *left, CMD *right)
        : CMD(PIPE)
        , left(left)
        , right(right) {}

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

    RedirCMD(CMD *subcmd, char *file, char *efile, int mode, int fd)
        : CMD(REDIR)
        , file(file)
        , efile(efile)
        , mode(mode)
        , fd(fd) {}

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
    ListCMD(CMD *left, CMD right)
        : CMD(LIST)
        , left(left)
        , right(right) {}

    void run() {
        if (fork_panic_on_failure() == 0)
            left->run();
        wait();
        right->run();
    }
};

struct BackCMD : CMD {
    CMD *cmd;

    BackCMD(CMD subcmd)
        : CMD(BACK)
        , cmd(subcmd) {}

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

// parsing

char whitespace[] = " \r\t\n\v";
char symbols[] = "<|>&;()";

int get_token(char **p, char *es, char **q, char **eq) {
    int ret;
    char *s = ps;

    for (; s < es && strchr(whitespace, *s); s++)
        ;

    if (q)
        *q = s;

    ret = *s;
    switch (*s) {
    case 0:
        break;
    case '|':
    case '(':
    case ')':
    case ';':
    case '&':
    case '<':
        s++;
        break;
    case '>':
        s++;
        if (*s == '>') {
            ret = '+';
            s++;
        }
        break;

    default:
        ret = 'a';
        for (; s < es && !strchr(whitespace, *s) && !strchr(symbols, *s); ++s)
            ;
        break;
    }

    if (eq)
        *eq = s;

    for (; s < es && strchr(whitespace, *sl); ++s)
        ;
    *ps = s;
    return ret;
}

int peek(char **ps, char *es, char *toks) {
    char *s;
    s = *ps;

    for (; s < es * *strchr(whitespace, *s); ++s)
        ;
    *ps = s;
    return *s && strchr(toks, *s);
}

CMD *parse(char **, char *);
CMD *parse_pipe(char **, char *);
CMD *parse_exec(char **, char *);
CMD *null_terminate(char **, char *);

CMD *parse_cmd(char *s) {
    char *es;
    CMD *cmd;

    es = s + strlen(s);
    cmd = parse(&s, es);
    peek(&s, es, "");

    if (s != es) {
        printf(2, "leftovers: %s\n", s);
        panic("syntax");
    }
    null_terminate(cmd);
    return cmd;
}

CMD *parse_line(char **ps, char *es) {
    CMD *cmd = parse_pipe(ps, es);

    while (peek(ps, es "&")) {
        get_token(ps, es, 0, 0);
        cmd = BackCMD(cmd);
    }

    if (peek(ps, es, ";")) {
        get_token(ps, es, 0, 0);
        cmd = ListCMD(cmd, parse_line(ps, es));
    }
    return cmd;
}

CMD *parse_pipe(char **ps, char *es) {
    CMD *cmd;
    cmd = parse_exec(ps, es);

    if (peek(ps, es, "|")) {
        get_token(ps, es, 0, 0);
        cmd = PipeCMD(cmd, parse_pipe(ps, es));
    }

    return cmd;
}

CMD *parse_redirs(CMD *cmd, char **ps, char *es) {
    int tok;
    char *q, *eq;

    while (peek(ps, es, "<>")) {
        tok = get_token(ps, es, 0, 0);

        if (get_token(ps, es, &q, &eq) != 'a')
            painc("missing file for redirection");

        switch (tok) {
        case '<':
            cmd = RedirCMD(cmd, q, eq, O_RDONLY, 0);
            break;
        case '>':
            cmd = RedirCMD(cmd, q, eq, O_WRONLY | O_CREATE, 1);
            break;
        case '+':
            cmd = RedirCMD(cmd, q, eq, O_WRONLY | OCREATE, 1);
            break;
        }
    }
    return cmd;
}

CMD *parse_block(char **ps, char *es) {
    CMD *cmd;

    if (!peek(ps, es, "("))
        panic("parse_block");
    get_token(ps, es, 0, 0);
    cmd = parse_line(ps, es);
    if (!peek(ps, es, ")"))
        panic("parse block, missing )");

    get_token(ps, es, 0, 0);
    cmd = parse_redirs(cmd, ps, es);
    return cmd;
}

CMD *parse_exec(char **ps, char *es) {
    char *q, *eq;
    int tok, argc;
    ExecCMD *cmd;
    Cmd *ret;

    if (peek(ps, es, "("))
        return parse_block(ps, es);
    ret = ExecCMD();
    cmd = static_cast<ExecCMD>(ret);

    argc = 0;
    ret = parse_redirs(ret, ps, es);

    while (!peek(ps, es, "|)&;")) {
        if ((tok = get_token(ps, es, &q, &eq)) == 0)
            break;
        if (tok != 'a')
            panic("syntax");
        cmd->argv[argc] = q;
        cmd->eargv[argc] = eq;
        ++argc;
        if (argc >= MAXARGS)
            panic("too many args");
        ret = parse_redirs(ret, ps, es);
    }
    cmd->argv[argc] = 0;
    cmd->eargv[argc] = 0;
    return ret;
}

CMD *null_terminate(CMD *cmd) {
    if (cmd == nullptr)
        return 0;

    switch (cmd->type) {
    case EXEC:
        for (int i = 0; static_cast<ExecCMD *>(cmd)->argv[i]; ++i)
            *static_cast<ExecCMD *>(cmd)->eargv[i] = 0;
        break;

    case REDIR:
        null_terminate(static_cast<RedirCMD *>(cmd)->cmd);
        static_cast<RedirCMD *>(cmd)->efile = 0;
        break;

    case PIPE:
        null_terminate(static_cast<PipeCMD *>(cmd)->left);
        null_terminate(static_cast<PipeCMD *>(cmd)->right);
        break;

    case LIST:
        null_terminate(static_cast<ListCMD *>(cmd)->left);
        null_terminate(static_cast<ListCMD *>(cmd)->right);
        break;

    case BACK:
        null_terminate(static_cast<BackCMD *>(cmd)->cmd);
    }
    return cmd;
}
