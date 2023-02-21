#include <typeinfo>
#include <string>
#include <cstdint>

// A custom enum class which supports inheritance and can be used internally as a replacement for string arguments
class UE5_INLINE_CLASS_ENUM_EXAMPLE 
{
	// An enum macro definition which can be used to define a custom enum class
	#define UE5_INLINE_CLASS_ENUM enum class

	// using declaration for unsigned long long int
	using ULINT64 = unsigned long long int;

public:

	// Constructor
	explicit UE5_INLINE_CLASS_ENUM_EXAMPLE(ULINT64 value) : _value{ value } {};

	// Overloaded operators
	bool operator== (const UE5_INLINE_CLASS_ENUM_EXAMPLE& other) const
	{
		return _value == other._value;
	}

	// Overloaded operators
	friend std::ostream& operator<< (std::ostream& os, const UE5_INLINE_CLASS_ENUM_EXAMPLE& c)
	{
		std::string name = typeid(c).name();
		os << name;
		return os;
	}

	// Static values
	static const UE5_INLINE_CLASS_ENUM_EXAMPLE NONE;
	static const UE5_INLINE_CLASS_ENUM_EXAMPLE BLUE;
	static const UE5_INLINE_CLASS_ENUM_EXAMPLE GREEN;

private:

	// Internal value
	ULINT64 _value;

	// deleted assignment operator
	UE5_INLINE_CLASS_ENUM_EXAMPLE& operator=(const UE5_INLINE_CLASS_ENUM_EXAMPLE& c) = delete;
};

const UE5_INLINE_CLASS_ENUM_EXAMPLE UE5_INLINE_CLASS_ENUM_EXAMPLE::NONE{ 0ui64 };

// Example usage:
UE5_INLINE_CLASS_ENUM_EXAMPLE c = UE5_INLINE_CLASS_ENUM_EXAMPLE::NONE;

//static_assert(c == UE5_INLINE_CLASS_ENUM_EXAMPLE::NONE, "c is not equal to UE5_INLINE_CLASS_ENUM_EXAMPLE::NONE");
//static_assert(c == 0ui64, "c is not equal to UE5_INLINE_CLASS_ENUM_EXAMPLE::NONE");


