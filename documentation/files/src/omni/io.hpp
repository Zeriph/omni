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
#if !defined(OMNI_IO_HPP)
#define OMNI_IO_HPP 1

#include <omni/defs/global.hpp>
#include <omni/strings.hpp>
#include <omni/string/util.hpp>
#include <omni/types/fstream_t.hpp>
#include <omni/sequence.hpp>
#include <omni/stack_buffer.hpp>

// TODO: make note in the docs for these that the wchar_t functions that specify a buffer size are _not_
// sizeof but the actual buffer size, for example:
// wchar_t buf[256] -> sizeof(buf) == sizeof(wchar_t) * 256, so buffer_length should be 256 (or sizeof(buf)/sizeof(wchar_t))

namespace omni {
    namespace io {
        namespace cfile {
            bool copy(const std::string& file, const std::string& new_name, bool overwrite);
            bool copy(const std::string& file, const std::string& new_name);
            bool create(const std::string& file, bool create_path);
            bool create(const std::string& file);
            bool exists(const std::string& file);
            bool exist(const std::string& file);
            std::string get_contents(const std::string& file);
            uint64_t get_size(const std::string& file);
            bool move(const std::string& file, const std::string& new_name, bool create_path);
            bool move(const std::string& file, const std::string& new_name);
            bool rename(const std::string& file, const std::string& new_name, bool create_path);
            bool rename(const std::string& file, const std::string& new_name);
            

            // TODO: omni::seq::XX functions needs to have the template < template < class, class >, allocator > stuff
            uint64_t read(const std::string& file, omni::seq::char_t& buffer);
            uint64_t read(const std::string& file, omni::seq::wide_char_t& buffer);
            uint64_t read(const std::string& file, omni::seq::uint8_t& buffer);
            uint64_t read(const std::string& file, omni::seq::int8_t& buffer);
            // TODO: add the following for read/write
            // template < typename T, uint16_t SZ>
            // uint64_t read(const std::string& file, omni::stack_buffer<T, SZ>& buffer);


