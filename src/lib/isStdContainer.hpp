#include <type_traits>

namespace PanCake
{
    template <typename T, typename = void>
    struct isStdContainer : std::false_type {};

    template <typename T>
    struct isStdContainer<T,
        std::void_t<
            decltype(std::declval<T&>().begin()),
            decltype(std::declval<T&>().end()),
            decltype(begin(std::declval<T&>()) == std::declval<typename T::iterator>()),
            decltype(end(std::declval<T&>()) == std::declval<typename T::iterator>()),
            decltype(data(std::declval<T&>()) == std::declval<typename T::value_type*>()),
            typename T::value_type
        >> : std::true_type {};
}

