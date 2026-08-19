#include <stdio.h>

#include "day02_pointers.h"

static int tests_run = 0;
static int tests_passed = 0;

#define CHECK(condition, message)                \
    do                                           \
    {                                            \
        if (!(condition))                        \
        {                                        \
            printf("    原因：%s\n", message); \
            return 0;                            \
        }                                        \
    } while (0)

static int test_swap_changes_both_values(void)
{
    int left = 12;
    int right = -3;

    CHECK(d2_swap_int(&left, &right), "两个有效指针应交换成功");
    CHECK(left == -3, "交换后 left 应为 -3");
    CHECK(right == 12, "交换后 right 应为 12");
    return 1;
}

static int test_swap_rejects_null(void)
{
    int value = 7;

    CHECK(!d2_swap_int(NULL, &value), "left 为空时应失败");
    CHECK(value == 7, "失败时不能修改有效参数");
    CHECK(!d2_swap_int(&value, NULL), "right 为空时应失败");
    CHECK(value == 7, "第二次失败也不能修改有效参数");
    return 1;
}

static int test_min_max_handles_mixed_values(void)
{
    const int values[] = {5, -2, 9, 1, -7};
    int minimum = 0;
    int maximum = 0;

    CHECK(d2_min_max(values, 5U, &minimum, &maximum), "正常数组应计算成功");
    CHECK(minimum == -7, "最小值应为 -7");
    CHECK(maximum == 9, "最大值应为 9");
    return 1;
}

static int test_min_max_handles_all_negative_values(void)
{
    const int values[] = {-8, -3, -11, -5};
    int minimum = 0;
    int maximum = 0;

    CHECK(d2_min_max(values, 4U, &minimum, &maximum), "全负数数组也应成功");
    CHECK(minimum == -11, "全负数数组最小值应为 -11");
    CHECK(maximum == -3, "全负数数组最大值应为 -3");
    return 1;
}

static int test_min_max_rejects_invalid_arguments(void)
{
    const int values[] = {1, 2};
    int minimum = 123;
    int maximum = 456;

    CHECK(!d2_min_max(NULL, 2U, &minimum, &maximum), "数组为空时应失败");
    CHECK(minimum == 123 && maximum == 456, "失败时不能修改两个输出值");
    CHECK(!d2_min_max(values, 0U, &minimum, &maximum), "长度为 0 时应失败");
    CHECK(!d2_min_max(values, 2U, NULL, &maximum), "minimum 为空时应失败");
    CHECK(!d2_min_max(values, 2U, &minimum, NULL), "maximum 为空时应失败");
    return 1;
}

static int test_string_length(void)
{
    CHECK(d2_string_length("STM32") == 5U, "STM32 包含 5 个字符");
    CHECK(d2_string_length("") == 0U, "空字符串长度应为 0");
    CHECK(d2_string_length(NULL) == 0U, "空指针输入应返回 0");
    return 1;
}

static void run_test(const char *name, int (*test_function)(void))
{
    int passed;

    tests_run++;
    printf("进度 %d/6：%s\n", tests_run, name);
    passed = test_function();
    if (passed != 0)
    {
        tests_passed++;
        printf("    结果：通过\n");
    }
    else
    {
        printf("    结果：失败\n");
    }
}

int main(void)
{
    run_test("指针交换", test_swap_changes_both_values);
    run_test("交换的空指针检查", test_swap_rejects_null);
    run_test("混合数组最小最大值", test_min_max_handles_mixed_values);
    run_test("全负数最小最大值", test_min_max_handles_all_negative_values);
    run_test("最小最大值参数检查", test_min_max_rejects_invalid_arguments);
    run_test("字符串长度", test_string_length);

    printf("\n第 2 天结果：%d/%d 通过\n", tests_passed, tests_run);
    return (tests_passed == tests_run) ? 0 : 1;
}
