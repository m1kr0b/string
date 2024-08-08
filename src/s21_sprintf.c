#include "s21_string.h"

int s21_sprintf(char *str, char *format, ...) {
  va_list ap;
  va_start(ap, format);

  struct mod token = {'\0'};
  token.accuracy = 6;

  char *str_current_adress = str;  // указатель на текущий адрес str
  char *form_current_adress = format;  // указатель на текущий адрес format

  int other = 0;  // проверка на спецификатор
  int flag_entry = 0;
  int space_count = 0;
  // ниже буфферы для разных типов
  char p_value_int[50];
  char *p_value_float = s21_NULL;

  char buff_char;
  char *p_string = s21_NULL;
  char *pp_string = s21_NULL;
  // ниже переменные для short и long флагов
  short short_check = 0;
  unsigned short uns_short_check = 0;
  long long_check = 0;
  unsigned long uns_long_check = 0;

  while (*form_current_adress) {
    if (*form_current_adress == '%' || (other)) {
      if (!other) form_current_adress++;

      micropars(form_current_adress,
                &other);  // проверка на то, включен ли флаг

      if (other) {
        switch (*form_current_adress)  // после прохода спецификатора other
                                       // должен быть = 0
        {
          case 'c':
            buff_char = (char)va_arg(ap, int);
            str_current_adress =
                mod_char(&buff_char, &token, str_current_adress, &flag_entry);
            if (!flag_entry) {
              *str_current_adress++ = buff_char;
              flag_entry = 0;
            }
            form_current_adress++;
            other = 0;
            break;
          case 'd':
            if (token.length == 'h') {
              short_check = (short int)(va_arg(ap, int));
              s21_itoa(short_check, p_value_int,
                       &token);  // переворачиваем, записываем в массив
            } else if (token.length == 'l') {
              long_check = (va_arg(ap, long));
              s21_itoa(long_check, p_value_int,
                       &token);  // переворачиваем, записываем в массив
            } else {
              s21_itoa(va_arg(ap, int), p_value_int, &token);
            }

            str_current_adress =
                mod_integer(p_value_int, &token, str_current_adress,
                            &flag_entry, &space_count);
            if (!flag_entry) {
              str_current_adress = &str[s21_strlen(s21_strcat(
                  str, p_value_int))];  // перенос указателя на текущий str
              flag_entry = 0;
            }
            form_current_adress++;
            other = 0;
            break;
          case 'i':
            if (token.length == 'h') {
              short_check = (short int)(va_arg(ap, int));
              s21_itoa(short_check, p_value_int,
                       &token);  // переворачиваем, записываем в массив
            } else if (token.length == 'l') {
              long_check = (long int)(va_arg(ap, long int));
              s21_itoa(long_check, p_value_int,
                       &token);  // переворачиваем, записываем в массив
            } else {
              s21_itoa(va_arg(ap, int), p_value_int, &token);
            }

            str_current_adress =
                mod_integer(p_value_int, &token, str_current_adress,
                            &flag_entry, &space_count);
            if (!flag_entry) {
              str_current_adress = &str[s21_strlen(s21_strcat(
                  str, p_value_int))];  // перенос указателя на текущий str
              flag_entry = 0;
            }
            form_current_adress++;
            other = 0;
            break;
          case 'f':
            s21_float(va_arg(ap, double), &p_value_float, &token);
            str_current_adress =
                mod_float(p_value_float, &token, str_current_adress,
                          &flag_entry, &space_count);
            if (!flag_entry) {
              str_current_adress = &str[s21_strlen(s21_strcat(
                  str, p_value_float))];  // перенос указателя на текущий str
              flag_entry = 0;
            }
            form_current_adress++;
            other = 0;
            free(p_value_float);
            break;
          case 's':
            pp_string = va_arg(ap, char *);
            p_string = (char *)malloc(
                s21_strlen(pp_string) +
                1 * sizeof(char));  // для преобразования точности
            for (s21_size_t i = 0; i < s21_strlen(pp_string); i++) {
              p_string[i] = pp_string[i];
            }
            p_string[s21_strlen(pp_string)] = '\0';
            str_current_adress =
                mod_string(p_string, &token, str_current_adress, &flag_entry);
            if (!flag_entry) {
              for (s21_size_t i = 0; i < s21_strlen(p_string); i++)
                *str_current_adress++ = p_string[i];
            }
            form_current_adress++;
            other = 0;
            // free(p_string);
            break;
          case 'u':
            if (token.length == 'h') {
              uns_short_check = (va_arg(ap, int));
              s21_itoa_u(uns_short_check,
                         p_value_int);  // переворачиваем, записываем в массив
            } else if (token.length == 'l') {
              uns_long_check = (va_arg(ap, long));
              s21_itoa_u(uns_long_check,
                         p_value_int);  // переворачиваем, записываем в массив
            } else {
              s21_itoa_u(va_arg(ap, int), p_value_int);
            }
            str_current_adress = mod_uns_integer(
                p_value_int, &token, str_current_adress, &flag_entry);
            if (!flag_entry) {
              str_current_adress = &str[s21_strlen(s21_strcat(
                  str, p_value_int))];  // перенос указателя на текущий str
              flag_entry = 0;
            }
            form_current_adress++;
            other = 0;
            break;
          default:
            printf("S21_sprintf: error");
        }
      } else {
        form_current_adress =
            modpars(form_current_adress, &token, &other, &space_count);
      }
    } else {
      *str_current_adress++ = *form_current_adress++;
    }
  }

  va_end(ap);

  return s21_strlen(str);
}
