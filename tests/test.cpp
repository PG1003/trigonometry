#include <trigonometry.h>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <cmath>


#ifdef __cpp_lib_math_constants
#include <numbers>
inline constexpr double pi = std::numbers::pi;
#else
constexpr double pi = 3.141592653589793238462643383279502884L;
#endif

static int total_checks  = 0;
static int failed_checks = 0;

static bool report_failed_check( const char* const file, const int line, const char * const condition )
{
    std::cout << "check failed! (file " << file << ", line " << line << "): " << condition << '\n';
    ++failed_checks;
    return false;
}

#define assert_true( c ) do { ++total_checks; ( c ) || report_failed_check( __FILE__, __LINE__, #c ); } while( false )
#define assert_false( c ) do { ++total_checks; !( c ) || report_failed_check( __FILE__, __LINE__, #c ); } while( false )
#define assert_same( x, y ) do { ++total_checks; ( std::abs( x - y ) < 1e-14 ) || report_failed_check( __FILE__, __LINE__, #x ", " #y ); } while( false )


using namespace pg::math;

using ideg  = basic_angle< int, deg_conv >;

void arithmetic()
{
    const deg d1( 42.0 );
    const deg d2 = { 24 };
    assert_same( d1.angle(), 42 );
    assert_same( d2.angle(), 24 );

    const deg d3 = d1 + d2;
    assert_same( d3.angle(), 66 );

    deg d4 = d3;
    d4 += d2;
    assert_same( d4.angle(), 90 );

    const deg d5 = d1 - d2;
    assert_same( d5.angle(), 18 );

    deg d6 = d1;
    d6 -= d2;
    assert_same( d6.angle(), 18 );

    const deg d7 = d1 * 2;
    const deg d8 = d1 * 2.0;
    assert_same( d7.angle(), 84 );
    assert_same( d8.angle(), 84 );

    deg d9( 90 );
    d9 *= 2;
    assert_same( d9.angle(), 180 );
    d9 *= 2.0;
    assert_same( d9.angle(), 360 );

    const deg d10 = d1 / 2;
    const deg d11 = d1 / 2.0;
    assert_same( d10.angle(), 21 );
    assert_same( d11.angle(), 21 );

    deg d12( 90 );
    d12 /= 2;
    assert_same( d12.angle(), 45 );
    d12 /= 3.0;
    assert_same( d12.angle(), 15 );

    const deg d13 = d3 % 20;
    const deg d14 = d3 % 20.0;
    assert_same( d13.angle(), 6 );
    assert_same( d14.angle(), 6 );

    deg d15( 90 );
    d15 %= 60;
    assert_same( d15.angle(), 30 );
    d15 %= 20.0;
    assert_same( d15.angle(), 10 );

    const ideg d16 = ideg( 42 ) / 5;
    const ideg d17 = ideg( 42 ) / 5.0;
    assert_same( d16.angle(), 8 );
    assert_same( d17.angle(), 8 );

    ideg d18( 42 );
    d18 /= 5;
    assert_same( d18.angle(), 8 );
    d18 /= 3.0;
    assert_same( d18.angle(), 2 );

    const ideg d19 = ideg( 66 ) % 20;
    const ideg d20 = ideg( 66 ) % 20.0;
    assert_same( d19.angle(), 6 );
    assert_same( d20.angle(), 6 );

    ideg d21( 90 );
    d21 %= 60;
    assert_same( d21.angle(), 30 );
    d21 %= 20.0;
    assert_same( d21.angle(), 10 );

    ideg d22( 66 );
    d22 += ideg( 24 );
    assert_same( d22.angle(), 90 );

    const ideg d23 = ideg( 42 ) - ideg( 24 );
    assert_same( d23.angle(), 18 );

    ideg d24( 42 );
    d24 -= ideg( 24 );
    assert_same( d24.angle(), 18 );

    const ideg d25 = ideg( 42 ) * 2;
    const ideg d26 = ideg( 42 ) * 2.0;
    assert_same( d25.angle(), 84 );
    assert_same( d26.angle(), 84 );

    ideg d27( 90 );
    d27 *= 2;
    assert_same( d27.angle(), 180 );
    d27 *= 2.0;
    assert_same( d27.angle(), 360 );
}

