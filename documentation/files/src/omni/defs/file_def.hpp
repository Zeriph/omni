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
#if !defined(OMNI_FILE_DEF_HPP)
#define OMNI_FILE_DEF_HPP 1

#include <sys/stat.h>
#include <sys/types.h>
#if defined(OMNI_OS_WIN)
    #include <windows.h>
#else
    #include <dirent.h> // for *Nix directory access
    #include <unistd.h>
    #include <sys/time.h>
    #include <fcntl.h>
#endif
#include <cstdarg>

#if defined(OMNI_OS_WIN)
    // Because we are using Windows we need to convert the name to 8.3 format otherwise, it is possible to get
    // an INVALID_HANDLE_VALUE returned from a valid file. 
    // Example: _C:\Develop\C++\file.txt_ could exist and there is nothing in the name more than 8 characters
    // long, but because the folder _C++_ has invalid 8.3 characters in it, it will fail. _C++_ in 8.3 format is _C__~1_
    // CreateFile also needs a _\\?\_ in front of the file to open an actual file handle (_\\.\_ for a device)    
    #define OMNI_FILE_CHECKA_FW(file, ret) if (file.length() > MAX_PATH) { OMNI_ERRV_RETV_FW("file name exceeds maximum path length: ", MAX_PATH, omni::exceptions::path_exception(omni::string::to_string(file)), ret) }
    #define OMNI_FILE_CHECKW_FW(tf, file, ret) file; \
            if (tf.length() > 4 && tf.substr(0, 4) != L"\\\\?\\") { tf = std::wstring(L"\\\\?\\") + tf; } \
            if (tf.length() >= OMNI_MAX_PATH_FW) { OMNI_ERRV_RETV_FW("file name exceeds maximum path length: ", OMNI_MAX_PATH_FW, omni::exceptions::path_exception(omni::string::to_string(file)), ret) }
#endif

#if !defined(OMNI_IO_FILE_TRUNCATE_FN)
    #define OMNI_IO_FILE_TRUNCATE_FN ::truncate
#endif
#if !defined(OMNI_IO_FILE_FTRUNCATE_FN)
    #define OMNI_IO_FILE_FTRUNCATE_FN ::ftruncate
#endif

#if !defined(OMNI_IO_FILE_COPY_BUFSZ)
    #define OMNI_IO_FILE_COPY_BUFSZ 4096
#endif

#endif // OMNI_FILE_DEF_HPP
