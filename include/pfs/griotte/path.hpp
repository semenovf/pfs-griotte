#pragma once
#include <cassert>
#include <vector>
#include <pfs/griotte/point.hpp>
#include <pfs/griotte/rect.hpp>


// FIXME Implement path using relative coordinates internally.

//
// [8.3.8 The grammar for path data](https://www.w3.org/TR/SVGTiny12/paths.html#PathElement)
//
//     path-data ::=
//         wsp* moveto-drawto-command-groups? wsp*
//     moveto-drawto-command-groups ::=
//         moveto-drawto-command-group
//         | moveto-drawto-command-group wsp* moveto-drawto-command-groups
//     moveto-drawto-command-group ::=
//         moveto wsp* drawto-commands?
//     drawto-commands ::=
//         drawto-command
//         | drawto-command wsp* drawto-commands
//     drawto-command ::=
//         closepath
//         | lineto
//         | horizontal-lineto
//         | vertical-lineto
//         | curveto
//         | smooth-curveto
//         | quadratic-bezier-curveto
//         | smooth-quadratic-bezier-curveto
//     moveto ::=
//         ( "M" | "m" ) wsp* moveto-argument-sequence
//     moveto-argument-sequence ::=
//         coordinate-pair
//         | coordinate-pair comma-wsp? lineto-argument-sequence
//     closepath ::=
//         ("Z" | "z")
//     lineto ::=
//         ( "L" | "l" ) wsp* lineto-argument-sequence
//     lineto-argument-sequence ::=
//         coordinate-pair
//         | coordinate-pair comma-wsp? lineto-argument-sequence
//     horizontal-lineto ::=
//         ( "H" | "h" ) wsp* horizontal-lineto-argument-sequence
//     horizontal-lineto-argument-sequence ::=
//         coordinate
//         | coordinate comma-wsp? horizontal-lineto-argument-sequence
//     vertical-lineto ::=
//         ( "V" | "v" ) wsp* vertical-lineto-argument-sequence
//     vertical-lineto-argument-sequence ::=
//         coordinate
//         | coordinate comma-wsp? vertical-lineto-argument-sequence
//     curveto ::=
//         ( "C" | "c" ) wsp* curveto-argument-sequence
//     curveto-argument-sequence ::=
//         curveto-argument
//         | curveto-argument comma-wsp? curveto-argument-sequence
//     curveto-argument ::=
//         coordinate-pair comma-wsp? coordinate-pair comma-wsp? coordinate-pair
//     smooth-curveto ::=
//         ( "S" | "s" ) wsp* smooth-curveto-argument-sequence
//     smooth-curveto-argument-sequence ::=
//         smooth-curveto-argument
//         | smooth-curveto-argument comma-wsp? smooth-curveto-argument-sequence
//     smooth-curveto-argument ::=
//         coordinate-pair comma-wsp? coordinate-pair
//     quadratic-bezier-curveto ::=
//         ( "Q" | "q" ) wsp* quadratic-bezier-curveto-argument-sequence
//     quadratic-bezier-curveto-argument-sequence ::=
//         quadratic-bezier-curveto-argument
//         | quadratic-bezier-curveto-argument comma-wsp?
//             quadratic-bezier-curveto-argument-sequence
//     quadratic-bezier-curveto-argument ::=
//         coordinate-pair comma-wsp? coordinate-pair
//     smooth-quadratic-bezier-curveto ::=
//         ( "T" | "t" ) wsp* smooth-quadratic-bezier-curveto-argument-sequence
//     smooth-quadratic-bezier-curveto-argument-sequence ::=
//         coordinate-pair
//         | coordinate-pair comma-wsp? smooth-quadratic-bezier-curveto-argument-sequence
//     coordinate-pair ::=
//         coordinate comma-wsp? coordinate
//     coordinate ::=
//         number
//     nonnegative-number ::=
//         integer-constant
//         | floating-point-constant
//     number ::=
//         sign? integer-constant
//         | sign? floating-point-constant
//     flag ::=
//         "0" | "1"
//     comma-wsp ::=
//         (wsp+ comma? wsp*) | (comma wsp*)
//     comma ::=
//         ","
//     integer-constant ::=
//         digit-sequence
//     floating-point-constant ::=
//         fractional-constant exponent?
//         | digit-sequence exponent
//     fractional-constant ::=
//         digit-sequence? "." digit-sequence
//         | digit-sequence "."
//     exponent ::=
//         ( "e" | "E" ) sign? digit-sequence
//     sign ::=
//         "+" | "-"
//     digit-sequence ::=
//         digit
//         | digit digit-sequence
//     digit ::=
//         "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"
//     wsp ::=
//         (#x20 | #x9 | #xD | #xA)


namespace pfs {
namespace griotte {

enum class path_entry_enum : int
{
      move_to      ///!<Move to
    , line_to      ///!<Line to
    , curve_to     ///!<Curve to
    , close_path   ///!<Close path
};

template <typename UnitT>
class path
{
public:
    using unit_type  = UnitT;
    using point_type = point<unit_type>;
    using rect_type  = rect<unit_type>;

