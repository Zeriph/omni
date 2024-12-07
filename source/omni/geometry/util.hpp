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

namespace omni {
    namespace geometry {
        template < typename T >
        inline omni::geometry::point2d<T>
        point_on_circle(T degrees, T radius, T center_x, T center_y)
        {
            if ((degrees < static_cast<T>(0)) || (degrees > static_cast<T>(360))) {
                OMNI_ERR_FW("angle must be between 0-360 degrees", omni::exceptions::overflow_error("angle must be between 0-360 degrees"))
            }
            T x; T y;
            omni::math::point_on_circle(degrees, radius, center_x, center_y, x, y);
            return omni::geometry::point2d<T>(x, y);
        }

        // DEV_NOTE: the following is template specialized due to the fact that uint8_t
        // will never be greater than 360 or less than 0, so no need for error check

        template <>
        inline omni::geometry::point2d<uint8_t>
        point_on_circle<uint8_t>(uint8_t degrees, uint8_t radius, uint8_t center_x, uint8_t center_y)
        {
            uint8_t x; uint8_t y;
            omni::math::point_on_circle(degrees, radius, center_x, center_y, x, y);
            return omni::geometry::point2d<uint8_t>(x, y);
        }
    }
}

#endif // OMNI_GEOMETRY_UTIL_HPP
