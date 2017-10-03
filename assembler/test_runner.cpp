#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>

#include "wordcount.h"

const int length = 100000;
const int iter = 1000;
const int offs = 10;

char str[length + 1];

int main() {
	std::mt19937 mt(4);

	double time_avx = 0, time_simple = 0;

	std::cout << "Counting words in strings of length " << length << ", repeat " << iter * offs << " times\n";
	flush(std::cout);

	for (int test = 0; test < 100; test++) {
		for (int w = 0; w < length; w++) {
			if (mt() % 2) {
				str[w] = space;
			} else {
				str[w] = '0';
			}
		}
		str[length] = 0;

		for (int e = 0; e < 100; e++) {
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
				return 0;
			}
		}
	}

	std::cout << "Done\n";
	std::cout << std::fixed << std::setprecision(3);
	std::cout << "Simple count time: " << time_simple << " sec\n";
	std::cout << "AVX count time: " << time_avx << " sec\n";
	std::cout << "AVX is " << time_simple / time_avx << " times faster\n";
	return 0;
}
