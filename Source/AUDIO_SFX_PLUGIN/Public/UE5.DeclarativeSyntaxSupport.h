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
#include <variant>
#include <type_traits>

template<typename WidgetType>
struct TSlateBaseNamedArgsUE5;

template<typename T, typename... Args>
using UE5_VARIANT_METHOD = std::function<T& (Args&...)>;

template<typename T>
using UE5_VARIANT_ATTRIBUTE = std::variant<T&>;

template<typename T, typename... Args, typename... OtherArgs>
using UE5_METHOD = std::variant<UE5_VARIANT_METHOD<T&, Args&...>, OtherArgs&...>;

template<typename... Args>
using UE5_ATTRIBUTE = std::variant<Args&...>;

//template<typename T>
//using UE5_ATTRIBUTE = std::variant<T>;

/**
 
According to an OpenAI chat client, the Unreal Engine reflection system can be further improved and optimized in several ways:

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
 
 class MyWidget : public INLINE_CLASS_UE5<MyWidget>
 {
 public:
    this->SLATE_BEGIN_ARGS();
    this->AddAttributePrivate<bool>("_IsEnabled", TAttribute<bool>(true), [this](const TAttribute<bool>& Attribute) { return Attribute.Get() });
    this->AddAttributePrivate<float>("_PreferredWidth", TAttribute<float>(150.0f), [this](const TAttribute<bool>& Attribute) { return Attribute.Get() });
    this->AddAttributePrivate<FLinearColor>("_ForegroundColor", TAttribute<FLinearColor>(FLinearColor::White), [this](const TAttribute<bool>& Attribute) { return Attribute.Get() },...AttributeGetter...,...AttributeSetter...);
    this->AddAttributePublic<bool>("IsEnabled", TAttribute<bool>(true), [this](const TAttribute<bool>& Attribute) { return Attribute.Get() });
    this->AddEventPrivate<T>(...);
    this->AddMethodPrivate<UE5_METHOD<T(T,...)>>(...);
    this->AddEventPublic<T>(...);
    this->AddMethodPublic<T>(...);
    this->SLATE_END_ARGS();
 
	MyWidget(const FArguments& InArgs)
	{
		// Use InArgs to access arguments passed in
	}
 };

 TSharedRef<MyWidget> widget = MyWidget::New();
 widget->AddMethod<UE5_METHOD<int32(int32)>(
	"Width", 
	[this](const int& Value) { return Value > 0; }, 
	[this](const int& Value) { UE_LOG(LogTemp, Error, "Invalid argument value for Width"); }, 
	[this](int& Value = 100) { return Value; }
 );
 widget->AddAttribute<bool>("IsEnabled", true, TAttribute<bool>(true), [this](const TAttribute<bool>& Attribute) { return Attribute.Get() });
 
 // Define a custom event type
 struct MyEvent {
    int x;
    int y;
 };
 
 // Define a validation callback for the event
 auto eventValidationCallback = [this](const MyEvent& event) {
	  // Validate the event data
	  if (event.x < 0 || event.y < 0) {
	      return false;
	  }
	  return true;
 };

 // Define an error-handling callback for the event
 auto eventErrorCallback = [this](const MyEvent& event) {
   // Handle the error
   UE_LOG(LogTemp, Error, "Error: Invalid event data!");
 };

 // Add the custom event to the widget arguments
 widget->AddEvent<struct MyEvent>(MyEvent{0, 1}, eventValidationCallback, eventErrorCallback);

*/
#include <iostream>
#include <map>
#include <variant>
#include <string>
#include <functional>
#include <algorithm>
#include <stdexcept>

struct TRefParams
{
    explicit TRefParams(TRefParams& TwoIntRefParamABObjRef) : _a{ TwoIntRefParamABObjRef._a }, _b{ TwoIntRefParamABObjRef._b } {};

    TRefParams() : _a{ 0 }, _b{ 0 } {};

    int _a;
    int _b;
};

template <typename WidgetType>
class INLINE_CLASS_UE5
{
public:

    static WidgetType&& New() {
        static WidgetType instance;
        return instance;
    }
    
    #define BEGIN_CLASS_DEFINITION_UE5(MyInlineClass, ...) \
    template <typename OtherWidgetType> \
    class #MyInlineClass : public INLINE_CLASS_UE5, __VA_ARGS__ \
    { \

    #define END_CLASS_DEFINITION_UE5() \
	}; \

    void BEGIN_CLASS_MEMBER_DEFINITIONS_UE5()
    {
        bBeginArgsFlag = true;
    }

    void END_CLASS_MEMBER_DEFINITIONS_UE5()
    {
        bBeginArgsFlag = false;
    }

