#include <iostream>

namespace myTypeTraits {

// Integral Constant
template <typename T, T val>
struct integral_constant
{
    static constexpr T value = val;
    using type = T;
    using value_type = integral_constant;
    // Conversion operator to retrieve the value
    constexpr operator value_type () const noexcept
    {
        return value; 
    }
    // Function call operator to retrieve the value
    constexpr value_type operator ()() const noexcept 
    {
        return value;
    }
};

// Bool Constant and True/False Type Aliases
template <bool val>
using bool_constant = integral_constant<bool, val>;

using true_type = bool_constant<true>;
using false_type = bool_constant<false>;

// Is Same Type Trait
template <typename T, typename U>
struct is_same : false_type
{};

// Inline variable for easy access to is_same value
template <typename T, typename U>
inline constexpr bool is_same_v = is_same<T, U>::value;

// Specialization for the case when both types are the same
template <typename T>
struct is_same<T, T> : true_type
{};

// Remove Const Type Trait
template <typename T>
struct remove_const
{
    using type = T;
};

// Specialization to remove const qualifier
template<typename T>
struct remove_const<const T>
{
    using type = T;
};

// Alias to simplify access to the type without const qualifier
template <typename T>
using remove_const_t = typename remove_const<T>::type;

// Remove Volatile Type Trait
template <typename T>
struct remove_volatile
{   
    using type = T;
};

// Specialization to remove volatile qualifier
template <typename T>
struct remove_volatile<volatile T>
{   
    using type = T;
};

// Alias to simplify access to the type without volatile qualifier
template <typename T>
using remove_volatile_t = typename remove_volatile<T>::type;

// Remove CV (Const and Volatile) Type Trait
template <typename T>
struct remove_cv 
{
    using type = remove_volatile_t<remove_const_t<T>>;
};

// Alias to simplify access to the type without const and volatile qualifiers
template <typename T>
using remove_cv_t = typename remove_cv<T>::type;

// Is Void Type Trait
template <typename T>
struct is_void : is_same<void, typename remove_cv<T>::type>
{};

// Inline variable for easy access to is_void value
template <typename T>
inline constexpr bool is_void_v = is_void<T>::value;

// Is Null Pointer Type Trait
template <typename T>
struct is_null_pointer : false_type
{};

// Specialization for std::nullptr_t
template <>
struct is_null_pointer<std::nullptr_t> : true_type
{};

// Inline variable for easy access to is_null_pointer value
template< class T >
inline constexpr bool is_null_pointer_v = is_null_pointer<T>::value;

// Is Integral Type Trait (using requires clause)
template< class T >
struct is_integral : bool_constant<
    requires(T t, T* ptr, void (*f)(T)) {
        reinterpret_cast<T>(t);
        ptr + t;
        f(0);
    }
>  {};

// Inline variable for easy access to is_integral value
template< class T >
inline constexpr bool is_integral_v = is_integral<T>::value;

// Is Floating Point Type Trait
template <typename T>
struct is_floating_point : integral_constant<bool, is_same<float, typename remove_cv<T>::type>::value
                                                || is_same<double, typename remove_cv<T>::type>::value
                                                || is_same<long double, typename remove_cv<T>::type>::value>
{};

// Inline variable for easy access to is_floating_point value
template< class T >
inline constexpr bool is_floating_point_v = is_floating_point<T>::value;

// Is Array Type Trait
template <typename T>
struct is_array : false_type
{};

// Specialization for unbounded arrays
template <typename T>
struct is_array<T[]> : true_type
{};

// Specialization for bounded arrays
template <typename T, size_t N>
struct is_array<T[N]> : true_type
{};

// Inline variable for easy access to is_array value
template <typename T>
inline constexpr bool is_array_v = is_array<T>::value;

// Is Enum Type Trait (using compiler intrinsic)
template <typename T>
struct is_enum : integral_constant<bool, __is_enum(T)> 
{};

// Inline variable for easy access to is_enum value
template <typename T>
inline constexpr bool is_enum_v = is_enum<T>::value;

// Is Union Type Trait (using compiler intrinsic)
template <typename T>
struct is_union : integral_constant<bool, __is_union(T)>
{};

// Inline variable for easy access to is_union value
template <typename T>
inline constexpr bool is_union_v = is_union<T>::value;

// Is Class Type Trait (using compiler intrinsic)
template <typename T>
struct is_class : integral_constant<bool, __is_class(T)>
{};

// Inline variable for easy access to is_class value
template <typename T>
inline constexpr bool is_class_v = is_class<T>::value;

// Is Pointer Type Trait
template <typename T>
struct is_pointer : false_type
{};

// Specialization for pointer types
template <typename T>
struct is_pointer<T*> : true_type
{};

// Specialization for const pointers
template <typename T>
struct is_pointer<T* const> : true_type
{};

// Specialization for volatile pointers
template <typename T>
struct is_pointer<T* volatile> : true_type
{};

// Specialization for const volatile pointers
template <typename T>
struct is_pointer<T* const volatile> : true_type
{};

// Inline variable for easy access to is_pointer value
template <typename T>
inline constexpr bool is_pointer_v = is_pointer<T>::value;

// Is Lvalue Reference Type Trait
template <typename T>
struct is_lvalue_referance : false_type
{};

// Specialization for lvalue references
template <typename T>
struct is_lvalue_referance<T&> : true_type
{};

// Inline variable for easy access to is_lvalue_referance value
template <typename T>
inline constexpr bool is_lvalue_referance_v = is_lvalue_referance<T>::value;

// Is Rvalue Reference Type Trait
template <typename T>
struct is_rvalue_referance : false_type
{};

// Specialization for rvalue references
template <typename T>
struct is_rvalue_referance<T&&> : true_type
{};

// Inline variable for easy access to is_rvalue_referance value
template <typename T>
inline constexpr bool is_rvalue_referance_v = is_rvalue_referance<T>::value;

// Is Arithmetic Type Trait
template <typename T>
struct is_arithmetic : integral_constant<bool, is_integral<T>::value || is_floating_point<T>::value>
{};

// Inline variable for easy access to is_arithmetic value
template <typename T>
inline constexpr bool is_arithmetic_v = is_arithmetic<T>::value;

// Is Fundamental Type Trait
template <typename T>
struct is_fundamental : integral_constant<bool,
                                             is_arithmetic<T>::value ||
                                             is_void<T>::value || 
                                             is_null_pointer<T>::value>
{};

// Inline variable for easy access to is_fundamental value
template <typename T>
inline constexpr bool is_fundamental_v = is_fundamental<T>::value;

// Helper Trait for Member Pointers
template <typename T>
struct is_member_pointer_helper : false_type
{};

// Specialization for member pointers
template <typename T, typename U>
struct is_member_pointer_helper<T U::*> : true_type
{};

// Is Member Pointer Type Trait
template <typename T>
struct is_member_pointer : is_member_pointer_helper<typename remove_cv<T>::type>
{};

// Inline variable for easy access to is_member_pointer value
template <typename T>
inline constexpr bool is_member_pointer_v = is_member_pointer<T>::value;

// Is Scalar Type Trait
template <typename T>
struct is_scalar : integral_constant<bool, is_arithmetic<T>::value || is_enum<T>::value ||
                                            is_pointer<T>::value || is_member_pointer<T>::value || 
                                            is_null_pointer<T>::value>
{};

// Inline variable for easy access to is_scalar value
template <typename T>
inline constexpr bool is_scalar_v = is_scalar<T>::value;

// Helper Trait for Member Function Pointers
template <typename T>
struct is_member_function_pointer_helper : false_type
{};

// Specialization for member function pointers
template <typename T, typename U>
struct is_member_function_pointer_helper<T U::*> : integral_constant<bool, __is_function(T)>
{};

// Is Member Function Pointer Type Trait
template <typename T>
struct is_member_function_pointer : is_member_function_pointer_helper<T>
{};

// Inline variable for easy access to is_member_function_pointer value
template <typename T>
inline constexpr bool is_member_function_pointer_v = is_member_function_pointer<T>::value;

// Is Member Object Pointer Type Trait
template <typename T>
struct is_member_object_pointer : integral_constant<bool, is_member_function_pointer_v<T> ||
                                                          is_member_pointer_v<T>>
{};

// Inline variable for easy access to is_member_object_pointer value
template <typename T>
inline constexpr bool is_member_object_pointer_v = is_member_object_pointer<T>::value;

// Is Object Type Trait
template<class T>
struct is_object : std::integral_constant<bool,
                                                is_scalar_v<T> ||
                                                is_array_v<T> ||
                                                is_union_v<T> ||
                                                is_class_v<T>> 
{};

// Is Compound Type Trait
template<class T>
struct is_compound : integral_constant<bool, !is_fundamental<T>::value> 
{};

// Inline variable for easy access to is_compound value
template <typename T>
inline constexpr bool is_compound_v = is_compound<T>::value;

// is_reference trait
template <typename T>
struct is_reference : std::false_type
{};

// Specialization for lvalue references
template <typename T>
struct is_reference<T&> : std::true_type
{};

// Specialization for rvalue references
template <typename T>
struct is_reference<T&&> : std::true_type
{};

// Inline variable for easy access to is_reference value
template <typename T>
inline constexpr bool is_reference_v = is_reference<T>::value;

// is_const trait
template <typename T>
struct is_const : std::false_type
{};

// Specialization for const-qualified types
template <typename T>
struct is_const<const T> : std::true_type
{};

// Inline variable for easy access to is_const value
template <typename T>
inline constexpr bool is_const_v = is_const<T>::value;

// is_volatile trait
template <typename T>
struct is_volatile : std::false_type
{};

// Specialization for volatile types
template <typename T>
struct is_volatile<volatile T> : std::true_type
{};

// Inline variable for easy access to is_volatile value
template <typename T>
inline constexpr bool is_volatile_v = is_volatile<T>::value;

// is_trivial trait
template <typename T>
struct is_trivial : std::integral_constant<bool, __is_trivial(T)>
{};

// Inline variable for easy access to is_trivial value
template <typename T>
inline constexpr bool is_trivial_v = is_trivial<T>::value;

// is_trivially_copyable trait
template <typename T>
struct is_trivially_copyable : std::integral_constant<bool, __is_trivially_copyable(T)>
{};

// Inline variable for easy access to is_trivially_copyable value
template <typename T>
inline constexpr bool is_trivially_copyable_v = is_trivially_copyable<T>::value;


// is_standard_layout trait
template <typename T>
struct is_standard_layout : std::integral_constant<bool, __is_standard_layout(T)>
{};

// Inline variable for easy access to is_standard_layout value
template <typename T>
inline constexpr bool is_standard_layout_v = is_standard_layout<T>::value;

// is_pod trait
template <typename T>
struct is_pod : std::integral_constant<bool, __is_pod(T)>
{};

// Inline variable for easy access to is_pod value
template <typename T>
inline constexpr bool is_pod_v = is_pod<T>::value;

// Adds the const qualifier to a type T
template <typename T>
struct add_const 
{
    // The type member alias is defined as const T
    using type = const T;
};

// Helper alias template to simplify access to add_const
template <typename T>
using add_const_t = typename add_const<T>::type;

// Adds the volatile qualifier to a type T
template <typename T>
struct add_volatile
{
    // The type member alias is defined as volatile T
    using type = volatile T;
};

// Helper alias template to simplify access to add_volatile
template <typename T>
using add_volatile_t = typename add_volatile<T>::type;

// Adds both const and volatile qualifiers to a type T
template <typename T>
struct add_cv
{
    // The type member alias is defined as const volatile T
    using type = const volatile T;
};

// Helper alias template to simplify access to add_cv
template <typename T>
using add_cv_t = typename add_cv<T>::type;

// Primary template for remove_reference
template <typename T>
struct remove_reference 
{ 
    using type = T; 
};

// Specialization for lvalue references
template <typename T>
struct remove_reference<T&> 
{ 
    using type = T;
};

// Specialization for rvalue references
template <typename T>
struct remove_reference<T&&> 
{ 
    using type = T;
};

// Helper alias template for easy access to remove_reference
template <typename T>
using remove_reference_t = typename remove_reference<T>::type;

// Adds an lvalue reference to a type T
template <typename T>
struct add_lvalue_reference 
{
    using type = T&;
};

// Helper alias template to simplify access to add_lvalue_reference
template <typename T>
using add_lvalue_reference_t = typename add_lvalue_reference<T>::type;

// Adds an rvalue reference to a type T
template <typename T>
struct add_rvalue_reference 
{
    using type = T&&;
};

// Helper alias template to simplify access to add_rvalue_reference
template <typename T>
using add_rvalue_reference_t = typename add_rvalue_reference<T>::type;

// Remove pointer type trait
template<class T> 
struct remove_pointer { 
    using type = T; 
};

template<class T> 
struct remove_pointer<T*> { 
    using type = T; 
};

template<class T> 
struct remove_pointer<T* const> { 
    using type = T; 
};

template<class T> 
struct remove_pointer<T* volatile> { 
    using type = T; 
};

template<class T> 
struct remove_pointer<T* const volatile> { 
    using type = T; 
};

// Helper alias template
template<class T>
using remove_pointer_t = typename remove_pointer<T>::type;

// Add pointer type trait
template <typename T>
struct add_pointer {
    using type = T*;
};

// Specializations for const, volatile, and cv-qualifiers
template <typename T>
struct add_pointer<T*> {
    using type = T*;
};

template <typename T>
struct add_pointer<const T> {
    using type = const T*;
};

template <typename T>
struct add_pointer<volatile T> {
    using type = volatile T*;
};

template <typename T>
struct add_pointer<const volatile T> {
    using type = const volatile T*;
};

// Helper alias template
template <typename T>
using add_pointer_t = typename add_pointer<T>::type;

// Primary template
template <bool B, typename T = void>
struct enable_if
{};

// Specialization for true condition
template <typename T>
struct enable_if<true, T>
{
    using type = T;
};

// Helper alias template
template <bool B, typename T = void>
using enable_if_t = typename enable_if<B, T>::type;


template<bool B, typename T, typename F>
struct conditional
{
    using type = T; 
};

template<typename T, typename F>
struct conditional<false, T, F>
{
    using type = F; 
};

// Helper alias template
template<bool B, typename T, typename F>
using conditional_t = typename conditional<B, T, F>::type;







}
//
