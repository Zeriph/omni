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
#if !defined(OMNI_PROPERTY_HPP)
#define OMNI_PROPERTY_HPP 1
#include <omni/defs/class_macros.hpp>
#include <omni/delegate/0.hpp>
#include <omni/delegate/1.hpp>
#include <omni/defs/consts.hpp>

// DEV_NOTE: defining OMNI_SAFE_PROP will make all property types thread safe
#if defined(OMNI_SAFE_PROP)
    #include <omni/sync/scoped_lock.hpp>
    #define OMNI_SAFE_PROP_MTX_FW mutable OMNI_MUTEX_T m_mtx;
    #define OMNI_SAFE_PROP_MILST_FW m_mtx(),
    #define OMNI_SAFE_PROP_INIT_FW omni::sync::mutex_init(this->m_mtx);
    #define OMNI_SAFE_PROP_DTOR_FW omni::sync::mutex_destroy(this->m_mtx);
    #define OMNI_SAFE_PROP_LOCK_FW omni::sync::mutex_lock(this->m_mtx);
    #define OMNI_SAFE_PROP_UNLOCK_FW omni::sync::mutex_unlock(this->m_mtx);
    #define OMNI_SAFE_PROP_ALOCK_FW omni::sync::scoped_lock<omni::sync::mutex_t> auto_mtx(&this->m_mtx);
#else
    #define OMNI_SAFE_PROP_MTX_FW
    #define OMNI_SAFE_PROP_MILST_FW
    #define OMNI_SAFE_PROP_INIT_FW
    #define OMNI_SAFE_PROP_DTOR_FW
    #define OMNI_SAFE_PROP_LOCK_FW
    #define OMNI_SAFE_PROP_UNLOCK_FW
    #define OMNI_SAFE_PROP_ALOCK_FW 
#endif

namespace omni {
    // DEV_NOTE:  property == C# public get/set, property_getter == C# public get, property_setter == C# public set

    template < typename T >
    class property
    {
        public:
            typedef T value_t;
            typedef omni::delegate<value_t> get;
            typedef omni::delegate1<void, value_t> set;
            typedef property<value_t> property_t;

            property() : 
                OMNI_CTOR_FW(omni::property<T>)
                OMNI_SAFE_PROP_MILST_FW
                m_get(), m_set(), m_val()
            {
                OMNI_SAFE_PROP_INIT_FW
                this->m_get.template bond_const<property_t, &property_t::_get>(*this);
                this->m_set.template bond<property_t, &property_t::_set>(*this);
            }
            
            property(value_t val) : 
                OMNI_CTOR_FW(omni::property<T>)
                OMNI_SAFE_PROP_MILST_FW
                m_get(), m_set(), m_val(val)
            {
                OMNI_SAFE_PROP_INIT_FW
                this->m_get.template bond_const<property_t, &property_t::_get>(*this);
                this->m_set.template bond<property_t, &property_t::_set>(*this);
            }
            
            property(get gfn) : 
                OMNI_CTOR_FW(omni::property<T>)
                OMNI_SAFE_PROP_MILST_FW
                m_get(gfn), m_set(), m_val()
            {
                OMNI_SAFE_PROP_INIT_FW
                this->m_set.template bond<property_t, &property_t::_set>(*this);
            }
            
            property(set sfn) : 
                OMNI_CTOR_FW(omni::property<T>)
                OMNI_SAFE_PROP_MILST_FW
                m_get(), m_set(sfn), m_val()
            {
                OMNI_SAFE_PROP_INIT_FW
                this->m_get.template bond_const<property_t, &property_t::_get>(*this);
            }
            
            property(get gfn, value_t val) : 
                OMNI_CTOR_FW(omni::property<T>)
                OMNI_SAFE_PROP_MILST_FW
                m_get(gfn), m_set(), m_val(val)
            {
                OMNI_SAFE_PROP_INIT_FW
                this->m_set.template bond<property_t, &property_t::_set>(*this);
            }
            
            property(set sfn, value_t val) : 
                OMNI_CTOR_FW(omni::property<T>)
                OMNI_SAFE_PROP_MILST_FW
                m_get(), m_set(sfn), m_val()
            {
                OMNI_SAFE_PROP_INIT_FW
                this->m_get.template bond_const<property_t, &property_t::_get>(*this);
                this->m_set(val);
            }
            
