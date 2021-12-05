# Concepts

## `keyword`

**Synopsis:**
```c++
namespace rbr::concepts
{
  template<typename K> concept keyword = requires( K k )
  {
    typename K::tag_type;
    { K::template accept<int>() } -> std::same_as<bool>;
  };
}
```

A type `T` modeling `rbr::concepts::keyword` can be used to build sequence of options.

## `option`

**Synopsis:**
```c++
namespace rbr::concepts
{
  template<typename O> concept option = requires( O const& o )
  {
    { o(typename std::remove_cvref_t<O>::keyword_type{}) }
    -> std::same_as<typename std::remove_cvref_t<O>::stored_value_type>;
  };
}
```

A type `T` modeling `rbr::concepts::option` can be used to build an instance of `rbr::settings`.

## `type_checker`

**Synopsis:**
```c++
namespace rbr::concepts
{
  template<typename C> concept type_checker = requires( C const& )
  {
    typename C::template apply<int>::type;
  };
}
```