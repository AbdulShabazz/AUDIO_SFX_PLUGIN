#include <typeinfo>
#include <string>

    // Example inheritance-supported custom enum class which can be used internally as a replacement for string input
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
        UE5_INLINE_CLASS_ENUM& operator=() = delete;
        UE5_INLINE_CLASS_ENUM(const UE5_INLINE_CLASS_ENUM& C) = delete;
    };
    

    const UE5_INLINE_CLASS_ENUM UE5_INLINE_CLASS_ENUM::NONE(0);
    const UE5_INLINE_CLASS_ENUM UE5_INLINE_CLASS_ENUM::BLUE(1);
    const UE5_INLINE_CLASS_ENUM UE5_INLINE_CLASS_ENUM::GREEN(2);

    // Example usage:
    UE5_INLINE_CLASS_ENUM c = UE5_INLINE_CLASS_ENUM::NONE;