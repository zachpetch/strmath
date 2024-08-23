#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static char *_reverse(const char *a);
static char *_negate(const char *a);
static int _longest(const char *a, const char *b);
static bool _is_larger(const char *a, const char *b);
static char *_get_positive_sum(const char *a, const char *b);
static char *_get_difference(const char *a, const char *b);
// char* abs(const char* a);
char *add(const char *a, const char *b);
char *subtract(const char *a, const char *b);
char *multiply(const char *a, const char *b);
char *divide(const char *a, const char *b);

/**
 * Returns a reversed copy of the given string
 * The caller is responsible for freeing the returned string.
 */
static char *_reverse(const char *a)
{
    if (!a || !*a)
        return strdup(a);

    int length = strlen(a);
    char *x = calloc(length + 1, sizeof(char));

    // for (int i = length - 1; i >= 0; i--)
    //     x[i] = a[length - i - 1];

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
    if (a == NULL || *a == '\0')
        return strdup("");

    if (a[0] == '-')
        return strdup(a + 1);

    char *negated = malloc(strlen(a) + 2);
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
    size_t a_length = strlen(a);
    size_t b_length = strlen(b);

    if (a_length > b_length)
        return true;

    if (a_length < b_length)
        return false;

    return strcmp(a, b) > 0;
}

/**
 * Returns the sum of two positive integers.
 * The caller is responsible for freeing the returned string.
 */
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

/**
 * Returns the difference between a and b.
 * This function assumes a >= b >= 0.
 * The caller is responsible for freeing the returned string.
 */
static char *_get_difference(const char *a, const char *b)
{
    if (strcmp(a, b) == 0)
        return strdup("0");

    char *x = _reverse(a);
    char *y = _reverse(b);

    size_t a_length = strlen(a);
    size_t b_length = strlen(b);
    char *difference = calloc(a_length + 1, sizeof(char));

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
// static char *_get_difference(const char *a, const char *b)
// {
//     if (strcmp(a, b) == 0)
//         return strdup("0");

//     char *x = _reverse(a);
//     char *y = _reverse(b);

//     int sub_diff;
//     char t[2];
//     int i;
//     int borrow = 0;
//     char *difference = calloc(strlen(a) + 1, sizeof(char));

//     for (i = 0; i < strlen(y); i++) {
//         sub_diff = (x[i] - '0') - (y[i] - '0') - borrow;
//         if (sub_diff < 0) {
//             sub_diff += 10;
//             borrow = 1;
//         } else {
//             borrow = 0;
//         }
//         sprintf(t, "%d", sub_diff);
//         strncat(difference, t, 1);
//     }

//     if (strlen(a) > strlen(b))
//         while (i < strlen(a))
//             strncat(difference, &a[i++], 1);

//     char *result = _reverse(difference);
//     i = 0;
//     while (result[i] == '0')
//         i++;

//     char *final_result = strdup(&result[i]);

//     free(result);
//     free(difference);
//     return final_result;
// }

/**
 * Returns the absolute value of the given number
 * The caller is responsible for freeing the returned string.
 */
// char* abs(const char* a) {
//     if (a == NULL || *a == '\0') {
//         return strdup("");
//     }

//     if (a[0] == '-') {
//         return strdup(a + 1);
//     }

//     return strdup(a);
// }

/**
 * Returns the sum of two integers.
 * The caller is responsible for freeing the returned string.
 */
char *add(const char *a, const char *b)
{
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
        char *result = _get_positive_sum(a_pos, b_pos);
        free(a_pos);
        free(b_pos);
        return _negate(result);
    }

    return _get_positive_sum(a, b);
}

/**
 * Returns the difference between two integers.
 * The caller is responsible for freeing the returned string.
 */
char *subtract(const char *a, const char *b)
{
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
    char *result = calloc(1, sizeof(char));

    return result;
}

/**
 * Returns the quotient of two integers.
 * The caller is responsible for freeing the returned string.
 */
char *divide(const char *a, const char *b)
{
    char *result = calloc(1, sizeof(char));

    return result;
}

int main() {
    char *a = "8";
    char *b = "4";

    char *sum = add(a, b);
    char *difference = subtract(a, b);
    char *product = multiply(a, b);
    char *quotient = divide(a, b);

    printf("a + b = %s\n", sum);
    printf("a - b = %s\n", difference);
    printf("a * b = %s\n", product);
    printf("a ÷ b = %s\n", quotient);

    printf("%s - %s = %s\n", "1000", "999", subtract("1000", "999"));
    printf("%s - %s = %s\n", "999", "1000", subtract("999", "1000"));
    printf("%s - %s = %s\n", "-999", "-1000", subtract("-999", "-1000"));
    printf("%s - %s = %s\n", "-1000", "-999", subtract("-1000", "-999"));
    printf("%s - %s = %s\n", "999", "-1000", subtract("-999", "-1000"));
    printf("%s - %s = %s\n", "-1000", "999", subtract("-1000", "-999"));
    printf("%s - %s = %s\n", "-999", "1000", subtract("-999", "-1000"));
    printf("%s - %s = %s\n", "1000", "-999", subtract("-1000", "-999"));

    free(sum);
    free(difference);
    free(product);
    free(quotient);

    return 0;
}