            uint64_t read(const std::string& file, std::string& buffer);
            uint64_t unsafe_read(const std::string& file, char* buffer, uint64_t length);
            uint64_t unsafe_read(const std::string& file, wchar_t* buffer, uint64_t length);
            uint64_t unsafe_read(const std::string& file, uint8_t* buffer, uint64_t length);
            uint64_t unsafe_read(const std::string& file, int8_t* buffer, uint64_t length);
            bool remove(const std::string& file);
            #if defined(OMNI_NON_PORTABLE)
                bool set_size(const std::string& file, uint64_t size);
            #endif
            uint64_t write(const std::string& file, const omni::seq::char_t& buffer, bool append);
            uint64_t write(const std::string& file, const omni::seq::wide_char_t& buffer, bool append);
            uint64_t write(const std::string& file, const omni::seq::uint8_t& buffer, bool append);
            uint64_t write(const std::string& file, const omni::seq::int8_t& buffer, bool append);
            uint64_t write(const std::string& file, const std::string& buffer, bool append);
            uint64_t unsafe_write(const std::string& file, const char* buffer, uint64_t length, bool append);
            uint64_t unsafe_write(const std::string& file, const wchar_t* buffer, uint64_t length, bool append);
            uint64_t unsafe_write(const std::string& file, const uint8_t* buffer, uint64_t length, bool append);
            uint64_t unsafe_write(const std::string& file, const int8_t* buffer, uint64_t length, bool append);
            uint64_t write_line(const std::string& file, const omni::seq::char_t& buffer, bool append);
            uint64_t write_line(const std::string& file, const omni::seq::wide_char_t& buffer, bool append);
            uint64_t write_line(const std::string& file, const omni::seq::uint8_t& buffer, bool append);
            uint64_t write_line(const std::string& file, const omni::seq::int8_t& buffer, bool append);
            uint64_t write_line(const std::string& file, const std::string& buffer, bool append);
            uint64_t unsafe_write_line(const std::string& file, const char* buffer, uint64_t length, bool append);
            uint64_t unsafe_write_line(const std::string& file, const wchar_t* buffer, uint64_t length, bool append);
            uint64_t unsafe_write_line(const std::string& file, const uint8_t* buffer, uint64_t length, bool append);
            uint64_t unsafe_write_line(const std::string& file, const int8_t* buffer, uint64_t length, bool append);
            uint64_t write(const std::string& file, const omni::seq::char_t& buffer);
            uint64_t write(const std::string& file, const omni::seq::wide_char_t& buffer);
            uint64_t write(const std::string& file, const omni::seq::uint8_t& buffer);
            uint64_t write(const std::string& file, const omni::seq::int8_t& buffer);
            uint64_t write(const std::string& file, const std::string& buffer);
            uint64_t unsafe_write(const std::string& file, const char* buffer, uint64_t length);
            uint64_t unsafe_write(const std::string& file, const wchar_t* buffer, uint64_t length);
            uint64_t unsafe_write(const std::string& file, const uint8_t* buffer, uint64_t length);
            uint64_t unsafe_write(const std::string& file, const int8_t* buffer, uint64_t length);
            uint64_t write_line(const std::string& file, const omni::seq::char_t& buffer);
            uint64_t write_line(const std::string& file, const omni::seq::wide_char_t& buffer);
            uint64_t write_line(const std::string& file, const omni::seq::uint8_t& buffer);
            uint64_t write_line(const std::string& file, const omni::seq::int8_t& buffer);
            uint64_t write_line(const std::string& file, const std::string& buffer);
            uint64_t unsafe_write_line(const std::string& file, const char* buffer, uint64_t length);
            uint64_t unsafe_write_line(const std::string& file, const wchar_t* buffer, uint64_t length);
            uint64_t unsafe_write_line(const std::string& file, const uint8_t* buffer, uint64_t length);
            uint64_t unsafe_write_line(const std::string& file, const int8_t* buffer, uint64_t length);
        }
        namespace wfile {
            bool copy(const std::wstring& file, const std::wstring& new_name, bool overwrite);
            bool copy(const std::wstring& file, const std::wstring& new_name);
            bool create(const std::wstring& file, bool create_path);
            bool create(const std::wstring& file);
            bool exists(const std::wstring& file);
            bool exist(const std::wstring& file);
            std::wstring get_contents(const std::wstring& file);
            uint64_t get_size(const std::wstring& file);
            bool move(const std::wstring& file, const std::wstring& new_name, bool create_path);
            bool move(const std::wstring& file, const std::wstring& new_name);
            bool rename(const std::wstring& file, const std::wstring& new_name, bool create_path);
            bool rename(const std::wstring& file, const std::wstring& new_name);
            uint64_t read(const std::wstring& file, omni::seq::char_t& buffer);
            uint64_t read(const std::wstring& file, omni::seq::wide_char_t& buffer);
            uint64_t read(const std::wstring& file, omni::seq::uint8_t& buffer);
            uint64_t read(const std::wstring& file, omni::seq::int8_t& buffer);
            uint64_t read(const std::wstring& file, std::wstring& buffer);
            uint64_t unsafe_read(const std::wstring& file, char* buffer, uint64_t length);
            uint64_t unsafe_read(const std::wstring& file, wchar_t* buffer, uint64_t length);
            uint64_t unsafe_read(const std::wstring& file, uint8_t* buffer, uint64_t length);
            uint64_t unsafe_read(const std::wstring& file, int8_t* buffer, uint64_t length);
            bool remove(const std::wstring& file);
            #if defined(OMNI_NON_PORTABLE)
                bool set_size(const std::wstring& file, uint64_t size);
            #endif
            uint64_t write(const std::wstring& file, const omni::seq::char_t& buffer, bool append);
            uint64_t write(const std::wstring& file, const omni::seq::wide_char_t& buffer, bool append);
            uint64_t write(const std::wstring& file, const omni::seq::uint8_t& buffer, bool append);
            uint64_t write(const std::wstring& file, const omni::seq::int8_t& buffer, bool append);
            uint64_t write(const std::wstring& file, const std::wstring& buffer, bool append);
            uint64_t unsafe_write(const std::wstring& file, const char* buffer, uint64_t length, bool append);
            uint64_t unsafe_write(const std::wstring& file, const wchar_t* buffer, uint64_t length, bool append);
            uint64_t unsafe_write(const std::wstring& file, const uint8_t* buffer, uint64_t length, bool append);
            uint64_t unsafe_write(const std::wstring& file, const int8_t* buffer, uint64_t length, bool append);
            uint64_t write_line(const std::wstring& file, const omni::seq::char_t& buffer, bool append);
            uint64_t write_line(const std::wstring& file, const omni::seq::wide_char_t& buffer, bool append);
            uint64_t write_line(const std::wstring& file, const omni::seq::uint8_t& buffer, bool append);
            uint64_t write_line(const std::wstring& file, const omni::seq::int8_t& buffer, bool append);
            uint64_t write_line(const std::wstring& file, const std::wstring& buffer, bool append);
            uint64_t unsafe_write_line(const std::wstring& file, const char* buffer, uint64_t length, bool append);
            uint64_t unsafe_write_line(const std::wstring& file, const wchar_t* buffer, uint64_t length, bool append);
            uint64_t unsafe_write_line(const std::wstring& file, const uint8_t* buffer, uint64_t length, bool append);
            uint64_t unsafe_write_line(const std::wstring& file, const int8_t* buffer, uint64_t length, bool append);
            uint64_t write(const std::wstring& file, const omni::seq::char_t& buffer);
            uint64_t write(const std::wstring& file, const omni::seq::wide_char_t& buffer);
            uint64_t write(const std::wstring& file, const omni::seq::uint8_t& buffer);
            uint64_t write(const std::wstring& file, const omni::seq::int8_t& buffer);
            uint64_t write(const std::wstring& file, const std::wstring& buffer);
            uint64_t unsafe_write(const std::wstring& file, const char* buffer, uint64_t length);
            uint64_t unsafe_write(const std::wstring& file, const wchar_t* buffer, uint64_t length);
            uint64_t unsafe_write(const std::wstring& file, const uint8_t* buffer, uint64_t length);
            uint64_t unsafe_write(const std::wstring& file, const int8_t* buffer, uint64_t length);
            uint64_t write_line(const std::wstring& file, const omni::seq::char_t& buffer);
            uint64_t write_line(const std::wstring& file, const omni::seq::wide_char_t& buffer);
            uint64_t write_line(const std::wstring& file, const omni::seq::uint8_t& buffer);
            uint64_t write_line(const std::wstring& file, const omni::seq::int8_t& buffer);
            uint64_t write_line(const std::wstring& file, const std::wstring& buffer);
            uint64_t unsafe_write_line(const std::wstring& file, const char* buffer, uint64_t length);
            uint64_t unsafe_write_line(const std::wstring& file, const wchar_t* buffer, uint64_t length);
            uint64_t unsafe_write_line(const std::wstring& file, const uint8_t* buffer, uint64_t length);
            uint64_t unsafe_write_line(const std::wstring& file, const int8_t* buffer, uint64_t length);
        }
        namespace file {
            // std::string
            inline bool copy(const std::string& file, const std::string& new_name, bool overwrite) { return omni::io::cfile::copy(file, new_name, overwrite); }
            inline bool copy(const std::string& file, const std::string& new_name) { return omni::io::cfile::copy(file, new_name); }
            inline bool create(const std::string& file, bool create_path) { return omni::io::cfile::create(file, create_path); }
            inline bool create(const std::string& file) { return omni::io::cfile::create(file); }
            inline bool exists(const std::string& file) { return omni::io::cfile::exists(file); }
            inline bool exist(const std::string& file) { return omni::io::cfile::exist(file); }
            inline std::string get_contents(const std::string& file) { return omni::io::cfile::get_contents(file); }
            inline uint64_t get_size(const std::string& file) { return omni::io::cfile::get_size(file); }
            inline bool move(const std::string& file, const std::string& new_name, bool create_path) { return omni::io::cfile::move(file, new_name, create_path); }
            inline bool move(const std::string& file, const std::string& new_name) { return omni::io::cfile::move(file, new_name); }
            inline bool rename(const std::string& file, const std::string& new_name, bool create_path) { return omni::io::cfile::rename(file, new_name, create_path); }
            inline bool rename(const std::string& file, const std::string& new_name) { return omni::io::cfile::rename(file, new_name); }
            inline uint64_t read(const std::string& file, omni::seq::char_t& buffer) { return omni::io::cfile::read(file, buffer); }
            inline uint64_t read(const std::string& file, omni::seq::wide_char_t& buffer) { return omni::io::cfile::read(file, buffer); }
            inline uint64_t read(const std::string& file, omni::seq::uint8_t& buffer) { return omni::io::cfile::read(file, buffer); }
            inline uint64_t read(const std::string& file, omni::seq::int8_t& buffer) { return omni::io::cfile::read(file, buffer); }
            inline uint64_t read(const std::string& file, std::string& buffer) { return omni::io::cfile::read(file, buffer); }
            inline uint64_t unsafe_read(const std::string& file, char* buffer, uint64_t length) { return omni::io::cfile::unsafe_read(file, buffer, length); }
            inline uint64_t unsafe_read(const std::string& file, wchar_t* buffer, uint64_t length) { return omni::io::cfile::unsafe_read(file, buffer, length); }
            inline uint64_t unsafe_read(const std::string& file, uint8_t* buffer, uint64_t length) { return omni::io::cfile::unsafe_read(file, buffer, length); }
            inline uint64_t unsafe_read(const std::string& file, int8_t* buffer, uint64_t length) { return omni::io::cfile::unsafe_read(file, buffer, length); }
            inline bool remove(const std::string& file) { return omni::io::cfile::remove(file); }
            #if defined(OMNI_NON_PORTABLE)
                inline bool set_size(const std::string& file, uint64_t size) { return omni::io::cfile::set_size(file, size); }
            #endif
            inline uint64_t write(const std::string& file, const omni::seq::char_t& buffer, bool append) { return omni::io::cfile::write(file, buffer, append); }
            inline uint64_t write(const std::string& file, const omni::seq::wide_char_t& buffer, bool append) { return omni::io::cfile::write(file, buffer, append); }
            inline uint64_t write(const std::string& file, const omni::seq::uint8_t& buffer, bool append) { return omni::io::cfile::write(file, buffer, append); }
            inline uint64_t write(const std::string& file, const omni::seq::int8_t& buffer, bool append) { return omni::io::cfile::write(file, buffer, append); }
            inline uint64_t write(const std::string& file, const std::string& buffer, bool append) { return omni::io::cfile::write(file, buffer, append); }
            inline uint64_t unsafe_write(const std::string& file, const char* buffer, uint64_t length, bool append) { return omni::io::cfile::unsafe_write(file, buffer, length, append); }
            inline uint64_t unsafe_write(const std::string& file, const wchar_t* buffer, uint64_t length, bool append) { return omni::io::cfile::unsafe_write(file, buffer, length, append); }
            inline uint64_t unsafe_write(const std::string& file, const uint8_t* buffer, uint64_t length, bool append) { return omni::io::cfile::unsafe_write(file, buffer, length, append); }
            inline uint64_t unsafe_write(const std::string& file, const int8_t* buffer, uint64_t length, bool append) { return omni::io::cfile::unsafe_write(file, buffer, length, append); }
            inline uint64_t write_line(const std::string& file, const omni::seq::char_t& buffer, bool append) { return omni::io::cfile::write_line(file, buffer, append); }
            inline uint64_t write_line(const std::string& file, const omni::seq::wide_char_t& buffer, bool append) { return omni::io::cfile::write_line(file, buffer, append); }
            inline uint64_t write_line(const std::string& file, const omni::seq::uint8_t& buffer, bool append) { return omni::io::cfile::write_line(file, buffer, append); }
            inline uint64_t write_line(const std::string& file, const omni::seq::int8_t& buffer, bool append) { return omni::io::cfile::write_line(file, buffer, append); }
            inline uint64_t write_line(const std::string& file, const std::string& buffer, bool append) { return omni::io::cfile::write_line(file, buffer, append); }
            inline uint64_t unsafe_write_line(const std::string& file, const char* buffer, uint64_t length, bool append) { return omni::io::cfile::unsafe_write_line(file, buffer, length, append); }
            inline uint64_t unsafe_write_line(const std::string& file, const wchar_t* buffer, uint64_t length, bool append) { return omni::io::cfile::unsafe_write_line(file, buffer, length, append); }
            inline uint64_t unsafe_write_line(const std::string& file, const uint8_t* buffer, uint64_t length, bool append) { return omni::io::cfile::unsafe_write_line(file, buffer, length, append); }
            inline uint64_t unsafe_write_line(const std::string& file, const int8_t* buffer, uint64_t length, bool append) { return omni::io::cfile::unsafe_write_line(file, buffer, length, append); }
            inline uint64_t write(const std::string& file, const omni::seq::char_t& buffer) { return omni::io::cfile::write(file, buffer); }
            inline uint64_t write(const std::string& file, const omni::seq::wide_char_t& buffer) { return omni::io::cfile::write(file, buffer); }
            inline uint64_t write(const std::string& file, const omni::seq::uint8_t& buffer) { return omni::io::cfile::write(file, buffer); }
            inline uint64_t write(const std::string& file, const omni::seq::int8_t& buffer) { return omni::io::cfile::write(file, buffer); }
            inline uint64_t write(const std::string& file, const std::string& buffer) { return omni::io::cfile::write(file, buffer); }
            inline uint64_t unsafe_write(const std::string& file, const char* buffer, uint64_t length) { return omni::io::cfile::unsafe_write(file, buffer, length); }
            inline uint64_t unsafe_write(const std::string& file, const wchar_t* buffer, uint64_t length) { return omni::io::cfile::unsafe_write(file, buffer, length); }
            inline uint64_t unsafe_write(const std::string& file, const uint8_t* buffer, uint64_t length) { return omni::io::cfile::unsafe_write(file, buffer, length); }
            inline uint64_t unsafe_write(const std::string& file, const int8_t* buffer, uint64_t length) { return omni::io::cfile::unsafe_write(file, buffer, length); }
            inline uint64_t write_line(const std::string& file, const omni::seq::char_t& buffer) { return omni::io::cfile::write_line(file, buffer); }
            inline uint64_t write_line(const std::string& file, const omni::seq::wide_char_t& buffer) { return omni::io::cfile::write_line(file, buffer); }
            inline uint64_t write_line(const std::string& file, const omni::seq::uint8_t& buffer) { return omni::io::cfile::write_line(file, buffer); }
            inline uint64_t write_line(const std::string& file, const omni::seq::int8_t& buffer) { return omni::io::cfile::write_line(file, buffer); }
            inline uint64_t write_line(const std::string& file, const std::string& buffer) { return omni::io::cfile::write_line(file, buffer); }
            inline uint64_t unsafe_write_line(const std::string& file, const char* buffer, uint64_t length) { return omni::io::cfile::unsafe_write_line(file, buffer, length); }
            inline uint64_t unsafe_write_line(const std::string& file, const wchar_t* buffer, uint64_t length) { return omni::io::cfile::unsafe_write_line(file, buffer, length); }
            inline uint64_t unsafe_write_line(const std::string& file, const uint8_t* buffer, uint64_t length) { return omni::io::cfile::unsafe_write_line(file, buffer, length); }
            inline uint64_t unsafe_write_line(const std::string& file, const int8_t* buffer, uint64_t length) { return omni::io::cfile::unsafe_write_line(file, buffer, length); }
            
