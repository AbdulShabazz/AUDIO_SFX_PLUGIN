// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

	#include "CoreMinimal.h"
	#include "Misc/Attribute.h"
	#include "Layout/Visibility.h"
	#include "Layout/Clipping.h"
	#include "Layout/FlowDirection.h"
	#include "Rendering/SlateRenderTransform.h"
	#include "GenericPlatform/ICursor.h"
	#include "Types/ISlateMetaData.h"
	#include "Widgets/SNullWidget.h"
	#include "Widgets/Accessibility/SlateWidgetAccessibleTypes.h"
	#include <unordered_map>
	#include <functional>
	#include <type_traits>
	#include <cstdint>
	#include <ctime>
	#include <typeinfo>
	#include <iostream>
	#include <variant>
	#include <string>
	#include <algorithm>
	#include <stdexcept>

namespace UE5_INLINE_CLASS_NAMESPACE
{

	/**
 
	According to an OpenAI chat client, the Unreal Engine reflection system can be improved further and optimized in several ways:

	1. Caching and pre-computation: Reflection data is generated during runtime, which can impact performance. 
	The Unreal Engine could cache the reflection data and pre-compute certain values to reduce the runtime overhead.

	2. Reducing the size of reflection data: The size of the reflection data can have a direct impact on performance, as more memory needs to be allocated and managed. 
	The Unreal Engine could look for ways to reduce the size of the reflection data, for example by storing only the essential information for each class and avoiding redundant data.

	3. Improving the performance of reflection-related operations: The Unreal Engine could look for ways to improve the performance of the operations that use reflection data, such as querying properties, calling functions, and creating instances of classes. 
	For example, the engine could use more efficient algorithms or data structures to perform these operations.

	4. Integrating with other systems: The Unreal Engine reflection system could be integrated with other systems in the engine, such as the blueprint visual scripting system, to make the best use of the reflection data and reduce overhead.

	5. Supporting more types of data: The Unreal Engine could expand the types of data that are reflected, including custom data types, to provide more flexibility and power to developers.

	It's worth noting that any improvements made to the Unreal Engine reflection system should also balance the trade-off between performance and maintainability. 
	While optimizations can improve performance, they may also make the codebase more complex and harder to maintain, so it's important to carefully consider the trade-offs when making changes.

		INLINE_CLASS_UE5 is able to support custom argument types,
		along with default values, through a minimal class interface.
		And facilitates validation of each argument by accepting a truthy-type callback.
		It also provides error handling using an error handling callback for each argument.
		Additionally, the dynamic implementation is written to be C++20 compliant, is more maintainable, 
		as it can be easily modified and extended as needed.

		The Visual Studio compiler automatically attempts to inline class methods defined in header file classes, 
		so it may be possible for a dynamic C++ implementation of the reflection system to rival the
		current state-of-the-art reflection system, while supporting type-safety and a wider array of data types -- 
		greatly increasing the robustness and stability of the system.

	Example usage:
 
	using namespace UE5_INLINE_CLASS_NAMESPACE;
	
	class beta : public UE5_INLINE_CLASS<beta>
	{
	public:
		beta()
		{
			// Optional nested class constructor
			UE5_BEGIN_CLASS_DEFINITION( "Class" ) : [public / private / virtual ...] , ...

			// inline class member definition(s)
			UE5_BEGIN_CLASS_MEMBER_DEFINITIONS();

				AddPrivateAttribute(...);
				AddPrivateMethod(...);
				AddPublicAttribute(...);
				AddPublicMethod(...);

			UE5_END_CLASS_MEMBER_DEFINITIONS();

			UE5_END_CLASS_DEFINITION()

		}
	};

	// Create a reference to an object of type TRefParams by forwarding an rvalue reference.
	TRefParams& TRefParamsObjRef = std::forward<TRefParams&>(TRefParams());

	// Create a reference to an object of type beta by forwarding an rvalue reference to the result of calling beta::New().
	beta& BetaTestClass = beta::New();

	// Add a method named "MyCustomMethod" to the BetaTestClass object, which takes a TRefParams reference and has three associated std::function objects:
	// 1. A void function that prints "Hello World!" to the console.
	// 2. A boolean function that checks if the values of TRefParamsObjRef's _a and _b member variables are non-negative and returns a boolean.
	// 3. A void function that prints a warning message to the console if the values of TRefParamsObjRef's _a and _b member variables are negative.	
	BetaTestClass.AddMethod<
		std::string,
		std::function<void(TRefParams&)>,
		std::function<bool(TRefParams&)>,
		std::function<void(TRefParams&)>>(
			"MyCustomMethod",
			[&](TRefParams& TRefParamsObjRef) { std::cout << "Hello World!" << std::endl; },
			[&](TRefParams& TRefParamsObjRef) { return TRefParamsObjRef._a >= 0 && TRefParamsObjRef._b >= 0; },
			[&](TRefParams& TRefParamsObjRef) { std::cout << "Warning: One or more parameters is less than zero!" << std::endl; }
	);

	// Call the "MyCustomMethod" Setter
	BetaTestClass.Invoke<TRefParams&>("MyCustomMethod", TRefParamsObjRef);

	// Call the "MyCustomMethod" Getter
	TRefParams& TRefParamsObjRef2 = BetaTestClass.Invoke<TRefParams&>("MyCustomMethod", TRefParamsObjRef);

	// Add a named attribute "MyCustomAttribute" to the BetaTestClass object, which takes a TRefParams reference and has three associated std::function objects:
	// 1. A TRefParams& accessor() function that prints "Hello World!" to the console.
	// 2. A boolean function that checks if the values of TRefParamsObjRef's _a and _b member variables are non-negative and returns a boolean.
	// 3. A void function that prints a warning message to the console if the values of TRefParamsObjRef's _a and _b member variables are negative.
	BetaTestClass.AddAttribute(...);

	// Call the "MyCustomAttribute" Setter
	BetaTestClass.Invoke<TRefParams&>("MyCustomAttribute", TRefParamsObjRef);

	// Call the "MyCustomAttribute" Getter
	TRefParams& TRefParamsObjRef = BetaTestClass.Invoke<TRefParams&>("MyCustomAttribute", TRefParamsObjRef);

	*/

