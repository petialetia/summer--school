#include <stdio.h>
#include <math.h>
#include <iso646.h>
#include <assert.h>

enum {
      NOSOL,
      INFINITY_ROOTS,
      ONE_ROOT,
      TWO_ROOTS
    };
//-----------------------------------------------
//! Solves a square equating ax2 + bx + c = 0
//!  @param [in]   a     a-coefficient
//!  @param [in]   b     b-coefficient
//!  @param [in]   c     c-coefficient
//!  @param [out] x1        first root
//!  @param [out] x2       second root
//!
//!  @return Number of roots
//!
//!  @note infinity roots  -    infinity
//!  @note linear equation -      linear
//!  @note zero solutions  -       nosol
//!  @note One root        -     OneRoot
//!  @note Two roots       -    TwoRoots
//-----------------------------------------------

int IsZero(double a)
{
    return (fabs(a) < 1e-6);
}


int SolveLinear(double b, double c, double* x1, double* x2)
{
    assert (isfinite(b));
    assert (isfinite(c));
    assert (x1 != NULL);

    if ((IsZero(b)) and (IsZero(c)))
        return INFINITY_ROOTS;
    if (IsZero(b))
        return NOSOL;
    else
        {
        *x1 = -c/b;
        *x2 = -c/b;
        return ONE_ROOT;
        }
}


int SolveSquare(double a, double b, double c, double* x1, double* x2)
{
    assert (isfinite(a));
    assert (isfinite(b));
    assert (isfinite(c));

    assert (x1 != NULL);
    assert (x2 != NULL);
    assert (x1 != x2);

    if (IsZero(a))
          return SolveLinear(b, c, x1, x2);
    else
        {
        double d = b*b - 4*a*c;
        if (IsZero(d))
            {
            *x1 =  (-b)/(2*a);
            *x2 =  (-b)/(2*a);
            return ONE_ROOT;
            }
        else if (d > 0)
            {
            *x1 = (-b + sqrt(d)) / (2*a);
            *x2 = (-b - sqrt(d)) / (2*a);
            return TWO_ROOTS;
            }
        else return NOSOL;
        }
}


void Test_SolveSquare();


int main()
{
// Test_SolveSquare();
// return 0;
    printf("This is program to solve power 2 equations\n");
    printf("Put coefficients with space\n");

    double a  = 0,
           b  = 0,
           c  = 0,
           x1 = 0,
           x2 = 0;

    scanf("%lg %lg %lg", &a, &b, &c);

    int NumRoots = SolveSquare(a, b, c, &x1, &x2);

    switch (NumRoots)
        {
        case NOSOL:
            printf("This equation has no solutions");
            break;
        case ONE_ROOT:
            printf("x = %.3lg", x1);
            break;
        case TWO_ROOTS:
            printf("x1 = %3.3lg\nx2 = %3.3lg", x1, x2);
            break;
        case INFINITY_ROOTS:
            printf("x belongs R");
            break;
        default:
            printf("Something went wrong. Check SolveSquare");
        }
    return 0;
}

void Test_SolveSquare()
{
  double resx1  = 0,
         resx2  = 0,
         a      = 0,
         b      = 0,
         c      = 0,
         realx1 = 0,
         realx2 = 0,
         Val    = 0,
         ExpVal = 0;

  resx1  =  2,
  resx2  =  4,
  a      =  1,
  b      = -6,
  c      =  8,
          SolveSquare(a, b, c, &realx1, &realx2);
          if (((resx1 == realx1) and (resx2 == realx2)) or
              ((resx1 == realx2) and (resx2 == realx1)))
                    printf("Test on line %d OK\n",__LINE__);
          else printf(" Test on line %d failed\n"
                      " expected x1 = %g x2 = %g\n"
                      " real     x1 = %g x2 = %g\n",
                      __LINE__, resx1, resx2, realx1, realx2);

  resx1  =  3,
  resx2  =  3,
  a      =  1,
  b      = -6,
  c      =  9,
          SolveSquare(a, b, c, &realx1, &realx2);
          if (((resx1 == realx1) and (resx2 == realx2)) or
              ((resx1 == realx2) and (resx2 == realx1)))
                    printf("Test on line %d OK\n",__LINE__);
          else printf(" Test on line %d failed\n"
                      " expected x1 = %g x2 = %g\n"
                      " real     x1 = %g x2 = %g\n",
                      __LINE__, resx1, resx2, realx1, realx2);

  resx1  =  2,
  resx2  =  2,
  a      =  0,
  b      =  3,
  c      = -6,
          SolveSquare(a, b, c, &realx1, &realx2);
          if (((resx1 == realx1) and (resx2 == realx2)) or
              ((resx1 == realx2) and (resx2 == realx1)))
                    printf("Test on line %d OK\n",__LINE__);
          else printf("Test on line %d failed\n"
                      " expected x1 = %g x2 = %g\n"
                      " real     x1 = %g x2 = %g\n",
                      __LINE__, resx1, resx2, realx1, realx2);

  ExpVal = NOSOL,
  a      =     0,
  b      =     0,
  c      =     5,
          Val = SolveSquare(a, b, c, &realx1, &realx2);
          if (Val == ExpVal)
            printf("Test on line %d OK\n",__LINE__);
          else
            printf("Test on line %d failed\n"
                   " expected Val = %g\n"
                   " real     Val = %g\n",
                   __LINE__, ExpVal, Val);

  ExpVal = INFINITY_ROOTS,
  a      =     0,
  b      =     0,
  c      =     0,
          Val = SolveSquare(a, b, c, &realx1, &realx2);
          if (Val == ExpVal)
            printf("Test on line %d OK\n",__LINE__);
          else
            printf("Test on line %d failed\n"
                   " expected Val = %g\n"
                   " real     Val = %g\n",
                   __LINE__, ExpVal, Val);

}



