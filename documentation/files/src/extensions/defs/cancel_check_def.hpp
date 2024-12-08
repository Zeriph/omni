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
#if !defined(OMNI_EXTENSION_CANCEL_CHECK_DEF_HPP)
#define OMNI_EXTENSION_CANCEL_CHECK_DEF_HPP 1

// TODO: (continuous) add any other no-library entities here that do _not_ relate to the safe options

#if defined(OMNI_NO_GUI_EXTENSIONS)
    #if !defined(OMNI_NO_GUI_EXTENSION_USE_X11)
        #define OMNI_NO_GUI_EXTENSION_USE_X11
    #endif
    #if !defined(OMNI_NO_EXTENSION_GUI_LIB)
        #define OMNI_NO_EXTENSION_GUI_LIB
    #endif
    #if !defined(OMNI_NO_GUI_EXTENSION_USE_APP)
        #define OMNI_NO_GUI_EXTENSION_USE_APP
    #endif
#endif
#if defined(OMNI_GUI_EXTENSION_USE_X11) && defined(OMNI_NO_GUI_EXTENSION_USE_X11)
    #undef OMNI_GUI_EXTENSION_USE_X11
#endif
#if defined(OMNI_EXTENSION_GUI_LIB) && defined(OMNI_NO_EXTENSION_GUI_LIB)
    #undef OMNI_EXTENSION_GUI_LIB
#endif
#if defined(OMNI_GUI_EXTENSION_APP) && defined(OMNI_NO_GUI_EXTENSION_USE_APP)
    #undef OMNI_GUI_EXTENSION_APP
#endif

#endif // OMNI_EXTENSION_CANCEL_CHECK_DEF_HPP