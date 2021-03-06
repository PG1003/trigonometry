// See LICENSE for the Copyright Notice

#include <cmath>
#include <ostream>

#ifdef __cpp_lib_math_constants
# include <numbers>
#endif

#ifdef __cpp_lib_format
# include <format>
#endif

#ifdef __has_cpp_attribute
# if __has_cpp_attribute( nodiscard )
#  define PG_TRIGONOMETRY_NODISCARD [[nodiscard]]
# endif
#endif
#ifndef PG_TRIGONOMETRY_NODISCARD
# define PG_TRIGONOMETRY_NODISCARD
#endif

namespace pg
{

namespace math
{

namespace detail
{

namespace trig
{

#ifdef __cpp_lib_math_constants
constexpr double pi = std::numbers::pi;
#else
constexpr double pi = 3.141592653589793238462643383279502884L;
#endif

}

}


/**
 * \brief Base type for angle-like objects
 *
 * \tparam T The storage type of angle value
 * \tparam CONV The conversion object with a constexpr static \em semicircle containing the value for a half circle.
 */
template< typename T, typename CONV >
struct basic_angle
{
    using value_type = T;
    using conversion = CONV;

    constexpr basic_angle() = default;
    constexpr basic_angle( const basic_angle & ) = default;
    constexpr basic_angle( basic_angle && ) = default;
    constexpr basic_angle & operator =( const basic_angle & ) = default;

    constexpr basic_angle( T value )
        : value( value )
    {}

    constexpr basic_angle< T, CONV > & operator +=( basic_angle< T, CONV > other )
    {
        value += other.value;
        return *this;
    }

    constexpr basic_angle< T, CONV > & operator -=( const basic_angle< T, CONV > other )
    {
        value -= other.value;
        return *this;
    }

    template< typename D >
    constexpr basic_angle< T, CONV > operator /=( D number )
    {
        value = static_cast< T >( value / number );
        return *this;
    }

    template< typename M >
    constexpr basic_angle< T, CONV > operator *=( M number )
    {
        value = static_cast< T >( value * number );
        return *this;
    }

    template< typename M >
    basic_angle< T, CONV > operator %=( M number ) noexcept
    {
        value = static_cast< T >( std::fmod( value, number ) );
        return *this;
    }

    /**
     * \brief Returns the value of the angle object.
     * 
     * \return The value of the angle object.
     */
    PG_TRIGONOMETRY_NODISCARD constexpr T angle() const
    {
        return value;
    }

    /**
     * \brief Normalizes the angle object between -/+ semicircle.
     */
    void normalize() noexcept
    {
        const auto full_cicle = CONV::semicircle * 2.0;

        auto normalized = std::fmod( value, full_cicle );
        if( normalized < CONV::semicircle )
        {
            normalized += full_cicle;
        }
        else if( normalized > CONV::semicircle )
        {
            normalized -= full_cicle;
        }

        value = static_cast< T >( normalized );
    }

    /**
     * \brief Returns a normalized angle object with a value between -/+ semicircle.
     * 
     *  The angle object itself is left unchanged.
     * 
     * \return A normalized copy of the angle object.
     */
    PG_TRIGONOMETRY_NODISCARD basic_angle< T, CONV > normalized() const noexcept
    {
        auto new_normalized = *this;
        new_normalized.normalize();

        return new_normalized;
    }

    /**
     * \brief Normalizes the angle object to a value between 0 to 2 * semicircle.
     */
    void normalize_abs() noexcept
    {
        const auto full_cicle = CONV::semicircle * 2.0;

        auto normalized = std::fmod( value, full_cicle );
        if( normalized < T() )
        {
            normalized += full_cicle;
        }

        value = static_cast< T >( normalized );
    }

    /**
     * \brief Returns a normalized angle object with a value between 0 to 2 * semicircle.
     * 
     *  The angle object itself is left unchanged.
     * 
     * \return A normalized copy of the angle object.
     */
    PG_TRIGONOMETRY_NODISCARD basic_angle< T, CONV > normalized_abs() const noexcept
    {
        auto new_normalized = *this;
        new_normalized.normalize_abs();

        return new_normalized;
    }

protected:

