#include <stdio.h>
#include "chapter_2/typedefs.h"

void show_bytes(byte_pointer start, int len) {
  for (int i = 0; i < len; i++) {
    printf("%.02x\n", start[i]);
  }
}

void show_int(int x) {
  show_bytes((byte_pointer) &x, sizeof(int));
}

void show_float(float x) {
  show_bytes((byte_pointer) &x, sizeof(float));
}

void show_pointer(void *x) {
  show_bytes((byte_pointer) &x, sizeof(void *));
}