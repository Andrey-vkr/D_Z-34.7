#include <iostream>
#include <concepts>
#include <string>


template <typename T>
concept ComplexConcept = requires(const T v)
{
	{ v.hash() } -> std::convertible_to<long>;
	{ v.toString() } -> std::same_as<std::string>;
} && !std::has_virtual_destructor<T>::value;

class ExampleConcept1
{
	int _num{};
public:
	ExampleConcept1(const int num) :_num(num) {}

	long hash() const
	{
		return _num;
	}

	std::string toString() const
	{
		return std::to_string(_num);
	}
};

class ExampleConcept2
{
	int _num{};
public:
	ExampleConcept2(const int num) :_num(num) {}

	virtual ~ExampleConcept2() {}

	long hash() const
	{
		return _num;
	}

	std::string toString() const
	{
		return std::to_string(_num);
	}
};

template <ComplexConcept T>
void printConcept(T v)
{
	std::cout << "hash: " << v.hash() << '\n';
	std::cout << "toString: " << v.toString() << '\n';
}


int main()
{
	ExampleConcept1 c1{ 12 };
	static_assert(ComplexConcept<ExampleConcept1>);  // compiles successfully
	printConcept(c1);

	//ExampleConcept2 c2{ 12 };
	//static_assert(ComplexConcept<ExampleConcept2>); // compilation error!
	//printConcept(c2);

	return 0;
}

