/*
 * Copyright (c) 2017, Zeriph Enterprises
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * - Neither the name of Zeriph, Zeriph Enterprises, LLC, nor the names
 *   of its contributors may be used to endorse or promote products
 *   derived from this software without specific prior written permission.
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
            
            // Operators - get (rval)
            operator value_t()         { return this->_vget(); }
            operator value_t() const   { return this->_vget(); }
            value_t operator()()       { return this->_vget(); }
            value_t operator()() const { return this->_vget(); }
            
            /* DEV_NOTE: you might get compiler warnings about property<T> need return 
            property<T>& for ++/-- post/pre inc/dec, or that we 'should' overload 'operator=', but
            note that we specifically don't overload the operator=(property_t) so as all rval's
            to this instance 'should' be of 'value_t' types, example:
            
            // overloading the operator= here would give us an implicit cast to a property<int>
            property<int> t = 10;
            int i = t--;
            // here i == 10 and t == 9
            int x = --t;
            // here both x and t == 8 */
            
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
            
            #if defined(OMNI_TYPE_INFO)
                omni::type< omni::property<T> > m_type;
            #endif
            OMNI_SAFE_PROP_MTX_FW
            /** The 'get' functor. Used to attach to a user defined or default 'get' function */
            get m_get;
            /** The 'set' functor. Used to attach to a user defined or default 'set' function */
            set m_set;
            /** The underlying m_val */
            value_t m_val;
    };
}

#endif // OMNI_PROPERTY_HPP

