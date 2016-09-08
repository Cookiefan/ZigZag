//手动开栈
VS(C++):
#pragma comment(linker, "/STACK:102400000,102400000")

G++:
int size = 256 << 20; // 256MB
char *p = (char*)malloc(size) + size;
__asm__("movl %0, %%esp\n" :: "r"(p));
//__asm__("movl %0, %%rsp\n" :: "r"(p));