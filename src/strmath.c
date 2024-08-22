#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *_abs(char *a)
{
    if (a[0] == '-')
        return a + 1;

    return a;
}

/**
 * Returns a reversed copy of the given string
 */
static char *_reverse(const char *a)
{
    if (!a || !*a)
        return strdup(a);

    int length = strlen(a);
    char *x = calloc(length + 1, sizeof(char));

    for (int i = length - 1; i >= 0; i--)
        x[i] = a[length - i - 1];

    return x;
}

/**
 * Returns the length of the longest string.
 * Todo: Make this a variadic function to handle any number of arguments.
 */
static int _longest(const char *a, const char *b)
{
    unsigned int x = strlen(a);
    unsigned int y = strlen(b);

    if (x > y)
        return x;

    return y;
}

static char *_get_positive_sum(const char *a, const char *b)
{
    size_t length_a = strlen(a);
    size_t length_b = strlen(b);

    char *x = _reverse(a);
    char *y = _reverse(b);

    size_t longest = _longest(a, b);
    char *sum = calloc(longest + 2, sizeof(char));

    unsigned int carry = 0;
    unsigned int sub_sum;

    for (size_t i = 0; i < longest; i++) {
        sub_sum = (i < length_a ? x[i] - '0' : 0) + (i < length_b ? y[i] - '0' : 0) + carry;
        if (sub_sum > 9) {
            carry = 1;
            sub_sum -= 10;
        } else {
            carry = 0;
        }

        sum[i] = sub_sum + '0';
    }

    if (carry) {
        sum[longest] = carry + '0';
    }

    char *result = _reverse(sum);
    free(x);
    free(y);
    free(sum);

    return result;
}

char *add(const char *a, const char *b)
{
    char *x = malloc(_longest(a, b) + 1);

    if (a[0] == '-' && b[0] != '-') {
        //
    }

    return _reverse(x);
}

char *subtract(const char *a, const char *b)
{
    char *result = calloc(1, sizeof(char));

    return result;
}

char *multiply(const char *a, const char *b)
{
    char *result = calloc(1, sizeof(char));

    return result;
}

char *divide(const char *a, const char *b)
{
    char *result = calloc(1, sizeof(char));

    return result;
}

int main() {
    char *a = "8";
    char *b = "4";

    char *sum = _get_positive_sum(a, b);
    char *difference = subtract(a, b);
    char *product = multiply(a, b);
    char *quotient = divide(a, b);

    printf("a + b = %s\n", sum);
    printf("a - b = %s\n", difference);
    printf("a * b = %s\n", product);
    printf("a ÷ b = %s\n", quotient);

    free(sum);
    free(difference);
    free(product);
    free(quotient);

    return 0;
}
