#include <iostream>
#include "type_traits.hpp" // Replace with the actual header file name if needed

struct TrivialStruct {
    int x;
};

struct NonTrivialStruct {
    NonTrivialStruct() : x(0) {}
    NonTrivialStruct(const NonTrivialStruct&) = delete; // Non-trivial copy constructor
    int x;
};

struct StandardLayout {
    int x;
    double y;
};

struct NonStandardLayout {
    virtual void func() {}
    int x;
};


struct PodType {
    int x;
    double y;
};

struct NonPodType {
    NonPodType() = default; // User-defined default constructor
    int x;
    double y;
};

template <typename T>
typename myTypeTraits::enable_if<myTypeTraits::is_integral<T>::value, T>::type
foo(T value)
{
    return value + 1;
}

// Function template that is enabled only for floating-point types
template <typename T>
typename myTypeTraits::enable_if<myTypeTraits::is_floating_point<T>::value, T>::type
foo(T value)
{
    return value * 2.0;
}

using chosen_type = myTypeTraits::conditional_t<true, int, double>; 
using other_type = myTypeTraits::conditional_t<false, int, double>;


int main() {
    // Test is_same
    std::cout << "is_same_v<int, int>: " << myTypeTraits::is_same_v<int, int> << "\n";
    std::cout << "is_same_v<int, double>: " << myTypeTraits::is_same_v<int, double> << "\n";

    // Test remove_const
    std::cout << "is_same_v<myTypeTraits::remove_const_t<const int>, int>: " 
              << myTypeTraits::is_same_v<myTypeTraits::remove_const_t<const int>, int> << "\n";

    // Test is_void
    std::cout << "is_void_v<void>: " << myTypeTraits::is_void_v<void> << "\n";
    std::cout << "is_void_v<int>: " << myTypeTraits::is_void_v<int> << "\n";

    // Test is_null_pointer
    std::nullptr_t np = nullptr;
    std::cout << "is_null_pointer_v<decltype(np)>: " << myTypeTraits::is_null_pointer_v<decltype(np)> << "\n";

    // Test is_integral
    std::cout << "is_integral_v<int>: " << myTypeTraits::is_integral_v<int> << "\n";
    std::cout << "is_integral_v<float>: " << myTypeTraits::is_integral_v<float> << "\n";

    // Test is_floating_point
    std::cout << "is_floating_point_v<float>: " << myTypeTraits::is_floating_point_v<float> << "\n";
    std::cout << "is_floating_point_v<int>: " << myTypeTraits::is_floating_point_v<int> << "\n";

    // Test is_array
    std::cout << "is_array_v<int[]>: " << myTypeTraits::is_array_v<int[]> << "\n";
    std::cout << "is_array_v<int[5]>: " << myTypeTraits::is_array_v<int[5]> << "\n";

    // Test is_enum
    enum MyEnum { A, B, C };
    std::cout << "is_enum_v<MyEnum>: " << myTypeTraits::is_enum_v<MyEnum> << "\n";
    std::cout << "is_enum_v<int>: " << myTypeTraits::is_enum_v<int> << "\n";

    // Test is_pointer
    int* ptr = nullptr;
    std::cout << "is_pointer_v<decltype(ptr)>: " << myTypeTraits::is_pointer_v<decltype(ptr)> << "\n";
    std::cout << "is_pointer_v<int>: " << myTypeTraits::is_pointer_v<int> << "\n";

    // Test is_lvalue_referance
    int x = 5;
    std::cout << "is_lvalue_referance_v<int&>: " << myTypeTraits::is_lvalue_referance_v<int&> << "\n";
    std::cout << "is_lvalue_referance_v<int>: " << myTypeTraits::is_lvalue_referance_v<int> << "\n";

    // Test is_rvalue_referance
    std::cout << "is_rvalue_referance_v<int&&>: " << myTypeTraits::is_rvalue_referance_v<int&&> << "\n";
    std::cout << "is_rvalue_referance_v<int>: " << myTypeTraits::is_rvalue_referance_v<int> << "\n";

    // Test is_arithmetic
    std::cout << "is_arithmetic_v<int>: " << myTypeTraits::is_arithmetic_v<int> << "\n";
    std::cout << "is_arithmetic_v<double>: " << myTypeTraits::is_arithmetic_v<double> << "\n";

    // Test is_fundamental
    std::cout << "is_fundamental_v<int>: " << myTypeTraits::is_fundamental_v<int> << "\n";
    // std::cout << "is_fundamental_v<void>: " << myTypeTraits::is_fundamental_v<void> << "\n";



    std::cout << "is_reference_v<int>: " << myTypeTraits::is_reference_v<int> << "\n"; // Expected: 0 (false)
    std::cout << "is_reference_v<int&>: " << myTypeTraits::is_reference_v<int&> << "\n"; // Expected: 1 (true)
    std::cout << "is_reference_v<int&&>: " << myTypeTraits::is_reference_v<int&&> << "\n"; // Expected: 1 (true)

    std::cout << "is_const_v<int>: " << myTypeTraits::is_const_v<int> << "\n"; // Expected: 0 (false)
    std::cout << "is_const_v<const int>: " << myTypeTraits::is_const_v<const int> << "\n"; // Expected: 1 (true)


    std::cout << "is_trivial<TrivialStruct>::value: " << std::is_trivial<TrivialStruct>::value << "\n"; // Expected: 1 (true)
    std::cout << "is_trivial<NonTrivialStruct>::value: " << std::is_trivial<NonTrivialStruct>::value << "\n"; // Expected: 0 (false)

    std::cout << "is_standard_layout_v<int>: " << myTypeTraits::is_standard_layout_v<int> << "\n"; // Expected: 1 (true)
    std::cout << "is_standard_layout_v<StandardLayout>: " << myTypeTraits::is_standard_layout_v<StandardLayout> << "\n"; // Expected: 1 (true)
    std::cout << "is_standard_layout_v<NonStandardLayout>: " << myTypeTraits::is_standard_layout_v<NonStandardLayout> << "\n"; // Expected: 0 (false)


    std::cout << "is_pod_v<int>: " << myTypeTraits::is_pod_v<int> << "\n"; // Expected: 1 (true)
    std::cout << "is_pod_v<PodType>: " << myTypeTraits::is_pod_v<PodType> << "\n"; // Expected: 1 (true)
    std::cout << "is_pod_v<NonPodType>: " << myTypeTraits::is_pod_v<NonPodType> << "\n"; // Expected: 0 (false)

    std::cout << foo(5) << "\n";
    std::cout << foo(5.5) << "\n";

    chosen_type a = 42; 
    other_type b = 3.14; 

    std::cout << "chosen_type is int: " << myTypeTraits::is_same_v<chosen_type, int> << "\n";
    std::cout << "other_type is double: " << myTypeTraits::is_same_v<other_type, double> << "\n";


    return 0;
}
