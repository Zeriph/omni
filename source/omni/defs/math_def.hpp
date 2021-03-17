/*
 * Copyright (c), Zeriph Enterprises
 * All rights reserved.
 * 
 * Contributor(s):
 * Zechariah Perez, omni (at) zeriph (dot) com
 * 
 * THIS SOFTWARE IS PROVIDED BY ZERIPH AND CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL ZERIPH AND CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#if !defined(OMNI_MATH_DEF_HPP)
#define OMNI_MATH_DEF_HPP 1

#define OMNI_MATH_MAX_ROUND_DIGITS_FW 15
#define OMNI_MATH_ROUND_LIMIT_FW 1e16

// float
#if !defined(OMNI_E_F)
    #if (defined(OMNI_USE_M_E_F) || defined(OMNI_USE_MATH_DEFS)) && defined(M_E)
        #define OMNI_E_F static_cast<float>(M_E)
    #else
        #define OMNI_E_F 2.7182818F
    #endif
#endif
#if !defined(OMNI_PI_F)
    #if (defined(OMNI_USE_M_PI_F) || defined(OMNI_USE_MATH_DEFS)) && defined(M_PI)
        #define OMNI_PI_F static_cast<float>(M_PI)
    #else
        #define OMNI_PI_F 3.1415926F
    #endif
    #define OMNI_PI_F_180 0.0174533F
    #define OMNI_180_PI_F 57.2957805F
#endif
#if !defined(OMNI_TAU_F)
    #define OMNI_TAU_F 6.2831852F
#endif

// double
#if !defined(OMNI_E)
    #if (defined(OMNI_USE_M_E) || defined(OMNI_USE_MATH_DEFS)) && defined(M_E)
        #define OMNI_E M_E
    #else
        #define OMNI_E 2.71828182845904523536
    #endif
#endif
#if !defined(OMNI_PI)
    #if (defined(OMNI_USE_M_PI) || defined(OMNI_USE_MATH_DEFS)) && defined(M_PI)
        #define OMNI_PI M_PI
    #else
        #define OMNI_PI 3.14159265358979323846
    #endif
    #define OMNI_PI_180 0.01745329251994329577
    #define OMNI_180_PI 57.29577951308232087684
#endif
#if !defined(OMNI_TAU)
    #define OMNI_TAU 6.28318530717958647692
#endif

/*
    DEV_NOTE: these are the exact values from the .NET lib, links:
    https://docs.microsoft.com/en-us/dotnet/api/system.math.pi?view=net-5.0
    public const double PI = 3.1415926535897931;
    https://docs.microsoft.com/en-us/dotnet/api/system.math.e?view=net-5.0
    public const double E = 2.7182818284590451;
    https://docs.microsoft.com/en-us/dotnet/api/system.math.tau?view=net-5.0
    public const double Tau = 6.2831853071795862;
*/
#define OMNI_MATH_COMPAT_PI 3.1415926535897931
#define OMNI_MATH_COMPAT_E 2.7182818284590451
#define OMNI_MATH_COMPAT_TAU 6.2831853071795862

// long double
#if !defined(OMNI_E_L)
    #if (defined(OMNI_USE_M_E_L) || defined(OMNI_USE_MATH_DEFS)) && defined(M_El)
        #define OMNI_E_L M_El
    #else
        #define OMNI_E_L 2.71828182845904523536028747135266250L
    #endif
#endif
#if !defined(OMNI_PI_L)
    #if (defined(OMNI_USE_M_PI_L) || defined(OMNI_USE_MATH_DEFS)) && defined(M_PIl)
        #define OMNI_PI_L M_PIl
    #else
        #define OMNI_PI_L 3.141592653589793238462643383279502884L
    #endif
    #define OMNI_PI_L_180 0.017453292519943295769236907684886127L
    #define OMNI_180_PI_L 57.295779513082320876798154814105170336L
#endif
#if !defined(OMNI_TAU_L)
    #define OMNI_TAU_L 6.283185307179586476925286766559005768L
#endif

