#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <list>

template <typename T>
struct is_cont {
	static const bool value = false;
};

template <typename T,typename Alloc>
struct is_cont<std::vector<T, Alloc>> {
	static const bool value = true;
};

template <typename T,typename Alloc>
struct is_cont<std::list<T, Alloc>> {
	static const bool value = true;
};

template <typename T, class = typename std::enable_if<is_cont<T>::value>::type>
void print(const T& v) {
	for(const auto &ip_part : v) {
		if (&ip_part != &v.front())
			std::cout << '.';
		std::cout << ip_part;
	}
	std::cout << std::endl;
}

template <typename T>
typename std::enable_if<std::is_integral<T>::value, T>::type print(const T &val) {
	for (int i = sizeof(T); i > 0; --i) {
		if (i != sizeof(T))
			std::cout << '.';
		std::cout << +((val >> (8 * (i - 1))) & 0xFF);
	}
	std::cout << std::endl;
	return val;
}

void print(const std::string &val) {
	std::cout << val << std::endl;
}

int main() {
	try {
		print(char(-1));
		print(short(0));
		print(int(2130706433));
		print(long(8875824491850138409));
		print(std::string("192.168.0.1"));
		print(std::vector<int>{172, 31, 0, 1});
		print(std::list<int>{8, 8, 8, 8});
	} catch(const std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
