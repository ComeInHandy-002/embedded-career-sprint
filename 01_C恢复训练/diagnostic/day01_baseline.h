#ifndef DAY01_BASELINE_H
#define DAY01_BASELINE_H

#include <stdbool.h>
#include <stddef.h>

/*
 * 返回 true 表示成功，返回 false 表示参数非法。
 * 失败时不得修改输出参数指向的值。
 */
bool d1_sum(const int *values, size_t length, int *sum);
bool d1_max(const int *values, size_t length, int *maximum);
bool d1_reverse(int *values, size_t length);
size_t d1_count_equal(const int *values, size_t length, int target);

#endif