/*
TODO: finish implementing these
see: /Code/omni/references/kernel_sources/Apple/MacOSX10.14_include/math.h

#define M_LOG2E     1.44269504088896340735992468100189214   // log2(e)
#define M_LOG10E    0.434294481903251827651128918916605082  // log10(e)
#define M_LN2       0.693147180559945309417232121458176568  // loge(2)
#define M_LN10      2.30258509299404568401799145468436421   // loge(10)
#define M_PI_2      1.57079632679489661923132169163975144   // pi/2
#define M_PI_4      0.785398163397448309615660845819875721  // pi/4
#define M_1_PI      0.318309886183790671537767526745028724  // 1/pi
#define M_2_PI      0.636619772367581343075535053490057448  // 2/pi
#define M_2_SQRTPI  1.12837916709551257389615890312154517   // 2/sqrt(pi)
#define M_SQRT2     1.41421356237309504880168872420969808   // sqrt(2)
#define M_SQRT1_2   0.707106781186547524400844362104849039  // 1/sqrt(2)
*/


// radians =  degrees * π / 180
#define OMNI_DEG_TO_RAD(deg) (deg) * OMNI_PI_180

// degrees = radians * 180 / π
#define OMNI_RAD_TO_DEG(rad) (rad) * OMNI_180_PI

#define OMNI_MATH_DELTA(a,b) ((a) - (b))

#define OMNI_MATH_GET_POINT_X_FW(T, center_pt, radius, angle) \
    static_cast<T>((static_cast<double>(center_pt) + (static_cast<double>(radius) * std::sin(OMNI_DEG_TO_RAD(static_cast<double>(angle))))))

#define OMNI_MATH_GET_POINT_Y_FW(T, center_pt, radius, angle) \
    static_cast<T>((static_cast<double>(center_pt) + (static_cast<double>(radius) * std::cos(OMNI_DEG_TO_RAD(static_cast<double>(angle))))))

#define OMNI_MATH_GET_POINT_X_INT_FW(T, center_pt, radius, angle) \
    static_cast<T>(std::ceil((static_cast<double>(center_pt) + (static_cast<double>(radius) * std::sin(OMNI_DEG_TO_RAD(static_cast<double>(angle)))))))

#define OMNI_MATH_GET_POINT_Y_INT_FW(T, center_pt, radius, angle) \
    static_cast<T>(std::ceil((static_cast<double>(center_pt) + (static_cast<double>(radius) * std::cos(OMNI_DEG_TO_RAD(static_cast<double>(angle)))))))

#define OMNI_MATH_ANGLE_ERR_FW(angle) if ((angle < 0) || (angle > 360)) { OMNI_ERR_FW("angle must be between 0-360 degrees", omni::exceptions::overflow_error("angle must be between 0-360 degrees")) }

#define OMNI_MATH_GET_POINT_FW(T, out_x, out_y, center_x, center_y, radius, angle) \
    OMNI_MATH_ANGLE_ERR_FW(angle) \
    out_x = OMNI_MATH_GET_POINT_X_FW(T, center_x, radius, angle); \
    out_y = OMNI_MATH_GET_POINT_Y_FW(T, center_y, radius, angle)

#define OMNI_MATH_GET_POINT_INT_FW(T, out_x, out_y, center_x, center_y, radius, angle) \
    OMNI_MATH_ANGLE_ERR_FW(angle) \
    out_x = OMNI_MATH_GET_POINT_X_INT_FW(T, center_x, radius, angle); \
    out_y = OMNI_MATH_GET_POINT_Y_INT_FW(T, center_y, radius, angle)

#define OMNI_RECT_XYWH_CONTAINS_FW(rx,ry,rw,rh,ox,oy) ((ox >= rx) && (ox <= (rx + rw)) && (oy >= ry) && (oy <= (ry + rh)))
#define OMNI_RECT_LTRB_CONTAINS_FW(left,top,right,bottom,ox,oy) ((ox >= left) && (ox <= right) && (oy >= top) && (oy <= bottom))

#define OMNI_CIRCLE_CONTAINS_POINT_FW(cx,cy,r,x,y,oc) (oc ? (((x - cx)*(x - cx)) + ((y - cy) * (y - cy))) <= (r * r) : (((x - cx) * (x - cx)) + ((y - cy) * (y - cy))) < (r * r))

#define OMNI_DISTANCE_2POINTS_2D_FW(start_x, start_y, end_x, end_y) (std::sqrt(static_cast<double>((start_x - end_x) * (start_x - end_x)) + static_cast<double>((start_y - end_y) * (start_y - end_y))))

#define OMNI_DISTANCE_2POINTS_3D_FW(start_x, start_y, start_z, end_x, end_y, end_z) (std::sqrt(static_cast<double>((start_x - end_x) * (start_x - end_x)) + static_cast<double>((start_y - end_y) * (start_y - end_y)) + static_cast<double>((start_z - end_z) * (start_z - end_z))))

#endif // OMNI_MATH_DEF_HPP
