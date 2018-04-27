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
#include <omni/chrono/stopwatch.hpp>

omni::stopwatch::stopwatch() :
    OMNI_CTOR_FW(omni::stopwatch)
    m_end(),
    m_init(),
    m_isrun(false),
    m_isstrt(false)
{
    #if !defined(OMNI_CHRONO_AUTO_INIT_TICK)
        omni::chrono::monotonic::initialize();
    #endif
    std::memset(&this->m_init, 0, sizeof(omni::chrono::tick_t));
    std::memset(&this->m_end, 0, sizeof(omni::chrono::tick_t));
    this->m_isrun = false;
    OMNI_D5_FW("created");
}

omni::stopwatch::stopwatch(const omni::stopwatch &cp) :
    OMNI_CPCTOR_FW(cp)
    m_end(),
    m_init(),
    m_isrun(false),
    m_isstrt(false)
{
    #if defined(OMNI_OS_WIN) || defined(OMNI_OS_APPLE)
        this->m_init = cp.m_init;
        this->m_end = cp.m_end;
    #else
        this->m_init.tv_sec = cp.m_init.tv_sec;
        this->m_init.tv_nsec = cp.m_init.tv_nsec;
        this->m_end.tv_sec = cp.m_end.tv_sec;
        this->m_end.tv_nsec = cp.m_end.tv_nsec;
    #endif
    this->m_isrun = cp.m_isrun;
    this->m_isstrt = cp.m_isstrt;
    OMNI_D5_FW("copied");
}

omni::stopwatch::~stopwatch()
{
    OMNI_TRY_FW
    OMNI_DTOR_FW
    OMNI_CATCH_FW
    OMNI_D5_FW("destroyed");
}

// TODO: omni::timespan elapsed();

uint64_t omni::stopwatch::elapsed_us() const
{
    return omni::chrono::elapsed_us(this->m_init,
        (this->m_isrun ? omni::chrono::monotonic_tick() : this->m_end)
    );
}

uint64_t omni::stopwatch::elapsed_ms() const
{
    return omni::chrono::elapsed_ms(this->m_init,
        (this->m_isrun ? omni::chrono::monotonic_tick() : this->m_end)
    );
}

uint64_t omni::stopwatch::elapsed_s() const
{
    return omni::chrono::elapsed_s(this->m_init,
        (this->m_isrun ? omni::chrono::monotonic_tick() : this->m_end)
    );
}

bool omni::stopwatch::is_running() const
{
    return this->m_isrun;
}

omni::stopwatch& omni::stopwatch::reset()
{
    this->stop();
    this->_zero();
    OMNI_D2_FW("reset");
    return *this;
}

omni::stopwatch& omni::stopwatch::restart()
{
    return this->restart(0);
}

omni::stopwatch& omni::stopwatch::restart(unsigned long offset_ms)
{
    this->reset();
    OMNI_D2_FW("restarted");
    return this->start(offset_ms);
}

omni::stopwatch& omni::stopwatch::start()
{
    return this->start(0);
}

omni::stopwatch& omni::stopwatch::start(unsigned long offset_ms)
{
    if (this->m_isrun) {
        // Don't 'start' if we are already running
        OMNI_D2_FW("stopwatch already running");
        return *this;
    }
    if (!this->m_isstrt) {
        omni::chrono::tick_t syst = omni::chrono::monotonic_tick();
        // if the user specifies an offset, we need to adjust the 'syst' var to
        // be as if it were 'behind' by 'offset_ms'
        #if defined(OMNI_OS_WIN) || defined(OMNI_OS_APPLE)
            if (offset_ms > 0) {                        
                #if defined(OMNI_OS_WIN)
                    #if defined(OMNI_WIN_MONO_TICK_QPC)
                        //elapsed_us(init,end) = (((end - init) * 1000000) / freq);
                        // init = end - ((off * freq) / 1000) <-- note: 1000 because of ms
                        this->m_init.QuadPart = syst.QuadPart - ((offset_ms * omni::chrono::monotonic::frequency().QuadPart) / 1000);
                    #else
                        // GetTickCount/GetTickCount64/clock: all represent ms so no adjust needed, just a cast
                        this->m_init = syst - static_cast<omni::chrono::tick_t>(offset_ms);
                    #endif
                #else // OMNI_OS_APPLE
                    this->m_init = syst - static_cast<omni::chrono::tick_t>((offset_ms*1000000));
                #endif
            } else {
                this->m_init = syst;
            }
        #else
            if (offset_ms > 0) {
                if (offset_ms >= 1000) {
                    this->m_init.tv_sec = syst.tv_sec - (offset_ms / 1000);
                } else {
                    this->m_init.tv_sec = syst.tv_sec;
                }
                this->m_init.tv_nsec = syst.tv_nsec - ((offset_ms % 1000)*1000000);
            } else {
                this->m_init.tv_sec = syst.tv_sec;
                this->m_init.tv_nsec = syst.tv_nsec;
            }
        #endif
        this->m_end = this->m_init;
        this->m_isstrt = true;
        #if defined(OMNI_OS_WIN) || defined(OMNI_OS_APPLE)
            #if defined(OMNI_OS_WIN) && defined(OMNI_WIN_MONO_TICK_QPC)
                OMNI_DV2_FW("initial clock = ", this->m_init.QuadPart);
            #else
                OMNI_DV2_FW("initial clock = ", this->m_init);
            #endif
        #else
            OMNI_DV2_FW("initial clock = ", this->m_init.tv_nsec);
        #endif
    }
    this->m_isrun = true;
    return *this;
}

omni::stopwatch& omni::stopwatch::stop()
{
    if (this->m_isrun) {
        this->m_end = omni::chrono::monotonic_tick();
        this->m_isrun = false;
        #if defined(OMNI_OS_WIN) || defined(OMNI_OS_APPLE)
            #if defined(OMNI_OS_WIN) && defined(OMNI_WIN_MONO_TICK_QPC)
                OMNI_DV2_FW("end clock = ", this->m_end.QuadPart);
            #else
                OMNI_DV2_FW("end clock = ", this->m_end);
            #endif
        #else
            OMNI_DV2_FW("end clock = ", this->m_end.tv_nsec);
        #endif
    }
    #if defined(OMNI_DBG_L2)
        else { OMNI_D2_FW("stopwatch not running"); }
    #endif
    return *this;
}

omni::stopwatch& omni::stopwatch::operator=(const omni::stopwatch &other)
{
    if (this != &other) {
        this->stop();
        OMNI_ASSIGN_FW(other)
        this->m_end = other.m_end;
        this->m_init = other.m_init;
        this->m_isrun = other.m_isrun;
        this->m_isstrt = other.m_isstrt;
    }
    return *this;
}

omni::stopwatch& omni::stopwatch::operator=(bool enable)
{
    if (enable) { this->start(); }
    else { this->stop(); }
    return *this;
}

bool omni::stopwatch::operator==(const omni::stopwatch &o) const
{
    if (this == &o) { return true; }
    return (omni::chrono::equal(this->m_init, o.m_init) &&
            omni::chrono::equal(this->m_end, o.m_end) &&
            this->m_isrun == o.m_isrun &&
            this->m_isstrt == o.m_isstrt)
            OMNI_EQUAL_FW(o);
}

bool omni::stopwatch::operator!=(const omni::stopwatch &o) const
{
    return !(*this == o);
}

void omni::stopwatch::_zero()
{
    std::memset(&this->m_init, 0, sizeof(omni::chrono::tick_t));
    this->m_end = this->m_init;
    this->m_isstrt = false;
}
