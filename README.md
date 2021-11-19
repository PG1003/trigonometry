# A C++ library for strongly typed trigonometric values and utilities

This library provides data types and utilities for trigonometric calculations.  
The strong types for radians, degrees and gradians prevents programming errors when doing trigonometric calculations.
For example errors such as forgetting to convert a variable to degrees or passing a degrees value to the `std::sin` function.  
The trigonometric types have overloaded mathematical and logic operators to simplify calculations.
This library also includes wrappers for the standard C++ trigonometric functions to support types that are defined with this library.

## Features

* Strongly typed trigonometric types for radians, degrees and gradians.
* Explicit converstions between types.
* Trigonomentric fuctions using the trigonometric types.
* User defined trigonometric types.

## Requirements

A compiler with support for C++14 or newer.

## Examples

### Trigonometric types and literals

```c++
pg::math::rad  radians( 2.0 );
pg::math::deg  degrees( 360.0 );
pg::math::grad gradians( 400.0 );

using namespace pg::math::trigonometric_litherals;

radians  = 1_rad;
degrees  = 180_deg;
gradians = 200_grad;
```

### Arithmetic

```c++
using namespace pg::math::trigonometric_litherals;

auto deg1 = 45.0_deg;
deg1 *= 10;

auto deg2 = deg1 - 90.0_deg;
auto deg3 = deg2 / 2;

assert( deg3.angle() == 180.0 );
```

### Comparison

```c++
pg::math::rad rad1( std::numbers::pi );
pg::math::rad rad2( 0 );
pg::math::rad rad3( 2.0 * std::numbers::pi );

assert( rad1 > rad2 );
assert( rad1 < rad3 );
assert( rad1 != rad2 );
```

### Trigonometric functions

```c++
auto radians  = pg::math::asin( 0.5 );
auto degrees  = pg::math::asin< pg::math::deg >( 0.5 );
auto gradians = pg::math::asin< pg::math::grad >( 0.5 );

std::cout << "radians  = " << radians.angle() << '\n'
          << "degrees  = " << degrees.angle() << '\n'
          << "gradians = " << gradians.angle() << '\n';

auto sin_radians  = pg::math::sin( radians );
auto sin_degrees  = pg::math::sin( degrees );
auto sin_gradians = pg::math::sin( gradians );

std::cout << "sin( radians )  = " << sin_radians << '\n'
          << "sin( degrees )  = " << sin_degrees << '\n'
          << "sin( gradians ) = " << sin_gradians << '\n';
```
The output is:
>radians  = 0.523599  
>degrees  = 30  
>gradians = 33.3333  
>sin( radians )  = 0.5  
>sin( degrees )  = 0.5  
>sin( gradians ) = 0.5

### Converstion between radians, degrees and gradians

```c++
auto radians  = pg::math::asin( 1 );
auto degrees  = pg::math::angle_cast< pg::math::deg >( radians );
auto gradians = pg::math::angle_cast< pg::math::grad >( degrees );

std::cout << "radians  = " << radians.angle() << '\n'
          << "degrees  = " << degrees.angle() << '\n'
          << "gradians = " << gradians.angle() << '\n';
```
The output is:
>radians  = 1.5708  
>degrees  = 90  
>gradians = 100

### Custom trigonometric type

```c++
struct conversion
{
    constexpr static int16_t semicircle = 128;
}

using my_ideg = pg::math::basic_angle< int16_t, conversion >;

my_ideg ideg1 = pg::math::acos< my_ideg >( 0 );
my_ideg ideg2 = pg::math::acos< my_ideg >( 1 );
my_ideg ideg3 = pg::math::acos< my_ideg >( -1 );

std::cout << "acos( 0 )  = " << ideg1.angle() << '\n'
          << "acos( 1 )  = " << ideg2.angle() << '\n'
          << "acos( -1 ) = " << ideg3.angle() << '\n';

auto ideg_cos_x = pg::math::cos( my_ideg( 42 ) );
auto ideg_cos_y = pg::math::cos( my_ideg( -128 ) );
auto ideg_cos_z = pg::math::cos( my_ideg( 0 ) );

std::cout << "ideg_cos_x = " << ideg_cos_x << '\n'
          << "ideg_cos_y = " << ideg_cos_y << '\n'
          << "ideg_cos_z = " << ideg_cos_z << '\n';
```
The output is:
>acos( 0 )  = 64  
>acos( 1 )  = 0  
>acos( -1 ) = 128  
>ideg_cos_x = 0.514103  
>ideg_cos_y = -1  
>ideg_cos_z = 1
