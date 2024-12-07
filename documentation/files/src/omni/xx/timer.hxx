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

/* DEV_NOTE: this file is not intended to be used directly by any user code!

 i.e. do not #include <omni/xxx_impl.hxx> and do not compile this source directly.
 this file is included directly in other source. 
*/

// so as not to accidentally build this file with the source
// these macros are defined in chrono
#if !defined(OMNI_TIMER_T_FW) || !defined(OMNI_TMR_ALOCK_FW) || !defined(OMNI_TMR_MLOCK_FW) || !defined(OMNI_TMR_ULOCK_FW)
    #error "invalid preprocessor directive detected"
#endif

#if !defined(OMNI_TIMER_EX_STOP_FW)
    #define OMNI_TIMER_EX_STOP_FW
#endif

#if !defined(OMNI_TIMER_EX_RUN_BEG_FW)
    #define OMNI_TIMER_EX_RUN_BEG_FW
#endif

#if !defined(OMNI_TIMER_EX_RUN_END_FW)
    #define OMNI_TIMER_EX_RUN_END_FW
#endif

omni::chrono::OMNI_TIMER_T_FW::~OMNI_TIMER_T_FW()
{
    OMNI_TRY_FW
    OMNI_DTOR_FW
    this->stop();
    OMNI_CATCH_FW
    OMNI_D5_FW("destroyed");
}

bool omni::chrono::OMNI_TIMER_T_FW::auto_reset() const
{
    OMNI_TMR_ALOCK_FW 
    return OMNI_VAL_HAS_FLAG_BIT(this->m_status, OMNI_TIMER_AUTO_FLAG_FW);
}

uint32_t omni::chrono::OMNI_TIMER_T_FW::interval() const
{
    OMNI_TMR_ALOCK_FW 
    return static_cast<uint32_t>(this->m_int);
}

bool omni::chrono::OMNI_TIMER_T_FW::is_running() const
{
    OMNI_TMR_ALOCK_FW
    return OMNI_VAL_HAS_FLAG_BIT(this->m_status, OMNI_TIMER_RUN_FLAG_FW);
}

void omni::chrono::OMNI_TIMER_T_FW::reset()
{
    this->stop();
    this->start();
}

void omni::chrono::OMNI_TIMER_T_FW::set_auto_reset(bool autoreset)
{
    OMNI_TMR_ALOCK_FW 
    if (autoreset) {
        OMNI_VAL_SET_FLAG_BIT(this->m_status, OMNI_TIMER_AUTO_FLAG_FW);
    } else {
        OMNI_VAL_UNSET_FLAG_BIT(this->m_status, OMNI_TIMER_AUTO_FLAG_FW);
    }
}

void omni::chrono::OMNI_TIMER_T_FW::set_interval(uint32_t ival)
{
    OMNI_TMR_ALOCK_FW 
    this->m_int = ival;
}

void omni::chrono::OMNI_TIMER_T_FW::start()
{
    this->start(0);
}

void omni::chrono::OMNI_TIMER_T_FW::start(uint32_t delay)
{
    if (!this->is_running()) {
        { // error check scope (for auto mutex)
            OMNI_TMR_ALOCK_FW
            if (!this->tick) {
                OMNI_ERR_RET_FW(OMNI_INVALID_DELEGATE_FUNC_STR, omni::exceptions::invalid_delegate())
            }
            if (this->m_int == 0) {
                OMNI_ERRV_RET_FW("Start error: ", OMNI_INDEX_OOR_STR, omni::exceptions::index_out_of_range())
            }
            OMNI_VAL_UNSET_FLAG_BIT(this->m_status, OMNI_TIMER_STOP_FLAG_FW);
        }
        if (delay == 0) {
            this->m_thread = 
                omni::sync::allocate_basic_thread<omni::chrono::OMNI_TIMER_T_FW,
                                                 &omni::chrono::OMNI_TIMER_T_FW::_run>(*this);
        } else {
            this->m_thread =
                omni::sync::allocate_basic_thread_parameterized<
                    omni::chrono::OMNI_TIMER_T_FW,
                    &omni::chrono::OMNI_TIMER_T_FW::_run_delayed>
                    (*this, &delay);
        }
        OMNI_SLEEP_INIT();
        while (!this->is_running()) { OMNI_SLEEP1(); }
    }
    #if defined(OMNI_DBG_L2)
    else { OMNI_D2_FW("The timer is already running"); }
    #endif
}

