#ifndef RING_BUFFER_H
#define RING_BUFFER_H

/*
 * 本练习只依赖 C 标准库，不需要安装任何第三方库。
 * size_t 来自 stddef.h，bool 来自 stdbool.h。
 */
#include <stdbool.h>
#include <stddef.h>

/* 固定容量便于第一周观察回绕过程，暂时不做动态内存分配。 */
#define RB_CAPACITY 8U

/* 每个公开函数都通过状态码明确报告成功或失败。 */
typedef enum
{
    RB_OK = 0,
    RB_EMPTY,
    RB_FULL,
    RB_INVALID_ARGUMENT
} RbStatus;

/*
 * data：实际保存整数的位置。
 * head：下一次读取的位置。
 * tail：下一次写入的位置。
 * count：当前有效元素数量。
 */
typedef struct
{
    int data[RB_CAPACITY];
    size_t head;
    size_t tail;
    size_t count;
} RingBuffer;

RbStatus rb_init(RingBuffer *buffer);
RbStatus rb_push(RingBuffer *buffer, int value);
RbStatus rb_pop(RingBuffer *buffer, int *value);
RbStatus rb_peek(const RingBuffer *buffer, int *value);
size_t rb_size(const RingBuffer *buffer);
bool rb_is_empty(const RingBuffer *buffer);
bool rb_is_full(const RingBuffer *buffer);

#endif