    struct entry
    {
        path_entry_enum type;
        point_type p;

        entry (path_entry_enum atype
                , point_type const & apoint)
            : type{atype}
            , p{apoint}
        {}
    };

    using entry_collection = std::vector<entry>;
    using iterator         = typename entry_collection::iterator;
    using const_iterator   = typename entry_collection::const_iterator;
    using reference        = typename entry_collection::reference;
    using const_reference  = typename entry_collection::const_reference;

private:
    entry_collection _v; // collection of the path antries

public:
    /**
     * @brief Constructs a path with start point at (0, 0).
     */
    path () noexcept
    {
        _v.emplace_back(path_entry_enum::move_to, point_type{0, 0});
    }

    /**
     * @brief Constructs a path with start point at @a start.
     * @note Considered that start point is in absolute coordinates.
     */
    path (point_type const & start) noexcept
    {
        _v.emplace_back(path_entry_enum::move_to, start);
    }

    ~path () = default;
    path (path const & rhs) = default;
    path & operator = (path const & rhs) = default;
    path (path && rhs) = default;
    path & operator = (path && rhs) = default;

    bool empty () const
    {
        return _v.empty();
    }

    iterator begin ()
    {
        return _v.begin();
    }

    iterator end ()
    {
        return _v.end();
    }

    const_iterator begin () const
    {
        return _v.begin();
    }

    const_iterator end () const
    {
        return _v.end();
    }

    const_iterator cbegin () const
    {
        return _v.cbegin();
    }

    const_iterator cend () const
    {
        return _v.cend();
    }

    void move_to (point_type const & p, bool is_relative = false);

    inline void move_to (unit_type x, unit_type y, bool is_relative = false)
    {
        move_to(point_type{x, y}, is_relative);
    }

    inline void rel_move_to (point_type const & p)
    {
        move_to(p, true);
    }

    inline void rel_move_to (unit_type x, unit_type y)
    {
        move_to(point_type{x, y}, true);
    }

    inline void line_to (point_type const & p, bool is_relative = false);

    inline void line_to (unit_type x, unit_type y, bool is_relative = false)
    {
        line_to(point_type{x, y}, is_relative);
    }

    inline void rel_line_to (point_type const & p)
    {
        line_to(p, true);
    }

    inline void rel_line_to (unit_type x, unit_type y)
    {
        line_to(point_type{x, y}, true);
    }

    inline void hline_to (unit_type x, bool is_relative = false)
    {
        line_to(x, 0, is_relative);
    }

    inline void rel_hline_to (unit_type x)
    {
        line_to(x, 0, true);
    }

    inline void vline_to (unit_type y, bool is_relative = false)
    {
        line_to(0, y, is_relative);
    }

    inline void rel_vline_to (unit_type y)
    {
        line_to(0, y, true);
    }

    /**
     * @brief Adds a cubic Bezier curve between the current position and
     *        the given @a end_point using the control points specified
     *        by @a c1 and @c c2.
     * @param c1 First control point.
     * @param c2 Second control point.
     * @param end_point End point.
     */
    inline void curve_to (point_type const & c1
            , point_type const & c2
            , point_type const & ep
            , bool is_relative = false);

    inline void curve_to (unit_type cx1, unit_type cy1
            , unit_type cx2, unit_type cy2
            , unit_type ex, unit_type ey
            , bool is_relative = false)
    {
        curve_to(point_type{cx1, cy1}
                , point_type{cx2, cy2}
                , point_type{ex, ey}
                , is_relative);
    }

    /**
     *
     */
    inline void rel_curve_to (point_type const & c1
            , point_type const & c2
            , point_type const & ep)
    {
        curve_to(c1, c2, ep);
    }

    inline void rel_curve_to (unit_type cx1, unit_type cy1
            , unit_type cx2, unit_type cy2
            , unit_type ex, unit_type ey)
    {
        curve_to(point_type{cx1, cy1}
                , point_type{cx2, cy2}
                , point_type{ex, ey}
                , true);
    }

    /**
     * @brief Adds a quadratic Bezier curve between the current position and
     *        the given @a end_point with the control point specified by @a c.
     * @param c Control point.
     * @param ep End point.
     */
    void curve_to (point_type const & c
            , point_type const & ep
            , bool is_relative = false);

    inline void curve_to (unit_type cx, unit_type cy
            , unit_type ex, unit_type ey
            , bool is_relative = false)
    {
        curve_to(point_type{cx, cy}
                , point_type{ex, ey}
                , is_relative);
    }

    inline void rel_curve_to (point_type const & c
            , point_type const & ep)
    {
        curve_to(c, ep, true);
    }

    inline void rel_curve_to (unit_type cx, unit_type cy
            , unit_type ex, unit_type ey)
    {
        curve_to(point_type{cx, cy}
                , point_type{ex, ey}
                , true);
    }