            property(get gfn, set sfn) : 
                OMNI_CTOR_FW(omni::property<T>)
                OMNI_SAFE_PROP_MILST_FW
                m_get(gfn), m_set(sfn), m_val()
            {
                OMNI_SAFE_PROP_INIT_FW
            }
            
            property(get gfn, set sfn, value_t val) : 
                OMNI_CTOR_FW(omni::property<T>)
                OMNI_SAFE_PROP_MILST_FW
                m_get(gfn), m_set(sfn), m_val()
            {
                OMNI_SAFE_PROP_INIT_FW
                this->m_set(val);
            }
            
            property(const omni::template property<T> &cp) :
                OMNI_CPCTOR_FW(cp)
                OMNI_SAFE_PROP_MILST_FW
                m_get(cp.m_get), m_set(cp.m_set), m_val(cp.m_val)
            {
                OMNI_SAFE_PROP_INIT_FW
            }
            
            ~property()
            {
                OMNI_TRY_FW
                OMNI_DTOR_FW
                OMNI_SAFE_PROP_DTOR_FW
                OMNI_CATCH_FW
            }
            
            void bind_get(get gfn)
            {
                OMNI_SAFE_PROP_ALOCK_FW
                this->m_get = gfn;
            }
            
            void bind_set(set sfn)
            {
                OMNI_SAFE_PROP_ALOCK_FW
                this->m_set = sfn;
            }
            
            /*
                DEV_NOTE: you might get compiler warnings about needing to return a `property<T>&` for
                the post/pre operator overloads (e.g. ++/--), or that we should overload `operator=(property<T>)`,
                but we specifically do not overload the `operator=(property<T>)` so as all rvals to this
                instance _should_ be of `value_t` types. For example, in `property<int> t = 10;` if we
                overloaded `operator=(property<T>)`, the assignment (i.e. `= 10;`) would preform an
                implicit cast to a `property<int>` with the underlying value of 10, which is not what we want.
                
                Instead, by overloading only the operators below, we can treat this `property` type
                like it is underlying type with all other operations preformed.
            */

            // Operators - get (rval)
            operator value_t()         { return this->_vget(); }
            operator value_t() const   { return this->_vget(); }
            value_t operator()()       { return this->_vget(); }
            value_t operator()() const { return this->_vget(); }
            
            // Operators - set (lval)
            value_t operator++() { // pre increment
                value_t tmp = this->_vget();
                this->_vset(++tmp);
                return tmp;
            }
            value_t operator--() { // pre decrement
                value_t tmp = this->_vget();
                this->_vset(--tmp);
                return tmp;
            }
            value_t operator++(int) { // post increment
                value_t tmp = this->_vget();
                value_t t2 = tmp;
                this->_vset(++t2);
                return tmp;
            }
            value_t operator--(int) { // post decrement
                value_t tmp = this->_vget();
                value_t t2 = tmp;
                this->_vset(--t2);
                return tmp;
            }
            property_t& operator=(value_t val) {
                this->_vset(val);
                return *this;
            }
            property_t& operator+=(value_t val) { 
                value_t tmp = this->_vget();
                this->_vset(tmp + val);
                return *this;
            }
            property_t& operator-=(value_t val) {
                value_t tmp = this->_vget();
                this->_vset(tmp - val);
                return *this;
            }
            property_t& operator*=(value_t val) {
                value_t tmp = this->_vget();
                this->_vset(tmp * val);
                return *this;
            }
            property_t& operator/=(value_t val) {
                value_t tmp = this->_vget();
                this->_vset(tmp / val);
                return *this;
            }
            property_t& operator%=(value_t val) {    
                value_t tmp = this->_vget();
                this->_vset(tmp % val);
                return *this;
            }
            property_t& operator&=(value_t val) {
                value_t tmp = this->_vget();
                this->_vset(tmp & val);
                return *this;
            }
            property_t& operator|=(value_t val) {    
                value_t tmp = this->_vget();
                this->_vset(tmp | val);
                return *this;
            }
            property_t& operator^=(value_t val) {    
                value_t tmp = this->_vget();
                this->_vset(tmp ^ val);
                return *this;
            }
            property_t& operator<<=(value_t val) {    
                value_t tmp = this->_vget();
                this->_vset(tmp << val);
                return *this;
            }
            property_t& operator>>=(value_t val) {    
                value_t tmp = this->_vget();
                this->_vset(tmp >> val);
                return *this;
            }

