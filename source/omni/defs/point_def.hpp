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
#if !defined(OMNI_POINT_DEF_HPP)
#define OMNI_POINT_DEF_HPP 1

#if defined(OMNI_SAFE_POINT2D)
    #include <omni/sync/lock.hpp>
    #include <omni/sync/scoped_lock.hpp>
    #define OMNI_SAFE_P2DMTX_FW  ,m_mtx()
    #define OMNI_SAFE_P2LOCK_FW   this->m_mtx.lock();
    #define OMNI_SAFE_P2UNLOCK_FW this->m_mtx.unlock();
    #define OMNI_SAFE_P2ALOCK_FW  omni::sync::scoped_basic_lock uuid12345(&this->m_mtx);
    #define OMNI_SAFE_P2OALOCK_FW(o)  omni::sync::scoped_basic_lock uuid54321(&o.m_mtx);
#else
    #define OMNI_SAFE_P2DMTX_FW
    #define OMNI_SAFE_P2LOCK_FW
    #define OMNI_SAFE_P2UNLOCK_FW
    #define OMNI_SAFE_P2ALOCK_FW
    #define OMNI_SAFE_P2OALOCK_FW(o) 
#endif

#if defined(OMNI_SAFE_POINT3D)
    #include <omni/sync/lock.hpp>
    #include <omni/sync/scoped_lock.hpp>
    #define OMNI_SAFE_P3DMTX_FW  ,m_mtx()
    #define OMNI_SAFE_P3LOCK_FW   this->m_mtx.lock();
    #define OMNI_SAFE_P3UNLOCK_FW this->m_mtx.unlock();
    #define OMNI_SAFE_P3ALOCK_FW  omni::sync::scoped_basic_lock uuid12345(&this->m_mtx);
    #define OMNI_SAFE_P3OALOCK_FW(o)  omni::sync::scoped_basic_lock uuid54321(&o.m_mtx);
#else
    #define OMNI_SAFE_P3DMTX_FW
    #define OMNI_SAFE_P3LOCK_FW
    #define OMNI_SAFE_P3UNLOCK_FW
    #define OMNI_SAFE_P3ALOCK_FW
    #define OMNI_SAFE_P3OALOCK_FW(o) 
#endif

#if defined(OMNI_SAFE_GEO_SIZE)
    #include <omni/sync/lock.hpp>
    #include <omni/sync/scoped_lock.hpp>
    #define OMNI_SAFE_GSZDMTX_FW  ,m_mtx()
    #define OMNI_SAFE_GSZLOCK_FW   this->m_mtx.lock();
    #define OMNI_SAFE_GSZUNLOCK_FW this->m_mtx.unlock();
    #define OMNI_SAFE_GSZALOCK_FW  omni::sync::scoped_basic_lock uuid12345(&this->m_mtx);
    #define OMNI_SAFE_GSZOALOCK_FW(o)  omni::sync::scoped_basic_lock uuid54321(&o.m_mtx);
#else
    #define OMNI_SAFE_GSZDMTX_FW
    #define OMNI_SAFE_GSZLOCK_FW
    #define OMNI_SAFE_GSZUNLOCK_FW
    #define OMNI_SAFE_GSZALOCK_FW 
    #define OMNI_SAFE_GSZOALOCK_FW(o) 
#endif

#if defined(OMNI_SAFE_RECTANGLE)
    #include <omni/sync/lock.hpp>
    #include <omni/sync/scoped_lock.hpp>
    #define OMNI_SAFE_RECTMTX_FW  ,m_mtx()
    #define OMNI_SAFE_RECTLOCK_FW   this->m_mtx.lock();
    #define OMNI_SAFE_RECTUNLOCK_FW this->m_mtx.unlock();
    #define OMNI_SAFE_RECTALOCK_FW  omni::sync::scoped_basic_lock uuid12345(&this->m_mtx);
    #define OMNI_SAFE_RECTOALOCK_FW(o)  omni::sync::scoped_basic_lock uuid54321(&o.m_mtx);
#else
    #define OMNI_SAFE_RECTMTX_FW
    #define OMNI_SAFE_RECTLOCK_FW
    #define OMNI_SAFE_RECTUNLOCK_FW
    #define OMNI_SAFE_RECTALOCK_FW
    #define OMNI_SAFE_RECTOALOCK_FW(o) 
#endif

#endif // OMNI_POINT_DEF_HPP