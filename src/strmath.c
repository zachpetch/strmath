#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

static bool _validate_integer(const char *a);
static char *_reverse(const char *a);
static char *_negate(const char *a);
static int _longest(const char *a, const char *b);
static bool _is_larger(const char *a, const char *b);
static char *_add_a_zero(const char *a);
static int _get_digit(const char *a, int i);
static char *_get_sum(const char *a, const char *b);
static char *_get_difference(const char *a, const char *b);
char *absv(const char* a);
char *add(const char *a, const char *b);
char *subtract(const char *a, const char *b);
char *multiply(const char *a, const char *b);
char *divide(const char *a, const char *b);
// TODO: exponents, factorials, modulo, permutations, combinations, binomial coefficients
// TODO: scientific notation, rounding

/**
 * Returns true if the given string is an integer.
 */
static bool _validate_integer(const char *a)
{
    if (a[0] == '-')
        return _validate_integer(a + 1);

    for (int i = 0; i < strlen(a); i++) {
        if (!isdigit(a[i]))
            return false;
    }

    return true;
}

/**
 * Returns a reversed copy of the given string
 * The caller is responsible for freeing the returned string.
 */
static char *_reverse(const char *a)
{
    if (!_validate_integer(a))
        return NULL;

    if (!a || !*a)
        return strdup(a);

    int length = strlen(a);
    char *x = calloc(length + 1, sizeof(char));

    for (int i = 0; i < length; i++)
        x[i] = a[length - i - 1];

    return x;
}

/**
 * Returns the negative inverse of a given number.
 * The caller is responsible for freeing the returned string.
 */
static char *_negate(const char *a)
{
    if (!_validate_integer(a))
        return NULL;

    if (a[0] == '-')
        return strdup(a + 1);

    char *negated = malloc(strlen(a) + 2);
    if (!negated)
        return NULL;

    negated[0] = '-';
    strcpy(negated + 1, a);

    return negated;
}

/**
 * Returns the length of the longest string.
 */
static int _longest(const char *a, const char *b)
{
    unsigned int x = strlen(a);
    unsigned int y = strlen(b);

    if (x > y)
        return x;

    return y;
}

/**
 * Returns true if a is greater than b.
 */
static bool _is_larger(const char *a, const char *b)
{
    if (!_validate_integer(a) || !_validate_integer(b))
        return NULL;

    size_t a_length = strlen(a);
    size_t b_length = strlen(b);

    if (a_length > b_length)
        return true;

    if (a_length < b_length)
        return false;

    return strcmp(a, b) > 0;
}

/**
 * Adds a zero to the end of the string (equivalent to multiplying by ten).
 * The caller is responsible for freeing the returned string.
 */
static char *_add_a_zero(const char *a)
{
    if (!_validate_integer(a))
        return NULL;

    size_t len = strlen(a);
    char *result = malloc(len + 2);
    if (result == NULL)
        return NULL;

    strcpy(result, a);
    result[len] = '0';
    result[len + 1] = '\0';

    return result;
}

/**
 * Returns the digit as an int in the ith position of a.
 * The caller is responsible for freeing the returned int.
 */
static int _get_digit(const char *a, int i)
{
    return a[i] - '0';
}

/**
 * Returns the sum of two positive integers.
 * The caller is responsible for freeing the returned string.
 */
