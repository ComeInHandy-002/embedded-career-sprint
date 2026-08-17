#include <stdio.h>

#include "day01_baseline.h"

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

static int test_sum_normal_array(void)
{
    const int values[] = {3, -2, 7, 1};
    int sum = 0;

    CHECK(d1_sum(values, 4U, &sum), "正常数组求和应成功");
    CHECK(sum == 9, "3 + (-2) + 7 + 1 应等于 9");
    return 1;
}

static int test_sum_rejects_invalid_arguments(void)
{
    const int values[] = {1, 2};
    int valid_sum = 0;
    int sum = 123;

    CHECK(d1_sum(values, 2U, &valid_sum), "先确认正常数组求和已经实现");
    CHECK(!d1_sum(NULL, 2U, &sum), "数组指针为空时应失败");
    CHECK(sum == 123, "失败时不能修改输出值");
    CHECK(!d1_sum(values, 2U, NULL), "输出指针为空时应失败");
    return 1;
}

static int test_max_handles_negative_values(void)
{
    const int values[] = {-8, -3, -11, -5};
    int maximum = 0;

    CHECK(d1_max(values, 4U, &maximum), "非空数组求最大值应成功");
    CHECK(maximum == -3, "全为负数时最大值应为 -3");
    return 1;
}

static int test_max_rejects_empty_array(void)
{
    const int values[] = {9};
    int valid_maximum = 0;
    int maximum = 456;

    CHECK(d1_max(values, 1U, &valid_maximum), "先确认非空数组最大值已经实现");
    CHECK(!d1_max(values, 0U, &maximum), "长度为 0 时应失败");
    CHECK(maximum == 456, "失败时不能修改输出值");
    return 1;
}

static int test_reverse_changes_array_in_place(void)
{
    int values[] = {1, 2, 3, 4, 5};
    const int expected[] = {5, 4, 3, 2, 1};
    size_t index;

    CHECK(d1_reverse(values, 5U), "正常数组反转应成功");
    for (index = 0U; index < 5U; index++)
    {
        CHECK(values[index] == expected[index], "反转后的元素顺序不正确");
    }
    CHECK(!d1_reverse(NULL, 5U), "数组指针为空时应失败");
    return 1;
}

static int test_count_equal_handles_matches(void)
{
    const int values[] = {4, 2, 4, 4, 7, 2};

    CHECK(d1_count_equal(values, 6U, 4) == 3U, "数组中应有 3 个 4");
    CHECK(d1_count_equal(values, 6U, 9) == 0U, "数组中没有 9");
    CHECK(d1_count_equal(NULL, 6U, 4) == 0U, "非法输入应返回 0");
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
    run_test("数组求和", test_sum_normal_array);
    run_test("求和参数检查", test_sum_rejects_invalid_arguments);
    run_test("负数数组最大值", test_max_handles_negative_values);
    run_test("空数组没有最大值", test_max_rejects_empty_array);
    run_test("原地反转数组", test_reverse_changes_array_in_place);
    run_test("统计目标值", test_count_equal_handles_matches);

    printf("\n诊断结果：%d/%d 通过\n", tests_passed, tests_run);
    return (tests_passed == tests_run) ? 0 : 1;
}
