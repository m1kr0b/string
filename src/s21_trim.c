#include "s21_string.h"

void *s21_trim(const char *src, const char *trim_chars) {
  int start = find_start_index(src, trim_chars);
  int end = find_end_index(src, trim_chars);
  char *trimmed = calloc(end - start + 2, sizeof(char));
  if (start != -1) {
    if (end - start > 0) {
      if (trimmed != s21_NULL) {
        for (int k = 0; start <= end; start++, k++) trimmed[k] = src[start];
      }
    }
  } else {
    trimmed[0] = 0;
  }
  return (void *)trimmed;
}

int find_start_index(const char *src, const char *trim_chars) {
  int flag = -1;
  for (int i = 0; src[i] != 0; i++) {
    int match = 0;
    for (int j = 0; trim_chars[j]; j++) {
      if (src[i] == trim_chars[j]) match = 1;
    }
    if (match != 1) {
      flag = i;
      break;
    }
  }
  return flag;
}

int find_end_index(const char *src, const char *trim_chars) {
  int flag = -1;
  int i = s21_strlen(src) - 1;
  for (; i >= 0; i--) {
    int match = 0;
    for (int j = 0; trim_chars[j]; j++) {
      if (src[i] == trim_chars[j]) match = 1;
    }
    if (match != 1) {
      flag = i;
      break;
    }
  }
  return flag;
}
