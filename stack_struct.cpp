#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

const int MAX_START_SIZE_STACK = 2000000;
//typedef double Elem_t;

struct Stack
{
    uint64_t capacity_ = 0;
    uint64_t size_ = 0;
    int* buffer_ = nullptr;
};


void Construct(Stack* stack, uint64_t size)
{
    assert(stack);
    assert(size < MAX_START_SIZE_STACK);

    stack->buffer_ = (int*)calloc(size, sizeof(int));
    stack->size_ = 0;
    stack->capacity_ = size;
}

void push(Stack* stack, int value)
{
    assert(stack);

    stack->size_++;
    if (stack->size_ == stack->capacity_)
    {
        int* tmp = (int*)realloc(stack->buffer_, stack->capacity_*2);
        assert(tmp);
        stack->buffer_ = tmp;
    }
    stack->buffer_[stack->size_] = value;
}

int top(Stack* stack)
{
    assert(stack);
    return stack->buffer_[stack->size_];
}


void pop(Stack* stack)
{
    assert(stack);
    if (stack->size_ > 0)
    {
        stack->buffer_[stack->size_] = 0;
        stack->size_--;
    }
    //else return 1;
}

void Destroy(Stack* stack)
{
    free(stack->buffer_);
    stack->size_ = 0;
    stack->capacity_ = 0;
}


int main()
{
    Stack myFirstTry = {};
    Construct(&myFirstTry, 3);
    push(&myFirstTry, 1);
    push(&myFirstTry, 2);
    push(&myFirstTry, 3);
    push(&myFirstTry, 4);
    pop(&myFirstTry);
    printf("%d", top(&myFirstTry));

    return 0;
}
