#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <cstring>

#include "wordcount.h"
#include "memcpy.h"

const int length = 100000000;
const int iter = 10;
const int offs = 1;

char cpa[length], cpb[length];
char str[length + 1];
std::mt19937 mt(time(0));

void test_wordcount() {

	double time_avx = 0, time_simple = 0;

	std::cout << "Counting words in strings of length " << length << ", repeat " << iter * offs << " times\n";
	flush(std::cout);

	for (int test = 0; test < iter; test++) {
		for (int w = 0; w < length; w++) {
			if (mt() % 2) {
				str[w] = space;
			} else {
				str[w] = 'a' + mt() % 26;
			}
		}
		str[length] = 0;

		int st = 0;

		for (int e = 0 + st; e < offs + st; e++) {
			auto pa = std::chrono::steady_clock::now();
			int res_1 = count_words_avx(str + e);
			auto pb = std::chrono::steady_clock::now();
			int res_2 = count_words_simple(str + e);
			auto pc = std::chrono::steady_clock::now();

			time_avx += (std::chrono::duration<double>(pb - pa)).count();
			time_simple += (std::chrono::duration<double>(pc - pb)).count();

			if (res_1 != res_2) {
				std::cout << "WA " << res_1 << " " << res_2 << " iter " << test << " len " << e << "\n";
				std::cout << str + e << "\n";
				return;
			}
		}
	}

	std::cout << "Done\n";
	std::cout << std::fixed << std::setprecision(3);
	std::cout << "Simple count time: " << time_simple << " sec\n";
	std::cout << "AVX count time: " << time_avx << " sec\n";
	std::cout << "AVX is " << time_simple / time_avx << " times faster\n";
}

void test_memcpy() {

	std::cout << "Copying strings of length " << length << ", repeat " << iter * offs << " times\n";
	flush(std::cout);

	double time_avx = 0, time_simple = 0;
	for (int test = 0; test < iter; test++) {
		for (int w = 0; w < length; w++) {
			str[w] = 'A' + mt() % 26;
		}

		str[length] = 0;

		for (int e = 0; e < offs; e++) {
			auto pa = std::chrono::steady_clock::now();
			memcpy_avx(cpa, str + e, length - e);
			auto pb = std::chrono::steady_clock::now();
			memcpy_simple(cpb, str + e, length - e);
			auto pc = std::chrono::steady_clock::now();

			time_avx += (std::chrono::duration<double>(pb - pa)).count();
			time_simple += (std::chrono::duration<double>(pc - pb)).count();

			if (strncmp(cpa + e, cpb + e, length - e) != 0) {
				std::cout << "WA " << " iter " << test << " len " << e << "\n";
//				std::cout << str + e << "\n";
//				std::cout << cpa + e << "\n" << cpb + e << "\n";
				return;
			}
		}
	}

	std::cout << "Done\n";
	std::cout << std::fixed << std::setprecision(3);
	std::cout << "Simple copy time: " << time_simple << " sec\n";
	std::cout << "AVX copy time: " << time_avx << " sec\n";
	std::cout << "AVX is " << time_simple / time_avx << " times faster\n";
}

int main() {
	test_wordcount();
	test_memcpy();
	return 0;
}
