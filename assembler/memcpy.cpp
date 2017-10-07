#include "memcpy.h"

void memcpy_simple(void* dst, const void* src, std::size_t size) {
	char * dst_oth = reinterpret_cast<char *>(dst);
	const char * src_oth = reinterpret_cast<const char *>(src);
	for (std::size_t i = 0; i < size; i++) {
		dst_oth[i] = src_oth[i];
	}
}

void memcpy_avx(void* dst, const void* src, std::size_t size) {
	if (size < 64) {
		memcpy_simple(dst, src, size);
		return;
	}
	int offs = reinterpret_cast<unsigned long long>(src) % 32;

	if (offs != 0) {
		int df = 32 - offs;
		memcpy_simple(dst, src, df);
		dst = reinterpret_cast<char *>(dst) + df;
		src = reinterpret_cast<const char *>(src) + df;
		size -= df;
	}
	__m256i * dst_oth = reinterpret_cast<__m256i *>(dst);
	const __m256i * src_oth = reinterpret_cast<const __m256i *>(src);
	std::size_t i = 0;
	if(reinterpret_cast<unsigned long long>(dst) % 32 == 0){
		for (; (i + 1) * 32 <= size; i++) {
			_mm256_store_si256(dst_oth + i, _mm256_load_si256(src_oth + i));
		}
	} else {
		for (; (i + 1) * 32 <= size; i++) {
			_mm256_storeu_si256(dst_oth + i, _mm256_load_si256(src_oth + i));
		}
	}
	memcpy_simple(dst_oth + i, src_oth + i, size - i * 32);
}
