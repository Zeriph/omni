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
#if !defined(OMNI_DELEGATE_COMMON_HPP)
#define OMNI_DELEGATE_COMMON_HPP 1
#include <omni/defs/global.hpp>
#if defined(OMNI_SAFE_EVENTS) || defined(OMNI_SAFE_DELEGATES)
    #include <omni/sync/scoped_lock.hpp>
#endif
#if defined(OMNI_SAFE_EVENTS)
    #define OMNI_SAFE_EVENT_MTX_FW mutable OMNI_MUTEX_T m_mtx;
    #define OMNI_SAFE_EVENT_MILST_FW m_mtx(),
    #define OMNI_SAFE_EVENT_INIT_FW omni::sync::mutex_init(this->m_mtx);
    #define OMNI_SAFE_EVENT_DTOR_FW omni::sync::mutex_destroy(this->m_mtx);
    #define OMNI_SAFE_EVENT_LOCK_FW omni::sync::mutex_lock(this->m_mtx);
    #define OMNI_SAFE_EVENT_UNLOCK_FW omni::sync::mutex_unlock(this->m_mtx);
    #define OMNI_SAFE_EVENT_ALOCK_FW omni::sync::scoped_lock<omni::sync::mutex_t> auto_mtx(&this->m_mtx);
#else
    #define OMNI_SAFE_EVENT_MTX_FW
    #define OMNI_SAFE_EVENT_MILST_FW
    #define OMNI_SAFE_EVENT_INIT_FW
    #define OMNI_SAFE_EVENT_DTOR_FW
    #define OMNI_SAFE_EVENT_LOCK_FW
    #define OMNI_SAFE_EVENT_UNLOCK_FW
    #define OMNI_SAFE_EVENT_ALOCK_FW 
#endif
#if defined(OMNI_SAFE_DELEGATES)
    #define OMNI_SAFE_DGATE_MTX_FW mutable OMNI_MUTEX_T m_mtx;
    #define OMNI_SAFE_DGATE_MILST_FW m_mtx(),
    #define OMNI_SAFE_DGATE_INIT_FW omni::sync::mutex_init(this->m_mtx);
    #define OMNI_SAFE_DGATE_DTOR_FW omni::sync::mutex_destroy(this->m_mtx);
    #define OMNI_SAFE_DGATE_LOCK_FW omni::sync::mutex_lock(this->m_mtx);
    #define OMNI_SAFE_DGATE_UNLOCK_FW omni::sync::mutex_unlock(this->m_mtx);
    #define OMNI_SAFE_DGATE_ALOCK_FW omni::sync::scoped_lock<omni::sync::mutex_t> auto_mtx(&this->m_mtx);
#else
    #define OMNI_SAFE_DGATE_MTX_FW
    #define OMNI_SAFE_DGATE_MILST_FW
    #define OMNI_SAFE_DGATE_INIT_FW
    #define OMNI_SAFE_DGATE_DTOR_FW
    #define OMNI_SAFE_DGATE_LOCK_FW
    #define OMNI_SAFE_DGATE_UNLOCK_FW
    #define OMNI_SAFE_DGATE_ALOCK_FW 
#endif
#include <string>
#include <iterator>
#include <omni/sequence.hpp>

#endif // OMNI_DELEGATE_COMMON_HPP
