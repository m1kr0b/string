#include "s21_string.h"

char *s21_strcat(char *str1, char *str2) {
  char *ptr = NULL;

  for (s21_size_t i = 0; i <= s21_strlen(str1); i++) {
    ptr = str1 + i;
  }

  for (s21_size_t k = 0; k <= s21_strlen(str2); k++) {
    if (k == s21_strlen(str2)) {
      ptr[k] = '\0';
      continue;
    }

    ptr[k] = str2[k];
  }

  return str1;
}