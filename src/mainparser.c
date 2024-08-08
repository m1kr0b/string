#include "s21_string.h"
void micropars(char *form_current_addres, int *other) {
  char flags[] = {'c', 'd', 'i', 'e', 'E', 'f', 'g', 'G',
                  'o', 's', 'u', 'x', 'X', 'p', 'n', '\0'};

  *other = 0;

  for (int i = 0; flags[i] != '\0'; i++) {
    if (flags[i] == *form_current_addres) {
      *other = 1;
    }
  }
}

char *modpars(char *form_current_address, struct mod *p_token, int *other,
              int *space_count) {
  char *buff;
  char *tmp = s21_NULL;
  int mem_error = 0;
  buff = malloc(sizeof(char));
  buff[0] = '\0';

  if (*form_current_address == '-' ||  // флаги
      *form_current_address == '+' || *form_current_address == ' ') {
    p_token->flag = *form_current_address++;
    if (p_token->flag == ' ') {
      (*space_count)++;
    }
    *other = 1;
  }

  for (int i = 0; *form_current_address >= 48 && *form_current_address <= 57;
       i++)  // ШИРИНА - заносим в массив buff цифры по аски
  {
    buff[i] = *form_current_address++;
    tmp = realloc(buff, (i + 2) * sizeof(char));  // запись в буфферный массив
    if (tmp == s21_NULL) {
      mem_error = 1;
    } else {
      buff = tmp;
      buff[i + 1] = '\0';
      *other = 1;
    }
  }

  p_token->width = s21_atoi(buff);  // перевод из чар в инт число

  tmp = realloc(
      buff,
      sizeof(
          char));  // очистка буфферного массива, до состояния в момент маллок
  if (tmp == s21_NULL) {
    mem_error = 1;
  } else {
    buff = tmp;
    *buff = '\0';
  }

  if (*form_current_address == '.')  // Точность
  {
    form_current_address++;
    for (int i = 0; *form_current_address >= 48 && *form_current_address <= 57;
         i++) {
      buff[i] = *form_current_address++;
      tmp = realloc(buff, (i + 2) * sizeof(char));
      if (tmp == s21_NULL) {
        mem_error = 1;
      } else {
        buff = tmp;
        buff[i + 1] = '\0';
      }
    }
    *other = 1;
  }
  if (*buff != '\0') {
    p_token->accuracy = s21_atoi(buff);
    tmp = realloc(buff, sizeof(char));
    if (tmp == s21_NULL) {
      mem_error = 1;
    } else {
      buff = tmp;
      *buff = '\0';
    }
  }

  if (*form_current_address == 'h' ||  // длина
      *form_current_address == 'l') {
    p_token->length = *form_current_address++;
    *other = 1;
  }
  free(buff);

  if (mem_error) form_current_address = s21_NULL;
  return form_current_address;
}

char *mod_char(char *p_char, struct mod *p_token, char *str_current_adress,
               int *flag_entry)  // доделать длину l, доделать просто цифру
{
  *flag_entry = 0;

  if (p_token->flag == '+') {
    if (p_token->width) {
      for (int i = 1; i < p_token->width; i++) {
        *str_current_adress++ = ' ';
      }
    }
    *str_current_adress++ = *p_char;
    *str_current_adress = '\0';
    *flag_entry = 1;
  }

  if (p_token->flag == '-') {
    *str_current_adress++ = *p_char;
    if (p_token->width) {
      for (int i = 1; i < p_token->width; i++) {
        *str_current_adress++ = ' ';
      }
    }
    *str_current_adress = '\0';
    *flag_entry = 1;
  }

  if (p_token->width && *flag_entry == 0) {
    for (int i = 1; i < p_token->width; i++) {
      *str_current_adress++ = ' ';
    }
    *str_current_adress++ = *p_char;
    *str_current_adress = '\0';
    *flag_entry = 1;
  }

  p_token->flag = 0;
  p_token->accuracy = 6;
  p_token->length = 0;
  p_token->width = 0;

  return str_current_adress;
}

char *mod_integer(char *p_value_int, struct mod *p_token,
                  char *str_current_adress, int *flag_entry, int *space_count) {
  *flag_entry = 0;

  if (*space_count) {
    for (int i = 0; i < *space_count; i++) *str_current_adress++ = ' ';
  }

  if (p_token->flag == '+') {
    if (p_token->width) {
      for (int i = s21_strlen(p_value_int); i < p_token->width; i++) {
        *str_current_adress++ = ' ';
      }
    }
    str_current_adress = &str_current_adress[s21_strlen(
        s21_strcat(str_current_adress, p_value_int))];
    *flag_entry = 1;
  }

  if (p_token->flag == '-') {
    str_current_adress = &str_current_adress[s21_strlen(
        s21_strcat(str_current_adress, p_value_int))];
    if (p_token->width) {
      for (int i = s21_strlen(p_value_int); i < p_token->width; i++) {
        *str_current_adress++ = ' ';
      }
      *str_current_adress = '\0';
    }
    *flag_entry = 1;
  }

  if (p_token->width && *flag_entry == 0) {
    for (int i = s21_strlen(p_value_int); i < p_token->width; i++) {
      *str_current_adress++ = ' ';
    }
    str_current_adress = &str_current_adress[s21_strlen(
        s21_strcat(str_current_adress, p_value_int))];
    *flag_entry = 1;
  }
  p_token->flag = 0;
  p_token->accuracy = 6;
  p_token->length = 0;
  p_token->width = 0;

  return str_current_adress;
}

