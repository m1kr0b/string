#include "s21_string.h"

// Копирует строку, на которую указывает src, в dest.
char *s21_strcpy(char *dest, const char *src) {
  for (int i = 0; src[i] != '\0'; i++) dest[i] = src[i];

  return dest;
}

// Копирует до n символов из строки, на которую указывает src, в dest.
char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  s21_size_t len_src = s21_strlen(src);

  for (s21_size_t i = 0; i < len_src; i++) {
    if (i < n) {
      dest[i] = src[i];
    } else {
      dest[i] = '\0';
    }
  }

  return dest;
}

// Вычисляет длину начального сегмента str1,
// который полностью состоит из символов, не входящих в str2.
s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t result = 0;

  s21_size_t len_str1 = s21_strlen(str1);
  s21_size_t len_str2 = s21_strlen(str2);

  for (s21_size_t i = 0; i < len_str1; i++) {
    for (s21_size_t j = 0; j < len_str2; j++) {
      if (str1[i] == str2[j]) {
        i = len_str1;
        break;
      }
    }
    if (i != len_str1) {
      result++;
    }
  }

  return result;
}

// Выполняет поиск во внутреннем массиве номера ошибки errnum
// и возвращает указатель на строку с сообщением об ошибке.
// Нужно объявить макросы, содержащие массивы сообщений об ошибке
// для операционных систем mac и linux. Описания ошибок есть
// в оригинальной библиотеке.
// Проверка текущей ОС осуществляется с помощью директив.

char unknown_error_str[100];

char *s21_strerror(int errnum) {
  char *result = s21_NULL;
  char *list_errors[] = ERR_LIST;
  if (errnum >= 0 && errnum <= N) {
    result = list_errors[errnum];
  } else {
    s21_sprintf(unknown_error_str, "Unknown error: %d", errnum);
    result = unknown_error_str;
  }

  return result;
}

// Вычисляет длину строки str, не включая завершающий нулевой символ.
s21_size_t s21_strlen(const char *str) {
  s21_size_t result = 0;
  for (; str[result] != '\0'; result++)
    ;

  return result;
}

// Находит первый символ в строке str1,
// который соответствует любому символу, указанному в str2.
char *s21_strpbrk(const char *str1, const char *str2) {
  int flag = 0;
  char *result = (char *)str1;

  s21_size_t len_str1 = s21_strlen(str1);
  s21_size_t len_str2 = s21_strlen(str2);

  for (s21_size_t i = 0; i < len_str1; i++) {
    for (s21_size_t j = 0; j < len_str2; j++) {
      if (str1[i] == str2[j]) {
        flag = 1;
        i = len_str1;
        break;
      }
    }
    if (!flag) result++;
  }

  if (!flag) result = s21_NULL;
  return result;
}

// Выполняет поиск последнего вхождения символа c (беззнаковый тип)
// в строке, на которую указывает аргумент str.
char *s21_strrchr(const char *str, int c) {
  int flag = 0;
  int temp = 0;
  char *result = (char *)str;

  s21_size_t len_str1 = s21_strlen(str);

  for (s21_size_t i = 0; i <= len_str1; i++) {
    if (str[i] == c) {
      flag = 1;
      result += temp;
      temp = 1;
    } else {
      temp++;
    }
  }

  if (!flag) result = s21_NULL;

  return result;
}

// Вычисляет длину начального сегмента str1,
// который полностью состоит из символов str2.
s21_size_t s21_strspn(const char *str1, const char *str2) {
  s21_size_t result = 0;

  s21_size_t len_str1 = s21_strlen(str1);
  s21_size_t len_str2 = s21_strlen(str2);
  int log = 0;
  for (s21_size_t i = 0; i < len_str1; i++) {
    for (s21_size_t j = 0; j < len_str2; j++) {
      log = 0;
      if (str1[i] == str2[j]) {
        log = 1;
        break;
      }
    }
    if (!log) {
      break;
    } else {
      result++;
    }
  }
  return result;
}

// Находит первое вхождение всей строки needle
// (не включая завершающий нулевой символ),
// которая появляется в строке haystack.
char *s21_strstr(const char *haystack, const char *needle) {
  char *result = s21_NULL;

  s21_size_t len_haystack = s21_strlen(haystack);
  s21_size_t len_needle = s21_strlen(needle);

  for (s21_size_t i = 0; i < len_haystack; i++) {
    if (haystack[i] == needle[0]) {
      for (s21_size_t j = 1; j < len_needle; j++) {
        if (haystack[i + j] != needle[j]) {
          break;
        } else {
          if (j == len_needle - 1) {
            result = (char *)&(haystack[i]);
            i = len_haystack;
          }
        }
      }
    }
  }
  return result;
}

// Разбивает строку str на ряд токенов, разделенных delim.
char *s21_strtok(char *str, const char *delim) {
  int flag = 0;

  static s21_size_t count = 0;
  static char *p_str = s21_NULL;

  if (str) {
    p_str = str;
    count = 0;
  } else {
    if (p_str) {
      p_str += count;
      count = 0;
    } else {
      flag++;
    }
  }

  if (!flag) {
    p_str += s21_strspn(p_str, delim);
    s21_size_t len_p_str = s21_strlen(p_str);
    s21_size_t len_delim = s21_strlen(delim);

    if (!s21_strcspn(p_str, delim)) {
      p_str = s21_NULL;
    } else {
      for (s21_size_t i = 0; (i < len_p_str) && !flag; i++) {
        for (s21_size_t j = 0; (j < len_delim) && !flag; j++) {
          if (p_str[i] == delim[j]) {
            p_str[i] = '\0';
            count = i + 1;
            flag++;
          }
        }
      }
      if (!flag) {
        count += len_p_str;
      }
    }
  }

  return p_str;
}