void compare()
{
    using namespace pg::math::trigonometric_literals;

    assert_true( 0_deg < 42_deg );
    assert_true( 0_deg <= 42_deg );
    assert_true( 42_deg <= 42_deg );
    assert_false( 42_deg < 0_deg );
    assert_false( 42_deg < 42_deg );
    assert_true( 42_deg > 0_deg );
    assert_true( 42_deg >= 0_deg );
    assert_true( 42_deg >= 42_deg );
    assert_false( 0_deg >42_deg );
    assert_false( 0_deg >= 42_deg );
    assert_true( 42_deg == 42_deg );
    assert_false( 42_deg != 42_deg );
    assert_true( 0_deg != 42_deg );
    assert_false( 42_deg != 42_deg );
}

void literals()
{
    using namespace pg::math::trigonometric_literals;

    auto d1 = 42_deg;
    assert_same( d1.angle(), 42 );

    auto d2 = 24.42_deg;
    assert_same( d2.angle(), 24.42 );

    auto d3 = -42_deg;
    assert_same( d3.angle(), -42 );

    auto r1 = 42_rad;
    assert_same( r1.angle(), 42 );

    auto r2 = 24.42_rad;
    assert_same( r2.angle(), 24.42 );

    auto r3 = -42_rad;
    assert_same( r3.angle(), -42 );

    auto g1 = 42_grad;
    assert_same( g1.angle(), 42 );

    auto g2 = 24.42_grad;
    assert_same( g2.angle(), 24.42 );

    auto g3 = -42_grad;
    assert_same( g3.angle(), -42 );
}

void angle_cast()
{
    using namespace pg::math::trigonometric_literals;

    const auto deg_180 = 180_deg;
    const auto rad_1   = angle_cast< rad >( deg_180 );
    const auto grad_1  = angle_cast< grad >( deg_180 );
    assert_same( deg_180.angle(), 180.0 );
    assert_same( rad_1.angle(), pi );
    assert_same( grad_1.angle(), 200 );

    const auto rad_05   = rad( pi / 2 );
    const auto deg_90   = angle_cast< deg >( rad_05 );
    const auto grad_100 = angle_cast< grad >( rad_05 );
    assert_same( rad_05.angle(), pi / 2.0 );
    assert_same( deg_90.angle(), 90 );
    assert_same( grad_100.angle(), 100 );

    const auto grad_400 = 400_grad;
    const auto rad_2    = angle_cast< rad >( grad_400 );
    const auto deg_360  = angle_cast< deg >( grad_400 );
    assert_same( grad_400.angle(), 400 );
    assert_same( rad_2.angle(), 2 * pi );
    assert_same( deg_360.angle(), 360 );
}