            // std::wstring
            inline bool copy(const std::wstring& file, const std::wstring& new_name, bool overwrite) { return omni::io::wfile::copy(file, new_name, overwrite); }
            inline bool copy(const std::wstring& file, const std::wstring& new_name) { return omni::io::wfile::copy(file, new_name); }
            inline bool create(const std::wstring& file, bool create_path) { return omni::io::wfile::create(file, create_path); }
            inline bool create(const std::wstring& file) { return omni::io::wfile::create(file); }
            inline bool exists(const std::wstring& file) { return omni::io::wfile::exists(file); }
            inline bool exist(const std::wstring& file) { return omni::io::wfile::exist(file); }
            inline std::wstring get_contents(const std::wstring& file) { return omni::io::wfile::get_contents(file); }
            inline uint64_t get_size(const std::wstring& file) { return omni::io::wfile::get_size(file); }
            inline bool move(const std::wstring& file, const std::wstring& new_name, bool create_path) { return omni::io::wfile::move(file, new_name, create_path); }
            inline bool move(const std::wstring& file, const std::wstring& new_name) { return omni::io::wfile::move(file, new_name); }
            inline bool rename(const std::wstring& file, const std::wstring& new_name, bool create_path) { return omni::io::wfile::rename(file, new_name, create_path); }
            inline bool rename(const std::wstring& file, const std::wstring& new_name) { return omni::io::wfile::rename(file, new_name); }
            inline uint64_t read(const std::wstring& file, omni::seq::char_t& buffer) { return omni::io::wfile::read(file, buffer); }
            inline uint64_t read(const std::wstring& file, omni::seq::wide_char_t& buffer) { return omni::io::wfile::read(file, buffer); }
            inline uint64_t read(const std::wstring& file, omni::seq::uint8_t& buffer) { return omni::io::wfile::read(file, buffer); }
            inline uint64_t read(const std::wstring& file, omni::seq::int8_t& buffer) { return omni::io::wfile::read(file, buffer); }
            inline uint64_t read(const std::wstring& file, std::wstring& buffer) { return omni::io::wfile::read(file, buffer); }
            inline uint64_t unsafe_read(const std::wstring& file, char* buffer, uint64_t length) { return omni::io::wfile::unsafe_read(file, buffer, length); }
            inline uint64_t unsafe_read(const std::wstring& file, wchar_t* buffer, uint64_t length) { return omni::io::wfile::unsafe_read(file, buffer, length); }
            inline uint64_t unsafe_read(const std::wstring& file, uint8_t* buffer, uint64_t length) { return omni::io::wfile::unsafe_read(file, buffer, length); }
            inline uint64_t unsafe_read(const std::wstring& file, int8_t* buffer, uint64_t length) { return omni::io::wfile::unsafe_read(file, buffer, length); }
            inline bool remove(const std::wstring& file) { return omni::io::wfile::remove(file); }
            #if defined(OMNI_NON_PORTABLE)
                inline bool set_size(const std::wstring& file, uint64_t size) { return omni::io::wfile::set_size(file, size); }
            #endif
            inline uint64_t write(const std::wstring& file, const omni::seq::char_t& buffer, bool append) { return omni::io::wfile::write(file, buffer, append); }
            inline uint64_t write(const std::wstring& file, const omni::seq::wide_char_t& buffer, bool append) { return omni::io::wfile::write(file, buffer, append); }
            inline uint64_t write(const std::wstring& file, const omni::seq::uint8_t& buffer, bool append) { return omni::io::wfile::write(file, buffer, append); }
            inline uint64_t write(const std::wstring& file, const omni::seq::int8_t& buffer, bool append) { return omni::io::wfile::write(file, buffer, append); }
            inline uint64_t write(const std::wstring& file, const std::wstring& buffer, bool append) { return omni::io::wfile::write(file, buffer, append); }
            inline uint64_t unsafe_write(const std::wstring& file, const char* buffer, uint64_t length, bool append) { return omni::io::wfile::unsafe_write(file, buffer, length, append); }
            inline uint64_t unsafe_write(const std::wstring& file, const wchar_t* buffer, uint64_t length, bool append) { return omni::io::wfile::unsafe_write(file, buffer, length, append); }
            inline uint64_t unsafe_write(const std::wstring& file, const uint8_t* buffer, uint64_t length, bool append) { return omni::io::wfile::unsafe_write(file, buffer, length, append); }
            inline uint64_t unsafe_write(const std::wstring& file, const int8_t* buffer, uint64_t length, bool append) { return omni::io::wfile::unsafe_write(file, buffer, length, append); }
            inline uint64_t write_line(const std::wstring& file, const omni::seq::char_t& buffer, bool append) { return omni::io::wfile::write_line(file, buffer, append); }
            inline uint64_t write_line(const std::wstring& file, const omni::seq::wide_char_t& buffer, bool append) { return omni::io::wfile::write_line(file, buffer, append); }
            inline uint64_t write_line(const std::wstring& file, const omni::seq::uint8_t& buffer, bool append) { return omni::io::wfile::write_line(file, buffer, append); }
            inline uint64_t write_line(const std::wstring& file, const omni::seq::int8_t& buffer, bool append) { return omni::io::wfile::write_line(file, buffer, append); }
            inline uint64_t write_line(const std::wstring& file, const std::wstring& buffer, bool append) { return omni::io::wfile::write_line(file, buffer, append); }
            inline uint64_t unsafe_write_line(const std::wstring& file, const char* buffer, uint64_t length, bool append) { return omni::io::wfile::unsafe_write_line(file, buffer, length, append); }
            inline uint64_t unsafe_write_line(const std::wstring& file, const wchar_t* buffer, uint64_t length, bool append) { return omni::io::wfile::unsafe_write_line(file, buffer, length, append); }
            inline uint64_t unsafe_write_line(const std::wstring& file, const uint8_t* buffer, uint64_t length, bool append) { return omni::io::wfile::unsafe_write_line(file, buffer, length, append); }
            inline uint64_t unsafe_write_line(const std::wstring& file, const int8_t* buffer, uint64_t length, bool append) { return omni::io::wfile::unsafe_write_line(file, buffer, length, append); }
            inline uint64_t write(const std::wstring& file, const omni::seq::char_t& buffer) { return omni::io::wfile::write(file, buffer); }
            inline uint64_t write(const std::wstring& file, const omni::seq::wide_char_t& buffer) { return omni::io::wfile::write(file, buffer); }
            inline uint64_t write(const std::wstring& file, const omni::seq::uint8_t& buffer) { return omni::io::wfile::write(file, buffer); }
            inline uint64_t write(const std::wstring& file, const omni::seq::int8_t& buffer) { return omni::io::wfile::write(file, buffer); }
            inline uint64_t write(const std::wstring& file, const std::wstring& buffer) { return omni::io::wfile::write(file, buffer); }
            inline uint64_t unsafe_write(const std::wstring& file, const char* buffer, uint64_t length) { return omni::io::wfile::unsafe_write(file, buffer, length); }
            inline uint64_t unsafe_write(const std::wstring& file, const wchar_t* buffer, uint64_t length) { return omni::io::wfile::unsafe_write(file, buffer, length); }
            inline uint64_t unsafe_write(const std::wstring& file, const uint8_t* buffer, uint64_t length) { return omni::io::wfile::unsafe_write(file, buffer, length); }
            inline uint64_t unsafe_write(const std::wstring& file, const int8_t* buffer, uint64_t length) { return omni::io::wfile::unsafe_write(file, buffer, length); }
            inline uint64_t write_line(const std::wstring& file, const omni::seq::char_t& buffer) { return omni::io::wfile::write_line(file, buffer); }
            inline uint64_t write_line(const std::wstring& file, const omni::seq::wide_char_t& buffer) { return omni::io::wfile::write_line(file, buffer); }
            inline uint64_t write_line(const std::wstring& file, const omni::seq::uint8_t& buffer) { return omni::io::wfile::write_line(file, buffer); }
            inline uint64_t write_line(const std::wstring& file, const omni::seq::int8_t& buffer) { return omni::io::wfile::write_line(file, buffer); }
            inline uint64_t write_line(const std::wstring& file, const std::wstring& buffer) { return omni::io::wfile::write_line(file, buffer); }
            inline uint64_t unsafe_write_line(const std::wstring& file, const char* buffer, uint64_t length) { return omni::io::wfile::unsafe_write_line(file, buffer, length); }
            inline uint64_t unsafe_write_line(const std::wstring& file, const wchar_t* buffer, uint64_t length) { return omni::io::wfile::unsafe_write_line(file, buffer, length); }
            inline uint64_t unsafe_write_line(const std::wstring& file, const uint8_t* buffer, uint64_t length) { return omni::io::wfile::unsafe_write_line(file, buffer, length); }
            inline uint64_t unsafe_write_line(const std::wstring& file, const int8_t* buffer, uint64_t length) { return omni::io::wfile::unsafe_write_line(file, buffer, length); }
        }

