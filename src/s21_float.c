#include "s21_string.h"
void s21_float(double number, char **p_str, struct mod *p_token) {
  int mem_error = 0;
  char *tmp_ptr = s21_NULL;

  int sign = 0;
  if (number < 0) {
    number = fabs(number);
    sign = 1;
  }

  double w_number = 0.0;
  modf(number, &w_number);

  int count_str = 0;
  *p_str = malloc(sizeof(char));
  (*p_str)[0] = '\0';

  // whole part
  // ========================================================

  // add minus
  if (sign) {
    tmp_ptr = realloc(*p_str, 2 * sizeof(char));
    if (tmp_ptr == s21_NULL) {
      mem_error = 1;
    } else {
      *p_str = tmp_ptr;
      (*p_str)[0] = '-';
      (*p_str)[1] = '\0';
      count_str++;
    }
  } else {
    if (p_token->flag == '+') {
      tmp_ptr = realloc(*p_str, 2 * sizeof(char));
      if (tmp_ptr == s21_NULL) {
        mem_error = 1;
      } else {
        *p_str = tmp_ptr;
        (*p_str)[0] = '+';
        (*p_str)[1] = '\0';
        count_str++;
      }
    }
  }

  // add zero
  if (!w_number && !mem_error) {
    tmp_ptr = realloc(*p_str, (count_str + 2) * sizeof(char));
    if (tmp_ptr == s21_NULL) {
      mem_error = 1;
    } else {
      *p_str = tmp_ptr;
      (*p_str)[count_str] = 48;
      (*p_str)[++count_str] = '\0';
    }
  }

  // whole -> reverse
  double temp = 0;
  int count_rev = 0;
  char *reverse = malloc(sizeof(char));

  number -= w_number;  // sic!

  while (w_number > 0) {
    temp = fmod(w_number, 10.0);
    w_number -= temp;  // not good (
    w_number /= 10.0;
    tmp_ptr = realloc(reverse, (count_rev + 2) * sizeof(char));
    if (tmp_ptr == s21_NULL) {
      mem_error = 1;
      break;
    } else {
      reverse = tmp_ptr;
      reverse[count_rev] = 48 + (int)temp;
      reverse[++count_rev] = '\0';
    }
  }

  // revers -> p_str
  while (count_rev > 0) {
    tmp_ptr = realloc(*p_str, (count_str + 2) * sizeof(char));
    if (tmp_ptr == s21_NULL) {
      mem_error = 1;
      break;
    } else {
      *p_str = tmp_ptr;
      (*p_str)[count_str] = reverse[--count_rev];
      (*p_str)[++count_str] = '\0';
    }
  }

  free(reverse);

  // add dot
  // ========================================================
  if (p_token->accuracy) {
    tmp_ptr = realloc(*p_str, (count_str + 2) * sizeof(char));
    if (tmp_ptr == s21_NULL) {
      mem_error = 1;
    } else {
      *p_str = tmp_ptr;
      (*p_str)[count_str] = '.';
      (*p_str)[++count_str] = '\0';
    }
  }

  // fractional part
  // ========================================================
  tmp_ptr = realloc(*p_str, (count_str + p_token->accuracy + 1) * sizeof(char));
  if (tmp_ptr == s21_NULL) {
    mem_error = 1;
  } else {
    *p_str = tmp_ptr;
  }

  int flag_round = 0;
  for (int i = 0; i < p_token->accuracy; i++) {
    temp = number * pow(10.0, i + 1);
    (*p_str)[count_str + i] = 48 + (int)fmod(temp, 10);
    if (i == p_token->accuracy - 1) {
      temp = number * pow(10.0, i + 2);
      if ((int)fmod(temp, 10) >= 5) {
        flag_round = 1;
        (*p_str)[count_str + p_token->accuracy] = '\0';
        round_str(&(*p_str), count_str + p_token->accuracy);
      }
    }
  }

  if (!flag_round && p_token->accuracy)
    (*p_str)[count_str + p_token->accuracy] = '\0';
}

void round_str(char **p_str, int count_str) {
  int mem_error = 0;
  char *tmp_ptr = s21_NULL;

  int flag = 1;
  for (int i = count_str - 1; flag && (i >= 0); i--) {
    if (((*p_str)[i] == '.') || ((*p_str)[i] == '-') || ((*p_str)[i] == '+')) {
      continue;
    } else {
      if ((*p_str)[i] < '9') {
        (*p_str)[i] += 1;
        flag = 0;
      } else {
        (*p_str)[i] = '0';
      }
    }
  }

  if (flag) {
    tmp_ptr = realloc(*p_str, (count_str + 2) * sizeof(char));
    if (tmp_ptr == s21_NULL) {
      mem_error = 1;
    } else {
      *p_str = tmp_ptr;
      for (int i = count_str; i > 0; i--) {
        if (((*p_str)[i - 1] == '-') || ((*p_str)[i - 1] == '+')) {
          break;
        } else {
          (*p_str)[i] = (*p_str)[i - 1];
        }
      }
      if ((*p_str)[0] == '-') {
        (*p_str)[1] = '1';
      } else {
        (*p_str)[0] = '1';
      }
      (*p_str)[++count_str] = '\0';
    }
  }

  (*p_str)[count_str] = '\0';
  if (mem_error) *p_str = s21_NULL;
}