void normalize()
{
    using namespace pg::math::trigonometric_literals;

    auto deg1  = 270_deg;
    auto deg1n = deg1.normalized();
    deg1.normalize();
    assert_same( deg1n.angle(), -90 );
    assert_same( deg1.angle(), -90 );

    auto deg2  = -270_deg;
    auto deg2n = deg2.normalized();
    deg2.normalize();
    assert_same( deg2n.angle(), 90 );
    assert_same( deg2.angle(), 90 );

    auto deg3  = 450_deg;
    auto deg3n = deg3.normalized_abs();
    deg3.normalize_abs();
    assert_same( deg3n.angle(), 90 );
    assert_same( deg3.angle(), 90 );

    auto deg4  = -90_deg;
    auto deg4n = deg4.normalized_abs();
    deg4.normalize_abs();
    assert_same( deg4n.angle(), 270 );
    assert_same( deg4.angle(), 270 );

    auto deg5  = 360_deg;
    auto deg5n = deg5.normalized_abs();
    deg5.normalize_abs();
    assert_same( deg5n.angle(), 0 );
    assert_same( deg5.angle(), 0 );

    ideg deg6( 270 );
    auto deg6n = deg6.normalized();
    deg6.normalize();
    assert_same( deg6n.angle(), -90 );
    assert_same( deg6.angle(), -90 );

    ideg deg7( -270 );
    auto deg7n = deg7.normalized();
    deg7.normalize();
    assert_same( deg7n.angle(), 90 );
    assert_same( deg7.angle(), 90 );

    ideg deg8( 450 );
    auto deg8n = deg8.normalized_abs();
    deg8.normalize_abs();
    assert_same( deg8n.angle(), 90 );
    assert_same( deg8.angle(), 90 );

    ideg deg9( -90 );
    auto deg9n = deg9.normalized_abs();
    deg9.normalize_abs();
    assert_same( deg9n.angle(), 270 );
    assert_same( deg9.angle(), 270 );

    ideg deg10( 360 );
    auto deg10n = deg10.normalized_abs();
    deg10.normalize_abs();
    assert_same( deg10n.angle(), 0 );
    assert_same( deg10.angle(), 0 );

    rad  rad1( 1.5 * pi );
    auto rad1n = rad1.normalized();
    rad1.normalize();
    assert_same( rad1n.angle(), -0.5 * pi );
    assert_same( rad1.angle(), -0.5 * pi );

    rad  rad2( -1.5 * pi );
    auto rad2n = rad2.normalized();
    rad2.normalize();
    assert_same( rad2n.angle(), 0.5 * pi );
    assert_same( rad2.angle(), 0.5 * pi );

    rad  rad3( 2.5 * pi );
    auto rad3n = rad3.normalized_abs();
    rad3.normalize_abs();
    assert_same( rad3n.angle(), 0.5 * pi );
    assert_same( rad3.angle(), 0.5 * pi );

    rad  rad4( -2.5 * pi );
    auto rad4n = rad4.normalized_abs();
    rad4.normalize_abs();
    assert_same( rad4n.angle(), 1.5 * pi );
    assert_same( rad4.angle(), 1.5 * pi );

    rad  rad5( 2 * pi );
    auto rad5n = rad5.normalized_abs();
    rad5.normalize_abs();
    assert_same( rad5n.angle(), 0 );
    assert_same( rad5.angle(), 0 );

    auto grad1  = 300_grad;
    auto grad1n = grad1.normalized();
    grad1.normalize();
    assert_same( grad1n.angle(), -100 );
    assert_same( grad1.angle(), -100 );

    auto grad2  = -300_grad;
    auto grad2n = grad2.normalized();
    grad2.normalize();
    assert_same( grad2n.angle(), 100 );
    assert_same( grad2.angle(), 100 );

    auto grad3  = 500_grad;
    auto grad3n = grad3.normalized_abs();
    grad3.normalize_abs();
    assert_same( grad3n.angle(), 100 );
    assert_same( grad3.angle(), 100 );

    auto grad4  = -100_grad;
    auto grad4n = grad4.normalized_abs();
    grad4.normalize_abs();
    assert_same( grad4n.angle(), 300 );
    assert_same( grad4.angle(), 300 );

    auto grad5  = 400_grad;
    auto grad5n = grad5.normalized_abs();
    grad5.normalize_abs();
    assert_same( grad5n.angle(), 0 );
    assert_same( grad5.angle(), 0 );
}

void angle_ceil()
{
    using namespace pg::math::trigonometric_literals;

    auto d1  = 24.42_deg;
    auto d1_ = ceil( d1 );
    assert_same( d1_.angle(), 25 );

    auto d2  = 24.84_deg;
    auto d2_ = ceil( d2 );
    assert_same( d2_.angle(), 25 );
}

void angle_floor()
{
    using namespace pg::math::trigonometric_literals;

    auto d1  = 24.42_deg;
    auto d1_ = floor( d1 );
    assert_same( d1_.angle(), 24 );

    auto d2  = 24.84_deg;
    auto d2_ = floor( d2 );
    assert_same( d2_.angle(), 24 );
}

void angle_round()
{
    using namespace pg::math::trigonometric_literals;

    auto d1  = 24.42_deg;
    auto d1_ = round( d1 );
    assert_same( d1_.angle(), 24 );

    auto d2  = 24.84_deg;
    auto d2_ = round( d2 );
    assert_same( d2_.angle(), 25 );
}

void sin()
{
    auto sin_deg_05 = sin( deg( 150 ) );
    assert_same( sin_deg_05, 0.5 );

    auto sin_rad_05 = sin( rad( pi / 6.0 ) );
    assert_same( sin_rad_05, 0.5 );

    auto sin_grad_1 = sin( grad( 300 ) );
    assert_same( sin_grad_1, -1 );
}

void asin()
{
    auto asin_deg_05 = pg::math::asin< deg >( 0.5 );
    assert_same( asin_deg_05.angle(), 30 );

    auto asin_rad_05_1 = pg::math::asin( 0.5 );
    assert_same( asin_rad_05_1.angle(), pi / 6.0 );
    auto asin_rad_05_2 = pg::math::asin< rad >( 0.5 );
    assert_same( asin_rad_05_2.angle(), pi / 6.0 );

    auto asin_grad_1 = pg::math::asin< grad >( -1 );
    assert_same( asin_grad_1.angle(), -100 );
}

