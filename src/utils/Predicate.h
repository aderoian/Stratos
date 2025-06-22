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
    explicit Predicate(bool value) : func([value](const T& obj) { return value; }) {}
    explicit Predicate(std::function<bool>&& func) : func(std::move(func)) {}

    bool test(T& object) const;

    Predicate& operator=(const bool (T::*funcPtr)() const);
    Predicate& operator=(bool value);

    bool operator()(T& object) const;
    Predicate operator!() const;
    Predicate operator&&(const Predicate& other) const;
    Predicate operator||(const Predicate& other) const;
    Predicate operator&&(bool (T::*funcPtr)() const) const;
    Predicate operator||(bool (T::*funcPtr)() const) const;

    Predicate operator&&(bool other) const;
    Predicate operator||(bool other) const;

    virtual ~Predicate() = default;

  private:
    std::function<bool(const T&)> func;
};

template <typename T> bool Predicate<T>::test(T& object) const {
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
template <typename T> bool Predicate<T>::operator()(T& object) const {
    return test(object);
}
template <typename T> Predicate<T> Predicate<T>::operator!() const {
    return Predicate([f = func](const T& obj) { return !f(obj); });
}
template <typename T> Predicate<T> Predicate<T>::operator&&(const Predicate& other) const {
    return Predicate([f1 = func, f2 = other.func](const T& obj) { return f1(obj) && f2(obj); });
}
template <typename T> Predicate<T> Predicate<T>::operator||(const Predicate& other) const {
    return Predicate([f1 = func, f2 = other.func](const T& obj) { return f1(obj) || f2(obj); });
}
template <typename T> Predicate<T> Predicate<T>::operator&&(bool (T::*funcPtr)() const) const {
    return Predicate([f = func, funcPtr](const T& obj) { return f(obj) && (obj.*funcPtr)(); });
}
template <typename T> Predicate<T> Predicate<T>::operator||(bool (T::*funcPtr)() const) const {
    return Predicate([f = func, funcPtr](const T& obj) { return f(obj) || (obj.*funcPtr)(); });
}
template <typename T> Predicate<T> Predicate<T>::operator&&(bool other) const {
    return Predicate([f = func, other](const T& obj) { return f(obj) && other; });
}
template <typename T> Predicate<T> Predicate<T>::operator||(bool other) const {
    return Predicate([f = func, other](const T& obj) { return f(obj) || other; });
}

template <typename T> Predicate<T> operator&&(bool (T::*lhs)() const, const Predicate<T>& rhs) {
    return Predicate<T>([lhs, f = rhs.func](const T& obj) { return (obj.*lhs)() && f(obj); });
}
template <typename T> Predicate<T> operator||(bool (T::*lhs)() const, const Predicate<T>& rhs) {
    return Predicate<T>([lhs, f = rhs.func](const T& obj) { return (obj.*lhs)() || f(obj); });
}
template <typename T> Predicate<T> operator&&(bool lhs, const Predicate<T>& rhs) {
    return Predicate<T>([lhs, f = rhs.func](const T& obj) { return lhs && f(obj); });
}
template <typename T> Predicate<T> operator||(bool lhs, const Predicate<T>& rhs) {
    return Predicate<T>([lhs, f = rhs.func](const T& obj) { return lhs || f(obj); });
}

} // namespace stratos

#endif //PREDICATE_H