void omni::chrono::OMNI_TIMER_T_FW::stop()
{
    this->stop(0, true);
}

void omni::chrono::OMNI_TIMER_T_FW::stop(uint32_t join_timeout)
{
    this->stop(join_timeout, true);
}

void omni::chrono::OMNI_TIMER_T_FW::stop(uint32_t join_timeout, bool kill_on_timeout)
{
    if (this->is_running()) {
        OMNI_TMR_MLOCK_FW
        OMNI_VAL_SET_FLAG_BIT(this->m_status, OMNI_TIMER_STOP_FLAG_FW);
        OMNI_TMR_ULOCK_FW
        if (join_timeout == 0) {
            this->m_thread->join();
        } else {
            this->m_thread->join(join_timeout);
            if (kill_on_timeout && this->is_running()) { // still running?
                OMNI_D2_FW("timer still running after stop request, killing thread...");
                this->m_thread->kill();
            }
        }
        OMNI_TIMER_EX_STOP_FW
        OMNI_FREE(this->m_thread);
    }
    #if defined(OMNI_DBG_L2)
    else { OMNI_D2_FW("the timer is not running"); }
    #endif
}

void omni::chrono::OMNI_TIMER_T_FW::_run_delayed(omni::sync::thread_arg_t dly)  // only called if delay > 0
{
    uint32_t delay = *(static_cast<uint32_t*>(dly));
    OMNI_DV1_FW("timer thread: ", omni::sync::thread_id());
    OMNI_D2_FW("waiting to start, delay " << delay << "ms");
    OMNI_TMR_MLOCK_FW
    OMNI_VAL_SET_FLAG_BIT(this->m_status, OMNI_TIMER_RUN_FLAG_FW);
    OMNI_TMR_ULOCK_FW
    OMNI_SLEEP_INIT();
    omni::chrono::tick_t st = omni::chrono::monotonic_tick();
    while (!this->_stopreq() && (omni::chrono::elapsed_ms(st) < delay)) {
        OMNI_SLEEP1();
    }
    this->_do_run();
}

void omni::chrono::OMNI_TIMER_T_FW::_run()
{
    OMNI_DV1_FW("timer thread: ", omni::sync::thread_id());
    OMNI_D2_FW("start timer");
    OMNI_TMR_MLOCK_FW
    OMNI_VAL_SET_FLAG_BIT(this->m_status, OMNI_TIMER_RUN_FLAG_FW);
    OMNI_TMR_ULOCK_FW
    this->_do_run();
}

void omni::chrono::OMNI_TIMER_T_FW::_do_run()
{
    OMNI_TIMER_EX_RUN_BEG_FW
    omni::chrono::tick_t tickt;
    OMNI_SLEEP_INIT();
    omni::chrono::monotonic::initialize();
    do {
        if (this->_stopreq()) { break; }
        tickt = omni::chrono::monotonic_tick();
        while (omni::chrono::elapsed_ms(tickt) < this->interval()) {
                OMNI_SLEEP1();
                if (this->_stopreq()) { break; }
        }
        if (this->_stopreq()) { break; }
        this->_do_tick();
    } while (this->auto_reset());
    OMNI_TIMER_EX_RUN_END_FW
    OMNI_TMR_MLOCK_FW
    OMNI_VAL_UNSET_FLAG_BIT(this->m_status, OMNI_TIMER_RUN_FLAG_FW);
    OMNI_TMR_ULOCK_FW
}

bool omni::chrono::OMNI_TIMER_T_FW::_stopreq() const
{
    OMNI_TMR_ALOCK_FW
    return OMNI_VAL_HAS_FLAG_BIT(this->m_status, OMNI_TIMER_STOP_FLAG_FW);
}

#undef OMNI_TIMER_EX_STOP_FW
#undef OMNI_TIMER_EX_RUN_BEG_FW
#undef OMNI_TIMER_EX_RUN_END_FW
