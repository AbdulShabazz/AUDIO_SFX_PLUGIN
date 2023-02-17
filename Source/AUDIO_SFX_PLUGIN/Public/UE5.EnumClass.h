#include <typeinfo>
#include <string>

/**
The UE5_INLINE_CLASS_ENUM custom enum class behaves like an enum class which can be inherited from - and thus is extensible; and provides improved type safety and scoping compared to the older-style enum types. This custom enum class can be used internally in lieu of string input.

The UE5_INLINE_CLASS_ENUM class is intended as a more general-purpose data type that could be used throughout the engine, it may make more sense to add it to a shared library or module that can be accessed by other parts of the engine. For example, it could be added to a Runtime/Core or Runtime/Core/Public directory, which contains core engine functionality that is used throughout the engine. The UE5_INLINE_CLASS_ name is shared by a suite of other tools I am developing for Unreal Engine.

// Instantiation example
const UE5_INLINE_CLASS_ENUM UE5_INLINE_CLASS_ENUM::NONE(0);
const UE5_INLINE_CLASS_ENUM UE5_INLINE_CLASS_ENUM::BLUE(1);
const UE5_INLINE_CLASS_ENUM UE5_INLINE_CLASS_ENUM::GREEN(2);

// Example usage:
UE5_INLINE_CLASS_ENUM c = UE5_INLINE_CLASS_ENUM::NONE;
*/

// Example inheritance-supported custom enum class which can be used internally as a replacement for string required input
class UE5_INLINE_CLASS_ENUM 
{
public:
	static const UE5_INLINE_CLASS_ENUM NONE;
	static const UE5_INLINE_CLASS_ENUM BLUE;
	static const UE5_INLINE_CLASS_ENUM GREEN;

	// Overloaded operators
	bool operator== (const UE5_INLINE_CLASS_ENUM& other) const {
		return value_ == other.value_;
	}	
	
	friend std::ostream& operator<< (std::ostream& os, const UE5_INLINE_CLASS_ENUM& c) {
		std::string name = typeid(c).name();
		os << name;
		return os;
	}

// Constructor is private to prevent instantiation of additional values
private:
	UE5_INLINE_CLASS_ENUM(unsigned long long int value)
	{
		std::unordered_map<std::string,int> MyMap;
		MyMap::hasher MyHashFunc = MyMap.hash_function();
		value_  = MyHashFunc(value);
	};

	unsigned long long int value_;
	UE5_INLINE_CLASS_ENUM& operator=(const UE5_INLINE_CLASS_ENUM& c) = delete;
	UE5_INLINE_CLASS_ENUM(const UE5_INLINE_CLASS_ENUM& C) = delete;
};


const UE5_INLINE_CLASS_ENUM UE5_INLINE_CLASS_ENUM::NONE(0);
const UE5_INLINE_CLASS_ENUM UE5_INLINE_CLASS_ENUM::BLUE(1);
const UE5_INLINE_CLASS_ENUM UE5_INLINE_CLASS_ENUM::GREEN(2);

// Example usage:
UE5_INLINE_CLASS_ENUM c = UE5_INLINE_CLASS_ENUM::NONE;