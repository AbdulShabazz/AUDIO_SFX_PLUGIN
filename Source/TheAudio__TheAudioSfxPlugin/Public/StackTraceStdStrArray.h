#pragma once

// System Includes
#include <iostream>
#include <vector>
#include <string>

// Unreal Engine 5
#include <Logging/LogMacros.h>
#include <Logging/LogVerbosity.h>

/**

Example usage:

	StackTraceStdStrArray trace_a{"Hello"}; // "Hello"
	trace_a.push("World"); // "Hello >> World"
	trace_a.pop(); // "Hello"

*/
template <typename InputType = std::string>
class StackTraceStdStrArray : public std::vector<InputType>
{
public:
	// Constructor
	explicit StackTraceStdStrArray(const InputType& str) 
	{
		array.push_back(str);
		join();
	}

	// Push a new element onto the array
	void push(const InputType& str)
	{
		array.push_back(str);
		join();
	}

	// Pop the last element from the array
	InputType& pop()
	{
		InputType& result = array.back();
		array.pop_back();
		join();
		return result;
	}
	
	// Join the array into a single string with a delimiter between each element
	InputType join(const InputType separator = " >> ") const
	{
		// Create a new string of type InputType
		InputType result = InputType{};

		// Create a flag to indicate if this is the first element
		bool first = true;

		// Join the array into a single string
		for (const auto& buff : array) 
		{
			// Add the separator if this is not the first element
			if (!first) 
			{
				result += separator;
			}
			result += buff;
			first = false;
		}

		// Convert std::string (result) to a UE_LOG() friendly format
		UE_LOG(LogTemp, Display, TEXT("%s"), *FString(result.c_str()));

		// Return the result
		return result;
	}

private:
	// The array
	std::vector<InputType> array;

};
