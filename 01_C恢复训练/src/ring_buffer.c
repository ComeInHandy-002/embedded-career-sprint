#include "ring_buffer.h"

/*
 * 这个文件故意只保留可编译的骨架，不包含正确答案。
 * 请先在纸上写清楚每个函数的输入、输出和状态变化，再逐个实现。
 */

RbStatus rb_init(RingBuffer *buffer)
{
    (void)buffer;
    /* TODO：检查空指针，并把 head、tail、count 恢复到初始状态。 */
    if (buffer==NULL) {
        return RB_INVALID_ARGUMENT;
    }
    buffer->head=0U;
    buffer->tail=0U;
    buffer->count=0U;
    return RB_OK;
}

RbStatus rb_push(RingBuffer *buffer, int value)
{
    (void)buffer;
    (void)value;
    /* TODO：检查参数和满状态，写入数据，并处理 tail 回绕。 */
    if (buffer==NULL) {
        return RB_INVALID_ARGUMENT;
    }
    if (buffer->count==RB_CAPACITY) {
        return RB_FULL;
    }
    buffer->data[buffer->tail]=value;
    buffer->tail=(buffer->tail+1U)%RB_CAPACITY;
    buffer->count+=1U;
    return RB_OK;
}

RbStatus rb_pop(RingBuffer *buffer, int *value)
{
    (void)buffer;
    (void)value;
    /* TODO：检查参数和空状态，读出数据，并处理 head 回绕。 */
    if (buffer==NULL||value==NULL) {
        return RB_INVALID_ARGUMENT;
    }
    if (buffer->count==0) {
        return RB_EMPTY;
    }
    *value=buffer->data[buffer->head];
    buffer->head=(buffer->head+1U)%RB_CAPACITY;
    buffer->count-=1U;
    return RB_OK;
}

RbStatus rb_peek(const RingBuffer *buffer, int *value)
{
    (void)buffer;
    (void)value;
    /* TODO：读取队首数据，但不能改变 head、tail 和 count。 */
    if (buffer==NULL||value==NULL) {
        return RB_INVALID_ARGUMENT;
    }
    if (buffer->count==0U) {
        return RB_EMPTY;
    }
    *value=buffer->data[buffer->head];

    return RB_OK;
}

size_t rb_size(const RingBuffer *buffer)
{
    (void)buffer;
    /* TODO：空指针返回 0，否则返回当前元素数量。 */
    if (buffer==NULL) {
        return 0U;
    }
    return buffer->count;
}

bool rb_is_empty(const RingBuffer *buffer)
{
    (void)buffer;
    /* TODO：空指针按“空”处理，否则判断 count。 */
    if (buffer==NULL) {
        return true;
    }
    if (buffer->count==0U) {
        return true;
    }
    return false;
}

bool rb_is_full(const RingBuffer *buffer)
{
    (void)buffer;
    /* TODO：空指针不能视为已满，否则判断 count。 */
    if (buffer==NULL) {
        return false;
    }
    return buffer->count==RB_CAPACITY;
}

