//======================================================================================================================
/*
  RABERU - Fancy Parameters Library
  Copyright : RABERU Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <string_view>
#include <utility>

//======================================================================================================================
//! @defgroup utility   Helper types and function
//! @brief    Tools for interacting with Raberu components
//======================================================================================================================

//======================================================================================================================
//! @ingroup  utility
//! @{
//!   @defgroup udls   User-defined Literal operators
//!   @brief    UDL operators
//! @}
//======================================================================================================================
namespace rbr::_
{
  // Lightweight container of value in alternatives
  template<concepts::keyword T, typename V> struct type_or_
  {
    V value;

    template<concepts::option... Os>
    constexpr decltype(auto) operator()(Os&&... os) const { return fetch(*this, RBR_FWD(os)...); }
  };

  // Type -> String converter
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
    auto fn = [&]<std::size_t... Is>(std::index_sequence<Is...>)
    {
      return std::array<char const, sizeof...(Is) + 1>{value[Is]...};
    };

    return fn(std::make_index_sequence<size>{});
  }

  template<typename T>  inline constexpr auto type_array  = typer<T>();

  template<typename T, auto ID = type_array<T>>
  struct type_t
  {
    static constexpr auto name() { return std::string_view(ID.data(), ID.size());}
  };

  template<typename T>
  inline constexpr auto type  = type_t<T>{};
}


#if !defined(RBR_MAX_LITERAL_SIZE)
#define RBR_MAX_LITERAL_SIZE 32
#endif

namespace rbr
{
  //====================================================================================================================
  //! @namespace rbr::literals
  //! @brief Raberu literals namespace
  //====================================================================================================================
  namespace literals
  {
    //==================================================================================================================
    //! @ingroup utility
    //! @brief Compile-time static string
    //==================================================================================================================
    struct str
    {
      static constexpr std::size_t max_size = RBR_MAX_LITERAL_SIZE;

      char         data_[max_size+1];
      std::uint8_t size_;

      template<std::size_t N, std::size_t... Is>
      requires _::fits<N,max_size>
      constexpr str(const char (&s)[N], std::index_sequence<Is...>) : data_{s[Is]...}, size_(N)
      {}

      template <std::size_t N>
      requires _::fits<N,max_size>
      constexpr str(const char (&s)[N]) : str{s, std::make_index_sequence<N>{}}
      {}

      constexpr std::size_t       size()  const { return size_; }
      constexpr std::string_view  value() const { return std::string_view(&data_[0],size_); }

      friend std::ostream& operator<<(std::ostream& os, str const& s)
      {
        return os << '\'' << s.value() << '\'';
      }
    };
  }

  //====================================================================================================================
  //! @ingroup utility
  //! @brief Compile-time text based ID
  //! @tparam ID Compile-time string for the ID
  //====================================================================================================================
  template<literals::str ID> struct id_
  {
    /// Inserts an rbr::id_ in an output stream
    friend std::ostream& operator<<(std::ostream& os, id_ const&)
    {
      return os << ID;
    }
  };

  namespace literals
  {
    //==================================================================================================================
    //! @ingroup udls
    //! @brief Forms an ID constant literal
    //! @return An instance of rbr::id_ for the specified string
    //==================================================================================================================
    template<str ID> constexpr auto operator""_id() noexcept { return id_<ID>{}; }
  }
}
