#include "s21_string.h"

void *s21_insert(const char *src, const char *str, size_t start_index) {
  s21_size_t len_src = s21_strlen(src);
  s21_size_t len_str = s21_strlen(str);
  char *new_string = NULL;
  if (len_src && len_str && start_index < s21_strlen(src)) {
    new_string = malloc((len_src + len_str + 1) * sizeof(char));
    if (new_string != NULL) {
      s21_size_t j = 0;
      s21_size_t i = 0;

      for (; i < s21_strlen(src) + s21_strlen(str); i++) {
        if (i == start_index) {
          while (str[j]) {
            new_string[i + j] = str[j];
            j++;
          }
          i = i + j;
        }

        new_string[i] = src[i - j];
      }
      new_string[i] = '\0';
    }
  }

  return new_string;
}