#include "s21_string.h"

void *s21_to_upper(const char *str) {
  char *res = s21_NULL;
  s21_size_t len = s21_strlen(str);
  res = (char *)calloc(len + 1, sizeof(char));
  if (res != s21_NULL)
    for (s21_size_t i = 0; i <= len; i++) {
      res[i] = (str[i] >= 'a' && str[i] <= 'z') ? (str[i] - 32) : str[i];
    }

  // res[len] = '\0';
  return res;
}

void *s21_to_lower(const char *str) {
  char *res = s21_NULL;

  s21_size_t len = s21_strlen(str);
  res = (char *)calloc(len + 1, sizeof(char));
  if (res != s21_NULL)
    for (s21_size_t i = 0; i <= len; i++)
      res[i] = (str[i] >= 'A' && str[i] <= 'Z') ? (str[i] + 32) : str[i];

  return res;
}
