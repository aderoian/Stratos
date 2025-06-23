/*
 *
 *               _____  _                 _
 *              /  ___|| |               | |
 *              \ `--. | |_  _ __   __ _ | |_   ___   ___
 *               `--. \| __|| '__| / _` || __| / _ \ / __|
 *              /\__/ /| |_ | |   | (_| || |_ | (_) |\__ \
 *              \____/  \__||_|    \__,_| \__| \___/ |___/
 *
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Copyright (C) 2025 Armen Deroian
 *
 */

#ifndef PREDICATE_H
#define PREDICATE_H

#include <functional>

namespace stratos {
template <typename T> class Predicate {
  public:
    Predicate() = default;
    Predicate(bool (T::*funcPtr)() const) : func([funcPtr](const T& obj) { return (obj.*funcPtr)(); }) {}
    template <typename... BoundArgs, typename... MemberArgs>
    Predicate(bool (T::*funcPtr)(MemberArgs...) const, BoundArgs&&...boundArgs) : func([funcPtr, ...capturedArgs = std::forward<BoundArgs>(boundArgs)](const T& obj) { return (obj.*funcPtr)(capturedArgs...); }) {}
    explicit Predicate(bool value) : func([value](const T& obj) { return value; }) {}
    template <typename Callable, typename = std::enable_if_t<!std::is_same_v<std::decay_t<Callable>, Predicate>>>
    explicit Predicate(Callable&& callable) : func(std::forward<Callable>(callable)) {}

    bool test(const T& object) const;

    Predicate& operator=(const bool (T::*funcPtr)() const);
    Predicate& operator=(bool value);

    bool operator()(const T& object) const;
    Predicate operator!() const;
    Predicate operator&&(const Predicate& other) const;
    Predicate operator||(const Predicate& other) const;
    Predicate operator&&(bool (T::*funcPtr)() const) const;
    Predicate operator||(bool (T::*funcPtr)() const) const;

    Predicate operator&&(bool other) const;
    Predicate operator||(bool other) const;

    ~Predicate() = default;

  private:
    std::function<bool(const T&)> func;
};

template <typename T> bool Predicate<T>::test(const T& object) const {
    return func(object);
}
template <typename T> Predicate<T>& Predicate<T>::operator=(const bool (T::*funcPtr)() const) {
    func = [funcPtr](const T& obj) { return (obj.*funcPtr)(); };
    return *this;
}
template <typename T> Predicate<T>& Predicate<T>::operator=(bool value) {
    func = [value](const T& obj) { return value; };
    return *this;
}
template <typename T> bool Predicate<T>::operator()(const T& object) const {
    return test(object);
}
template <typename T> Predicate<T> Predicate<T>::operator!() const {
    return Predicate([f = [this](const T& obj) { return this->test(obj); }](const T& obj) { return !f(obj); });
}
template <typename T> Predicate<T> Predicate<T>::operator&&(const Predicate& other) const {
    return Predicate([f1 = [this](const T& obj) {
        return this->test(obj);
    }, f2 = [&other](const T& obj) {
        return other.test(obj);
    }](const T& obj) { return f1(obj) && f2(obj); });
}
template <typename T> Predicate<T> Predicate<T>::operator||(const Predicate& other) const {
    return Predicate([f1 = [this](const T& obj) { return this->test(obj); }, f2 = [&other](const T& obj) { return other.test(obj); }](const T& obj) { return f1(obj) || f2(obj); });
}
template <typename T> Predicate<T> Predicate<T>::operator&&(bool (T::*funcPtr)() const) const {
    return Predicate([f = [this](const T& obj) { return this->test(obj); }, funcPtr](const T& obj) { return f(obj) && (obj.*funcPtr)(); });
}
template <typename T> Predicate<T> Predicate<T>::operator||(bool (T::*funcPtr)() const) const {
    return Predicate([f = [this](const T& obj) { return this->test(obj); }, funcPtr](const T& obj) { return f(obj) || (obj.*funcPtr)(); });
}
template <typename T> Predicate<T> Predicate<T>::operator&&(bool other) const {
    return Predicate([f = [this](const T& obj) { return this->test(obj); }, other](const T& obj) { return f(obj) && other; });
}
template <typename T> Predicate<T> Predicate<T>::operator||(bool other) const {
    return Predicate([f = [this](const T& obj) { return this->test(obj); }, other](const T& obj) { return f(obj) || other; });
}

template <typename T> Predicate<T> operator&&(bool (T::*lhs)() const, const Predicate<T>& rhs) {
    return Predicate<T>([lhs, f = [&rhs](const T& obj) { return rhs.test(obj); }](const T& obj) { return (obj.*lhs)() && f(obj); });
}
template <typename T> Predicate<T> operator||(bool (T::*lhs)() const, const Predicate<T>& rhs) {
    return Predicate<T>([lhs, f = [&rhs](const T& obj) { return rhs.test(obj); }](const T& obj) { return (obj.*lhs)() || f(obj); });
}
template <typename T> Predicate<T> operator&&(bool lhs, const Predicate<T>& rhs) {
    return Predicate<T>([lhs, f = [&rhs](const T& obj) { return rhs.test(obj); }](const T& obj) { return lhs && f(obj); });
}
template <typename T> Predicate<T> operator||(bool lhs, const Predicate<T>& rhs) {
    return Predicate<T>([lhs, f = [&rhs](const T& obj) { return rhs.test(obj); }](const T& obj) { return lhs || f(obj); });
}

template <typename T> Predicate<T> makePredicate(bool (T::*funcPtr)() const) {
    return Predicate<T>(funcPtr);
}
template <typename T, typename... BoundArgs>
Predicate<T> makePredicate(bool (T::*funcPtr)(BoundArgs...) const, BoundArgs&&... boundArgs) {
    return Predicate<T>(funcPtr, std::forward<BoundArgs>(boundArgs)...);
}

} // namespace stratos

#endif //PREDICATE_H
