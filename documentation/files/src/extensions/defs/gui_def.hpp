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
#if !defined(OMNI_EXTENSION_GUI_DEF_HPP)
#define OMNI_EXTENSION_GUI_DEF_HPP 1
#include <omni/defs/global.hpp>

#if defined(OMNI_EXTENSION_GUI_LIB) || defined(OMNI_GUI_EXTENSION_APP)
    #if defined(OMNI_OS_WIN)
        #pragma comment(lib, "user32.lib")
    #else
        #if defined(OMNI_OS_APPLE) && !defined(OMNI_GUI_USE_X11)
            #import <Cocoa/Cocoa.h>
        #else
            #include <X11/Xlib.h>
            #include <unistd.h>
        #endif
    #endif
#endif

#endif // OMNI_EXTENSION_GUI_DEF_HPP