    void close_path ()
    {
        assert(!_v.empty());
        _v.emplace_back(path_entry_enum::close_path, point_type{0, 0});
    }

    /**
     * @brief Appends the given @a apath to this path as a closed subpath.
     */
    inline void append_path (path const & apath)
    {
        _v.insert(_v.begin(), apath._v.cbegin(), apath._v.cend());
    }

    template <typename U>
    friend rect_type bounding_rect (path<U> const & apath);

    template <typename U>
    friend rect_type control_point_rect (path<U> const & apath);
};

template <typename UnitT>
void path<UnitT>::move_to (point_type const & apoint, bool is_relative)
{
    // Collection of entries is always non-empty (according to constructors).
    assert(!_v.empty());

    point_type abspoint{apoint};
    reference back = _v.back();

    if (is_relative)
        abspoint += back.p;

    if (back.type != path_entry_enum::move_to)
        _v.emplace_back(path_entry_enum::move_to, abspoint);
    else
        back.p = abspoint; // Replace point
}

template <typename UnitT>
void path<UnitT>::line_to (point_type const & apoint, bool is_relative)
{
    assert(!_v.empty());

    if (is_relative) {
        point_type abspoint{_v.back().p};
        abspoint += apoint;
        _v.emplace_back(path_entry_enum::line_to, abspoint);
    } else {
        _v.emplace_back(path_entry_enum::line_to, apoint);
    }
}

template <typename UnitT>
void path<UnitT>::curve_to (point_type const & c1
        , point_type const & c2
        , point_type const & ep
        , bool is_relative)
{
    assert(!_v.empty());

    if (is_relative) {
        point_type sp{_v.back().p};
        _v.emplace_back(path_entry_enum::curve_to, sp + c1);
        _v.emplace_back(path_entry_enum::curve_to, sp + c2);
        _v.emplace_back(path_entry_enum::curve_to, sp + ep);
    } else {
        _v.emplace_back(path_entry_enum::curve_to, c1);
        _v.emplace_back(path_entry_enum::curve_to, c2);
        _v.emplace_back(path_entry_enum::curve_to, ep);
    }
}

template <typename UnitT>
void path<UnitT>::curve_to (point_type const & ctl_point
            , point_type const & end_point
            , bool is_relative)
{
    assert(!_v.empty());

    point_type const & sp = _v.back().p; // start point
    point_type cp{ctl_point};
    point_type ep{end_point};

    //
    // Calculate the absolute coordinates
    //
    if (is_relative) {
        cp += sp;
        ep += sp;
    }

    if (sp == cp && cp == ep)
        return;

    //
    // [Bézier curve](https://en.wikipedia.org/wiki/Bézier_curve)
    // Use "Degree Elevation" (conversion of a Bézier curve of degree 'n'
    // into a Bézier curve of degree 'n + 1' with the same shape)
    //
    // So quadratic curve (P0,C,P1) converted into cubic curve (P0,C1,C2,P1)
    // using formula:
    //
    // C1x = P0x + (2 * (Cx - P0x)) / 3
    // C1y = P0y + (2 * (Cy - P0y)) / 3
    // C2x = Cx  +      (P1x - Cx)  / 3
    // C2y = Cy  +      (P1y - Cy)  / 3
    //
    // Note: Qt5 (may be Qt4 too) uses another formula
    // (see QPainterPath::quadTo() implementation)
    //
    unit_type c1x = sp.get_x() + 2 * (cp.get_x() - sp.get_x()) / 3;
    unit_type c1y = sp.get_y() + 2 * (cp.get_y() - sp.get_y()) / 3;
    unit_type c2x = cp.get_x() +     (ep.get_x() - cp.get_x()) / 3;
    unit_type c2y = cp.get_y() +     (ep.get_y() - cp.get_y()) / 3;

    curve_to(point_type{c1x, c1y}, point_type{c2x, c2y}, ep, false);
}

/**
 * @return Calculated bounding rectangle of painter path @a apath.
 */
template <typename UnitT>
rect<UnitT> bounding_rect (path<UnitT> const & apath)
{
    using rect_type = rect<UnitT>;
    rect_type r;

    // TODO Implement bounding_rect()
    // // see qt5/qtbase/src/gui/painting/qpainterpath.cpp:computeBoundingRect()

    return r;
}

/**
 * @return Calculated rectangle containing all the points and
 *         control points in path @a apath.
 * @note This function is significantly faster to compute than the exact
 *        bounding_rect(), and the returned rectangle is always a superset
 *        of the rectangle returned by bounding_rect().
 */
template <typename UnitT>
rect<UnitT> control_point_rect (path<UnitT> const & apath)
{
    using rect_type = rect<UnitT>;
    rect_type r;

    // TODO Implement control_point_rect()
    // see qt5/qtbase/src/gui/painting/qpainterpath.cpp:computeControlPointRect()

    return r;
}

}} // namespace pfs::griotte
