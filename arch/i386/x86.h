// x86 specific instructions

namespace arch::i386 {
#define DEF_I386 static inline

DEF_I386 unsigned char inb(unsigned short port) {
    unsigned char data;

    asm volatile("in %1, %0" : "=a"(data) : "d"(port));
    return data;
}

DEF_I386 void insl(int port, void *addr, int cnt) {
    __asm__ volatile("cld; rep insl"
                     : "=D"(addr), "=c"(cnt)
                     : "d"(port), "0"(addr), "1"(cnt)
                     : "memory", "cc");
}

DEF_I386 void outb(unsigned short port, unsigned char data) {
    __asm__ volatile("out %0, %1" : : "a"(data), "d"(port));
}

DEF_I386 void outw(unsigned short port, unsigned short data) {
    __asm__ volatile("out %0, %1" : : "a"(data), "d"(port));
}

DEF_I386 void outsl(int port, void const *addr, int cnt) {
    __asm__ volatile("cld; rep outsl"
                     : "=S"(addr), "=c"(cnt)
                     : "d"(port), "0"(addr), "1"(cnt)
                     : "cc");
}

DEF_I386 void stosb(void *addr, int data, int cnt) {
    __asm__ volatile("cld; rep stosb"
                     : "=D"(addr), "=c"(cnt)
                     : "0"(addr), "1"(cnt), "a"(data)
                     : "memory", "cc");
}

} // namespace arch::i386
