#include <stdio.h>
#include <math.h>
#include <iso646.h>
#include <assert.h>
#define nosol -1
#define linear -2
#define infinity -3
//-----------------------------------------------
//! Solves a square equating ax2 + bx + c = 0
//!  @param [in] a   a-coefficient
//!  @param [in] b   b-coefficient
//!  @param [in] b   b-coefficient
//!  @param [out] x1 first root
//!  @param [out] x2 second root
//!
//!  @return Number of roots
//!
//!  @note infinity roots  - infinity
//!  @note linear equation -   linear
//!  @note zero solutions  -    nosol
//-----------------------------------------------
int korni(double a, double b, double c, double* x1, double* x2)
{
if ((a ==0) and (b == 0) and (c == 0))
    return infinity;
if (a != 0)
    {
    double d = 0;
    d = b*b - 4*a*c;
    if (d > 0)
        {
        *x1 = (-b + sqrt(d)) / (2*a);
        *x2 = (-b - sqrt(d)) / (2*a);
        return 2;
        }
    else if (d == 0)
        {
        *x1 =  (-1*b)/(2*a);
        *x2 =  (-1*b)/(2*a);
        return 1;
        }
    else return nosol;
    }
else
    {
    *x1 = -c/b;
    return linear;
    }
}
int main()
{
        printf("This is program to solve power 2 equations\n");
        printf("Put coefficients with space\n");

    double a, b, c, x1, x2;
        a = b = c = x1 = x2 = 0;
        scanf("%lg %lg %lg", &a, &b, &c);

    int kolvo = 0;
        kolvo = korni(a, b, c, &x1, &x2);
    if (kolvo == 2)
        printf("x1 = %3.3lg\nx2 = %3.3lg", x1, x2);
    else if (kolvo == 1)
        printf("x1 = x2 = %.3lg", x1);
    else if (kolvo == nosol)
        printf("This equation has no solutions");
    else if (kolvo == linear)
        printf("This is linear equation\n x = %.3lg",x1);
    else if (kolvo == infinity)
        printf("x belongs R");
    else
        printf("Something went wrong. Check korni");
return 0;
}
