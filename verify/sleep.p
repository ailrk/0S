/* modeling the lock acquire, release sleep and wakeup. */
#define ITER 4
#define N 2

bit lk;
byte value;
bit sleeping[N];

inline acquire(x) { atomic { x == 0; x = 1 }}
inline release(x) { assert x == 1; x = 0 }

inline sleep(cond, lk) {
    assert !sleeping[_pid];
    if
    :: cond -> skip
    :: else ->
        atomic { release(lk); sleeping[_pid] = 1 };
        sleeping[_pid] == 0;
        acquire(lk)
    fi
}

inline wakeup() {
    w = 0;
    do
    :: w < N ->
        sleeping[w] = 0;
        w = w + 1
    :: else -> break
    od
}

active[N] proctype consumer() {
    byte i, x;
    i = 0;
    do
    :: i < ITER ->
        acquire(lk);
        sleep(value > 0, lk);
        x = value;
        value = x - 1;
        x = 0;
        release(lk);
        i = i + 1;
    :: else -> break
    od;
    i = 0;
    skip
}

active[N] proctype producer() {
    byte i, x, w;
    i = 0;
    do
    :: i < ITER ->
        acquire(lk);
        x = value;
        value = x + 1;
        x = 0;
        release(lk);
        wakeup();
        i = i + 1;
    :: else -> break
    od;
    i = 0;
    skip
}
