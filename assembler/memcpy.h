/*
 * memcpy.h
 *
 *  Created on: 4 окт. 2017 г.
 *      Author: MY
 */

#ifndef MEMCPY_H_
#define MEMCPY_H_

#include <cstddef>

void memcpy_simple(void* dst, const void* src, std::size_t size);
void memcpy_avx(void* dst, const void* src, std::size_t size);
#endif /* MEMCPY_H_ */
