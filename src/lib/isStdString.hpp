#include <type_traits>

namespace PanCake
{
    template <typename T, typename = void>
    struct isStdString : std::false_type {};

    template <typename T>
    struct isStdString<T,
        std::void_t<
            decltype(std::declval<T&>().begin()),
            decltype(std::declval<T&>().end()),
            decltype(begin(std::declval<T&>()) == std::declval<typename T::iterator>()),
            decltype(end(std::declval<T&>()) == std::declval<typename T::iterator>()),
            decltype(data(std::declval<T&>()) == std::declval<typename T::value_type*>()),
            decltype(std::declval<T&>().c_str()),
            typename T::value_type
        >> : std::true_type {};
}

