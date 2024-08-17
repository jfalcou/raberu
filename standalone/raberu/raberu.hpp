//======================================================================================================================
/*
  RABERU - Fancy Parameters Library
  Copyright : RABERU Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#ifndef RABERU_HPP_INCLUDED
#define RABERU_HPP_INCLUDED
#include <type_traits>
namespace rbr
{
  namespace result {}
}
#define RBR_FWD(...) static_cast<decltype(__VA_ARGS__) &&>(__VA_ARGS__)
namespace rbr::stdfix
{
  template<typename T, typename U >
  concept is_same_impl = std::is_same_v<T, U>;
  template<typename T, typename U >
  concept same_as = is_same_impl<T, U> && is_same_impl<U, T>;
}
namespace rbr::_
{
  template<typename... Ks> struct keys {};
  template<typename K, typename Ks> struct contains;
  template<typename... Ks, typename K>
  struct  contains<K, keys<Ks...>> : std::bool_constant<(stdfix::same_as<K,Ks> || ...)>
  {};
  template<typename K, typename Ks, bool>  struct append_if_impl;
  template<typename... Ks, typename K> struct append_if_impl<K,keys<Ks...>,true>
  {
    using type = keys<Ks...>;
  };
  template<typename... Ks, typename K> struct append_if_impl<K,keys<Ks...>,false>
  {
    using type = keys<Ks...,K>;
  };
  template<typename K, typename Ks> struct append_if;
  template<typename K, typename Ks>
  struct append_if : append_if_impl<K,Ks, contains<K, Ks>::value>
  {};
  template<typename K1, typename K2> struct uniques;
  template<typename K1s, typename K2, typename... K2s>
  struct  uniques<K1s, keys<K2,K2s...>>
        : uniques< typename append_if<K2,K1s>::type, keys<K2s...> >
  {};
  template<typename K1s> struct  uniques<K1s, keys<>> { using type = K1s; };
  template<typename K1, typename K2> struct contain_all;
  template<typename K1s, typename... K2s>
  struct  contain_all<K1s, keys<K2s...>> : std::bool_constant<(contains<K2s,K1s>::value && ...)>
  {};
  template<typename K1s>  struct  contain_all<K1s   , keys<>>  : std::false_type {};
  template<typename K2s>  struct  contain_all<keys<>, K2s   >  : std::false_type {};
  template<>              struct  contain_all<keys<>,keys<>>   : std::true_type  {};
  template<typename K1, typename K2>
  struct is_equivalent : std::bool_constant<contain_all<K2,K1>::value && contain_all<K2,K1>::value>
  {};
}
namespace rbr
{
  template<typename... T> struct types {};
}
namespace rbr::concepts
{
  template<typename OS>
  concept stream = requires(OS& os, const char* s) { {os << s}; };
  template<typename K>
  concept keyword = requires(K const& k) { typename K::keyword_identifier; };
  template<typename K, typename T>
  concept keyword_with_default = keyword<K> && requires(K const& k, T const d) { { k.default_value(d) }; };
  template<typename O>
  concept option = requires(O const& o)
  {
    typename O::keyword_type;
    typename O::stored_value_type;
    { o.fetch(typename O::keyword_type{}) };
  };
  template<typename S> concept settings = requires( S const& s ) { typename S::rbr_settings; };
  template<typename Option, auto Keyword>
  concept exactly = stdfix::same_as<typename Option::keyword_type, std::remove_cvref_t<decltype(Keyword)>>;
}
#include <array>
#include <cstddef>
#include <cstdint>
#include <string_view>
#include <utility>
namespace rbr::_
{
 template <typename T> constexpr auto typer() noexcept
  {
#if defined(__clang__)
    constexpr auto pfx = std::string_view("auto rbr::_::typer() [T = ").size();
    constexpr auto sfx = std::string_view("]").size();
    constexpr auto raw = std::string_view(__PRETTY_FUNCTION__);
#elif defined(__GNUC__)
    constexpr auto pfx = std::string_view("constexpr auto rbr::_::typer() [with " "T = ").size();
    constexpr auto sfx = std::string_view("]").size();
    constexpr auto raw = std::string_view(__PRETTY_FUNCTION__);
#elif defined(_MSC_VER)
    constexpr auto pfx = std::string_view("auto __cdecl rbr::_::typer<").size();
    constexpr auto sfx = std::string_view(">(void)").size();
    constexpr auto raw = std::string_view(__FUNCSIG__);
#endif
    auto value = raw;
    value.remove_prefix(pfx);
    value.remove_suffix(sfx);
    constexpr auto size = raw.size() - (pfx + sfx);
    return [&]<std::size_t... Is>(std::index_sequence<Is...>)
    {
      return std::array<char const, sizeof...(Is) + 1>{value[Is]..., 0};
    }(std::make_index_sequence<size>{});
  }
  template<typename T, auto ID = typer<T>()>
  struct type_t
  {
    static constexpr auto name() noexcept { return std::string_view(ID.data(), ID.size());}
    template<concepts::stream Stream>
    friend auto& operator<<(Stream& os, type_t const&) { return os << name(); }
  };
  template<typename T> inline constexpr type_t<T> type  = {};
  template<std::size_t N, std::size_t M> concept fits = (N <= M);
}
#if !defined(RBR_MAX_LITERAL_SIZE)
#define RBR_MAX_LITERAL_SIZE 32
#endif
namespace rbr
{
  struct str
  {
    static constexpr std::size_t max_size = RBR_MAX_LITERAL_SIZE;
    char         data_[max_size+1];
    std::uint8_t size_;
    template<std::size_t N, std::size_t... Is>
    constexpr str(const char (&s)[N], std::index_sequence<Is...>) : data_{s[Is]...}, size_(N)
    {}
    template <std::size_t N>
    requires(N <= max_size)
    constexpr str(const char (&s)[N]) : str{s, std::make_index_sequence<N>{}}
    {}
    constexpr std::size_t       size()  const { return size_; }
    constexpr std::string_view  value() const { return std::string_view(&data_[0],size_); }
    template<concepts::stream Stream>
    friend auto& operator<<(Stream& os, str const& s)
    {
      return os << '\'' << s.value() << '\'';
    }
  };
  template<str ID> struct id_
  {
    template<concepts::stream Stream>
    friend auto& operator<<(Stream& os, id_ const&) { return os << ID; }
  };
  inline namespace literals
  {
    template<str ID> constexpr auto operator""_id() noexcept { return id_<ID>{}; }
  }
}
namespace rbr
{
  template<typename Type> struct only_t
  {
    template<typename U>
    static constexpr bool value = stdfix::same_as<Type,U>;
  };
  template<template<class> typename Traits> struct traits_check
  {
    template<typename U>
    static constexpr bool value = Traits<U>::value;
  };
  struct unknown_key
  {
    template<concepts::stream Stream>
    friend auto& operator<<(Stream& os, unknown_key const&)
    {
      return os << "rbr::unknown_key";
    }
  };
  template<typename Type>
  inline constexpr only_t<Type> only = {};
  template<template<class> typename Traits>
  inline constexpr traits_check<Traits> if_ = {};
  template<typename Keyword, typename Value>
  struct option
  {
    using keyword_type      = typename Keyword::keyword_identifier;
    using stored_value_type = Value;
    constexpr decltype(auto)  fetch(keyword_type const&) &      noexcept { return payload;            }
    constexpr decltype(auto)  fetch(keyword_type const&) &&     noexcept { return std::move(payload); }
    constexpr decltype(auto)  fetch(keyword_type const&) const& noexcept { return payload;            }
    template<concepts::stream Stream>
    friend auto& operator<<(Stream& os, option const& o)
    {
      if constexpr( requires{ display(os, Keyword{}, o.payload); } )
        return display(os, Keyword{}, o.payload);
      else
        return os << Keyword{} << " : " << o.payload << " (" << _::type<std::unwrap_ref_decay_t<Value>> << ")";
    }
    Value payload;
  };
  template<typename ID, typename Check = void> struct keyword;
  template<typename ID, typename Default>
  struct keyword_or
  {
    using keyword_identifier = typename ID::keyword_identifier;
    static constexpr bool is_flag = ID::is_flag;
    template<typename Value>
    constexpr option<keyword_identifier,Value> operator=(Value&& v) const { return {RBR_FWD(v)}; }
    template<typename S>
    constexpr decltype(auto) default_value(S const& s) const noexcept
    {
      if constexpr(std::invocable<Default, S>)  return default_(s);
      else                                      return default_;
    }
    constexpr bool operator==(keyword_or const&) const = default;
    Default default_;
  };
  template<typename ID>
  struct keyword<ID,void>
  {
    using keyword_identifier = keyword<ID>;
    static constexpr bool is_flag = false;
    constexpr keyword() noexcept {}
    constexpr keyword(ID const&) noexcept {}
    template<typename Value>
    constexpr option<keyword_identifier,Value> operator=(Value&& v) const { return {RBR_FWD(v)}; }
    template<typename Default>
    constexpr auto operator|(Default v) const noexcept { return keyword_or<keyword_identifier,Default>{std::move(v)}; }
    constexpr bool operator==(keyword const&) const = default;
    template<concepts::stream Stream>
    friend auto& operator<<(Stream& os, keyword const&)
    {
      if constexpr(requires{ os << ID{}; }) return os << ID{};
      else                                  return os << _::type<ID>;
    }
  };
  template<typename ID, typename Checker>
  struct keyword
  {
    using keyword_identifier = keyword<ID>;
    static constexpr bool is_flag = false;
    constexpr keyword() noexcept {}
    constexpr keyword(ID const&, Checker const&) noexcept {}
    constexpr bool operator==(keyword const&) const = default;
    template<typename Value>
    requires( Checker::template value<Value> )
    constexpr option<keyword_identifier,Value> operator=(Value&& v) const { return {RBR_FWD(v)}; }
    template<typename Value>
    requires( !Checker::template value<Value> )
    constexpr option<keyword_identifier,Value> operator=(Value&& v) const =delete;
    template<typename Default>
    constexpr auto operator|(Default v) const  { return keyword_or<keyword_identifier,Default>{std::move(v)}; }
    template<concepts::stream Stream>
    friend auto& operator<<(Stream& os, keyword const&)
    {
      if constexpr(requires{ os << ID{}; }) return os << ID{};
      else                                  return os << _::type<ID>;
    }
  };
  template<typename ID>
  keyword(ID const&) -> keyword<ID,void>;
  template<typename ID, typename Checker>
  keyword(ID const&, Checker const&) -> keyword<ID,Checker>;
  template<typename ID>
  struct flag
  {
    using keyword_identifier      = flag<ID>;
    using keyword_type            = flag<ID>;
    using stored_value_type       = bool;
    static constexpr bool is_flag = true;
    constexpr flag() noexcept {}
    constexpr flag(ID const&) noexcept {}
    constexpr bool  fetch(keyword_identifier const&)  const noexcept { return true; }
    template<typename S>
    constexpr bool default_value(S const&) const noexcept { return false; }
    constexpr flag operator=(auto const&) const { return {}; }
    template<typename Default>
    constexpr auto operator|(Default v) const  { return keyword_or<keyword_identifier,Default>{std::move(v)}; }
    template<concepts::stream Stream>
    friend auto& operator<<(Stream& os, flag const&)
    {
      if constexpr(requires{ os << ID{}; }) return os << ID{} << " : set";
      else                                  return os << _::type<ID> << " : set";
    }
  };
  inline namespace literals
  {
    template<str ID>
    constexpr auto operator""_kw() noexcept { return keyword<id_<ID>>{}; }
    template<str ID>
    constexpr auto operator""_fl() noexcept { return flag<id_<ID>>{}; }
  }
}
namespace rbr
{
  template<concepts::option... Options>
  struct settings : private Options...
  {
    using rbr_settings = void;
    static constexpr std::ptrdiff_t 	size () noexcept { return sizeof...(Options); }
    constexpr explicit(sizeof...(Options) == 1)
    settings(Options... opts) : Options(std::move(opts))... {}
    template<concepts::keyword K>
    constexpr decltype(auto) operator[](K const&) const { return unwrap(typename K::keyword_identifier{}); }
    template<concepts::keyword_with_default<settings> K>
    constexpr decltype(auto) operator[](K const& key) const
    {
      decltype(auto) that = unwrap(typename K::keyword_identifier{});
      if constexpr(stdfix::same_as<std::remove_cvref_t<decltype(that)>, unknown_key>)
        return key.default_value(*this);
      else
        return that;
    }
    template<concepts::keyword Key>
    static constexpr auto contains([[maybe_unused]] Key const& kw) noexcept
    {
      if constexpr( requires{ std::declval<settings>().fetch(typename Key::keyword_identifier{}); } )
      {
        using found = decltype(std::declval<settings>().fetch(typename Key::keyword_identifier{}));
        return !stdfix::same_as<found, unknown_key>;
      }
      else
      {
        return false;
      }
    }
    template<concepts::keyword... Keys>
    static constexpr auto contains_any(Keys... ks) noexcept { return (contains(ks) || ...); }
    template<concepts::keyword... Keys>
    static constexpr auto contains_only([[maybe_unused]] Keys const&... ks) noexcept
    {
      using current_keys    = _::keys<typename Options::keyword_type::keyword_identifier...>;
      using acceptable_keys = _::keys<typename Keys::keyword_identifier...>;
      using unique_set      = typename _::uniques<current_keys,acceptable_keys>::type;
      return  _::is_equivalent<unique_set, acceptable_keys>::value;
    }
    template<concepts::keyword... Keys>
    static constexpr auto contains_none(Keys... ks) noexcept { return !contains_any(ks...); }
    using Options::fetch...;
    template<concepts::stream Stream>
    friend auto& operator<<(Stream& os, settings const& s)
    {
      os << "{\n";
      ((os << "  " << static_cast<Options const&>(s) << "\n"),...);
      return os << "}";
    }
    private:
    template<typename K>
    constexpr decltype(auto) unwrap(K const& key) const
    {
      auto v = [&]()  { if constexpr(requires{ fetch(key); }) return fetch(key);
                        else                                  return unknown_key{};
                      }();
      return std::unwrap_reference_t<decltype(v)>(v);
    };
  };
  template<concepts::option... Opts>
  settings(Opts const&... opts) -> settings<Opts...>;
}
namespace rbr::_
{
  template<typename K, concepts::keyword... Kept>
  struct filter
  {
    using type = _::keys<Kept...>;
    template<typename T> constexpr auto operator%(keys<T> const&) const
    {
      using kw_t = typename T::keyword_type;
      if constexpr(!stdfix::same_as<K, typename kw_t::keyword_identifier>)  return filter<K, Kept..., kw_t>{};
      else                                                                  return *this;
    }
  };
  template< typename K, typename S> struct select_keys;
  template< typename K, concepts::option... Os>
  struct  select_keys<K,rbr::settings<Os...>>
        : decltype((filter<typename K::keyword_identifier>{}  % ... %  _::keys<Os>{}))
  {
  };
}
namespace rbr
{
  constexpr decltype(auto) fetch(concepts::keyword auto const& k, concepts::option auto const&... os)
  {
    auto const opts = settings(os...);
    return opts[k];
  }
  template<concepts::keyword K, typename V, concepts::option... Os>
  constexpr decltype(auto) fetch(keyword_or<K, V> const& k, Os const&... os)
  {
    auto const opts = settings(os...);
    return opts[k];
  }
  constexpr decltype(auto) fetch(concepts::keyword auto const& k, concepts::settings auto const& opts)
  {
    return opts[k];
  }
  template<typename... K1s, typename... K2s>
  constexpr auto merge(settings<K1s...> const& opts, settings<K2s...> const& defs) noexcept
  {
    auto selector = []<typename K, typename Opts>(K const&, Opts const& o, auto const& d)
                    {
                      constexpr K key;
                      if constexpr( Opts::contains(key) ) return (key = o.fetch(key));
                      else                                return (key = d.fetch(key));
                    };
    auto select = [&]<typename... Ks>(_::keys<Ks...> const&, auto const& os, auto const& ds)
    {
      return settings(selector(Ks{},os,ds)...);
    };
    return select(typename _::uniques < _::keys<typename K1s::keyword_type...>
                                      , _::keys<typename K2s::keyword_type...>
                                      >::type{},opts,defs);
  }
  template<concepts::keyword K, concepts::option... O>
  [[nodiscard]] constexpr auto drop([[maybe_unused]] K const& k, settings<O...> const& s)
  {
    using selected_keys_t = typename _::select_keys<K,settings<O...>>::type;
    return [&]<typename ... Ks>( _::keys<Ks...> )
    {
      return rbr::settings{ (Ks{} = s.fetch(Ks{}) )...};
    }(selected_keys_t{});
  }
  namespace result
  {
    template< typename Settings, template<typename...> class List = types> struct keywords;
    template< typename Settings, template<typename...> class List = types> struct values;
    template<typename... Opts, template<typename...> class List>
    struct keywords<settings<Opts...>, List>
    {
      using type = List<typename Opts::keyword_type...>;
    };
    template<typename... Opts, template<typename...> class List>
    struct values<settings<Opts...>, List>
    {
      using type = List<std::unwrap_reference_t<typename Opts::stored_value_type>...>;
    };
    template<typename Settings, template<typename...> class List = types>
    using keywords_t = typename keywords<Settings,List>::type;
    template<typename Settings, template<typename...> class List = types>
    using values_t = typename values<Settings,List>::type;
  }
  template<template<typename...> class List, typename... Opts>
  constexpr auto keywords([[maybe_unused]]rbr::settings<Opts...> const& s)
  {
    return result::keywords_t<rbr::settings<Opts...>,List>{typename Opts::keyword_type{}...};
  }
  template<template<typename...> class List, typename... Opts>
  constexpr auto values(rbr::settings<Opts...>& s)
  {
    return result::values_t<rbr::settings<Opts...>,List>{ s[typename Opts::keyword_type{}]... };
  }
  template<concepts::settings S1, concepts::settings S2>
  inline constexpr bool is_equivalent_v =   _::is_equivalent< result::keywords_t<S1,_::keys>
                                                            , result::keywords_t<S2,_::keys>
                                                            >::value
                                        &&  _::is_equivalent< result::keywords_t<S2,_::keys>
                                                            , result::keywords_t<S1,_::keys>
                                                            >::value;
  template<concepts::settings S1, concepts::settings S2>
  struct  is_equivalent : std::bool_constant<is_equivalent_v<S1,S2>>
  {};
  namespace result
  {
    template<auto Keyword, typename... Sources> struct fetch;
    template<auto Keyword, concepts::option... Os>
    struct fetch<Keyword, Os...>
    {
      using type = decltype( rbr::fetch(Keyword, std::declval<Os>()...) );
    };
    template<auto Keyword, concepts::settings Settings>
    struct fetch<Keyword, Settings>
    {
      using type = decltype( rbr::fetch(Keyword, std::declval<Settings>()) );
    };
    template<auto Keyword, typename... Sources>
    using fetch_t = typename fetch<Keyword,Sources...>::type;
    template<concepts::keyword K, concepts::option... O>
    struct drop
    {
      using type = decltype( rbr::drop(std::declval<K>(),std::declval<O>()...) );
    };
    template<concepts::keyword K, concepts::option... O>
    using drop_t = typename drop<K,O...>::type;
    template<concepts::settings S1, concepts::settings S2>
    struct merge
    {
      using type = decltype( rbr::merge(std::declval<S1>(),std::declval<S2>()) );
    };
    template<concepts::settings S1, concepts::settings S2>
    using merge_t = typename merge<S1,S2>::type;
  }
}
#undef RBR_FWD
#endif
