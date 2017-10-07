#include "memcpy.h"

#include <cassert>

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
	__m256i * dst_a = reinterpret_cast<__m256i *>(dst);
	const __m256i * src_a = reinterpret_cast<const __m256i *>(src);
	if(reinterpret_cast<unsigned long long>(dst) % 32 == 0){
		for (; 32 <= size;) {
			_mm256_store_si256(dst_a, _mm256_load_si256(src_a));
			size -= 32;
			dst_a++;
			src_a++;
		}
	} else {
		for (; 32 <= size;) {
			_mm256_storeu_si256(dst_a, _mm256_load_si256(src_a));
			size -= 32;
			dst_a++;
			src_a++;
		}
	}
	memcpy_simple(dst_a, src_a, size);
}
