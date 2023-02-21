#pragma once

#include <iostream>
#include <vector>
#include <string>

/**

Example usage:

	StackTraceStdStrArray trace_a{"Hello"}; // "Hello"
	trace_a.push("World"); // "Hello > World"
	trace_a.pop(); // "Hello"

*/
template <typename InputType = std::string>
class StackTraceStdStrArray : public std::vector<InputType>
{
public:
	explicit StackTraceStdStrArray(const InputType& str) 
	{
		array.push_back(str);
		join();
	}

	void push(const InputType& str)
	{
		array.push_back(str);
		join();
	}

	InputType& pop()
	{
		InputType& result = array.back();
		array.pop_back();
		join();
		return result;
	}
	
	InputType join(const InputType separator = "\n") const
	{
		InputType result = InputType{};
		InputType delim = InputType{};
		InputType pad = InputType{ " " };
		bool first = true;
		for (const auto& buff : array) 
		{
			if (!first) 
			{
				delim += pad;
				result += separator + delim;
			}
			result += buff;
			first = false;
		}
		std::cout << result << std::endl;
		return result;
	}

private:
	std::vector<InputType> array;

};
