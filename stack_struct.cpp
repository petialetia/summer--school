//#include <TxLib.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

//#define NDEBUG
#ifndef NDEBUG
#define ASSERT_OK if(!StackOK(stack)) {StackDump(stack); assert(!"OK");}
#else
#define ASSERT_OK ;
#endif

const unsigned int MAX_SIZE_STACK = 2000000;
typedef double Elem_t;

#ifndef NDEBUG
enum STACK_STATUS {STACK_IS_NOT_OK = 0, STACK_IS_OK = 1};
enum STACK_ERROR
{
    NO_ERR,
    SIZE_ERR,
    CAPACITY_ERR,
    POP_EMPTY,
    TOP_EMPTY,
    STACK_POINTER_ERR,
    BUFFER_POINTER_ERR,
    BUFFER_ERR
};
#endif

struct Stack
{
    uint64_t capacity_ = 0;
    uint64_t size_ = 0;
    Elem_t* buffer_ = nullptr;
    #ifndef NDEBUG
    STACK_ERROR status_ = NO_ERR;
    #endif
};


void Construct(Stack* stack, uint64_t size);
void push(Stack* stack, int value);
int  top(Stack* stack);
void pop(Stack* stack);
void clear(Stack* stack);
void Destroy(Stack* stack);
void CheckBuffer(Stack* stack);
#ifndef NDEBUG
int  StackOK(Stack* stack);
void StackDump(Stack* stack);
#endif




void Construct(Stack* stack, uint64_t size)
{
    assert(stack);
    if (size > MAX_SIZE_STACK)
    {
        printf("ARE YOU REALLY TRY TO CONSTRUCT STACK WITH THIS SIZE?\n");
        assert(0);
    }

    stack->buffer_ = (Elem_t*)calloc(size*10, sizeof(Elem_t));
    stack->size_ = 0;
    stack->capacity_ = size;
    #ifndef NDEBUG
    stack->status_ = NO_ERR;
    #endif
    for (int i = 0; i < size; ++i)
    {
        stack->buffer_[i] = NAN;
    }
    ASSERT_OK
}

void push(Stack* stack, int value)
{
    ASSERT_OK

    CheckBuffer(stack);
    stack->buffer_[stack->size_++] = value;

    ASSERT_OK
}

int top(Stack* stack)
{
    ASSERT_OK
    if (stack->size_ > 0)
    {
        return stack->buffer_[stack->size_ - 1];
    }
    #ifndef NDEBUG
    stack->status_ = TOP_EMPTY;
    #endif
    ASSERT_OK
}


void pop(Stack* stack)
{
    ASSERT_OK
    if (stack->size_ > 0)
    {
        stack->buffer_[stack->size_ - 1] = NAN;
        stack->size_--;
        CheckBuffer(stack);
    }
    else
    {
        #ifndef NDEBUG
        stack->status_ = POP_EMPTY;
        #endif
    }
    ASSERT_OK
}

void clear(Stack* stack)
{
    ASSERT_OK
    for (int i = 0; i < stack->size_; ++i)
    {
        stack->buffer_[i] = NAN;
    }                                            //DEBUG MODE HOW WORKS
    stack->size_ = 0;                            //должен ли clear реаллоцировать буффер до стандартного размера?
}

void Destroy(Stack* stack)
{
    ASSERT_OK
    free(stack->buffer_);
    stack->size_ = 0;
    stack->capacity_ = 0;
    stack->buffer_ = nullptr;
}

void CheckBuffer(Stack* stack)
{
    if (stack->size_ >= stack->capacity_ - 1)
    {
        Elem_t* tmp = (Elem_t*)realloc(stack->buffer_, stack->capacity_ * sizeof(Elem_t) * 2);
        assert(tmp);
        stack->capacity_ *= 2;
        stack->buffer_ = tmp;
        for (int i = stack->capacity_ - 1; i >= stack->capacity_ / 2; --i)
        {
            stack->buffer_[i] = NAN;
        }
    }
    if (stack->size_ <= stack->capacity_ / 3)
    {
        stack->buffer_ = (Elem_t*)realloc(stack->buffer_, stack->capacity_ * sizeof(Elem_t) / 2);
        stack->capacity_ /= 2;
    }
}

#ifndef NDEBUG
int StackOK(Stack* stack)
{
    if (stack->status_ != NO_ERR) return STACK_IS_NOT_OK;

    if (stack == 0)
    {
        stack->status_ = STACK_POINTER_ERR;
        return STACK_IS_NOT_OK;
    }
    if (stack->size_ > stack->capacity_)
    {
        stack->status_ = SIZE_ERR;
        return STACK_IS_NOT_OK;
    }
    if (stack->buffer_ == 0)
    {
        stack->status_ = BUFFER_POINTER_ERR;
        return STACK_IS_NOT_OK;
    }
    if (stack->size_ > MAX_SIZE_STACK)
    {
        stack->status_ = SIZE_ERR;
        return STACK_IS_NOT_OK;
    }
    if (stack->capacity_ > MAX_SIZE_STACK)
    {
        stack->status_ = CAPACITY_ERR;
        return STACK_IS_NOT_OK;
    }

    for (int i = 0; i < stack->capacity_; ++i)
    {
        if (i >= stack->size_)
        {
            if (!isnan(stack->buffer_[i]))
            {
                stack->status_ = BUFFER_ERR;
                return STACK_IS_NOT_OK;
            }
        }
        else
        {
            if (isnan(stack->buffer_[i]))
            {
                stack->status_ = BUFFER_ERR;
                return STACK_IS_NOT_OK;
            }
        }

    }
    return STACK_IS_OK;
}

void StackDump(Stack* stack)
{
    printf("Stack [%p] ", stack);

    if (stack->status_ == NO_ERR            ) printf(" Stack is OK\n");
    if (stack->status_ == SIZE_ERR          ) printf(" Stack size is not OK\n");
    if (stack->status_ == CAPACITY_ERR      ) printf(" Stack capacity is not OK\n");
    if (stack->status_ == POP_EMPTY         ) printf(" You try to pop from empty stack\n");
    if (stack->status_ == TOP_EMPTY         ) printf(" You try to top from empty stack\n");
    if (stack->status_ == STACK_POINTER_ERR ) printf(" Stack pointer is nullptr\n");
    if (stack->status_ == BUFFER_POINTER_ERR) printf(" Buffer pointer is nullptr\n");
    if (stack->status_ == BUFFER_ERR        ) printf(" Buffer was spoiled\n");

    printf("    size     = %llu\n"
           "    capacity = %llu\n", stack->size_, stack->capacity_);
    printf("     Buffer[%p]:\n", stack->buffer_);
    for (int i = 0; i < stack->capacity_; ++i)
    {
        if (i <  stack->size_)
            printf("        *[%2d] = %5lg\n", i, stack->buffer_[i]);
        else
            printf("         [%2d] = %5lg\n", i, stack->buffer_[i]);
    }

}
#endif

int main()
{
    Stack myFirstTry = {};
    Construct(&myFirstTry, 1);
    //pop(&myFirstTry);
    for (int i = 0; i < 50; i++)
    {
      push(&myFirstTry, i);
    }
    for (int i = 0; i < 42; i++)
    {
      pop(&myFirstTry);
    }
    clear(&myFirstTry);
    top(&myFirstTry);
    for (int i = 0; i < 50; i++)
    {
      push(&myFirstTry, i);
    }
    printf("<%d>", top(&myFirstTry));


    return 0;
}
