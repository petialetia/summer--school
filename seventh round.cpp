#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <iso646.h>
#include <string.h>

enum {ENQUEUE = 0, DEQUEUE = 1, FRONT = 2, SIZE = 3, CLEAR = 4, MIN = 5};

typedef int Elem_t;

const int MAX_START_SIZE_STACK = 2000000;
const int ERROR = -1;
const Elem_t MAX_INT = 2147483647;
const int NUM_METHODS = 6;
const int STANDART_SIZE = 13;

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
    if (sizeQueue(stackin, stackout) > 0)
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
    if (tmp != ERROR)
    {
        pop(stackout);
    }
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
    stackin->size_ = 0;

    stackout->size_ = 0;
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

int defineMethod(char** methods, char* method)
{
    for (int i = 0; i < NUM_METHODS; ++i)
    {
        if (!strcmp(methods[i], method))
        {
            return i;
        }
    }
}

int main()
{
    Stack stackIn  = {};
    Stack stackOut = {};
    Construct(&stackIn, STANDART_SIZE);
    Construct(&stackOut, STANDART_SIZE);

    int N = 0;
    scanf("%d", &N);
    char* methods[] = {"enqueue", "dequeue", "front", "size", "clear", "min"};

    for (int i = 0; i < N; ++i)
    {
        char method[10];
        scanf("%s", &method);
        int numMethod = defineMethod(methods, method);

        switch (numMethod)
        {
            case ENQUEUE:
            {
                int value = 0;
                scanf("%d", &value);
                enqueue(&stackIn, value);
                printf("ok\n");
                break;
            }
            case DEQUEUE:
            {
                int tmp = dequeue(&stackIn, &stackOut);
                if (tmp == ERROR)
                {
                    printf("error\n");
                }
                else
                {
                    printf("%d\n", tmp);
                }
                break;
            }
            case FRONT:
            {
                int tmp = front(&stackIn, &stackOut);
                if (tmp == ERROR)
                {
                    printf("error\n");
                }
                else
                {
                    printf("%d\n", tmp);
                }
                break;
            }
            case SIZE:
            {
                printf("%d\n", sizeQueue(&stackIn, &stackOut));
                break;
            }
            case CLEAR:
            {
                clear(&stackIn, &stackOut);
                printf("ok\n");
                break;
            }
            case MIN:
            {
                int tmp = minQueue(&stackIn, &stackOut);
                if (tmp == ERROR)
                {
                    printf("error\n");
                }
                else
                {
                    printf("%d\n", tmp);
                }
                break;
            }
            default:
            {
                printf("I DONT KNOW WHAT IS THIS SHIT\n");
                break;
            }
        }
    }

    return 0;
}
