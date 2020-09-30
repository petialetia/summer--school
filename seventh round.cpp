#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <iso646.h>


typedef int Elem_t;

const int MAX_START_SIZE_STACK = 2000000;
const int ERROR = -1;
const Elem_t MAX_INT = 1231231;

struct elemAndMin
{
    Elem_t elem_ = 0;
    Elem_t min_ = 0;
};

struct Stack
{
    uint64_t capacity_ = 0;
    uint64_t size_ = 0;
    elemAndMin* buffer_ = nullptr;
    Elem_t min_ = MAX_INT;
};

int front(Stack* stackin, Stack* stackout);
void pop(Stack* stack);
int isEmpty(Stack* stack);
int top(Stack* stack);
int sizeQueue(Stack* stackin, Stack* stackout);


void Construct(Stack* stack, uint64_t size)
{
    assert(stack);
    assert(size < MAX_START_SIZE_STACK);

    stack->buffer_ = (elemAndMin*)calloc(size, sizeof(elemAndMin));
    stack->size_ = 0;
    stack->capacity_ = size;
    stack->buffer_[0].min_ = MAX_INT;
}

void enqueue(Stack* stack, Elem_t value)
{
    assert(stack);

    stack->size_++;
    if (stack->size_ == stack->capacity_)
    {
        elemAndMin* tmp = (elemAndMin*)realloc(stack->buffer_, stack->capacity_ * sizeof(elemAndMin) * 2);
        stack->capacity_ *= 2;
        assert(tmp);
        stack->buffer_ = tmp;
    }
    stack->buffer_[stack->size_].elem_ = value;

    if (stack->size_ == 1)
    {
        stack->buffer_[stack->size_].min_ = stack->buffer_[stack->size_].elem_;
    }
    else
    {
        if (stack->buffer_[stack->size_].elem_ < stack->buffer_[stack->size_ - 1].min_)
        {
            stack->buffer_[stack->size_].min_ = stack->buffer_[stack->size_].elem_;
        }
        else
        {
            stack->buffer_[stack->size_].min_ = stack->buffer_[stack->size_ - 1].min_;
        }
    }
}

int minQueue(Stack* stackin, Stack* stackout)
{
    if (sizeQueue > 0)
    {
        if (stackin->buffer_[stackin->size_].min_ < stackout->buffer_[stackout->size_].min_)
        {
            return stackin->buffer_[stackin->size_].min_ ;
        }
        else
        {
            return stackout->buffer_[stackout->size_].min_;
        }
    }
    else
    {
        return ERROR;
    }
}

int dequeue(Stack* stackin, Stack* stackout)
{
    int tmp = front(stackin, stackout);
    pop(stackout);
    return tmp;
}

int front(Stack* stackin, Stack* stackout)
{
    assert(stackin);
    assert(stackout);

    if (sizeQueue(stackin, stackout) > 0)
    {
        if (!isEmpty(stackout))
        {
            return stackout->buffer_[stackout->size_].elem_;
        }
        else
        {
            while (!isEmpty(stackin))
            {
                enqueue(stackout, top(stackin));
                pop(stackin);
            }
        }
        return stackout->buffer_[stackout->size_].elem_;
    }
    else
    {
        return ERROR;
    }
}

int top(Stack* stack)
{
    return stack->buffer_[stack->size_].elem_;
}


void pop(Stack* stack)
{
    assert(stack);

    if (stack->size_ > 0)
    {
        stack->buffer_[stack->size_].elem_ = 0;
        stack->size_--;
    }
}

int sizeQueue(Stack* stackin, Stack* stackout)
{
    return (stackin->size_ + stackout->size_);
}

void clear(Stack* stackin, Stack* stackout)
{
    free(stackin->buffer_);
    stackin->size_ = 0;
    stackin->capacity_ = 0;
    stackin = nullptr;
    stackin->buffer_ = nullptr;

    free(stackout->buffer_);
    stackout->size_ = 0;
    stackout->capacity_ = 0;
    stackout = nullptr;
    stackout->buffer_ = nullptr;

    printf("ok\n");
}

int isEmpty(Stack* stack)
{
    assert(stack);

    if (stack->size_ == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int main()
{
    Stack stackIn  = {};
    Stack stackOut = {};
    Construct(&stackIn, 1);
    Construct(&stackOut, 1);
    enqueue(&stackIn, 2);
    enqueue(&stackIn, 4);
    enqueue(&stackIn, 6);
    enqueue(&stackIn, 8);

    printf("%d\n", front(&stackIn, &stackOut));
    printf("%d\n", dequeue(&stackIn, &stackOut));
    printf("%d\n", minQueue(&stackIn, &stackOut));



    return 0;
}
