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


/*
    The purpose of this file is to compile the additional "extensions" to Omni,
    such as the GUI/windowing or additional networking code.
*/ 

#if !defined(OMNI_NO_SINGLE_EXTENSION_FILE)

#include "extensions.hpp"

#if !defined(OMNI_EXTENSION_NET_LIB) && !defined(OMNI_NO_EXTENSION_NET_LIB)
    #define OMNI_EXTENSION_NET_LIB
#endif

#if !defined(OMNI_EXTENSION_GUI_LIB) && !defined(OMNI_NO_EXTENSION_GUI_LIB)
    #define OMNI_EXTENSION_GUI_LIB
#endif

#if defined(OMNI_EXTENSION_NET_LIB)
    #include "source/net_server.cpp"
    #include "source/net_client.cpp"
    #include "source/net_util.cpp"
#endif

#if defined(OMNI_EXTENSION_GUI_LIB)
    #include "source/gui_window.cpp"
    // #include "source/gui_app.cpp"
#endif

#endif
