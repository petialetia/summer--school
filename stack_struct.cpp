#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <iso646.h>

const int MAX_LINE = 100005;
const int MAX_START_SIZE_STACK = 2000000;
enum {ROUND_BRACKET = '(', SQUARE_BRACKET = '[', BRACE = '{',
      REV_ROUND_BRACKET = ')', REV_SQUARE_BRACKET = ']', REV_BRACE = '}',
      WRONG_PSP, RIGHT_PSP};

struct Stack
{
    uint64_t capacity_ = 0;
    uint64_t size_ = 0;
    char* buffer_ = nullptr;
};


void Construct(Stack* stack, uint64_t size)
{
    assert(stack);
    assert(size < MAX_START_SIZE_STACK);

    stack->buffer_ = (char*)calloc(size, sizeof(char));
    stack->size_ = 0;
    stack->capacity_ = size;
}

void push(Stack* stack, char value)
{
    assert(stack);

    stack->size_++;
    if (stack->size_ == stack->capacity_ - 1)
    {
        char* tmp = (char*)realloc(stack->buffer_, stack->capacity_*2);
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
}

void Destroy(Stack* stack)
{
    free(stack->buffer_);
    stack->size_ = 0;
    stack->capacity_ = 0;
    stack = nullptr;
}


int isPSP(Stack* string, char* str)
{
    for (int i = 0; str[i] != '\0'; ++i)
    {
        if (str[i] == ROUND_BRACKET or str[i] == SQUARE_BRACKET or str[i] == BRACE)
        {
            push(string, str[i]);
        }
        else
        {
        if (str[i] == REV_ROUND_BRACKET)
        {
            if (top(string) == ROUND_BRACKET)
            {
                pop(string);
            }
            else return WRONG_PSP;
        }

        if (str[i] == REV_SQUARE_BRACKET)
        {
            if (top(string) == SQUARE_BRACKET)
            {
                pop(string);
            }
            else return WRONG_PSP;
        }

        if (str[i] == REV_BRACE)
        {
            if (top(string) == BRACE)
            {
                pop(string);
            }
            else return WRONG_PSP;
        }
        }

    }
    if (string->size_ == 0)
    {
        return RIGHT_PSP;
    }
    else
    {
        return WRONG_PSP;
    }
}

int main()
{
    Stack string = {};
    Construct(&string, MAX_LINE);

    char* str = (char*)calloc(MAX_LINE, sizeof(char));
    fgets(str, MAX_LINE, stdin);

    if (isPSP(&string, str) == RIGHT_PSP)
    {
        printf("YES");
    }
    else
    {
        printf("NO");
    }
    return 0;
}

