#pragma once
#include <vector>
#include <pfs/griotte/color.hpp>

// TODO Apply cosmetic pen term (see QPen::isCosmetic())

namespace pfs {
namespace griotte {

enum class cap_style : int
{
      butt   = 0x00 ///!<A square line end that does not cover the end point of the line.
    , flat   = butt ///!<Synonym for butt.
    , square        ///!<A square line end that covers the end point and extends beyond it by half the line width.
    , round         ///!<A rounded line end.
};

template <typename UnitT>
class pen
{
public:
    using unit_type = UnitT;
    using dasharray_type = std::vector<unit_type>;

private:
    color          _color;
    int            _width;
    cap_style      _cap;
    dasharray_type _dasharray; // empty means solid line

public:
    /**
     * @brief Constructs an invisible stroke.
     */
    pen () noexcept
        : _color{0, 0, 0, 0}
        , _width{0}
        , _cap{cap_style::butt}
    {}

    /**
     * @brief Constructs a path with start point at @a start.
     */
    pen (color const & acolor, unit_type width = 1, cap_style acap = cap_style::butt) noexcept
        : _color{acolor}
        , _width{width}
        , _cap{acap}
    {}

    ~pen () = default;
    pen (pen const & rhs) = default;
    pen & operator = (pen const & rhs) = default;
    pen (pen && rhs) = default;
    pen & operator = (pen && rhs) = default;

    constexpr color get_color () const
    {
        return _color;
    }

    constexpr inline int get_width () const
    {
        return _width;
    }

    constexpr inline cap_style get_cap () const
    {
        return _cap;
    }

    constexpr inline dasharray_type const & get_dasharray () const
    {
        return _dasharray;
    }

    inline void add_dash (unit_type x)
    {
        _dasharray.push_back(x);
    }

    inline void clear_dasharray ()
    {
        _dasharray.clear();
    }
};

}} // namespace pfs::griotte