            OMNI_MEMBERS_FW(omni::property<T>) // disposing,name,type(),hash()

        private:
            OMNI_SAFE_PROP_MTX_FW
            get m_get;
            set m_set;
            value_t m_val;

            value_t _vget() const {
                OMNI_SAFE_PROP_ALOCK_FW
                return this->m_get();
            }
            
            void _vset(value_t value) {
                OMNI_SAFE_PROP_ALOCK_FW
                this->m_set(value);
            }
            
            value_t _get() const { return this->m_val; }
            
            void _set(value_t value) { this->m_val = value; }
    };

    template < typename T >
    class property_getter
    {
        public:
            typedef T value_t;
            typedef omni::delegate<value_t> get;
            typedef property_getter<value_t> property_t;

            property_getter() : 
                OMNI_CTOR_FW(omni::property_getter<T>)
                OMNI_SAFE_PROP_MILST_FW
                m_get(), m_val()
            {
                OMNI_SAFE_PROP_INIT_FW
                this->m_get.template bond_const<property_t, &property_t::_get>(*this);
            }
            
            property_getter(value_t val) : 
                OMNI_CTOR_FW(omni::property_getter<T>)
                OMNI_SAFE_PROP_MILST_FW
                m_get(), m_val(val)
            {
                OMNI_SAFE_PROP_INIT_FW
                this->m_get.template bond_const<property_t, &property_t::_get>(*this);
            }
            
            property_getter(get gfn) : 
                OMNI_CTOR_FW(omni::property_getter<T>)
                OMNI_SAFE_PROP_MILST_FW
                m_get(gfn), m_val()
            {
                OMNI_SAFE_PROP_INIT_FW
            }
            
            property_getter(get gfn, value_t val) : 
                OMNI_CTOR_FW(omni::property_getter<T>)
                OMNI_SAFE_PROP_MILST_FW
                m_get(gfn), m_val(val)
            {
                OMNI_SAFE_PROP_INIT_FW
            }
            
            property_getter(const omni::template property_getter<T> &cp) :
                OMNI_CPCTOR_FW(cp)
                OMNI_SAFE_PROP_MILST_FW
                m_get(cp.m_get), m_val(cp.m_val)
            {
                OMNI_SAFE_PROP_INIT_FW
            }
            
            ~property_getter()
            {
                OMNI_TRY_FW
                OMNI_DTOR_FW
                OMNI_SAFE_PROP_DTOR_FW
                OMNI_CATCH_FW
            }
            
            void bind_get(get gfn)
            {
                OMNI_SAFE_PROP_ALOCK_FW
                this->m_get = gfn;
            }
            
            // DEV_NOTE: see additional notes in omni::property<T>

            // Operators - get (rval)
            operator value_t()         { return this->_vget(); }
            operator value_t() const   { return this->_vget(); }
            value_t operator()()       { return this->_vget(); }
            value_t operator()() const { return this->_vget(); }
            
            OMNI_MEMBERS_FW(omni::property_getter<T>) // disposing,name,type(),hash()

        private:
            OMNI_SAFE_PROP_MTX_FW
            get m_get;
            value_t m_val;

            property_t& operator=(property_getter<T>& other); // = delete
            property_t& operator=(value_t other); // = delete

            value_t _vget() const {
                OMNI_SAFE_PROP_ALOCK_FW
                return this->m_get();
            }
            
            value_t _get() const { return this->m_val; }
    };

    template < typename T >
    class property_setter
    {
        public:
            typedef T value_t;
            typedef omni::delegate1<void, value_t> set;
            typedef property_setter<value_t> property_t;

            property_setter() : 
                OMNI_CTOR_FW(omni::property_setter<T>)
                OMNI_SAFE_PROP_MILST_FW
                m_set(), m_val()
            {
                OMNI_SAFE_PROP_INIT_FW
                this->m_set.template bond<property_t, &property_t::_set>(*this);
            }
            
            property_setter(value_t val) : 
                OMNI_CTOR_FW(omni::property_setter<T>)
                OMNI_SAFE_PROP_MILST_FW
                m_set(), m_val(val)
            {
                OMNI_SAFE_PROP_INIT_FW
                this->m_set.template bond<property_t, &property_t::_set>(*this);
            }
            