        namespace cdirectory {
            bool copy(const std::string& folder, const std::string& new_name, bool create_path);
            bool copy(const std::string& folder, const std::string& new_name);
            bool create(const std::string& folder, bool create_path);
            bool create(const std::string& folder);
            bool exists(const std::string& folder);
            bool exist(const std::string& folder);
            omni::seq::std_string_t get_directories(const std::string& folder);
            omni::seq::std_string_t get_all_directories(const std::string& folder);
            omni::seq::std_string_t get_files(const std::string& folder);
            omni::seq::std_string_t get_all_files(const std::string& folder);
            bool move(const std::string& folder, const std::string& new_name, bool create_path);
            bool move(const std::string& folder, const std::string& new_name);
            bool rename(const std::string& folder, const std::string& new_name, bool create_path);
            bool rename(const std::string& folder, const std::string& new_name);
            bool remove(const std::string& folder, bool recursive);
            bool remove(const std::string& folder);
        }
        namespace wdirectory {
            bool copy(const std::wstring& folder, const std::wstring& new_name, bool create_path);
            bool copy(const std::wstring& folder, const std::wstring& new_name);
            bool create(const std::wstring& folder, bool create_path);
            bool create(const std::wstring& folder);
            bool exists(const std::wstring& folder);
            bool exist(const std::wstring& folder);
            omni::seq::std_wstring_t get_directories(const std::wstring& folder);
            omni::seq::std_wstring_t get_all_directories(const std::wstring& folder);
            omni::seq::std_wstring_t get_files(const std::wstring& folder);
            omni::seq::std_wstring_t get_all_files(const std::wstring& folder);
            bool move(const std::wstring& folder, const std::wstring& new_name, bool create_path);
            bool move(const std::wstring& folder, const std::wstring& new_name);
            bool rename(const std::wstring& folder, const std::wstring& new_name, bool create_path);
            bool rename(const std::wstring& folder, const std::wstring& new_name);
            bool remove(const std::wstring& folder, bool recursive);
            bool remove(const std::wstring& folder);
        }
        namespace directory {
            // std::string
            inline bool copy(const std::string& folder, const std::string& new_name, bool create_path) { return omni::io::cdirectory::copy(folder, new_name, create_path); }
            inline bool copy(const std::string& folder, const std::string& new_name) { return omni::io::cdirectory::copy(folder, new_name); }
            inline bool create(const std::string& folder, bool create_path) { return omni::io::cdirectory::create(folder, create_path); }
            inline bool create(const std::string& folder) { return omni::io::cdirectory::create(folder); }
            inline bool exists(const std::string& folder) { return omni::io::cdirectory::exists(folder); }
            inline bool exist(const std::string& folder) { return omni::io::cdirectory::exist(folder); }
            inline omni::seq::std_string_t get_directories(const std::string& folder) { return omni::io::cdirectory::get_directories(folder); }
            inline omni::seq::std_string_t get_all_directories(const std::string& folder) { return omni::io::cdirectory::get_all_directories(folder); }
            inline omni::seq::std_string_t get_files(const std::string& folder) { return omni::io::cdirectory::get_files(folder); }
            inline omni::seq::std_string_t get_all_files(const std::string& folder) { return omni::io::cdirectory::get_all_files(folder); }
            inline bool move(const std::string& folder, const std::string& new_name, bool create_path) { return omni::io::cdirectory::move(folder, new_name, create_path); }
            inline bool move(const std::string& folder, const std::string& new_name) { return omni::io::cdirectory::move(folder, new_name); }
            inline bool rename(const std::string& folder, const std::string& new_name, bool create_path) { return omni::io::cdirectory::rename(folder, new_name, create_path); }
            inline bool rename(const std::string& folder, const std::string& new_name) { return omni::io::cdirectory::rename(folder, new_name); }
            inline bool remove(const std::string& folder, bool recursive) { return omni::io::cdirectory::remove(folder, recursive); }
            inline bool remove(const std::string& folder) { return omni::io::cdirectory::remove(folder); }
            // std::wstring
            inline bool copy(const std::wstring& folder, const std::wstring& new_name, bool create_path) { return omni::io::wdirectory::copy(folder, new_name, create_path); }
            inline bool copy(const std::wstring& folder, const std::wstring& new_name) { return omni::io::wdirectory::copy(folder, new_name); }
            inline bool create(const std::wstring& folder, bool create_path) { return omni::io::wdirectory::create(folder, create_path); }
            inline bool create(const std::wstring& folder) { return omni::io::wdirectory::create(folder); }
            inline bool exists(const std::wstring& folder) { return omni::io::wdirectory::exists(folder); }
            inline bool exist(const std::wstring& folder) { return omni::io::wdirectory::exist(folder); }
            inline omni::seq::std_wstring_t get_directories(const std::wstring& folder) { return omni::io::wdirectory::get_directories(folder); }
            inline omni::seq::std_wstring_t get_all_directories(const std::wstring& folder) { return omni::io::wdirectory::get_all_directories(folder); }
            inline omni::seq::std_wstring_t get_files(const std::wstring& folder) { return omni::io::wdirectory::get_files(folder); }
            inline omni::seq::std_wstring_t get_all_files(const std::wstring& folder) { return omni::io::wdirectory::get_all_files(folder); }
            inline bool move(const std::wstring& folder, const std::wstring& new_name, bool create_path) { return omni::io::wdirectory::move(folder, new_name, create_path); }
            inline bool move(const std::wstring& folder, const std::wstring& new_name) { return omni::io::wdirectory::move(folder, new_name); }
            inline bool rename(const std::wstring& folder, const std::wstring& new_name, bool create_path) { return omni::io::wdirectory::rename(folder, new_name, create_path); }
            inline bool rename(const std::wstring& folder, const std::wstring& new_name) { return omni::io::wdirectory::rename(folder, new_name); }
            inline bool remove(const std::wstring& folder, bool recursive) { return omni::io::wdirectory::remove(folder, recursive); }
            inline bool remove(const std::wstring& folder) { return omni::io::wdirectory::remove(folder); }
        }