char *mod_uns_integer(char *p_value_int, struct mod *p_token,
                      char *str_current_adress, int *flag_entry) {
  *flag_entry = 0;

  if (p_token->flag == '+') {
    if (p_token->width) {
      for (int i = s21_strlen(p_value_int); i < p_token->width; i++) {
        *str_current_adress++ = ' ';
      }
    }
    str_current_adress = &str_current_adress[s21_strlen(
        s21_strcat(str_current_adress, p_value_int))];
    *flag_entry = 1;
  }

  if (p_token->flag == '-') {
    str_current_adress = &str_current_adress[s21_strlen(
        s21_strcat(str_current_adress, p_value_int))];
    if (p_token->width) {
      for (int i = s21_strlen(p_value_int); i < p_token->width; i++) {
        *str_current_adress++ = ' ';
      }
      *str_current_adress = '\0';
    }
    *flag_entry = 1;
  }

  if (p_token->width && *flag_entry == 0) {
    for (int i = s21_strlen(p_value_int); i < p_token->width; i++) {
      *str_current_adress++ = ' ';
    }
    str_current_adress = &str_current_adress[s21_strlen(
        s21_strcat(str_current_adress, p_value_int))];
    *flag_entry = 1;
  }

  p_token->flag = 0;
  p_token->accuracy = 6;
  p_token->length = 0;
  p_token->width = 0;

  return str_current_adress;
}

char *mod_string(char *p_string, struct mod *p_token, char *str_current_adress,
                 int *flag_entry) {
  *flag_entry = 0;

  char *tmp = s21_NULL;
  int mem_error = 0;

  if (p_token->flag == '+') {
    if (p_token->accuracy) {
      p_string = realloc(p_string, p_token->accuracy * sizeof(char));
      p_string[p_token->accuracy] = '\0';
      *flag_entry = 1;
    }

    if (p_token->width) {
      for (int i = s21_strlen(p_string); i < p_token->width; i++) {
        *str_current_adress++ = ' ';
      }
      *flag_entry = 1;
    }

    str_current_adress = &str_current_adress[s21_strlen(
        s21_strcat(str_current_adress, p_string))];
  }

  if (p_token->flag == '-') {
    if (p_token->accuracy) {
      p_string = realloc(p_string, p_token->accuracy * sizeof(char));
      p_string[p_token->accuracy] = '\0';
      *flag_entry = 1;
    }

    str_current_adress = &str_current_adress[s21_strlen(
        s21_strcat(str_current_adress, p_string))];
    if (p_token->width) {
      for (int i = s21_strlen(p_string); i < p_token->width; i++) {
        *str_current_adress++ = ' ';
      }
      *str_current_adress = '\0';
      *flag_entry = 1;
    }
  }

  if (p_token->width && *flag_entry == 0) {
    if (p_token->accuracy) {
      tmp = realloc(p_string, p_token->accuracy * sizeof(char));
      if (tmp == s21_NULL) {
        mem_error = 1;
      } else {
        p_string = tmp;
        p_string[p_token->accuracy] = '\0';
        *flag_entry = 1;
      }
    }

    for (int i = s21_strlen(p_string); i < p_token->width; i++) {
      *str_current_adress++ = ' ';
    }

    str_current_adress = &str_current_adress[s21_strlen(
        s21_strcat(str_current_adress, p_string))];
    *flag_entry = 1;
  }

  if (p_token->accuracy && *flag_entry == 0) {
    tmp = realloc(p_string, p_token->accuracy * sizeof(char));
    if (tmp == s21_NULL) {
      mem_error = 1;
    } else {
      p_string = tmp;
      p_string[p_token->accuracy] = '\0';
      str_current_adress = &str_current_adress[s21_strlen(
          s21_strcat(str_current_adress, p_string))];
      *flag_entry = 1;
    }
  }

  p_token->flag = 0;
  p_token->accuracy = 6;
  p_token->length = 0;
  p_token->width = 0;

  if (mem_error) str_current_adress = s21_NULL;
  free(p_string);
  return str_current_adress;
}

char *mod_float(char *p_value_float, struct mod *p_token,
                char *str_current_adress, int *flag_entry, int *space_count) {
  *flag_entry = 0;

  if (*space_count) {
    for (int i = 0; i < *space_count; i++) *str_current_adress++ = ' ';
  }

  if (p_token->flag == '+') {
    if (p_token->width) {
      for (int i = s21_strlen(p_value_float); i < p_token->width; i++) {
        *str_current_adress++ = ' ';
      }
      *flag_entry = 1;
    }

    str_current_adress = &str_current_adress[s21_strlen(
        s21_strcat(str_current_adress, p_value_float))];
  }

  if (p_token->flag == '-') {
    str_current_adress = &str_current_adress[s21_strlen(
        s21_strcat(str_current_adress, p_value_float))];
    if (p_token->width) {
      for (int i = s21_strlen(p_value_float); i < p_token->width; i++) {
        *str_current_adress++ = ' ';
      }
      *str_current_adress = '\0';
      *flag_entry = 1;
    }
  }

  if (p_token->width && *flag_entry == 0) {
    for (int i = s21_strlen(p_value_float); i < p_token->width; i++) {
      *str_current_adress++ = ' ';
    }

    str_current_adress = &str_current_adress[s21_strlen(
        s21_strcat(str_current_adress, p_value_float))];
    *flag_entry = 1;
  }

  p_token->flag = 0;
  p_token->accuracy = 6;
  p_token->length = 0;
  p_token->width = 0;

  return str_current_adress;
}