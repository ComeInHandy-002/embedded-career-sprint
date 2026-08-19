#ifndef DAY02_POINTERS_H
#define DAY02_POINTERS_H

#include <stdbool.h>
#include <stddef.h>

/*
 * 第 2 天只训练指针、数组和输出参数。
 * 返回 false 表示参数非法；失败时不得修改调用者原有数据。
 */
bool d2_swap_int(int *left, int *right);
bool d2_min_max(const int *values, size_t length, int *minimum, int *maximum);
size_t d2_string_length(const char *text);

#endif
