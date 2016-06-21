//
// Created by marcin on 6/16/16.
//
#include <stdio.h>
#include <stdarg.h>
#include <setjmp.h>
#include "cmocka.h"

#define array_length(x) (sizeof(x) / sizeof((x)[0]))

int mock_fprintf(FILE* const file, const char *format, ...) CMOCKA_PRINTF_ATTRIBUTE(2, 3);
int mock_printf(const char *format, ...) CMOCKA_PRINTF_ATTRIBUTE(1, 2);

static char temporary_buffer[256];

/* A mock fprintf function that checks the value of strings printed to the
 * standard error stream. */
int mock_fprintf(FILE* const file, const char *format, ...) {
    int return_value;
    va_list args;
    assert_true(file == stderr);
    va_start(args, format);
    return_value = vsnprintf(temporary_buffer, sizeof(temporary_buffer), format, args);
    check_expected_ptr(temporary_buffer);
    va_end(args);
    return return_value;
}

/* A mock printf function that checks the value of strings printed to the
 * standard output stream. */
int mock_printf(const char *format, ...) {
    int return_value;
    va_list args;
    va_start(args, format);
    return_value = vsnprintf(temporary_buffer, sizeof(temporary_buffer), format, args);
    check_expected_ptr(temporary_buffer);
    va_end(args);
    return return_value;
}