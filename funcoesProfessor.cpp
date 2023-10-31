#include <random>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <typename T>

inline T extract_bits (const T v, const unsigned bstart, const unsigned blength) {

	const T mask = (1 << blength) - 1;


	return ((v >> bstart) & mask);

}



template <typename T>

inline T set_bits (const T v, const unsigned bstart, const unsigned blength, const T bits) {

	const T mask = ((1 << blength) - 1) << bstart;


	return (v & ~mask) | (bits << bstart);

}