void cos()
{
    auto cos_deg_05 = cos( deg( 60 ) );
    assert_same( cos_deg_05, 0.5 );

    auto cos_rad_05 = cos( rad( pi / 3.0 ) );
    assert_same( cos_rad_05, 0.5 );

    auto cos_grad_1 = cos( grad( 200 ) );
    assert_same( cos_grad_1, -1 );
}

void acos()
{
    auto acos_deg_05 = pg::math::acos< deg >( 0.5 );
    assert_same( acos_deg_05.angle(), 60 );

    auto acos_rad_05_1 = pg::math::acos( 0.5 );
    assert_same( acos_rad_05_1.angle(), pi / 3.0 );
    auto acos_rad_05_2 = pg::math::acos< rad >( 0.5 );
    assert_same( acos_rad_05_2.angle(), pi / 3.0 );

    auto acos_grad_1 = pg::math::acos< grad >( -1 );
    assert_same( acos_grad_1.angle(), 200 );
}

void tan()
{
    auto tan_deg_1 = tan( deg( 45 ) );
    assert_same( tan_deg_1, 1 );

    auto tan_rad_1 = tan( rad( pi / 4.0 ) );
    assert_same( tan_rad_1, 1 );

    auto tan_grad_1 = tan( grad( 50 ) );
    assert_same( tan_grad_1, 1 );
}

void atan()
{
    auto atan_deg_1 = pg::math::atan< deg >( 1 );
    assert_same( atan_deg_1.angle(), 45 );

    auto atan_rad_1_1 = pg::math::atan( 1 );
    assert_same( atan_rad_1_1.angle(), pi / 4.0 );
    auto atan_rad_1_2 = pg::math::atan< rad >( 1 );
    assert_same( atan_rad_1_2.angle(), pi / 4.0 );

    auto atan_grad_1 = pg::math::atan< grad >( 1 );
    assert_same( atan_grad_1.angle(), 50 );
}

void atan2()
{
    auto atan2_deg_1 = pg::math::atan2< deg >( 1, 1 );
    assert_same( atan2_deg_1.angle(), 45 );

    auto atan2_rad_1_1 = pg::math::atan2( 1, 1 );
    assert_same( atan2_rad_1_1.angle(), pi / 4.0 );
    auto atan2_rad_1_2 = pg::math::atan2< rad >( 1, 1 );
    assert_same( atan2_rad_1_2.angle(), pi / 4.0 );

    auto atan2_grad_1 = pg::math::atan2< grad >( 1, 1 );
    assert_same( atan2_grad_1.angle(), 50 );
}

void formatting()
{
    using namespace pg::math::trigonometric_literals;

    std::stringstream ss;
    ss << 42_deg << '\n' << 1.5_rad << '\n' << 200_grad << '\n';

    const auto str_stream = ss.str();
    assert_true( str_stream == "42\n1.5\n200\n" );
    
#ifdef __cpp_lib_format
    const auto str_format = std::format( "{}\n{}\n{}\n", 13.37_deg, 4.2_rad, 100_grad );
    assert_true( str_format == "13.37\n4.2\n100\n" );
#endif
}

void adl()
{
    using namespace std;

    const auto x = pg::math::asin( 0.5 );
    const auto y = sin( x );

    assert_same( y, 0.5 );
}

void algorithms()
{
    using namespace std;
    using namespace pg::math::trigonometric_literals;
    
    const auto mx  = max( 45_deg, 90_deg );
    const auto mn  = min( 45_deg, 90_deg );

    assert_same( mx.angle(), 90.0 );
    assert_same( mn.angle(), 45.0 );

    const pg::math::deg degrees[ 4 ] = { 42_deg, 18_deg, 333_deg, 37_deg };
    const pg::math::deg total        = accumulate( begin( degrees ), end( degrees ), 7_deg );
    assert_same( total.angle(), 437.0 );

#if __cplusplus >= 201703L
    const auto cpx = clamp( 100_deg, 45_deg, 90_deg );
    const auto cp  = clamp( 60_deg, 45_deg, 90_deg );
    const auto cpn = clamp( 0_deg, 45_deg, 90_deg );

    assert_same( cpx.angle(), 90.0 );
    assert_same( cp.angle(), 60.0 );
    assert_same( cpn.angle(), 45.0 );
#endif
}

