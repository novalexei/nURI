/*
Copyright (c) 2016 Alexei Novakov
https://github.com/novalexei

Distributed under the Boost Software License, Version 1.0.
http://boost.org/LICENSE_1_0.txt
*/
#ifndef URI_STRUTIL_H
#define URI_STRUTIL_H

#include <string>
#include <string_view>

namespace nova
{
template<typename CharT, typename Traits>
class token_iterator
{
public:
    typedef std::basic_string_view<CharT, Traits> string_type;

    typedef string_type             value_type;
    typedef string_type             *pointer;
    typedef string_type             reference;
    typedef std::ptrdiff_t          difference_type;
    typedef std::input_iterator_tag iterator_category;

    token_iterator(const string_type &str, const string_type &delim, bool include_delim_in_token) noexcept :
            _string{str}, _delim{delim}, _include_delim_in_token{include_delim_in_token}
    {
        load_next();
    }

    token_iterator(const token_iterator& other) = default;
    token_iterator(token_iterator&& other) noexcept = default;

    token_iterator() noexcept : _string(""), _delim(""),
                                _start_pos(string_type::npos), _delim_index(string_type::npos) {}

    token_iterator& operator=(const token_iterator& other) = default;
    token_iterator& operator=(token_iterator&& other) noexcept = default;

    value_type operator*() const { return _string.substr(_start_pos, _delim_index - _start_pos); }

    /* We don't support -> as all dereferenced elements are temporary */
    pointer operator->() const noexcept = delete;

    inline token_iterator& operator++() noexcept
    {
        load_next();
        return *this;
    }

    inline const token_iterator operator++(int) noexcept
    {
        token_iterator tmp(*this);
        load_next();
        return tmp;
    }

    bool operator==(const token_iterator &other) const noexcept
    {
        if (_start_pos == string_type::npos) return other._start_pos == string_type::npos;
        return _string == other._string &&
               _delim == other._delim &&
               _start_pos == other._start_pos &&
               _delim_index == other._delim_index &&
               _include_delim_in_token == other._include_delim_in_token;
    }

    bool operator!=(const token_iterator &other) const noexcept { return !(other == *this); }

private:
    bool load_next() noexcept;

    string_type _string;
    string_type _delim;
    typename string_type::size_type _start_pos = 0;
    typename string_type::size_type _delim_index = 0;
    bool _include_delim_in_token = false;
};

template<typename CharT, typename Traits>
class basic_tokenizer
{
public:
    typedef std::basic_string_view<CharT, Traits> string_type;

    explicit basic_tokenizer(const string_type str,
                             const string_type delim = " \t\n\r\f",
                             bool include_delim_in_token = false) :
            _string{str}, _delim{delim}, _include_delim_in_token{include_delim_in_token} { }

    token_iterator<CharT, Traits> begin() const noexcept
    {
        return token_iterator<CharT, Traits>{_string, _delim, _include_delim_in_token};
    }

    token_iterator<CharT, Traits> end() const noexcept { return token_iterator<CharT, Traits>{}; }

private:
    string_type _string;
    string_type _delim;
    bool _include_delim_in_token;
};

template<typename CharT, typename Traits>
bool token_iterator<CharT, Traits>::load_next() noexcept
{
    _start_pos = _delim_index;
    if (_start_pos == string_type::npos) return false;
    if (_delim.size() == 1)
    {
        if (!_include_delim_in_token) _start_pos = _string.find_first_not_of(_delim[0], _start_pos);
        _delim_index = _string.find(_delim[0], _start_pos);
    }
    else
    {
        if (!_include_delim_in_token) _start_pos = _string.find_first_not_of(_delim, _start_pos);
        _delim_index = _string.find_first_of(_delim, _start_pos);
    }
    if (_include_delim_in_token && _delim_index != string_type::npos)
    {
        ++_delim_index;
        if (_delim_index >= _string.size()) _delim_index = string_type::npos;
    }
    return true;
}

template <typename CharT, typename Traits>
basic_tokenizer<CharT, Traits> make_tokenizer(std::basic_string_view<CharT, Traits> str)
{
    return basic_tokenizer<CharT, Traits>(str);
}

using tokenizer    = basic_tokenizer<typename std::string_view::value_type, typename std::string_view::traits_type>;
using u16tokenizer = basic_tokenizer<typename std::u16string_view::value_type, typename std::u16string_view::traits_type>;
using u32tokenizer = basic_tokenizer<typename std::u32string_view::value_type, typename std::u32string_view::traits_type>;

namespace
{
    void __append(std::string res, std::string_view str) { res += str; }

    template <typename... Args>
    void __append(std::string res, std::string_view str, Args &&... args)
    {
        res += str;
        __append(res, std::forward<Args>(args)...);
    }

    std::string_view::size_type __cat_size(std::string_view str) { return str.size(); }


    template <typename... Args>
    std::string_view::size_type __cat_size(std::string_view str, Args &&... args)
    {
        return str.size() + __cat_size(std::forward<Args>(args)...);
    }
}

template <typename... Args>
std::string cat(std::string_view str, Args &&... args)
{
    std::string res;
    res.reserve(__cat_size(str, std::forward<Args>(args)...));
    __append(res, str, std::forward<Args>(args)...);
    return res;
}

inline bool equal_ic(const std::string_view str1, const std::string_view str2)
{
    return str1.length() == str2.length() &&
           std::equal(str1.begin(), str1.end(), str2.begin(),
                      [](auto ch1, auto ch2) { return std::tolower(ch1) == std::tolower(ch2); });
}

}

#endif //URI_STRUTIL_H
