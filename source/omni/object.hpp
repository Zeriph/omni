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
#if !defined(OMNI_OBJECT_HPP)
#define OMNI_OBJECT_HPP 1
#include <omni/defs/class_macros.hpp>
#include <omni/type.hpp>
#include <omni/ostream.hpp>
#include <omni/string/util.hpp>
#include <omni/generic_ptr.hpp>
#include <omni/delegate/0.hpp>

namespace omni {
    /**
     * omni::object is a base type containing generic data that allows any children
     * to inherit certain feature sets, like a tag and a name property, as well as 
     * an event to alert any subscribers of when the object is being disposed (destroyed)
     */
    class object
    {
        public:
            object() :
                disposing(),
                name(),
                tag()
            { 
                OMNI_D5_FW("created omni::object with no name");
            }
            
            object(const omni::object& cp) :
                disposing(cp.disposing),
                name(cp.name),
                tag(cp.tag)
            {
                OMNI_DV5_FW("copied omni::object with name ", this->name);
            }
            
            explicit object(const omni::string_t& nm) : 
                disposing(),
                name(nm),
                tag()
            { 
                OMNI_DV5_FW("created omni::object with name ", this->name);
            }
            
            explicit object(const char* nm) : 
                disposing(),
                name(),
                tag()
            {
                this->name = omni::string::to_string_t(std::string(nm));
                OMNI_DV5_FW("created omni::object with name ", this->name);
            }
            
            explicit object(const omni::callback& ev) : 
                disposing(ev),
                name(),
                tag()
            {
                OMNI_DV5_FW("created omni::object with name ", this->name);
            }
            
            object(const char* nm, const omni::callback& ev) : 
                disposing(ev),
                name(),
                tag()
            { 
                this->name = omni::string::to_string_t(std::string(nm));
                OMNI_DV5_FW("created omni::object with name ", this->name);
            }
            
            object(const omni::string_t& nm, const omni::callback& ev) : 
                disposing(ev),
                name(nm),
                tag()
            { 
                OMNI_DV5_FW("created omni::object with name ", this->name);
            }
            
            virtual ~object()
            {
                OMNI_TRY_FW
                // Call the disposing event to allow any subscribers to clean up
                if (this->disposing) { this->disposing(); }
                OMNI_CATCH_FW
                OMNI_D5_FW("destroyed");
            }

            virtual omni::string_t to_string_t() const { return this->name; }

            uint64_t type() const { return omni::type_id<omni::object>(); }

            uint64_t hash() const { return reinterpret_cast<uint64_t>(this); }
            
            omni::object& operator=(const omni::object& o)
            {
                if (this != &o) {
                    this->disposing = o.disposing;
                    this->name = o.name;
                    this->tag = o.tag;
                }
                return *this;
            }
            
            bool operator==(const omni::object& o) const
            {
                return (
                    this == &o ||
                    (this->disposing == o.disposing &&
                    this->name == o.name &&
                    this->tag == o.tag)
                );
            }
            
            bool operator!=(const omni::object& o) const
            {
                return !(*this == o);
            }

            /** Called when the instance is being destroyed (destructor is called) */
            omni::action disposing;
            /** A property that allows you to assign a name to this object */
            omni::string_t name;
            /** A property allowing assignment of various objects and types. */
            omni::generic_ptr tag;

            friend std::ostream& operator<<(std::ostream& s, const omni::object& c)
            {
                s << c.name.c_str();
                return s;
            }

            friend std::wostream& operator<<(std::wostream& s, const omni::object& c)
            {
                s << c.name.c_str();
                return s;
            }
            
        protected:
            object(std::string nm) : 
                disposing(),
                name(),
                tag()
            {
                this->name = omni::string::to_string_t(nm);
                // this ctor is only valid for derived types
                OMNI_DV5_FW("created omni::object with name ", this->name);
            }
    };
} // namespace omni

#endif // OMNI_OBJECT_HPP
