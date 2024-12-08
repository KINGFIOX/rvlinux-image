#include <stdint.h>
#include <sys/syscall.h>
#include <unistd.h>

int main(void) {
  const char *msg = "Hello, World!\n";
  uintptr_t a0 = 0;
  uintptr_t a1 = (uintptr_t)msg;
  uintptr_t a2 = (uintptr_t)sizeof(msg);
  uintptr_t a7 = (uintptr_t)__NR_write;

  // __asm__ volatile("ebreak;");

  __asm__ volatile("add a0, %0, zero;"
                   "add a1, %1, zero;"
                   "add a2, %2, zero;"
                   "add a7, %3, zero;"
                   "ecall"
                   :
                   : "r"(a0), "r"(a1), "r"(a2), "r"(a7)
                   : "a0", "a1", "a2", "a7", "memory");
  return 0;
}
