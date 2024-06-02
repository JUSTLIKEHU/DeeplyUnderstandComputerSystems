#include <stdio.h>
#include <string.h>
#include "chapter_2/typedefs.h"

extern void show_bytes(byte_pointer start, int len);
extern void show_int(int);
extern void show_float(float);
extern void show_pointer(void*);


void PrintHexTest() {
  int num = 5;
  float num2 = 12345.0f;

  printf("Using %%02x:\n");
  printf("%2x\n", num);  // 输出 05
  printf("%2f\n", num2); // 输出 7b

  printf("Using %%.2x:\n");
  printf("%.2x\n", num);  // 输出 05
  printf("%.2f\n", num2); // 输出 7b
}

void PrintStr(const char* const s) {
  show_bytes((byte_pointer) s, strlen(s));
}

int main() {
  // PrintHexTest();
  PrintStr("abcdef");
  return 0;
}
