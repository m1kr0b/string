#include "test.h"

START_TEST(sprintf_check)
{
  char str[1000] = {'\0'};
  char str1[1000] = {'\0'};
  int res = s21_sprintf(str, "%3c %.1d %5s", 's', 4, "asd");
  int res1 = sprintf(str1, "%3c %.1d %5s", 's', 4, "asd");
  ck_assert_str_eq(str, str1);
  ck_assert_int_eq(res, res1);

  for (int i = 0; i < 1000; i++)
    str[i] = str1[i] = 0;
  res = s21_sprintf(str, "%.3s %10hd %c", "asdqwe", 42323, 's');
  res1 = sprintf(str1, "%.3s %10hd %c", "asdqwe", 42323, 's');
  ck_assert_str_eq(str, str1);
  ck_assert_int_eq(res, res1);

  for (int i = 0; i < 1000; i++) //!!!!
    str[i] = str1[i] = 0;
  res = s21_sprintf(str, "%3hu %10li %4s", 's', 1234322242323, "asdqwe");
  res1 = sprintf(str1, "%3hu %10li %4s", 's', 1234322242323, "asdqwe");
  ck_assert_str_eq(str, str1);
  ck_assert_int_eq(res, res1);

  for (int i = 0; i < 1000; i++)
    str[i] = str1[i] = 0;
  res = s21_sprintf(str, "%ld", 123332123123);
  res1 = sprintf(str1,"%ld", 123332123123);
  ck_assert_str_eq(str, str1);
  ck_assert_int_eq(res, res1);

  for (int i = 0; i < 1000; i++)
    str[i] = str1[i] = 0;
  res = s21_sprintf(str, "%-3u %10li %4s", 's', 1234322242323, "asdqwe");
  res1 = sprintf(str1, "%-3u %10li %4s", 's', 1234322242323, "asdqwe");
  ck_assert_str_eq(str, str1);
  ck_assert_int_eq(res, res1);

  for (int i = 0; i < 1000; i++)
    str[i] = str1[i] = 0;
  res = s21_sprintf(str, "%+10d", 323);
  res1 = sprintf(str1, "%+10d", 323);
  ck_assert_str_eq(str, str1);
  ck_assert_int_eq(res, res1);

  for (int i = 0; i < 1000; i++)
    str[i] = str1[i] = 0;
  res = s21_sprintf(str, "%-10hd", 7788123);
  res1 = sprintf(str1, "%-10hd", 7788123);
  ck_assert_str_eq(str, str1);
  ck_assert_int_eq(res, res1);

  for (int i = 0; i < 1000; i++)
    str[i] = str1[i] = 0;
  res = s21_sprintf(str, "% d", 123);
  res1 = sprintf(str1, "% d", 123);
  ck_assert_str_eq(str, str1);
  ck_assert_int_eq(res, res1);

    for (int i = 0; i < 1000; i++)
    str[i] = str1[i] = 0;
  res = s21_sprintf(str, "% f", 123.2);
  res1 = sprintf(str1, "% f", 123.2);
  ck_assert_str_eq(str, str1);
  ck_assert_int_eq(res, res1);

    for (int i = 0; i < 1000; i++)
    str[i] = str1[i] = 0;
  res = s21_sprintf(str, "%d", 123);
  res1 = sprintf(str1, "%d", 123);
  ck_assert_str_eq(str, str1);
  ck_assert_int_eq(res, res1);

  for (int i = 0; i < 1000; i++)
    str[i] = str1[i] = 0;
  res = s21_sprintf(str, "%+20f", 30.03);
  res1 = sprintf(str1, "%+20f", 30.03);
  ck_assert_str_eq(str, str1);
  ck_assert_int_eq(res, res1);

  for (int i = 0; i < 1000; i++)
    str[i] = str1[i] = 0;
  res = s21_sprintf(str, "%.10f", -98765.56789);
  res1 = sprintf(str1, "%.10f", -98765.56789);
  ck_assert_str_eq(str, str1);
  ck_assert_int_eq(res, res1);

    for (int i = 0; i < 1000; i++)
    str[i] = str1[i] = 0;
  res = s21_sprintf(str, "%lu %s", 102123321456456, "string");
  res1 = sprintf(str1, "%lu %s", 102123321456456, "string");
  ck_assert_str_eq(str, str1);
  ck_assert_int_eq(res, res1);

    for (int i = 0; i < 1000; i++)
    str[i] = str1[i] = 0;
  res = s21_sprintf(str, "%.2f", 1.999);
  res1 = sprintf(str1, "%.2f", 1.999);
  ck_assert_str_eq(str, str1);
  ck_assert_int_eq(res, res1);

      for (int i = 0; i < 1000; i++)
    str[i] = str1[i] = 0;
  res = s21_sprintf(str, "%.2f", 99.999);
  res1 = sprintf(str1, "%.2f", 99.999);
  ck_assert_str_eq(str, str1);
  ck_assert_int_eq(res, res1);

      for (int i = 0; i < 1000; i++)
    str[i] = str1[i] = 0;
  res = s21_sprintf(str, "%.2f", 0.998);
  res1 = sprintf(str1, "%.2f", 0.998);
  ck_assert_str_eq(str, str1);
  ck_assert_int_eq(res, res1);

      for (int i = 0; i < 1000; i++)
    str[i] = str1[i] = 0;
  res = s21_sprintf(str, "%i %s", 10212, "string");
  res1 = sprintf(str1, "%i %s", 10212, "string");
  ck_assert_str_eq(str, str1);
  ck_assert_int_eq(res, res1);

      for (int i = 0; i < 1000; i++)
    str[i] = str1[i] = 0;
  res = s21_sprintf(str, "%hi", 123);
  res1 = sprintf(str1, "%hi", 123);
  ck_assert_str_eq(str, str1);
  ck_assert_int_eq(res, res1);
  
  for (int i = 0; i < 1000; i++)
    str[i] = str1[i] = 0;
  res = s21_sprintf(str, "%.9f", -98765.56789);
  res1 = sprintf(str1, "%.9f", -98765.56789);
  ck_assert_str_eq(str, str1);
  ck_assert_int_eq(res, res1);

  for (int i = 0; i < 1000; i++)
    str[i] = str1[i] = 0;
  res = s21_sprintf(str, "%.10f", -98765.56789);
  res1 = sprintf(str1, "%.10f", -98765.56789);
  ck_assert_str_eq(str, str1);
  ck_assert_int_eq(res, res1);

  for (int i = 0; i < 1000; i++)
    str[i] = str1[i] = 0;
  res = s21_sprintf(str, "%.11f", -98765.56789);
  res1 = sprintf(str1, "%.11f", -98765.56789);
  ck_assert_str_eq(str, str1);
  ck_assert_int_eq(res, res1);

  for (int i = 0; i < 1000; i++)
    str[i] = str1[i] = 0;
  res = s21_sprintf(str, "%+10.10f", -98765.56789);
  res1 = sprintf(str1, "%+10.10f", -98765.56789);
  ck_assert_str_eq(str, str1);
  ck_assert_int_eq(res, res1);
}
END_TEST

Suite *s21_sprintf_suite()
{
  Suite *s = suite_create("sprintf_suite");
  TCase *tc = tcase_create("sprintf_test");
  tcase_add_test(tc, sprintf_check);
  suite_add_tcase(s, tc);
  return s;
}
