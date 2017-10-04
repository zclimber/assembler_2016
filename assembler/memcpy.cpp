#include "memcpy.h"

void memcpy_simple(void* dst, const void* src, std::size_t size) {
	char * dst_oth = reinterpret_cast<char *>(dst);
	const char * src_oth = reinterpret_cast<const char *>(src);
	for (std::size_t i = 0; i < size; i++) {
		dst_oth[i] = src_oth[i];
	}
}

void memcpy_avx(void* dst, const void* src, std::size_t size) {
	if (size < 32) {
		memcpy_simple(dst, src, size);
		return;
	}
	__m256i * dst_oth = reinterpret_cast<__m256i *>(dst);
	const __m256i * src_oth = reinterpret_cast<const __m256i *>(src);
	std::size_t i = 0;
	for (; (i + 1) * 32 <= size; i++) {
		_mm256_storeu_si256(dst_oth + i, _mm256_loadu_si256(src_oth + i));
	}
	memcpy_simple(dst_oth + i, src_oth + i, size - i * 32);
}
