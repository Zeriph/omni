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

#if !defined(OMNI_PI_F) // float
    #if defined (OMNI_USE_M_PI) && defined(M_PI)
        #define OMNI_PI_F static_cast<float>(M_PI)
    #else
        #define OMNI_PI_F 3.1415926F
    #endif
    #define OMNI_PI_F_180 0.0174533F
    #define OMNI_180_PI_F 57.2957805F
#endif

#if !defined(OMNI_PI) // double
    #if defined (OMNI_USE_M_PI) && defined(M_PI)
        #define OMNI_PI M_PI
    #else
        #define OMNI_PI 3.14159265358979323846
    #endif
    #define OMNI_PI_180 0.01745329251994329577
    #define OMNI_180_PI 57.29577951308232087684
#endif

#if !defined(OMNI_PI_L) // long double
    #if defined (OMNI_USE_M_PI_L) && defined(M_PIl)
        #define OMNI_PI_L M_PIl
    #else
        #define OMNI_PI_L 3.141592653589793238462643383279502884L
    #endif
    #define OMNI_PI_L_180 0.017453292519943295769236907684886127L
    #define OMNI_180_PI_L 57.295779513082320876798154814105170336L
#endif

#define OMNI_MATH_GET_POINT_X_FW(T, center_x, radius, angle) \
    static_cast<T>((static_cast<double>(center_x) + (static_cast<double>(radius) * std::cos((static_cast<double>(angle) * OMNI_PI_180)))))
    
#define OMNI_MATH_GET_POINT_Y_FW(T, center_y, radius, angle) \
    static_cast<T>((static_cast<double>(center_y) + (static_cast<double>(radius) * std::sin((static_cast<double>(angle) * OMNI_PI_180)))))

#define OMNI_MATH_GET_POINT_X_INT_FW(T, center_x, radius, angle) \
    static_cast<T>(std::ceil((static_cast<double>(center_x) + (static_cast<double>(radius) * std::cos((static_cast<double>(angle) * OMNI_PI_180))))))
    
#define OMNI_MATH_GET_POINT_Y_INT_FW(T, center_y, radius, angle) \
    static_cast<T>(std::ceil((static_cast<double>(center_y) + (static_cast<double>(radius) * std::sin((static_cast<double>(angle) * OMNI_PI_180))))))

#define OMNI_MATH_ANGLE_ERR_FW if (angle > 360) { OMNI_ERR_FW("angle cannot be greater than 360 degrees", omni::exceptions::overflow_error("angle cannot be greater than 360 degrees")) }

#define OMNI_MATH_GET_POINT_FW(T, out_x, out_y, center_x, center_y, radius, angle) \
    OMNI_MATH_ANGLE_ERR_FW \
    out_x = OMNI_MATH_GET_POINT_X_FW(T, center_x, radius, angle); \
    out_y = OMNI_MATH_GET_POINT_Y_FW(T, center_y, radius, angle)

#define OMNI_MATH_GET_POINT_INT_FW(T, out_x, out_y, center_x, center_y, radius, angle) \
    OMNI_MATH_ANGLE_ERR_FW \
    out_x = OMNI_MATH_GET_POINT_X_INT_FW(T, center_x, radius, angle); \
    out_y = OMNI_MATH_GET_POINT_Y_INT_FW(T, center_y, radius, angle)

#endif // OMNI_MATH_DEF_HPP