    template <typename... Args>
    void AddMethod(Args&&... values)
    {
        int MethodName = 0;
        int MethodParams = 1;
        int MethodBody = 2;
		int ValidationCallback = 3;
        int ErrorCallback = 4;

		std::string name = (values[MethodName];
        
        if((!values[ValidationCallback] || values[ValidationCallback](values[MethodParams])) && !bBeginArgsFlag)
        {
            _public[name] = std::forward<T>(values[MethodBody]);
            _public[name + "_ValidationCallback"] = std::forward<T>(values[ValidationCallback]);
            _public[name + "_ErrorCallback"] = std::forward<T>(values[ErrorCallback]);
        }
        else if(values[ErrorCallback] /* && has_foo_method<>::func*/)
        {
            values[ErrorCallback](values[MethodParams]);
        }
        else
        {
			throw std::runtime_error("Error: Invalid ValidationCallback parameter!");
        }
    }

    template <typename... Args>
    void AddAttribute(std::string& name, Args&&... values)
    {
        int AttributeParams = 0;
        int ValidationCallback = 1;
        int ErrorCallback = 2;

        if ((!values[ValidationCallback] || values[ValidationCallback](values[AttributeParams])) && !bBeginArgsFlag)
        { 
            _private[name] = values[AttributeParams];
            _public[name + "_Accessor"] = [this](auto& a) 
            {
                if (a != NULL)
                {
					_private[name] = a;
                }
                else
                {
					a = _private[name];
                }
				return _private[name];
            };
            _public[name + "_ValidationCallback"] = std::forward<T>(values[ValidationCallback]);
            _public[name + "_ErrorCallback"] = std::forward<T>(values[ErrorCallback]);
        }
        else if (values[ErrorCallback] /* && has_foo_method<WidgetType>::func*/)
        {
            values[ErrorCallback](values[AttributeParams]);
        }
        else
        {
            throw std::runtime_error("Error: Invalid ValidationCallback parameter!");
        }
    }

    class TReturnParams
    {
	public:
        explicit TReturnParams(
            UE5_VARIANT_METHOD
            <
            std::function<TRefParams& (TRefParams&)>,
            TRefParams&
            >
            (
                std::function<TRefParams& (TRefParams&)> InlineFuncRef,
                TRefParams& TwoIntRefParamABObjRef
                )
        ) {};

		explicit TReturnParams(TRefParams& TwoIntRefParamABObjRef) : _TwoIntRefParamABObjRef{ TwoIntRefParamABObjRef = TRefParams() } {};

		explicit TReturnParams() : _TwoIntRefParamABObjRef{ TRefParams() } {};

        TRefParams& operator >> (TRefParams&& params)
        {
            std::string name = _NameStdStr;
            if (!params)
            {
                std::cerr << "Error: Method or Attribute'" << name << "' missing _Accessor or params." << std::endl;
            }
            else
            {
                std::string ValidationCallback = name + "_ValidationCallback";
                std::string ErrorCallback = name + "_ErrorCallback";
                if (_public.find(ValidationCallback)(params))
                {
                    std::string nameAccessor = name + "_Accessor";
                    if (_public.count(nameAccessor))
                    {
                        _public.find(nameAccessor)(params);
                    }
                    else
                    {
                        _public.find(name)(params);
                    }
                }
                else
                {
                    _public.find(ErrorCallback)(params);
                }
            }
        };
        
    private:
        TRefParams& _TwoIntRefParamABObjRef;
	};
    
    // object selection operator
    TReturnParams& operator >> (const std::string& name)
    {
        std::string name = _NameStdStr;
        if (name == "")
        {
            std::cerr << "Error: Method or Attribute'" << name << "' missing _Accessor or params." << std::endl;
        }
        else
        {
            std::string ValidationCallback = name + "_ValidationCallback";
            std::string ErrorCallback = name + "_ErrorCallback";
            if (_public.find[ValidationCallback](params))
            {
                std::string nameAccessor = name + "_Accessor";
                if (_public.count(nameAccessor))
                {
                    _public.find(nameAccessor)(params);
                }
                else
                {
                    _public.find(name)(params);
                }
            }
            else
            {
                _public.find[ErrorCallback](params);
            }
        }
    }

public:
    std::unordered_map<std::string, std::variant<std::string, std::function<void(int&, int&)>, bool, void>> _public;
    std::unordered_map<std::string, std::variant<std::string, std::function<void(int&, int&)>, bool, void>> _private;
    
private:
    std::string _NameStdStr;
    bool bBeginArgsFlag = false;
    template <typename T>
    class has_foo_method
    {
        //template <typename T>
        static constexpr auto CheckMethod(T*) -> decltype(std::declval<T>().foo(), std::true_type());

        //template <typename T>
        static constexpr auto CheckMethod(...) -> std::false_type;

    public:
        static constexpr bool func = decltype(CheckMethod<T>(0))::func;
    };

    template <typename T>
    class has_foo_attribute
    {
        //template <typename T>
        static constexpr auto CheckAttribute(T*) -> decltype(std::declval<T>().foo, std::true_type());

        //template <typename T>
        static constexpr auto CheckAttribute(...) -> std::false_type;

    public:
        static constexpr bool value = decltype(CheckAttribute<T>(0))::value;
    };
};
