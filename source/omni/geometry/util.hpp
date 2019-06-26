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
#if !defined(OMNI_GEOMETRY_UTIL_HPP)
#define OMNI_GEOMETRY_UTIL_HPP 1
#include <omni/defs/global.hpp>
#include <omni/geometry/point2d.hpp>
#include <omni/math.hpp>

namespace omni {
    namespace geometry {
        template < typename T >
        inline omni::geometry::point2d<T>
        point_on_circle(T angle, T radius, T center_x, T center_y)
        {
            if (angle > static_cast<T>(360)) {
                OMNI_ERR_RETV_FW("angle cannot be greater than 360 degrees", omni::exceptions::overflow_error("angle cannot be greater than 360 degrees"), omni::geometry::point2d<T>())
            }
            T x; T y;
            omni::math::point_on_circle(angle, radius, center_x, center_y, x, y);
            return omni::geometry::point2d<T>(x, y);
        }

        template <>
        inline omni::geometry::point2d<int8_t>
        point_on_circle<int8_t>(int8_t angle, int8_t radius, int8_t center_x, int8_t center_y)
        {
            int8_t x; int8_t y;
            omni::math::point_on_circle(angle, radius, center_x, center_y, x, y);
            return omni::geometry::point2d<int8_t>(x, y);
        }

        template <>
        inline omni::geometry::point2d<uint8_t>
        point_on_circle<uint8_t>(uint8_t angle, uint8_t radius, uint8_t center_x, uint8_t center_y)
        {
            uint8_t x; uint8_t y;
            omni::math::point_on_circle(angle, radius, center_x, center_y, x, y);
            return omni::geometry::point2d<uint8_t>(x, y);
        }
    }
}

#endif // OMNI_GEOMETRY_UTIL_HPP
