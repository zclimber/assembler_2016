#include "wordcount.h"

typedef unsigned long long ull;

int count_words_simple(const char *str) {
	int ans = 0;
	if (*str != space) {
		ans++;
	}
	for (str += 1; *str; ++str) {
		if (*str != space && *(str - 1) == space) {
			ans++;
		}
	}
	return ans;
}

int count_words_avx(const char *str) {
	__m256i space_vec = _mm256_set1_epi8(space);
	__m256i end_vec = _mm256_set1_epi8(0);
	ull eqmask = 1LL << 31;
	int ans = 0, zero, i = 0;
	unsigned int dbits;

	int offs = reinterpret_cast<ull>(str) % 32;

	if (offs != 0) {
		int df = 32 - offs;
		for (int i = 0; i < df; i++) {
			eqmask += (1LL << (32 + i)) * (str[i] == space);
		}
		dbits = (eqmask ^ (eqmask >> 1)) >> 31;
		dbits &= (1LL << df) - 1;
		ans += __builtin_popcount(dbits);
		eqmask >>= df;
		str += df;
	}

	for (;; i += 32) {
		__m256i data = _mm256_stream_load_si256(
				reinterpret_cast<const __m256i *>(str + i));
		__m256i cmp = _mm256_cmpeq_epi8(data, space_vec);
		eqmask |= ((ull) _mm256_movemask_epi8(cmp)) << 32;
		cmp = _mm256_cmpeq_epi8(data, end_vec);
		zero = _mm256_movemask_epi8(cmp);
		dbits = (eqmask ^ (eqmask >> 1)) >> 31;
		if (zero != 0) {
			break;
		}
		ans += __builtin_popcount(dbits);
		eqmask >>= 32;
	}

	_mm256_zeroall();
	eqmask >>= 31;
	int len = __builtin_ctz(zero);
	eqmask |= (2LL << len);
	dbits = (eqmask ^ (eqmask >> 1)) & ((2LL << len) - 1);
	ans += __builtin_popcount(dbits);
	return ans / 2;
}