	template<typename WidgetType>
	struct TSlateBaseNamedArgsUE5;

	// BEGIN UE5.DeclarativeSyntaxSupport.h //

	struct TRefParams
	{
		explicit TRefParams(TRefParams& TwoIntRefParamObjRef) : _a{ TwoIntRefParamObjRef._a = 0 }, _b{ TwoIntRefParamObjRef._b = 0 } {};

		TRefParams() : _a{ 0 }, _b{ 0 } {};

		int _a;
		int _b;
	};

	template<typename WidgetType>
	class UE5_INLINE_CLASS
	{
	public:

		static WidgetType& New()
		{
			static WidgetType instance;
			return instance;
		}

		#define UE5_BEGIN_ADD_CLASS_DEFINITION(MyInlineClass, ...) \
		template <typename OtherWidgetType> \
		class #MyInlineClass : public INLINE_CLASS_UE5, __VA_ARGS__ \
		{ \

		#define UE5_END_ADD_CLASS_DEFINITION() \
		}; \

		void UE5_BEGIN_CLASS_MEMBER_DEFINITIONS()
		{
			bBeginArgsFlag = true;
		}

		void UE5_END_CLASS_MEMBER_DEFINITIONS()
		{
			bBeginArgsFlag = false;
		}

		// Other inline class members

