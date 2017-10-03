/*
 * wordcount.h
 *
 * Includes simple and AVX word counters
 */

#ifndef WORDCOUNT_H_
#define WORDCOUNT_H_

#include <immintrin.h>

const char space = ' ';

int count_words_simple(const char *str);
int count_words_avx(const char *str);

#endif /* WORDCOUNT_H_ */
