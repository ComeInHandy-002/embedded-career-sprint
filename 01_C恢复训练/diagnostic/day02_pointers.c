#include "day02_pointers.h"

bool d2_swap_int(int *left, int *right)
{
    (void)left;
    (void)right;
    /* TODO：检查两个指针，再通过临时变量交换它们指向的整数。 */
    if (left==NULL||right==NULL) {
        return false;
    }
    int temp_num=0;
    temp_num=*left;
    *left=*right;
    *right=temp_num;
    return true;

}

bool d2_min_max(const int *values, size_t length, int *minimum, int *maximum)
{
    (void)values;
    (void)length;
    (void)minimum;
    (void)maximum;
    /* TODO：检查参数，在局部变量中求最小值和最大值，成功后再写输出。 */
    if (values==NULL||length==0||minimum==NULL||maximum==NULL) {
        return false;
    }
    int min,max;
    min=max=values[0];
    for (size_t i=0;i<length;i++) {
        if (values[i]<min) {
            min=values[i];
        }
        else {
            if (values[i]>max) {
                max=values[i];
            }
        }
    }
    *minimum=min;
    *maximum=max;
    return true;
}

size_t d2_string_length(const char *text)
{
    (void)text;
    /* TODO：空指针返回 0；否则从首字符遍历到 '\0'，返回字符数量。 */
    if (text==NULL) {
        return 0U;
    }
    size_t i=0U;
    size_t count=0U;
    while (text[i]!='\0') {
        count++;
        i++;
    }
    return count;
}