		template <
			typename EventName,
			typename EventBody,
			typename ValidationCallback,
			typename ErrorCallback>
		void AddEvent(
			const EventName& EventNameStdStr,
			EventBody EventBodyVoidFunc,
			ValidationCallback ValidationCallbackBoolFunc,
			ErrorCallback ErrorCallbackVoidFunc)
		{
			auto method = [EventBodyVoidFunc, ValidationCallbackBoolFunc, ErrorCallbackVoidFunc](TRefParams& params) {
				if (ValidationCallbackBoolFunc(params))
				{
					EventBodyVoidFunc(params);
				}
				else
				{
					ErrorCallbackVoidFunc(params);
				}
			};
			_public.insert({ EventNameStdStr,method });
		}

		template <
			typename MethodName, 
			typename MethodBody, 
			typename ValidationCallback, 
			typename ErrorCallback>
		void AddMethod(
			const MethodName& MethodNameStdStr,
			MethodBody MethodBodyVoidFunc,
			ValidationCallback ValidationCallbackBoolFunc,
			ErrorCallback ErrorCallbackVoidFunc)
		{
			auto method = [MethodBodyVoidFunc, ValidationCallbackBoolFunc, ErrorCallbackVoidFunc](TRefParams& params) {
				if (ValidationCallbackBoolFunc(params)) 
				{
					MethodBodyVoidFunc(params);
				}
				else 
				{
					ErrorCallbackVoidFunc(params);
				}
			};
			_public.insert({ MethodNameStdStr,method });
		}

		template <
			typename AttributeName,
			typename AttributeBody,
			typename ValidationCallback,
			typename ErrorCallback>
		void AddAttribute(
			const AttributeName& AttributeNameStdStr,
			AttributeBody AttributeBodyTFunc,
			ValidationCallback ValidationCallbackBoolFunc,
			ErrorCallback ErrorCallbackVoidFunc)
		{
			auto method = [AttributeBodyTFunc, ValidationCallbackBoolFunc, ErrorCallbackVoidFunc](TRefParams& params) {
				if (ValidationCallbackBoolFunc(params))
				{
					AttributeBodyTFunc(params);
				}
				else
				{
					ErrorCallbackVoidFunc(params);
				}
			};
			_public.insert({ AttributeNameStdStr,method });
		}

		// public inline class members

		template <
			typename EventName,
			typename EventBody,
			typename ValidationCallback,
			typename ErrorCallback>
		void AddPublicEvent(
			const EventName& EventNameStdStr,
			EventBody EventBodyVoidFunc,
			ValidationCallback ValidationCallbackBoolFunc,
			ErrorCallback ErrorCallbackVoidFunc)
		{
			auto method = [EventBodyVoidFunc, ValidationCallbackBoolFunc, ErrorCallbackVoidFunc](TRefParams& params) {
				if (ValidationCallbackBoolFunc(params))
				{
					EventBodyVoidFunc(params);
				}
				else
				{
					ErrorCallbackVoidFunc(params);
				}
			};
			_public.insert({ EventNameStdStr,method });
		}

		template <
			typename MethodName,
			typename MethodBody,
			typename ValidationCallback,
			typename ErrorCallback>
		void AddPublicMethod(
			const MethodName& MethodNameStdStr,
			MethodBody MethodBodyVoidFunc,
			ValidationCallback ValidationCallbackBoolFunc,
			ErrorCallback ErrorCallbackVoidFunc)
		{
			auto method = [MethodBodyVoidFunc, ValidationCallbackBoolFunc, ErrorCallbackVoidFunc](TRefParams& params) {
				if (ValidationCallbackBoolFunc(params))
				{
					MethodBodyVoidFunc(params);
				}
				else
				{
					ErrorCallbackVoidFunc(params);
				}
			};
			_public.insert({ MethodNameStdStr,method });
		}

