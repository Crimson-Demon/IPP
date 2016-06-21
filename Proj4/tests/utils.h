//
// Created by marcin on 6/16/16.
//

#ifndef MIDDLE_AGES_UTILS_H
#define MIDDLE_AGES_UTILS_H

/* If this is being built for a unit test. */
#ifdef UNIT_TESTING

/* Redirect printf to a function in the test application so it's possible to
 * test the standard output. */
#ifdef printf
#undef printf
#endif /* printf */
extern int mock_printf(const char *format, ...);
#define printf mock_printf

/* Redirect fprintf to a function in the test application so it's possible to
 * test error messages. */
#ifdef fprintf
#undef fprintf
#endif /* fprintf */
#define fprintf mock_fprintf
extern int mock_fprintf(FILE * const file, const char *format, ...);

/* Redirect assert to mock_assert() so assertions can be caught by cmocka. */
#ifdef assert
#undef assert
#endif /* assert */
#define assert(expression) \
    mock_assert((int)(expression), #expression, __FILE__, __LINE__)
void mock_assert(const int result, const char* expression, const char *file,
                 const int line);

/* Redirect calloc and free to test_calloc() and test_free() so cmocka can
 * check for memory leaks. */
#ifdef calloc
#undef calloc
#endif /* calloc */
#define calloc(num, size) _test_calloc(num, size, __FILE__, __LINE__)
#ifdef free
#undef free
#endif /* free */
#define free(ptr) _test_free(ptr, __FILE__, __LINE__)
void* _test_calloc(const size_t number_of_elements, const size_t size,
                   const char* file, const int line);
void _test_free(void* const ptr, const char* file, const int line);

int calculator_main(int argc, char *argv[]);
/* Function main is defined in the unit test so redefine name of the main function
 * here. */
#define main calculator_main

/* All functions in this object need to be exposed to the test application,
 * so redefine static to nothing. */
#define static

#endif /* UNIT_TESTING */

#endif //MIDDLE_AGES_UTIL_H