        namespace cpath {
            std::string change_extension(const std::string& path, const std::string& extension);
            std::string combine(const std::string& path1, const std::string& path2);
            template < std::size_t SZ >
            inline std::string combine(const std::string& path1, const char (&data)[SZ]) { return omni::io::cpath::combine(path1, std::string(data)); }
            std::string get_extension(const std::string& path);
            std::string get_name(const std::string& path);
            std::string get_name_without_extension(const std::string& path);
            std::string get_parent_name(const std::string& path);
            std::string generate(const std::string& path);
            std::string generate(const std::string& path, const std::string& file);
            std::string generate(const std::string& path, const std::string& file, const std::string& ext);
            omni::seq::char_t get_invalid_file_chars();
            omni::seq::char_t get_invalid_path_chars();
            bool has_extension(const std::string& path);
            bool is_path_absolute(const std::string& path);
            std::string trim_trailing_slash(const std::string& path);
        }
        namespace wpath {
            std::wstring change_extension(const std::wstring& path, const std::wstring& extension);
            std::wstring combine(const std::wstring& path1, const std::wstring& path2);
            template < std::size_t SZ >
            inline std::wstring combine(const std::wstring& path1, const wchar_t (&data)[SZ]) { return omni::io::wpath::combine(path1, std::wstring(data)); }
            std::wstring get_extension(const std::wstring& path);
            std::wstring get_name(const std::wstring& path);
            std::wstring get_name_without_extension(const std::wstring& path);
            std::wstring get_parent_name(const std::wstring& path);
            std::wstring generate(const std::wstring& path);
            std::wstring generate(const std::wstring& path, const std::wstring& file);
            std::wstring generate(const std::wstring& path, const std::wstring& file, const std::wstring& ext);
            omni::seq::wide_char_t get_invalid_file_chars();
            omni::seq::wide_char_t get_invalid_path_chars();
            bool has_extension(const std::wstring& path);
            bool is_path_absolute(const std::wstring& path);
            std::wstring trim_trailing_slash(const std::wstring& path);
        }
        namespace path {
            // std::string
            inline std::string change_extension(const std::string& path, const std::string& extension) { return omni::io::cpath::change_extension(path, extension); }
            inline std::string combine(const std::string& path1, const std::string& path2) { return omni::io::cpath::combine(path1, path2); }
            template < std::size_t SZ >
            inline std::string combine(const std::string& path1, const char (&data)[SZ]) { return omni::io::cpath::combine(path1, std::string(data)); }
            inline std::string get_extension(const std::string& path) { return omni::io::cpath::get_extension(path); }
            inline std::string get_name(const std::string& path) { return omni::io::cpath::get_name(path); }
            inline std::string get_name_without_extension(const std::string& path) { return omni::io::cpath::get_name_without_extension(path); }
            inline std::string get_parent_name(const std::string& path) { return omni::io::cpath::get_parent_name(path); }
            inline std::string generate(const std::string& path) { return omni::io::cpath::generate(path); }
            inline std::string generate(const std::string& path, const std::string& file) { return omni::io::cpath::generate(path, file); }
            inline std::string generate(const std::string& path, const std::string& file, const std::string& ext) { return omni::io::cpath::generate(path, file, ext); }
            inline omni::seq::char_t get_invalid_file_chars() { return omni::io::cpath::get_invalid_file_chars(); }
            inline omni::seq::char_t get_invalid_path_chars() { return omni::io::cpath::get_invalid_path_chars(); }
            inline bool has_extension(const std::string& path) { return omni::io::cpath::has_extension(path); }
            inline bool is_path_absolute(const std::string& path) { return omni::io::cpath::is_path_absolute(path); }
            inline std::string trim_trailing_slash(const std::string& path) { return omni::io::cpath::trim_trailing_slash(path); }
            // std::wstring
            inline std::wstring change_extension(const std::wstring& path, const std::wstring& extension) { return omni::io::wpath::change_extension(path, extension); }
            inline std::wstring combine(const std::wstring& path1, const std::wstring& path2) { return omni::io::wpath::combine(path1, path2); }
            template < std::size_t SZ >
            inline std::wstring combine(const std::wstring& path1, const wchar_t (&data)[SZ]) { return omni::io::wpath::combine(path1, std::wstring(data)); }
            inline std::wstring get_extension(const std::wstring& path) { return omni::io::wpath::get_extension(path); }
            inline std::wstring get_name(const std::wstring& path) { return omni::io::wpath::get_name(path); }
            inline std::wstring get_name_without_extension(const std::wstring& path) { return omni::io::wpath::get_name_without_extension(path); }
            inline std::wstring get_parent_name(const std::wstring& path) { return omni::io::wpath::get_parent_name(path); }
            inline std::wstring generate(const std::wstring& path) { return omni::io::wpath::generate(path); }
            inline std::wstring generate(const std::wstring& path, const std::wstring& file) { return omni::io::wpath::generate(path, file); }
            inline std::wstring generate(const std::wstring& path, const std::wstring& file, const std::wstring& ext) { return omni::io::wpath::generate(path, file, ext); }
            inline omni::seq::wide_char_t get_invalid_file_wchars() { return omni::io::wpath::get_invalid_file_chars(); }
            inline omni::seq::wide_char_t get_invalid_path_wchars() { return omni::io::wpath::get_invalid_path_chars(); }
            inline bool has_extension(const std::wstring& path) { return omni::io::wpath::has_extension(path); }
            inline bool is_path_absolute(const std::wstring& path) { return omni::io::wpath::is_path_absolute(path); }
            inline std::wstring trim_trailing_slash(const std::wstring& path) { return omni::io::wpath::trim_trailing_slash(path); }
        }
    }
}

#endif // OMNI_IO_HPP
