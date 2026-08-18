#include "day01_baseline.h"

/*
 * 首日诊断骨架故意没有答案。
 * 请先在纸上写出每个函数的正常路径和失败路径，再独立完成 TODO。
 */

bool d1_sum(const int *values, size_t length, int *sum)
{
    (void)values;
    (void)length;
    (void)sum;
    /* TODO：检查参数，遍历数组并通过 sum 返回总和。 */
    int num=0;
    if (values==NULL||sum==NULL) {
        return false;
    }
    else {
        for (size_t i=0;i<length;i++)
        {
            num+=values[i];
            //*num+=values[i];解引用赋值会出现问题
        }
        *sum=num;
    }

    return true;
}

bool d1_max(const int *values, size_t length, int *maximum)
{
    (void)values;
    (void)length;
    (void)maximum;
    /* TODO：空数组没有最大值；非空数组从第一个元素开始比较。 */
    if (length==0||values==NULL||maximum==NULL) {
        return false;
    }
    else {
        *maximum=values[0];
        for (size_t i=0;i<length;i++) {
            if (*maximum<values[i]) {
                *maximum=values[i];
            }
        }

    }
    return true;
}

bool d1_reverse(int *values, size_t length)
{
    (void)values;
    (void)length;
    /* TODO：原地交换数组两端元素，不允许创建第二个等长数组。 */
    if (values==NULL) {
        return false;
    }
    int num=0;
    for (size_t i=0;i<length/2;i++) {
        num=values[i];
        values[i]=values[length-1-i];
        values[length-1-i]=num;
    }
    return true;
}

size_t d1_count_equal(const int *values, size_t length, int target)
{
    (void)values;
    (void)length;
    (void)target;
    /* TODO：统计等于 target 的元素个数；非法输入返回 0。 */
    if (values==NULL) {
        return 0U;
    }
    else {
        size_t count=0;
        for (size_t i=0;i<length;i++) {
            if (values[i]==target) {
                count++;
            }
        }
        return count;
    }

}
