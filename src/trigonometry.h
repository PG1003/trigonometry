// See LICENSE for the Copyright Notice

#include <cmath>
#include <type_traits>

#ifdef __cpp_lib_math_constants
#include <numbers>
#endif

#ifdef __has_cpp_attribute
#if __has_cpp_attribute( nodiscard )
#define TRIGONOMETRY_NODISCARD [[nodiscard]]
#endif
#endif
#ifndef TRIGONOMETRY_NODISCARD
#define TRIGONOMETRY_NODISCARD
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

    constexpr basic_angle< T, CONV > operator-()
    {
        value = -value;
        return *this;
    }

    TRIGONOMETRY_NODISCARD constexpr basic_angle< T, CONV > operator +( basic_angle< T, CONV > other ) const
    {
        return { value + other.value };
    }

    constexpr basic_angle< T, CONV > & operator +=( basic_angle< T, CONV > other )
    {
        value += other.value;
        return *this;
    }

    TRIGONOMETRY_NODISCARD constexpr basic_angle< T, CONV > operator -( const basic_angle< T, CONV > other ) const
    {
        return { value - other.value };
    }

    constexpr basic_angle< T, CONV > & operator -=( const basic_angle< T, CONV > other )
    {
        value -= other.value;
        return *this;
    }

    template< typename D >
    TRIGONOMETRY_NODISCARD constexpr basic_angle< T, CONV > operator /( D number ) const
    {
        return { static_cast< T >( value / number ) };
    }

    template< typename D >
    constexpr basic_angle< T, CONV > operator /=( D number )
    {
        value = static_cast< T >( value / number );
        return *this;
    }

    template< typename M >
    TRIGONOMETRY_NODISCARD constexpr basic_angle< T, CONV > operator *( M number ) const
    {
        return { static_cast< T >( value * number ) };
    }

    template< typename M >
    constexpr basic_angle< T, CONV > operator *=( M number )
    {
        value = static_cast< T >( value * number );
        return *this;
    }

    template< typename M >
    TRIGONOMETRY_NODISCARD constexpr basic_angle< T, CONV > operator %( M number ) const
    {
        return { static_cast< T >( std::fmod( value, number ) ) };
    }

    template< typename M >
    constexpr basic_angle< T, CONV > operator %=( M number )
    {
        value = static_cast< T >( std::fmod( value, number ) );
        return *this;
    }

    TRIGONOMETRY_NODISCARD constexpr bool operator <( const basic_angle< T, CONV > other )
    {
        return value < other.value;
    }

    TRIGONOMETRY_NODISCARD constexpr bool operator <=( const basic_angle< T, CONV > other )
    {
        return value <= other.value;
    }

    TRIGONOMETRY_NODISCARD constexpr bool operator >( const basic_angle< T, CONV > other )
    {
        return value > other.value;
    }

    TRIGONOMETRY_NODISCARD constexpr bool operator >=( const basic_angle< T, CONV > other )
    {
        return value >= other.value;
    }

    TRIGONOMETRY_NODISCARD constexpr bool operator ==( const basic_angle< T, CONV > other )
    {
        return value == other.value;
    }

    TRIGONOMETRY_NODISCARD constexpr bool operator !=( const basic_angle< T, CONV > other )
    {
        return value != other.value;
    }

    TRIGONOMETRY_NODISCARD constexpr T angle() const
    {
        return value;
    }

    constexpr void normalize()
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

    TRIGONOMETRY_NODISCARD constexpr basic_angle< T, CONV > normalized() const
    {
        auto new_normalized = *this;
        new_normalized.normalize();

        return new_normalized;
    }

    constexpr void normalize_abs()
    {
        const auto full_cicle = CONV::semicircle * 2.0;

        auto normalized = std::fmod( value, full_cicle );
        if( normalized < T() )
        {
            normalized += full_cicle;
        }

        value = static_cast< T >( normalized );
    }

    TRIGONOMETRY_NODISCARD constexpr basic_angle< T, CONV > normalized_abs() const
    {
        auto new_normalized = *this;
        new_normalized.normalize_abs();

        return new_normalized;
    }

protected:

    T value = T();
};

template< typename T, typename ANGLE_CONV,
          typename std::enable_if< std::is_floating_point< T >::value, int >::type = 0 >
TRIGONOMETRY_NODISCARD constexpr basic_angle< T, ANGLE_CONV > ceil( basic_angle< T, ANGLE_CONV > angle )
{
    return { std::ceil( angle.angle() ) };
}

template< typename T, typename ANGLE_CONV,
          typename std::enable_if< std::is_floating_point< T >::value, int >::type = 0 >
TRIGONOMETRY_NODISCARD constexpr basic_angle< T, ANGLE_CONV > floor( basic_angle< T, ANGLE_CONV > angle )
{
    return { std::floor( angle.angle() ) };
}