    T value = T();
};

template< typename T, typename CONV >
PG_TRIGONOMETRY_NODISCARD constexpr basic_angle< T, CONV > operator-( basic_angle< T, CONV > angle )
{
    return { -angle.angle() };
}

template< typename T, typename CONV >
PG_TRIGONOMETRY_NODISCARD constexpr basic_angle< T, CONV > operator +( basic_angle< T, CONV > left, basic_angle< T, CONV > right )
{
    return { left.angle() + right.angle() };
}

template< typename T, typename CONV >
PG_TRIGONOMETRY_NODISCARD constexpr basic_angle< T, CONV > operator -( basic_angle< T, CONV > left, basic_angle< T, CONV > right )
{
    return { left.angle() - right.angle() };
}

template< typename T, typename CONV, typename D >
PG_TRIGONOMETRY_NODISCARD constexpr basic_angle< T, CONV > operator /( basic_angle< T, CONV > angle, D number )
{
    return { static_cast< T >( angle.angle() / number ) };
}

template< typename T, typename CONV, typename M >
PG_TRIGONOMETRY_NODISCARD constexpr basic_angle< T, CONV > operator *( basic_angle< T, CONV > angle, M number )
{
    return { static_cast< T >( angle.angle() * number ) };
}

template< typename T, typename CONV, typename M >
PG_TRIGONOMETRY_NODISCARD basic_angle< T, CONV > operator %( basic_angle< T, CONV > angle, M number ) noexcept
{
    return { static_cast< T >( std::fmod( angle.angle(), number ) ) };
}

template< typename T, typename CONV >
PG_TRIGONOMETRY_NODISCARD constexpr bool operator <( basic_angle< T, CONV > left, basic_angle< T, CONV > right )
{
    return left.angle() < right.angle();
}

template< typename T, typename CONV >
PG_TRIGONOMETRY_NODISCARD constexpr bool operator <=( basic_angle< T, CONV > left, basic_angle< T, CONV > right )
{
    return left.angle() <= right.angle();
}

template< typename T, typename CONV >
PG_TRIGONOMETRY_NODISCARD constexpr bool operator >( basic_angle< T, CONV > left, basic_angle< T, CONV > right )
{
    return left.angle() > right.angle();
}

template< typename T, typename CONV >
PG_TRIGONOMETRY_NODISCARD constexpr bool operator >=( basic_angle< T, CONV > left, basic_angle< T, CONV > right )
{
    return left.angle() >= right.angle();
}

template< typename T, typename CONV >
PG_TRIGONOMETRY_NODISCARD constexpr bool operator ==( basic_angle< T, CONV > left, basic_angle< T, CONV > right )
{
    return left.angle() == right.angle();
}

template< typename T, typename CONV >
PG_TRIGONOMETRY_NODISCARD constexpr bool operator !=( basic_angle< T, CONV > left, basic_angle< T, CONV > right )
{
    return left.angle() != right.angle();
}

/**
 * \brief Returns an angle object with a value that is the nearest integer value not less than value of \em angle.
 *
 * \param angle The angle object from which the value of new angle object is derived.
 * 
 * \return An angle object with a value that is the nearest integer value not less than value of \em angle.
 */
template< typename T, typename CONV >
PG_TRIGONOMETRY_NODISCARD inline basic_angle< T, CONV > ceil( basic_angle< T, CONV > angle ) noexcept
{
    return { std::ceil( angle.angle() ) };
}

/**
 * \brief Returns an angle object with a value that is the largest integer value not greater than value of \em angle.
 *
 * \param angle The angle object from whichthe value of new angle is derived.
 * 
 * \return An angle object with a value that is the largest integer value not greater than value of \em angle.
 */
template< typename T, typename CONV >
PG_TRIGONOMETRY_NODISCARD inline basic_angle< T, CONV > floor( basic_angle< T, CONV > angle ) noexcept
{
    return { std::floor( angle.angle() ) };
}

/**
 * \brief Returns an angle object with a value that is the nearest integer of the value of \em angle.
 *
 * \param angle The angle object from which the value of new angle is derived.
 * 
 * \return An angle object with a value that is the nearest integer value of the value of \em angle.
 */
template< typename T, typename CONV >
PG_TRIGONOMETRY_NODISCARD inline basic_angle< T, CONV > round( basic_angle< T, CONV > angle ) noexcept
{
    return { std::round( angle.angle() ) };
}

/**
 * \brief Returns angle object of the given type that is derived another angle object.
 *
 * \tparam TO        The type of the returned angle object.
 * \tparam FROM_T    The storage type of the angle from which the new angle object is derived
 * \tparam FROM_CONV The conversion object of the angle from which the new angle object is derived
 * 
 * \param angle The angle object from which the new angle object is derived.
 * 
 * \return A new angle object of type \em TO with a value derived from \em from.
 */
template< typename TO, typename FROM_T, typename FROM_CONV >
PG_TRIGONOMETRY_NODISCARD inline TO angle_cast( const basic_angle< FROM_T, FROM_CONV > from ) noexcept
{
    const auto new_angle = from.angle() * ( TO::conversion::semicircle / FROM_CONV::semicircle );
    return { static_cast< typename TO::value_type >( new_angle ) };
}

/**
 * \brief Standard conversion type for angles in degrees
 */
struct deg_conv
{
    constexpr static long double semicircle = 180.0;
};

/**
 * \brief Standard conversion type for angles in radians
 */
struct rad_conv
{
    constexpr static long double semicircle = detail::trig::pi;
};

/**
 * \brief Standard conversion type for angles in gradians
 */
struct grad_conv
{
    constexpr static long double semicircle = 200.0;
};

using deg  = basic_angle< double, deg_conv >;
using rad  = basic_angle< double, rad_conv >;
using grad = basic_angle< double, grad_conv >;

/**
 * \brief Computes sine.
 * 
 * \param x An angle object.
 * 
 * \return The sine of \em x.
 */
template< typename CONV, typename T >
PG_TRIGONOMETRY_NODISCARD inline auto sin( basic_angle< T, CONV > x ) noexcept
{
    auto radians = detail::trig::pi * x.angle() / CONV::semicircle;
    return std::sin( radians );
}

/**
 * \brief Computes arc sine.
 * 
 * \tparam TO The resulting angle object type containing the arc sine of \em x.
 * \tparam T  The arithmetic type of \em x.
 * 
 * \param x An arithmetic value for wich the sine is calculated.
 * 
 * \return The arc sine of \em x as \em TO.
 */
template< typename TO = rad, typename T >
PG_TRIGONOMETRY_NODISCARD inline TO asin( T x ) noexcept
{
    auto value = TO::conversion::semicircle * std::asin( x ) / detail::trig::pi;
    return { static_cast< typename TO::value_type >( value ) };
}

/**
 * \brief Computes cosine.
 * 
 * \param x An angle object.
 * 
 * \return The cosine of \em x.
 */
template< typename T, typename CONV >
PG_TRIGONOMETRY_NODISCARD inline auto cos( basic_angle< T, CONV > x ) noexcept
{
    auto radians = detail::trig::pi * x.angle() / CONV::semicircle;
    return std::cos( radians );
}

/**
 * \brief Computes arc cosine.
 * 
 * \tparam TO The resulting angle object type containing the arc cosine of \em x.
 * \tparam T  The arithmetic type of \em x.
 * 
 * \param x An arithmetic value for wich the cosine is calculated.
 * 
 * \return The arc cosine of \em x as \em TO.
 */
template< typename TO = rad, typename T >
PG_TRIGONOMETRY_NODISCARD inline TO acos( T x ) noexcept
{
    auto value = TO::conversion::semicircle * std::acos( x ) / detail::trig::pi;
    return { static_cast< typename TO::value_type >( value ) };
}

/**
 * \brief Computes tangent.
 * 
 * \param x An angle object.
 * 
 * \return The tangent of \em x.
 */
template< typename T, typename CONV >
PG_TRIGONOMETRY_NODISCARD inline auto tan( basic_angle< T, CONV > x ) noexcept
{
    auto radians = detail::trig::pi * x.angle() / CONV::semicircle;
    return std::tan( radians );
}

/**
 * \brief Computes arc tangent.
 * 
 * \tparam TO The resulting angle object type containing the arc tangent of \em x.
 * \tparam T  The arithmetic type of \em x.
 * 
 * \param x An arithmetic value for wich the tangent is calculated.
 * 
 * \return The arc tangent of \em x as \em TO.
 */
template< typename TO = rad, typename T >
PG_TRIGONOMETRY_NODISCARD inline TO atan( T x ) noexcept
{
    auto value = TO::conversion::semicircle * std::atan( x ) / detail::trig::pi;
    return { static_cast< typename TO::value_type >( value ) };
}

/**
 * \brief Computes the arc tangent of y/x using the signs of arguments to determine the correct quadrant.
 * 
 * \tparam TO The resulting angle object type containing the arc tangent of \em x.
 * \tparam T1 The arithmetic type of \em y.
 * \tparam T2 The arithmetic type of \em x.
 * 
 * \param y An arithmetic value.
 * \param x An arithmetic value.
 * 
 * \return The arc tangent of \em y, \em x as \em TO.
 */
template< typename TO = rad, typename T1, typename T2 >
PG_TRIGONOMETRY_NODISCARD inline TO atan2( T1 y, T2 x ) noexcept
{
    auto value = TO::conversion::semicircle * std::atan2( y, x ) / detail::trig::pi;
    return { static_cast< typename TO::value_type >( value ) };
}

namespace trigonometric_literals
{

PG_TRIGONOMETRY_NODISCARD constexpr deg operator ""_deg( long double value )
{
    return { static_cast< double >( value ) };
}

PG_TRIGONOMETRY_NODISCARD constexpr deg operator ""_deg( unsigned long long int value )
{
    return { static_cast< double >( value ) };
}

PG_TRIGONOMETRY_NODISCARD constexpr rad operator ""_rad( long double value )
{
    return { static_cast< double >( value ) };
}

PG_TRIGONOMETRY_NODISCARD constexpr rad operator ""_rad( unsigned long long int value )
{
    return { static_cast< double >( value ) };
}

PG_TRIGONOMETRY_NODISCARD constexpr grad operator ""_grad( long double value )
{
    return { static_cast< double >( value ) };
}

PG_TRIGONOMETRY_NODISCARD constexpr grad operator ""_grad( unsigned long long int value )
{
    return { static_cast< double >( value ) };
}

}

template< typename T, typename CONV >
std::ostream & operator <<( std::ostream & os, basic_angle< T, CONV > angle ) noexcept
{
    return os << angle.angle();
}

}

}

#ifdef __cpp_lib_format

template< typename T, typename CONV, typename CharT >
struct std::formatter< pg::math::basic_angle< T, CONV >, CharT > : std::formatter< T, CharT >
{
    template< typename CTX >
    auto format( pg::math::basic_angle< T, CONV > angle, CTX & ctx )
    {
        return std::formatter< T, CharT >::format( angle.angle(), ctx );
    }
};

#endif