            property_setter(set sfn) : 
                OMNI_CTOR_FW(omni::property_setter<T>)
                OMNI_SAFE_PROP_MILST_FW
                m_set(sfn), m_val()
            {
                OMNI_SAFE_PROP_INIT_FW
            }
            
            property_setter(set sfn, value_t val) : 
                OMNI_CTOR_FW(omni::property_setter<T>)
                OMNI_SAFE_PROP_MILST_FW
                m_set(sfn), m_val()
            {
                OMNI_SAFE_PROP_INIT_FW
                this->m_set(val);
            }
            
            property_setter(const omni::template property_setter<T> &cp) :
                OMNI_CPCTOR_FW(cp)
                OMNI_SAFE_PROP_MILST_FW
                m_set(cp.m_set), m_val(cp.m_val)
            {
                OMNI_SAFE_PROP_INIT_FW
            }
            
            ~property_setter()
            {
                OMNI_TRY_FW
                OMNI_DTOR_FW
                OMNI_SAFE_PROP_DTOR_FW
                OMNI_CATCH_FW
            }
            
            void bind_set(set sfn)
            {
                OMNI_SAFE_PROP_ALOCK_FW
                this->m_set = sfn;
            }
            
            // DEV_NOTE: see additional notes in omni::property<T>

            // Operators - set (lval)
            value_t operator++() { // pre increment
                OMNI_SAFE_PROP_ALOCK_FW
                value_t tmp = this->m_value;
                this->m_set(++tmp);
                return tmp;
            }
            value_t operator--() { // pre decrement
                OMNI_SAFE_PROP_ALOCK_FW
                value_t tmp = this->m_value;
                this->m_set(--tmp);
                return tmp;
            }
            value_t operator++(int) { // post increment
                OMNI_SAFE_PROP_ALOCK_FW
                value_t tmp = this->m_value;
                value_t t2 = tmp;
                this->m_set(++t2);
                return tmp;
            }
            value_t operator--(int) { // post decrement
                OMNI_SAFE_PROP_ALOCK_FW
                value_t tmp = this->m_value;
                value_t t2 = tmp;
                this->m_set(--t2);
                return tmp;
            }
            property_t& operator=(value_t val) {
                OMNI_SAFE_PROP_ALOCK_FW
                this->m_set(val);
                return *this;
            }
            property_t& operator+=(value_t val) {
                OMNI_SAFE_PROP_ALOCK_FW
                this->m_set(this->m_value + val);
                return *this;
            }
            property_t& operator-=(value_t val) {
                OMNI_SAFE_PROP_ALOCK_FW
                this->m_set(this->m_value - val);
                return *this;
            }
            property_t& operator*=(value_t val) {
                OMNI_SAFE_PROP_ALOCK_FW
                this->m_set(this->m_value * val);
                return *this;
            }
            property_t& operator/=(value_t val) {
                OMNI_SAFE_PROP_ALOCK_FW
                this->m_set(this->m_value / val);
                return *this;
            }
            property_t& operator%=(value_t val) {    
                OMNI_SAFE_PROP_ALOCK_FW
                this->m_set(this->m_value % val);
                return *this;
            }
            property_t& operator&=(value_t val) {
                OMNI_SAFE_PROP_ALOCK_FW
                this->m_set(this->m_value & val);
                return *this;
            }
            property_t& operator|=(value_t val) {
                OMNI_SAFE_PROP_ALOCK_FW
                this->m_set(this->m_value | val);
                return *this;
            }
            property_t& operator^=(value_t val) {
                OMNI_SAFE_PROP_ALOCK_FW
                this->m_set(this->m_value ^ val);
                return *this;
            }
            property_t& operator<<=(value_t val) {
                OMNI_SAFE_PROP_ALOCK_FW
                this->m_set(this->m_value << val);
                return *this;
            }
            property_t& operator>>=(value_t val) {
                OMNI_SAFE_PROP_ALOCK_FW
                this->m_set(this->m_value >> val);
                return *this;
            }

            OMNI_MEMBERS_FW(omni::property_setter<T>) // disposing,name,type(),hash()

        private:            
            OMNI_SAFE_PROP_MTX_FW
            set m_set;
            value_t m_val;

            void _set(value_t value) { this->m_val = value; }
    };
}

#endif // OMNI_PROPERTY_HPP