static char *_get_sum(const char *a, const char *b)
{
    if (!_validate_integer(a) || !_validate_integer(b))
        return NULL;

    size_t length_a = strlen(a);
    size_t length_b = strlen(b);

    char *x = _reverse(a);
    char *y = _reverse(b);

    size_t longest = _longest(a, b);
    char *sum = malloc(longest + 2);
    if (!sum)
        return NULL;

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

/**
 * Returns the difference between a and b.
 * This function assumes a >= b >= 0.
 * The caller is responsible for freeing the returned string.
 */
static char *_get_difference(const char *a, const char *b)
{
    if (!_validate_integer(a) || !_validate_integer(b))
        return NULL;

    if (strcmp(a, b) == 0)
        return strdup("0");

    char *x = _reverse(a);
    char *y = _reverse(b);

    size_t a_length = strlen(a);
    size_t b_length = strlen(b);
    char *difference = malloc(a_length + 1);
    if (!difference)
        return NULL;

    int borrow = 0;
    int sub_diff;
    size_t i;

    for (i = 0; i < b_length; i++) {
        sub_diff = (x[i] - '0') - (y[i] - '0') - borrow;
        if (sub_diff < 0) {
            sub_diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        difference[i] = sub_diff + '0';
    }

    for (; i < a_length; i++) {
        sub_diff = (x[i] - '0') - borrow;
        if (sub_diff < 0) {
            sub_diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        difference[i] = sub_diff + '0';
    }

    char *reversed_diff = _reverse(difference);

    // Remove leading zeros
    char *final_result = reversed_diff;
    while (*final_result == '0' && *(final_result + 1) != '\0')
        final_result++;

    char *result = strdup(final_result);
    free(x);
    free(y);
    free(reversed_diff);
    free(difference);

    return result;
}

/**
 * Returns a added to itself b times.
 * Assumes a and b are positive integers.
 * Caller is responsible for freeing the returned string.
 */
static char *_get_product(char *a, char *b)
{
    if (!_validate_integer(a) || !_validate_integer(b))
        return NULL;

    char *result = strdup("0");
    char *rev_a = _reverse(a);

    for (size_t i = 0; i < strlen(rev_a); i++) {
        int x = _get_digit(rev_a, i);
        char *sub_sum = strdup("0");

        for (int j = 0; j < x; j++) {
            char *temp = _get_sum(sub_sum, b);
            free(sub_sum);
            sub_sum = temp;
        }

        for (int j = 0; j < i; j++) {
            char *temp = _add_a_zero(sub_sum);
            free(sub_sum);
            sub_sum = temp;
        }

        char *temp = _get_sum(result, sub_sum);
        free(result);
        result = temp;
        free(sub_sum);
    }

    free(rev_a);
    return result;
}

/**
 * Returns the absolute value of the given number
 * The caller is responsible for freeing the returned string.
 */
char *absv(const char* a) {
    if (!_validate_integer(a))
        return NULL;

    if (a[0] == '-') {
        return strdup(a + 1);
    }

    return strdup(a);
}

/**
 * Returns the sum of two integers.
 * The caller is responsible for freeing the returned string.
 */
char *add(const char *a, const char *b)
{
    if (!_validate_integer(a) || !_validate_integer(b))
        return NULL;

    if (a[0] == '-' && b[0] != '-') {
        char *a_pos = _negate(a);
        char *result = subtract(b, a_pos);
        free(a_pos);
        return result;
    }

    if (a[0] != '-' && b[0] == '-') {
        char *b_pos = _negate(b);
        char *result = subtract(a, b_pos);
        free(b_pos);
        return result;
    }

    if (a[0] == '-' && b[0] == '-') {
        char *a_pos = _negate(a);
        char *b_pos = _negate(b);
        char *result = _get_sum(a_pos, b_pos);
        free(a_pos);
        free(b_pos);
        return _negate(result);
    }

    return _get_sum(a, b);
}

/**
 * Returns the difference between two integers.
 * The caller is responsible for freeing the returned string.
 */
char *subtract(const char *a, const char *b)
{
    if (!_validate_integer(a) || !_validate_integer(b))
        return NULL;

    if (strcmp(a, b) == 0)
        return strdup("0");

    if (b[0] == '-')
        return add(a, _negate(b));

    if (a[0] == '-')
        return _negate(add(_negate(a), b));

    if (_is_larger(b, a))
        return _negate(_get_difference(b, a));

    return _get_difference(a, b);
}

/**
 * Returns the product of two integers.
 * The caller is responsible for freeing the returned string.
 */
char *multiply(const char *a, const char *b)
{
    if (!_validate_integer(a) || !_validate_integer(b))
        return NULL;

    char *abs_a = absv(a);
    char *abs_b = absv(b);

    char *result = _get_product(abs_a, abs_b);

    free(abs_a);
    free(abs_b);

    if ((a[0] == '-' && b[0] != '-') || (a[0] != '-' && b[0] == '-')) {
        char *negated_result = _negate(result);
        free(result);
        return negated_result;
    }

    return result;
}

/**
 * Returns the quotient of two integers.
 * The caller is responsible for freeing the returned string.
 */
char *divide(const char *a, const char *b)
{
    if (!_validate_integer(a) || !_validate_integer(b))
        return NULL;

    char *result = calloc(1, sizeof(char));

    return result;
}

int main() {
    char *a = "100";
    char *b = "99";
    char *x = "-100";
    char *y = "-99";

    printf("%s + %s = %s\n", a, b, add(a, b));
    printf("%s + %s = %s\n", b, a, add(b, a));
    printf("%s + %s = %s\n", y, x, add(y, x));
    printf("%s + %s = %s\n", x, y, add(x, y));
    printf("%s + %s = %s\n", b, x, add(b, x));
    printf("%s + %s = %s\n", x, b, add(x, b));
    printf("%s + %s = %s\n", y, a, add(y, a));
    printf("%s + %s = %s\n", a, y, add(a, y));

    printf("%s - %s = %s\n", a, b, subtract(a, b));
    printf("%s - %s = %s\n", b, a, subtract(b, a));
    printf("%s - %s = %s\n", y, x, subtract(y, x));
    printf("%s - %s = %s\n", x, y, subtract(x, y));
    printf("%s - %s = %s\n", b, x, subtract(b, x));
    printf("%s - %s = %s\n", x, b, subtract(x, b));
    printf("%s - %s = %s\n", y, a, subtract(y, a));
    printf("%s - %s = %s\n", a, y, subtract(a, y));

    printf("%s x %s = %s\n", a, b, multiply(a, b));
    printf("%s x %s = %s\n", b, a, multiply(b, a));
    printf("%s x %s = %s\n", y, x, multiply(y, x));
    printf("%s x %s = %s\n", x, y, multiply(x, y));
    printf("%s x %s = %s\n", b, x, multiply(b, x));
    printf("%s x %s = %s\n", x, b, multiply(x, b));
    printf("%s x %s = %s\n", y, a, multiply(y, a));
    printf("%s x %s = %s\n", a, y, multiply(a, y));

    printf("%s ÷ %s = %s\n", a, b, divide(a, b));
    printf("%s ÷ %s = %s\n", b, a, divide(b, a));
    printf("%s ÷ %s = %s\n", y, x, divide(y, x));
    printf("%s ÷ %s = %s\n", x, y, divide(x, y));
    printf("%s ÷ %s = %s\n", b, x, divide(b, x));
    printf("%s ÷ %s = %s\n", x, b, divide(x, b));
    printf("%s ÷ %s = %s\n", y, a, divide(y, a));
    printf("%s ÷ %s = %s\n", a, y, divide(a, y));

    return 0;
}
