#include <stdio.h>

#include "ring_buffer.h"

/*
 * 这是一个最小测试程序，不依赖第三方测试框架。
 * 每个用例返回 1 表示通过，返回 0 表示失败。
 */

static int tests_run = 0;
static int tests_passed = 0;

#define CHECK(condition, message)                    \
    do                                               \
    {                                                \
        if (!(condition))                            \
        {                                            \
            printf("    原因：%s\n", (message));     \
            return 0;                                \
        }                                            \
    } while (0)

static int test_init_creates_empty_buffer(void)
{
    RingBuffer buffer;

    CHECK(rb_init(&buffer) == RB_OK, "初始化应成功");
    CHECK(rb_size(&buffer) == 0U, "初始化后数量应为 0");
    CHECK(rb_is_empty(&buffer), "初始化后应为空");
    CHECK(!rb_is_full(&buffer), "初始化后不应为满");
    return 1;
}

static int test_push_changes_size(void)
{
    RingBuffer buffer;

    CHECK(rb_init(&buffer) == RB_OK, "初始化应成功");
    CHECK(rb_push(&buffer, 42) == RB_OK, "第一次写入应成功");
    CHECK(rb_size(&buffer) == 1U, "写入后数量应为 1");
    return 1;
}

static int test_fifo_order(void)
{
    RingBuffer buffer;
    int value = 0;

    CHECK(rb_init(&buffer) == RB_OK, "初始化应成功");
    CHECK(rb_push(&buffer, 10) == RB_OK, "写入 10 应成功");
    CHECK(rb_push(&buffer, 20) == RB_OK, "写入 20 应成功");
    CHECK(rb_pop(&buffer, &value) == RB_OK, "第一次读取应成功");
    CHECK(value == 10, "应先读出最早写入的 10");
    CHECK(rb_pop(&buffer, &value) == RB_OK, "第二次读取应成功");
    CHECK(value == 20, "随后应读出 20");
    return 1;
}

static int test_full_buffer_rejects_push(void)
{
    RingBuffer buffer;
    size_t index;

    CHECK(rb_init(&buffer) == RB_OK, "初始化应成功");
    for (index = 0U; index < RB_CAPACITY; index++)
    {
        CHECK(rb_push(&buffer, (int)index) == RB_OK, "容量范围内写入应成功");
    }
    CHECK(rb_is_full(&buffer), "写满后应报告已满");
    CHECK(rb_push(&buffer, 99) == RB_FULL, "写满后继续写入应返回 RB_FULL");
    CHECK(rb_size(&buffer) == RB_CAPACITY, "失败写入不能改变数量");
    return 1;
}

static int test_wrap_around_keeps_order(void)
{
    RingBuffer buffer;
    int value = 0;
    int index;

    CHECK(rb_init(&buffer) == RB_OK, "初始化应成功");
    for (index = 0; index < 6; index++)
    {
        CHECK(rb_push(&buffer, index) == RB_OK, "第一批写入应成功");
    }
    for (index = 0; index < 4; index++)
    {
        CHECK(rb_pop(&buffer, &value) == RB_OK, "第一批读取应成功");
        CHECK(value == index, "第一批读取顺序不正确");
    }
    for (index = 6; index < 10; index++)
    {
        CHECK(rb_push(&buffer, index) == RB_OK, "回绕后的写入应成功");
    }
    for (index = 4; index < 10; index++)
    {
        CHECK(rb_pop(&buffer, &value) == RB_OK, "回绕后的读取应成功");
        CHECK(value == index, "回绕后仍应保持先进先出");
    }
    return 1;
}

static int test_empty_buffer_rejects_pop(void)
{
    RingBuffer buffer;
    int value = 123;

    CHECK(rb_init(&buffer) == RB_OK, "初始化应成功");
    CHECK(rb_pop(&buffer, &value) == RB_EMPTY, "空缓冲区读取应返回 RB_EMPTY");
    CHECK(value == 123, "失败读取不应修改输出变量");
    return 1;
}

static int test_invalid_arguments(void)
{
    RingBuffer buffer;
    int value = 0;

    CHECK(rb_init(NULL) == RB_INVALID_ARGUMENT, "初始化空指针应失败");
    CHECK(rb_push(NULL, 1) == RB_INVALID_ARGUMENT, "向空指针写入应失败");
    CHECK(rb_pop(NULL, &value) == RB_INVALID_ARGUMENT, "从空指针读取应失败");
    CHECK(rb_init(&buffer) == RB_OK, "正常初始化应成功");
    CHECK(rb_pop(&buffer, NULL) == RB_INVALID_ARGUMENT, "输出指针为空应失败");
    CHECK(rb_peek(&buffer, NULL) == RB_INVALID_ARGUMENT, "查看时输出指针为空应失败");
    return 1;
}

static int test_peek_does_not_remove_value(void)
{
    RingBuffer buffer;
    int value = 0;

    CHECK(rb_init(&buffer) == RB_OK, "初始化应成功");
    CHECK(rb_push(&buffer, 77) == RB_OK, "写入应成功");
    CHECK(rb_peek(&buffer, &value) == RB_OK, "查看队首应成功");
    CHECK(value == 77, "查看到的值应为 77");
    CHECK(rb_size(&buffer) == 1U, "peek 不应删除元素");
    return 1;
}

static void run_test(const char *name, int (*test_function)(void))
{
    int passed;

    tests_run++;
    printf("进度 %d/8：%s\n", tests_run, name);
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
    run_test("初始化为空", test_init_creates_empty_buffer);
    run_test("写入改变数量", test_push_changes_size);
    run_test("先进先出", test_fifo_order);
    run_test("写满后拒绝写入", test_full_buffer_rejects_push);
    run_test("下标回绕", test_wrap_around_keeps_order);
    run_test("空缓冲区拒绝读取", test_empty_buffer_rejects_pop);
    run_test("非法参数", test_invalid_arguments);
    run_test("peek 不删除数据", test_peek_does_not_remove_value);

    printf("\n测试结果：%d/%d 通过\n", tests_passed, tests_run);
    return (tests_passed == tests_run) ? 0 : 1;
}