		template <
			typename AttributeName,
			typename AttributeBody,
			typename ValidationCallback,
			typename ErrorCallback>
		void AddPublicAttribute(
			const AttributeName& AttributeNameStdStr,
			AttributeBody AttributeBodyTFunc,
			ValidationCallback ValidationCallbackBoolFunc,
			ErrorCallback ErrorCallbackVoidFunc)
		{
			auto method = [AttributeBodyTFunc, ValidationCallbackBoolFunc, ErrorCallbackVoidFunc](TRefParams& params) {
				if (ValidationCallbackBoolFunc(params))
				{
					AttributeBodyTFunc(params);
				}
				else
				{
					ErrorCallbackVoidFunc(params);
				}
			};
			_public.insert({ AttributeNameStdStr,method });
		}

		// private inline class members

		template <
			typename EventName,
			typename EventBody,
			typename ValidationCallback,
			typename ErrorCallback>
		void AddPrivateEvent(
			const EventName& EventNameStdStr,
			EventBody EventBodyVoidFunc,
			ValidationCallback ValidationCallbackBoolFunc,
			ErrorCallback ErrorCallbackVoidFunc)
		{
			auto method = [EventBodyVoidFunc, ValidationCallbackBoolFunc, ErrorCallbackVoidFunc](TRefParams& params) {
				if (ValidationCallbackBoolFunc(params))
				{
					EventBodyVoidFunc(params);
				}
				else
				{
					ErrorCallbackVoidFunc(params);
				}
			};
			_private.insert({ EventNameStdStr,method });
		}

		template <
			typename MethodName,
			typename MethodBody,
			typename ValidationCallback,
			typename ErrorCallback>
		void AddPrivateMethod(
			const MethodName& MethodNameStdStr,
			MethodBody MethodBodyVoidFunc,
			ValidationCallback ValidationCallbackBoolFunc,
			ErrorCallback ErrorCallbackVoidFunc)
		{
			auto method = [MethodBodyVoidFunc, ValidationCallbackBoolFunc, ErrorCallbackVoidFunc](TRefParams& params) {
				if (ValidationCallbackBoolFunc(params))
				{
					MethodBodyVoidFunc(params);
				}
				else
				{
					ErrorCallbackVoidFunc(params);
				}
			};
			_private.insert({ MethodNameStdStr,method });
		}

		template <
			typename AttributeName,
			typename AttributeBody,
			typename ValidationCallback,
			typename ErrorCallback>
		void AddPrivateAttribute(
			const AttributeName& AttributeNameStdStr,
			AttributeBody AttributeBodyTFunc,
			ValidationCallback ValidationCallbackBoolFunc,
			ErrorCallback ErrorCallbackVoidFunc)
		{
			auto method = [AttributeBodyTFunc, ValidationCallbackBoolFunc, ErrorCallbackVoidFunc](TRefParams& params) {
				if (ValidationCallbackBoolFunc(params))
				{
					AttributeBodyTFunc(params);
				}
				else
				{
					ErrorCallbackVoidFunc(params);
				}
			};
			_private.insert({ AttributeNameStdStr,method });
		}

		template <typename ParamRefStruct>
		ParamRefStruct& Invoke(const std::string& name, ParamRefStruct& params) {
			if (_public.find(name) != _public.end())
			{
				_public[name](params);
			}
			else
			{
				std::cout << "Warning: UE5_INLINE_CLASS member [ " + name + " ] not found!" << std::endl;
			}
			return params;
		}

	public:
		template<typename UE5InlineClassReturnType>
		UE5InlineClassReturnType& GetClassMember(const std::string MemberNameStdStr)
		{
			return *_public.find(MemberNameStdStr);
		}

		template<typename UE5InlineClassReturnType>
		UE5InlineClassReturnType& GetPrivateClassMember(const std::string MemberNameStdStr)
		{
			return *_private.find(MemberNameStdStr);
		}

	private:
		std::unordered_map<std::string, std::function<std::variant<void, bool, TRefParams&>(std::string&, TRefParams&)>> _public;
		std::unordered_map<std::string, std::function<std::variant<void, bool, TRefParams&>(std::string&, TRefParams&)>> _private;
		std::string _NameClassStr;
		bool bBeginArgsFlag = false;

	};

}