template< typename T, typename ANGLE_CONV,
          typename std::enable_if< std::is_floating_point< T >::value, int >::type = 0 >
TRIGONOMETRY_NODISCARD constexpr basic_angle< T, ANGLE_CONV > round( basic_angle< T, ANGLE_CONV > angle )
{
    return { std::round( angle.angle() ) };
}

template< typename TO, typename FROM_T, typename FROM_CONV >
TRIGONOMETRY_NODISCARD constexpr TO angle_cast( const basic_angle< FROM_T, FROM_CONV > from )
{
    const auto new_angle = from.angle() * ( TO::conversion::semicircle / FROM_CONV::semicircle );
    return { static_cast< typename TO::value_type >( new_angle ) };
}

struct deg_conv
{
    constexpr static long double semicircle = 180.0;
};

struct rad_conv
{
    constexpr static long double semicircle = detail::trig::pi;
};

struct grad_conv
{
    constexpr static long double semicircle = 200.0;
};

using deg  = basic_angle< double, deg_conv >;
using rad  = basic_angle< double, rad_conv >;
using grad = basic_angle< double, grad_conv >;

template< typename CONV, typename T >
TRIGONOMETRY_NODISCARD constexpr auto sin( basic_angle< T, CONV > x )
{
    auto radians = ( detail::trig::pi * x.angle() ) / CONV::semicircle;
    return std::sin( radians );
}

template< typename T >
TRIGONOMETRY_NODISCARD constexpr rad asin( T x )
{
    return { static_cast< rad::value_type >( std::asin( x ) ) };
}

template< typename TO, typename T >
TRIGONOMETRY_NODISCARD constexpr TO asin( T x )
{
    auto value = ( TO::conversion::semicircle * std::asin( x ) ) / ( detail::trig::pi );
    return { static_cast< typename TO::value_type >( value ) };
}

template< typename T, typename CONV >
TRIGONOMETRY_NODISCARD constexpr auto cos( basic_angle< T, CONV > x )
{
    auto radians = ( detail::trig::pi * x.angle() ) / CONV::semicircle;
    return std::cos( radians );
}

template< typename T >
TRIGONOMETRY_NODISCARD constexpr rad acos( T x )
{
    return { static_cast< rad::value_type >( std::acos( x ) ) };
}

template< typename TO, typename T >
TRIGONOMETRY_NODISCARD constexpr TO acos( T x )
{
    auto value = ( TO::conversion::semicircle * std::acos( x ) ) / ( detail::trig::pi );
    return { static_cast< typename TO::value_type >( value ) };
}

template< typename T, typename CONV >
TRIGONOMETRY_NODISCARD constexpr auto tan( basic_angle< T, CONV > x )
{
    auto radians = ( detail::trig::pi * x.angle() ) / CONV::semicircle;
    return std::tan( radians );
}

template< typename T >
TRIGONOMETRY_NODISCARD constexpr rad atan( T x )
{
    return { static_cast< rad::value_type >( std::atan( x )  )};
}

template< typename TO, typename T >
TRIGONOMETRY_NODISCARD constexpr TO atan( T x )
{
    auto value = ( TO::conversion::semicircle * std::atan( x ) ) / ( detail::trig::pi );
    return { static_cast< typename TO::value_type >( value ) };
}

template< typename T1, typename T2 >
TRIGONOMETRY_NODISCARD constexpr rad atan2( T1 x, T2 y )
{
    return { static_cast< rad::value_type >( std::atan2( x, y )  )};
}

template< typename TO, typename T1, typename T2 >
TRIGONOMETRY_NODISCARD constexpr TO atan2( T1 x, T2 y )
{
    auto value = ( TO::conversion::semicircle * std::atan2( x, y ) ) / ( detail::trig::pi );
    return { static_cast< typename TO::value_type >( value ) };
}

namespace trigonometric_literals
{

TRIGONOMETRY_NODISCARD constexpr deg operator ""_deg( long double value )
{
    return { static_cast< double >( value ) };
}

TRIGONOMETRY_NODISCARD constexpr deg operator ""_deg( unsigned long long int value )
{
    return { static_cast< double >( value ) };
}

TRIGONOMETRY_NODISCARD constexpr rad operator ""_rad( long double value )
{
    return { static_cast< double >( value ) };
}

TRIGONOMETRY_NODISCARD constexpr rad operator ""_rad( unsigned long long int value )
{
    return { static_cast< double >( value ) };
}

TRIGONOMETRY_NODISCARD constexpr grad operator ""_grad( long double value )
{
    return { static_cast< double >( value ) };
}

TRIGONOMETRY_NODISCARD constexpr grad operator ""_grad( unsigned long long int value )
{
    return { static_cast< double >( value ) };
}

}

}

}