struct conversion
{
    constexpr static int semicircle = 128;
};

void readme_examples()
{
    {
        pg::math::deg  degrees( 360.0 );
        pg::math::rad  radians( 2.0 );
        pg::math::grad gradians( 400 );

        using namespace pg::math::trigonometric_literals;

        degrees  = 180_deg;
        radians  = 1_rad;
        gradians = 200_grad;
    }
    {
        using namespace pg::math::trigonometric_literals;

        auto deg1 = 45.0_deg;
        deg1 *= 10;

        auto deg2 = deg1 - 90.0_deg;
        auto deg3 = deg2 / 2;
        assert_true( deg3.angle() == 180.0 );
    }
    {
        pg::math::rad rad1( pi );
        pg::math::rad rad2( 0 );
        pg::math::rad rad3( 2.0 * pi );

        assert_true( rad1 > rad2 );
        assert_true( rad1 < rad3 );
        assert_true( rad1 != rad2 );
    }
    {
        auto radians  = pg::math::asin( 0.5 );
        auto degrees  = pg::math::asin< pg::math::deg >( 0.5 );
        auto gradians = pg::math::asin< pg::math::grad >( 0.5 );

//        std::cout << "radians  = " << radians.angle() << '\n'
//                  << "degrees  = " << degrees.angle() << '\n'
//                  << "gradians = " << gradians.angle() << '\n';
        (void)radians;
        (void)degrees;
        (void)gradians;

        auto sin_radians  = pg::math::sin( radians );
        auto sin_degrees  = pg::math::sin( degrees );
        auto sin_gradians = pg::math::sin( gradians );

//        std::cout << "sin( radians )  = " << sin_radians << '\n'
//                  << "sin( degrees )  = " << sin_degrees << '\n'
//                  << "sin( gradians ) = " << sin_gradians << '\n';
        (void)sin_radians;
        (void)sin_degrees;
        (void)sin_gradians;
    }
    {
        auto radians  = pg::math::asin( 1 );
        auto degrees  = pg::math::angle_cast< pg::math::deg >( radians );
        auto gradians = pg::math::angle_cast< pg::math::grad >( degrees );

//        std::cout << "radians  = " << radians.angle() << '\n'
//                  << "degrees  = " << degrees.angle() << '\n'
//                  << "gradians = " << gradians.angle() << '\n';
        (void)radians;
        (void)degrees;
        (void)gradians;
    }
    {
        using my_ideg = pg::math::basic_angle< int, conversion >;

        my_ideg ideg1 = pg::math::acos< my_ideg >( 0 );
        my_ideg ideg2 = pg::math::acos< my_ideg >( 1 );
        my_ideg ideg3 = pg::math::acos< my_ideg >( -1 );

//        std::cout << "acos( 0 )  = " << ideg1.angle() << '\n'
//                  << "acos( 1 )  = " << ideg2.angle() << '\n'
//                  << "acos( -1 ) = " << ideg3.angle() << '\n';
        (void)ideg1;
        (void)ideg2;
        (void)ideg3;

        auto ideg_cosx = pg::math::cos( my_ideg( 43 ) );
        auto ideg_cosy = pg::math::cos( my_ideg( -128 ) );
        auto ideg_cosz = pg::math::cos( my_ideg( 0 ) );

//        std::cout << "ideg_cosx = " << ideg_cosx << '\n'
//                  << "ideg_cosy = " << ideg_cosy << '\n'
//                  << "ideg_cosz = " << ideg_cosz << '\n';

        (void)ideg_cosx;
        (void)ideg_cosy;
        (void)ideg_cosz;
    }
}

int main( const int /* argc */, const char ** /* argv[] */ )
{
    arithmetic();
    compare();
    literals();
    angle_cast();
    normalize();
    angle_ceil();
    angle_floor();
    angle_round();
    sin();
    asin();
    cos();
    acos();
    tan();
    atan();
    atan2();
    formatting();
    adl();
    algorithms();
    readme_examples();

    std::cout << "Total tests: " << total_checks << ", Tests failed: " << failed_checks << '\n';

    return failed_checks ? 1 : 0;
}
