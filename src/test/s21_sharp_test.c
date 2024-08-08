#include "test.h"

START_TEST(sharp_check)
{
  char *src = "qwerty";
  char *str = "1234567";
  char *new_string = s21_insert(src, str, 3);
  ck_assert_str_eq(new_string, "qwe1234567rty"); // INSERT
  free(new_string);

  char *str1e = "aaabbb";
  char *str2e = " ";
  char *str3e = s21_insert(str1e, str2e, 3);
  ck_assert_str_eq(str3e, "aaa bbb");
  free(str3e);

  char *str1w = "/0/0/0\0a111";
  char *str2w = "ppp";
  char *str3w = s21_insert(str1w, str2w, 4);
  ck_assert_str_eq(str3w, "/0/0ppp/0");
  free(str3w);

  char str1a[80] = "Abcde";
  char str2a[80] = "123";
  s21_size_t index = -1;
  char *res = s21_insert(str1a, str2a, index);
  ck_assert_ptr_eq(res, s21_NULL);
  if (res)
  free(res);

  char *src1 = "qwerty";
  char *str1 = "et";
  char *new_string1 = s21_trim(src1, str1); // TRIM
  ck_assert_str_eq(new_string1, "qwerty");

  char src4[] = "     &#@\n\n\t Hello, World! *&#@\n\t   ";
  char trim_chars[] = " &#@\n\t";
  char *psrc = s21_trim(src4, trim_chars);
  ck_assert_pstr_eq(psrc, "Hello, World! *");
  free(psrc);

  char *str1q = "\0w1111222f333";
  char *str2q = "132f";
  char *str3q = s21_trim(str1q, str2q);
  ck_assert_str_eq(str3q, "");
  free(str3q);

  char src5[] = "   ";
  char trim_chars1[] = " ";
  psrc = s21_trim(src5, trim_chars1);
  ck_assert_pstr_eq(psrc, "");
  free(psrc);

  char *src2 = "qwerty";
  char *new_string2 = s21_to_upper(src2);
  ck_assert_pstr_eq(new_string2, "QWERTY");
  free(new_string2);

  char *src3 = "QWERTY";
  char *new_string3 = s21_to_lower(src3);
  ck_assert_pstr_eq(new_string3, "qwerty");
  free(new_string3);
}
END_TEST

Suite *s21_sharp_suite()
{
  Suite *s = suite_create("sharp_suite");
  TCase *tc = tcase_create("sharp_test");
  tcase_add_test(tc, sharp_check);
  suite_add_tcase(s, tc);
  return s;
}