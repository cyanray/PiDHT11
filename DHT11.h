#pragma once
#include <bitset>
class DHT11
{
private:
	unsigned int DHTPin;
	template <std::size_t R, std::size_t L, std::size_t N>
	std::bitset<R - (L - 1)> bitset_range(std::bitset<N> &bitset_);
public:
	DHT11(unsigned int DHT_PIN);
	void ReadData(unsigned long & temperture, unsigned long & humidity);
	~DHT11();
};

template<std::size_t R, std::size_t L, std::size_t N>
inline std::bitset<R - (L - 1)> DHT11::bitset_range(std::bitset<N>& bitset_)
{
	unsigned long mask = 1;
	unsigned long result = 0;
	for (size_t i = L; i < R; ++i)
	{
		if (bitset_[i])
			result |= mask;
		mask <<= 1;
	}
	return std::bitset<R - (L - 1)>(result);
}
