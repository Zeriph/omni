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
#include <omni/defs/file_def.hpp>
#define OMNI_IO_FILE_RW_FW 1
#include <omni/xx/io_file_rw.hxx>

namespace omni {
    namespace io {
        namespace cfile {
            bool copy(const std::string& file, const std::string& new_name, const omni::io::options& io_ops);
            bool copy(const std::string& file, const std::string& new_name);
            bool create(const std::string& file, const omni::io::options& io_ops);
            bool create(const std::string& file);
            bool exists(const std::string& file);
            bool exist(const std::string& file);
            std::string get_contents(const std::string& file);
            uint64_t get_size(const std::string& file);
            bool move(const std::string& file, const std::string& new_name, const omni::io::options& io_ops);
            bool move(const std::string& file, const std::string& new_name);
            bool rename(const std::string& file, const std::string& new_name, const omni::io::options& io_ops);
            bool rename(const std::string& file, const std::string& new_name);
            uint64_t read(const std::string& file, std::string& buffer);
            // std::vector/deque/array/list/etc.
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t read(const std::string& file, std_seq_t<T, std_allocator_t >& buffer)
            {
                return omni::io::file_internal::rd< std::string, std::ifstream, std_seq_t, T, std_allocator_t >(file, buffer, 0, 0, std::ios_base::beg);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t read(const char (&file)[SZ], std_seq_t<T, std_allocator_t >& buffer)
            {
                return omni::io::file_internal::rd< std::string, std::ifstream, std_seq_t, T, std_allocator_t >(std::string(file), buffer, 0, 0, std::ios_base::beg);
            }
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t read(const std::string& file, std_seq_t<T, std_allocator_t >& buffer, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd< std::string, std::ifstream, std_seq_t, T, std_allocator_t >(file, buffer, 0, file_offset, offset_direction);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t read(const char (&file)[SZ], std_seq_t<T, std_allocator_t >& buffer, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd< std::string, std::ifstream, std_seq_t, T, std_allocator_t >(std::string(file), buffer, 0, file_offset, offset_direction);
            }
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t read(const std::string& file, std_seq_t<T, std_allocator_t >& buffer, uint64_t length, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd< std::string, std::ifstream, std_seq_t, T, std_allocator_t >(file, buffer, length, file_offset, offset_direction);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t read(const char (&file)[SZ], std_seq_t<T, std_allocator_t >& buffer, uint64_t length, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd< std::string, std::ifstream, std_seq_t, T, std_allocator_t >(std::string(file), buffer, length, file_offset, offset_direction);
            }
            // char buf[]/wchar_t buf[]/uintX_t buf[]
            template < typename T, std::size_t SZ >
            uint64_t read(const std::string& file, T (&buffer)[SZ])
            {
                return omni::io::file_internal::rd< std::string, std::ifstream, T, SZ >(file, buffer, 0, 0, 0, std::ios_base::beg);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t read(const char (&file)[FSZ], T (&buffer)[SZ])
            {
                return omni::io::file_internal::rd< std::string, std::ifstream, T, SZ >(std::string(file), buffer, 0, 0, 0, std::ios_base::beg);
            }
            template < typename T, std::size_t SZ >
            uint64_t read(const std::string& file, T (&buffer)[SZ], std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd< std::string, std::ifstream, T, SZ >(file, buffer, 0, 0, file_offset, offset_direction);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t read(const char (&file)[FSZ], T (&buffer)[SZ], std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd< std::string, std::ifstream, T, SZ >(std::string(file), buffer, 0, 0, file_offset, offset_direction);
            }
            template < typename T, std::size_t SZ >
            uint64_t read(const std::string& file, T (&buffer)[SZ], uint64_t length, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd< std::string, std::ifstream, T, SZ >(file, buffer, length, 0, file_offset, offset_direction);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t read(const char (&file)[FSZ], T (&buffer)[SZ], uint64_t length, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd< std::string, std::ifstream, T, SZ >(std::string(file), buffer, length, 0, file_offset, offset_direction);
            }
            template < typename T, std::size_t SZ >
            uint64_t read(const std::string& file, T (&buffer)[SZ], uint64_t length, std::size_t buffer_offset, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd< std::string, std::ifstream, T, SZ >(file, buffer, length, buffer_offset, file_offset, offset_direction);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t read(const char (&file)[FSZ], T (&buffer)[SZ], uint64_t length, std::size_t buffer_offset, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd< std::string, std::ifstream, T, SZ >(std::string(file), buffer, length, buffer_offset, file_offset, offset_direction);
            }
            // omni::stack_buffer
            template < typename T, uint16_t SZ >
            uint64_t read(const std::string& file, omni::stack_buffer<T, SZ>& buffer)
            {
                return omni::io::file_internal::rd< std::string, std::ifstream, T, SZ >(file, buffer, 0, 0, 0, std::ios_base::beg);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t read(const char (&file)[FSZ], omni::stack_buffer<T, SZ>& buffer)
            {
                return omni::io::file_internal::rd< std::string, std::ifstream, T, SZ >(std::string(file), buffer, 0, 0, 0, std::ios_base::beg);
            }
            template < typename T, uint16_t SZ >
            uint64_t read(const std::string& file, omni::stack_buffer<T, SZ>& buffer, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd< std::string, std::ifstream, T, SZ >(file, buffer, 0, 0, file_offset, offset_direction);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t read(const char (&file)[FSZ], omni::stack_buffer<T, SZ>& buffer, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd< std::string, std::ifstream, T, SZ >(std::string(file), buffer, 0, 0, file_offset, offset_direction);
            }
            template < typename T, uint16_t SZ >
            uint64_t read(const std::string& file, omni::stack_buffer<T, SZ>& buffer, uint64_t length, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd< std::string, std::ifstream, T, SZ >(file, buffer, length, 0, file_offset, offset_direction);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t read(const char (&file)[FSZ], omni::stack_buffer<T, SZ>& buffer, uint64_t length, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd< std::string, std::ifstream, T, SZ >(std::string(file), buffer, length, 0, file_offset, offset_direction);
            }
            template < typename T, uint16_t SZ >
            uint64_t read(const std::string& file, omni::stack_buffer<T, SZ>& buffer, uint64_t length, std::size_t buffer_offset, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd< std::string, std::ifstream, T, SZ >(file, buffer, length, buffer_offset, file_offset, offset_direction);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t read(const char (&file)[FSZ], omni::stack_buffer<T, SZ>& buffer, uint64_t length, std::size_t buffer_offset, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd< std::string, std::ifstream, T, SZ >(std::string(file), buffer, length, buffer_offset, file_offset, offset_direction);
            }
            // read_element
            // std::vector/deque/array/list/etc.
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t read_element(const std::string& file, std_seq_t<T, std_allocator_t >& buffer)
            {
                return omni::io::file_internal::rd_el< std::string, std::ifstream, std_seq_t, T, std_allocator_t >(file, buffer, 0, 0, std::ios_base::beg);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t read_element(const char (&file)[SZ], std_seq_t<T, std_allocator_t >& buffer)
            {
                return omni::io::file_internal::rd_el< std::string, std::ifstream, std_seq_t, T, std_allocator_t >(std::string(file), buffer, 0, 0, std::ios_base::beg);
            }
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t read_element(const std::string& file, std_seq_t<T, std_allocator_t >& buffer, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd_el< std::string, std::ifstream, std_seq_t, T, std_allocator_t >(file, buffer, 0, file_offset, offset_direction);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t read_element(const char (&file)[SZ], std_seq_t<T, std_allocator_t >& buffer, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd_el< std::string, std::ifstream, std_seq_t, T, std_allocator_t >(std::string(file), buffer, 0, file_offset, offset_direction);
            }
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t read_element(const std::string& file, std_seq_t<T, std_allocator_t >& buffer, uint64_t elements, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd_el< std::string, std::ifstream, std_seq_t, T, std_allocator_t >(file, buffer, elements, file_offset, offset_direction);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t read_element(const char (&file)[SZ], std_seq_t<T, std_allocator_t >& buffer, uint64_t elements, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd_el< std::string, std::ifstream, std_seq_t, T, std_allocator_t >(std::string(file), buffer, elements, file_offset, offset_direction);
            }
            // char buf[]/wchar_t buf[]/uintX_t buf[]
            template < typename T, std::size_t SZ >
            uint64_t read_element(const std::string& file, T (&buffer)[SZ])
            {
                return omni::io::file_internal::rd_el< std::string, std::ifstream, T, SZ >(file, buffer, 0, 0, 0, std::ios_base::beg);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t read_element(const char (&file)[FSZ], T (&buffer)[SZ])
            {
                return omni::io::file_internal::rd_el< std::string, std::ifstream, T, SZ >(std::string(file), buffer, 0, 0, 0, std::ios_base::beg);
            }
            template < typename T, std::size_t SZ >
            uint64_t read_element(const std::string& file, T (&buffer)[SZ], std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd_el< std::string, std::ifstream, T, SZ >(file, buffer, 0, 0, file_offset, offset_direction);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t read_element(const char (&file)[FSZ], T (&buffer)[SZ], std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd_el< std::string, std::ifstream, T, SZ >(std::string(file), buffer, 0, 0, file_offset, offset_direction);
            }
            template < typename T, std::size_t SZ >
            uint64_t read_element(const std::string& file, T (&buffer)[SZ], uint64_t elements, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd_el< std::string, std::ifstream, T, SZ >(file, buffer, elements, 0, file_offset, offset_direction);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t read_element(const char (&file)[FSZ], T (&buffer)[SZ], uint64_t elements, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd_el< std::string, std::ifstream, T, SZ >(std::string(file), buffer, elements, 0, file_offset, offset_direction);
            }
            template < typename T, std::size_t SZ >
            uint64_t read_element(const std::string& file, T (&buffer)[SZ], uint64_t elements, std::size_t buffer_offset, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd_el< std::string, std::ifstream, T, SZ >(file, buffer, elements, buffer_offset, file_offset, offset_direction);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t read_element(const char (&file)[FSZ], T (&buffer)[SZ], uint64_t elements, std::size_t buffer_offset, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd_el< std::string, std::ifstream, T, SZ >(std::string(file), buffer, elements, buffer_offset, file_offset, offset_direction);
            }
            // omni::stack_buffer
            template < typename T, uint16_t SZ >
            uint64_t read_element(const std::string& file, omni::stack_buffer<T, SZ>& buffer)
            {
                return omni::io::file_internal::rd_el< std::string, std::ifstream, T, SZ >(file, buffer, 0, 0, 0, std::ios_base::beg);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t read_element(const char (&file)[FSZ], omni::stack_buffer<T, SZ>& buffer)
            {
                return omni::io::file_internal::rd_el< std::string, std::ifstream, T, SZ >(std::string(file), buffer, 0, 0, 0, std::ios_base::beg);
            }
            template < typename T, uint16_t SZ >
            uint64_t read_element(const std::string& file, omni::stack_buffer<T, SZ>& buffer, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd_el< std::string, std::ifstream, T, SZ >(file, buffer, 0, 0, file_offset, offset_direction);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t read_element(const char (&file)[FSZ], omni::stack_buffer<T, SZ>& buffer, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd_el< std::string, std::ifstream, T, SZ >(std::string(file), buffer, 0, 0, file_offset, offset_direction);
            }
            template < typename T, uint16_t SZ >
            uint64_t read_element(const std::string& file, omni::stack_buffer<T, SZ>& buffer, uint64_t elements, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd_el< std::string, std::ifstream, T, SZ >(file, buffer, elements, 0, file_offset, offset_direction);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t read_element(const char (&file)[FSZ], omni::stack_buffer<T, SZ>& buffer, uint64_t elements, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd_el< std::string, std::ifstream, T, SZ >(std::string(file), buffer, elements, 0, file_offset, offset_direction);
            }
            template < typename T, uint16_t SZ >
            uint64_t read_element(const std::string& file, omni::stack_buffer<T, SZ>& buffer, uint64_t elements, std::size_t buffer_offset, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd_el< std::string, std::ifstream, T, SZ >(file, buffer, elements, buffer_offset, file_offset, offset_direction);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t read_element(const char (&file)[FSZ], omni::stack_buffer<T, SZ>& buffer, uint64_t elements, std::size_t buffer_offset, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd_el< std::string, std::ifstream, T, SZ >(std::string(file), buffer, elements, buffer_offset, file_offset, offset_direction);
            }
            template < typename T >
            uint64_t unsafe_read_element(const std::string& file, T* buffer, uint64_t elements)
            {
                return omni::io::file_internal::unsafe_rd_el< std::string, std::ifstream, T >(file, buffer, elements);
            }
            uint64_t unsafe_read(const std::string& file, char* buffer, uint64_t length);
            uint64_t unsafe_read(const std::string& file, wchar_t* buffer, uint64_t length);
            uint64_t unsafe_read(const std::string& file, uint8_t* buffer, uint64_t length);
            uint64_t unsafe_read(const std::string& file, int8_t* buffer, uint64_t length);
            bool remove(const std::string& file);
            #if defined(OMNI_NON_PORTABLE)
                bool set_size(const std::string& file, uint64_t size);
            #endif
            uint64_t write(const std::string& file, const std::string& buffer, bool append);
            uint64_t write(const std::string& file, const std::string& buffer);
            // std::vector/deque/array/list/etc.
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write(const std::string& file, const std_seq_t<T, std_allocator_t >& buffer)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, std_seq_t, T, std_allocator_t >(file, buffer, 0, 0, false, false);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write(const char (&file)[SZ], const std_seq_t<T, std_allocator_t >& buffer)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, std_seq_t, T, std_allocator_t >(std::string(file), buffer, 0, 0, false, false);
            }
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write(const std::string& file, const std_seq_t<T, std_allocator_t >& buffer, uint64_t length, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, std_seq_t, T, std_allocator_t >(file, buffer, length, buffer_offset, false, false);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write(const char (&file)[SZ], const std_seq_t<T, std_allocator_t >& buffer, uint64_t length, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, std_seq_t, T, std_allocator_t >(std::string(file), buffer, length, buffer_offset, false, false);
            }
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write(const std::string& file, const std_seq_t<T, std_allocator_t >& buffer, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, std_seq_t, T, std_allocator_t >(file, buffer, 0, 0, append, false);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write(const char (&file)[SZ], const std_seq_t<T, std_allocator_t >& buffer, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, std_seq_t, T, std_allocator_t >(std::string(file), buffer, 0, 0, append, false);
            }
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write(const std::string& file, const std_seq_t<T, std_allocator_t >& buffer, uint64_t length, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, std_seq_t, T, std_allocator_t >(file, buffer, length, buffer_offset, append, false);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write(const char (&file)[SZ], const std_seq_t<T, std_allocator_t >& buffer, uint64_t length, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, std_seq_t, T, std_allocator_t >(std::string(file), buffer, length, buffer_offset, append, false);
            }
            // char buf[]/wchar_t buf[]/uintX_t buf[]
            template < typename T, std::size_t SZ >
            uint64_t write(const std::string& file, const T (&buffer)[SZ])
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, T, SZ >(file, buffer, 0, 0, false, false);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t write(const char (&file)[FSZ], const T (&buffer)[SZ])
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, T, SZ >(std::string(file), buffer, 0, 0, false, false);
            }
            template < typename T, std::size_t SZ >
            uint64_t write(const std::string& file, const T (&buffer)[SZ], uint64_t length, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, T, SZ >(file, buffer, length, buffer_offset, false, false);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t write(const char (&file)[FSZ], const T (&buffer)[SZ], uint64_t length, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, T, SZ >(std::string(file), buffer, length, buffer_offset, false, false);
            }
            template < typename T, std::size_t SZ >
            uint64_t write(const std::string& file, const T (&buffer)[SZ], bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, T, SZ >(file, buffer, 0, 0, append, false);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t write(const char (&file)[FSZ], const T (&buffer)[SZ], bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, T, SZ >(std::string(file), buffer, 0, 0, append, false);
            }
            template < typename T, std::size_t SZ >
            uint64_t write(const std::string& file, const T (&buffer)[SZ], uint64_t length, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, T, SZ >(file, buffer, length, buffer_offset, append, false);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t write(const char (&file)[FSZ], const T (&buffer)[SZ], uint64_t length, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, T, SZ >(std::string(file), buffer, length, buffer_offset, append, false);
            }
            // omni::stack_buffer
            template < typename T, uint16_t SZ >
            uint64_t write(const std::string& file, const omni::stack_buffer<T, SZ>& buffer)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, T, SZ >(file, buffer, 0, 0, false, false);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t write(const char (&file)[FSZ], const omni::stack_buffer<T, SZ>& buffer)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, T, SZ >(std::string(file), buffer, 0, 0, false, false);
            }
            template < typename T, uint16_t SZ >
            uint64_t write(const std::string& file, const omni::stack_buffer<T, SZ>& buffer, uint64_t length, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, T, SZ >(file, buffer, length, buffer_offset, false, false);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t write(const char (&file)[FSZ], const omni::stack_buffer<T, SZ>& buffer, uint64_t length, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, T, SZ >(std::string(file), buffer, length, buffer_offset, false, false);
            }
            template < typename T, uint16_t SZ >
            uint64_t write(const std::string& file, const omni::stack_buffer<T, SZ>& buffer, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, T, SZ >(file, buffer, 0, 0, append, false);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t write(const char (&file)[FSZ], const omni::stack_buffer<T, SZ>& buffer, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, T, SZ >(std::string(file), buffer, 0, 0, append, false);
            }
            template < typename T, uint16_t SZ >
            uint64_t write(const std::string& file, const omni::stack_buffer<T, SZ>& buffer, uint64_t length, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, T, SZ >(file, buffer, length, buffer_offset, append, false);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t write(const char (&file)[FSZ], const omni::stack_buffer<T, SZ>& buffer, uint64_t length, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, T, SZ >(std::string(file), buffer, length, buffer_offset, append, false);
            }
            // write_element
            // std::vector/deque/array/list/etc.
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write_element(const std::string& file, const std_seq_t<T, std_allocator_t >& buffer)
            {
                return omni::io::file_internal::write_el_fw< std::string, std::ofstream, std_seq_t, T, std_allocator_t >(file, buffer, 0, 0, false, false);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write_element(const char (&file)[SZ], const std_seq_t<T, std_allocator_t >& buffer)
            {
                return omni::io::file_internal::write_el_fw< std::string, std::ofstream, std_seq_t, T, std_allocator_t >(std::string(file), buffer, 0, 0, false, false);
            }
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write_element(const std::string& file, const std_seq_t<T, std_allocator_t >& buffer, uint64_t elements, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_el_fw< std::string, std::ofstream, std_seq_t, T, std_allocator_t >(file, buffer, elements, buffer_offset, false, false);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write_element(const char (&file)[SZ], const std_seq_t<T, std_allocator_t >& buffer, uint64_t elements, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_el_fw< std::string, std::ofstream, std_seq_t, T, std_allocator_t >(std::string(file), buffer, elements, buffer_offset, false, false);
            }
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write_element(const std::string& file, const std_seq_t<T, std_allocator_t >& buffer, bool append)
            {
                return omni::io::file_internal::write_el_fw< std::string, std::ofstream, std_seq_t, T, std_allocator_t >(file, buffer, 0, 0, append, false);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write_element(const char (&file)[SZ], const std_seq_t<T, std_allocator_t >& buffer, bool append)
            {
                return omni::io::file_internal::write_el_fw< std::string, std::ofstream, std_seq_t, T, std_allocator_t >(std::string(file), buffer, 0, 0, append, false);
            }
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write_element(const std::string& file, const std_seq_t<T, std_allocator_t >& buffer, uint64_t elements, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_el_fw< std::string, std::ofstream, std_seq_t, T, std_allocator_t >(file, buffer, elements, buffer_offset, append, false);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write_element(const char (&file)[SZ], const std_seq_t<T, std_allocator_t >& buffer, uint64_t elements, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_el_fw< std::string, std::ofstream, std_seq_t, T, std_allocator_t >(std::string(file), buffer, elements, buffer_offset, append, false);
            }
            // char buf[]/wchar_t buf[]/uintX_t buf[]
            template < typename T, std::size_t SZ >
            uint64_t write_element(const std::string& file, const T (&buffer)[SZ])
            {
                return omni::io::file_internal::write_el_fw< std::string, std::ofstream, T, SZ >(file, buffer, 0, 0, false, false);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t write_element(const char (&file)[FSZ], const T (&buffer)[SZ])
            {
                return omni::io::file_internal::write_el_fw< std::string, std::ofstream, T, SZ >(std::string(file), buffer, 0, 0, false, false);
            }
            template < typename T, std::size_t SZ >
            uint64_t write_element(const std::string& file, const T (&buffer)[SZ], uint64_t elements, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_el_fw< std::string, std::ofstream, T, SZ >(file, buffer, elements, buffer_offset, false, false);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t write_element(const char (&file)[FSZ], const T (&buffer)[SZ], uint64_t elements, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_el_fw< std::string, std::ofstream, T, SZ >(std::string(file), buffer, elements, buffer_offset, false, false);
            }
            template < typename T, std::size_t SZ >
            uint64_t write_element(const std::string& file, const T (&buffer)[SZ], bool append)
            {
                return omni::io::file_internal::write_el_fw< std::string, std::ofstream, T, SZ >(file, buffer, 0, 0, append, false);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t write_element(const char (&file)[FSZ], const T (&buffer)[SZ], bool append)
            {
                return omni::io::file_internal::write_el_fw< std::string, std::ofstream, T, SZ >(std::string(file), buffer, 0, 0, append, false);
            }
            template < typename T, std::size_t SZ >
            uint64_t write_element(const std::string& file, const T (&buffer)[SZ], uint64_t elements, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_el_fw< std::string, std::ofstream, T, SZ >(file, buffer, elements, buffer_offset, append, false);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t write_element(const char (&file)[FSZ], const T (&buffer)[SZ], uint64_t elements, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_el_fw< std::string, std::ofstream, T, SZ >(std::string(file), buffer, elements, buffer_offset, append, false);
            }
            // omni::stack_buffer
            template < typename T, uint16_t SZ >
            uint64_t write_element(const std::string& file, const omni::stack_buffer<T, SZ>& buffer)
            {
                return omni::io::file_internal::write_el_fw< std::string, std::ofstream, T, SZ >(file, buffer, 0, 0, false, false);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t write_element(const char (&file)[FSZ], const omni::stack_buffer<T, SZ>& buffer)
            {
                return omni::io::file_internal::write_el_fw< std::string, std::ofstream, T, SZ >(std::string(file), buffer, 0, 0, false, false);
            }
            template < typename T, uint16_t SZ >
            uint64_t write_element(const std::string& file, const omni::stack_buffer<T, SZ>& buffer, uint64_t elements, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_el_fw< std::string, std::ofstream, T, SZ >(file, buffer, elements, buffer_offset, false, false);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t write_element(const char (&file)[FSZ], const omni::stack_buffer<T, SZ>& buffer, uint64_t elements, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_el_fw< std::string, std::ofstream, T, SZ >(std::string(file), buffer, elements, buffer_offset, false, false);
            }
            template < typename T, uint16_t SZ >
            uint64_t write_element(const std::string& file, const omni::stack_buffer<T, SZ>& buffer, bool append)
            {
                return omni::io::file_internal::write_el_fw< std::string, std::ofstream, T, SZ >(file, buffer, 0, 0, append, false);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t write_element(const char (&file)[FSZ], const omni::stack_buffer<T, SZ>& buffer, bool append)
            {
                return omni::io::file_internal::write_el_fw< std::string, std::ofstream, T, SZ >(std::string(file), buffer, 0, 0, append, false);
            }
            template < typename T, uint16_t SZ >
            uint64_t write_element(const std::string& file, const omni::stack_buffer<T, SZ>& buffer, uint64_t elements, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_el_fw< std::string, std::ofstream, T, SZ >(file, buffer, elements, buffer_offset, append, false);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t write_element(const char (&file)[FSZ], const omni::stack_buffer<T, SZ>& buffer, uint64_t elements, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_el_fw< std::string, std::ofstream, T, SZ >(std::string(file), buffer, elements, buffer_offset, append, false);
            }

            uint64_t write_line(const std::string& file, const std::string& buffer, bool append);
            uint64_t write_line(const std::string& file, const std::string& buffer);
            // std::vector/deque/array/list/etc.
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write_line(const std::string& file, const std_seq_t<T, std_allocator_t >& buffer)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, std_seq_t, T, std_allocator_t >(file, buffer, 0, 0, false, true);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write_line(const char (&file)[SZ], const std_seq_t<T, std_allocator_t >& buffer)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, std_seq_t, T, std_allocator_t >(std::string(file), buffer, 0, 0, false, true);
            }
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write_line(const std::string& file, const std_seq_t<T, std_allocator_t >& buffer, uint64_t length, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, std_seq_t, T, std_allocator_t >(file, buffer, length, buffer_offset, false, true);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write_line(const char (&file)[SZ], const std_seq_t<T, std_allocator_t >& buffer, uint64_t length, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, std_seq_t, T, std_allocator_t >(std::string(file), buffer, length, buffer_offset, false, true);
            }
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write_line(const std::string& file, const std_seq_t<T, std_allocator_t >& buffer, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, std_seq_t, T, std_allocator_t >(file, buffer, 0, 0, append, true);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write_line(const char (&file)[SZ], const std_seq_t<T, std_allocator_t >& buffer, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, std_seq_t, T, std_allocator_t >(std::string(file), buffer, 0, 0, append, true);
            }
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write_line(const std::string& file, const std_seq_t<T, std_allocator_t >& buffer, uint64_t length, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, std_seq_t, T, std_allocator_t >(file, buffer, length, buffer_offset, append, true);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write_line(const char (&file)[SZ], const std_seq_t<T, std_allocator_t >& buffer, uint64_t length, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, std_seq_t, T, std_allocator_t >(std::string(file), buffer, length, buffer_offset, append, true);
            }
            // char buf[]/wchar_t buf[]/uintX_t buf[]
            template < typename T, std::size_t SZ >
            uint64_t write_line(const std::string& file, const T (&buffer)[SZ])
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, T, SZ >(file, buffer, 0, 0, false, true);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t write_line(const char (&file)[FSZ], const T (&buffer)[SZ])
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, T, SZ >(std::string(file), buffer, 0, 0, false, true);
            }
            template < typename T, std::size_t SZ >
            uint64_t write_line(const std::string& file, const T (&buffer)[SZ], uint64_t length, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, T, SZ >(file, buffer, length, buffer_offset, false, true);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t write_line(const char (&file)[FSZ], const T (&buffer)[SZ], uint64_t length, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, T, SZ >(std::string(file), buffer, length, buffer_offset, false, true);
            }
            template < typename T, std::size_t SZ >
            uint64_t write_line(const std::string& file, const T (&buffer)[SZ], bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, T, SZ >(file, buffer, 0, 0, append, true);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t write_line(const char (&file)[FSZ], const T (&buffer)[SZ], bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, T, SZ >(std::string(file), buffer, 0, 0, append, true);
            }
            template < typename T, std::size_t SZ >
            uint64_t write_line(const std::string& file, const T (&buffer)[SZ], uint64_t length, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, T, SZ >(file, buffer, length, buffer_offset, append, true);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t write_line(const char (&file)[FSZ], const T (&buffer)[SZ], uint64_t length, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, T, SZ >(std::string(file), buffer, length, buffer_offset, append, true);
            }
            // omni::stack_buffer
            template < typename T, uint16_t SZ >
            uint64_t write_line(const std::string& file, const omni::stack_buffer<T, SZ>& buffer)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, T, SZ >(file, buffer, 0, 0, false, true);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t write_line(const char (&file)[FSZ], const omni::stack_buffer<T, SZ>& buffer)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, T, SZ >(std::string(file), buffer, 0, 0, false, true);
            }
            template < typename T, uint16_t SZ >
            uint64_t write_line(const std::string& file, const omni::stack_buffer<T, SZ>& buffer, uint64_t length, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, T, SZ >(file, buffer, length, buffer_offset, false, true);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t write_line(const char (&file)[FSZ], const omni::stack_buffer<T, SZ>& buffer, uint64_t length, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, T, SZ >(std::string(file), buffer, length, buffer_offset, false, true);
            }
            template < typename T, uint16_t SZ >
            uint64_t write_line(const std::string& file, const omni::stack_buffer<T, SZ>& buffer, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, T, SZ >(file, buffer, 0, 0, append, true);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t write_line(const char (&file)[FSZ], const omni::stack_buffer<T, SZ>& buffer, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, T, SZ >(std::string(file), buffer, 0, 0, append, true);
            }
            template < typename T, uint16_t SZ >
            uint64_t write_line(const std::string& file, const omni::stack_buffer<T, SZ>& buffer, uint64_t length, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, T, SZ >(file, buffer, length, buffer_offset, append, true);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t write_line(const char (&file)[FSZ], const omni::stack_buffer<T, SZ>& buffer, uint64_t length, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, T, SZ >(std::string(file), buffer, length, buffer_offset, append, true);
            }

            template < typename T >
            uint64_t unsafe_write_element(const std::string& file, const T* buffer, uint64_t elements, bool append)
            {
                return omni::io::file_internal::unsafe_write_el_fw< std::string, std::ofstream, T >(file, buffer, elements, append);
            }
            template < typename T >
            uint64_t unsafe_write_element(const std::string& file, const T* buffer, uint64_t elements)
            {
                return omni::io::file_internal::unsafe_write_el_fw< std::string, std::ofstream, T >(file, buffer, elements, false);
            }
            uint64_t unsafe_write(const std::string& file, const char* buffer, uint64_t length, bool append);
            uint64_t unsafe_write(const std::string& file, const wchar_t* buffer, uint64_t length, bool append);
            uint64_t unsafe_write(const std::string& file, const uint8_t* buffer, uint64_t length, bool append);
            uint64_t unsafe_write(const std::string& file, const int8_t* buffer, uint64_t length, bool append);
            uint64_t unsafe_write(const std::string& file, const char* buffer, uint64_t length);
            uint64_t unsafe_write(const std::string& file, const wchar_t* buffer, uint64_t length);
            uint64_t unsafe_write(const std::string& file, const uint8_t* buffer, uint64_t length);
            uint64_t unsafe_write(const std::string& file, const int8_t* buffer, uint64_t length);
            uint64_t unsafe_write_line(const std::string& file, const char* buffer, uint64_t length, bool append);
            uint64_t unsafe_write_line(const std::string& file, const wchar_t* buffer, uint64_t length, bool append);
            uint64_t unsafe_write_line(const std::string& file, const uint8_t* buffer, uint64_t length, bool append);
            uint64_t unsafe_write_line(const std::string& file, const int8_t* buffer, uint64_t length, bool append);
            uint64_t unsafe_write_line(const std::string& file, const char* buffer, uint64_t length);
            uint64_t unsafe_write_line(const std::string& file, const wchar_t* buffer, uint64_t length);
            uint64_t unsafe_write_line(const std::string& file, const uint8_t* buffer, uint64_t length);
            uint64_t unsafe_write_line(const std::string& file, const int8_t* buffer, uint64_t length);
        }
        namespace wfile {
            bool copy(const std::wstring& file, const std::wstring& new_name, const omni::io::options& io_ops);
            bool copy(const std::wstring& file, const std::wstring& new_name);
            bool create(const std::wstring& file, const omni::io::options& io_ops);
            bool create(const std::wstring& file);
            bool exists(const std::wstring& file);
            bool exist(const std::wstring& file);
            std::wstring get_contents(const std::wstring& file);
            uint64_t get_size(const std::wstring& file);
            bool move(const std::wstring& file, const std::wstring& new_name, const omni::io::options& io_ops);
            bool move(const std::wstring& file, const std::wstring& new_name);
            bool rename(const std::wstring& file, const std::wstring& new_name, const omni::io::options& io_ops);
            bool rename(const std::wstring& file, const std::wstring& new_name);
            uint64_t read(const std::wstring& file, std::wstring& buffer);
            // std::vector/deque/array/list/etc.
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t read(const std::wstring& file, std_seq_t<T, std_allocator_t >& buffer)
            {
                return omni::io::file_internal::rd< std::wstring, std::wifstream, std_seq_t, T, std_allocator_t >(file, buffer, 0, 0, std::ios_base::beg);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t read(const wchar_t (&file)[SZ], std_seq_t<T, std_allocator_t >& buffer)
            {
                return omni::io::file_internal::rd< std::wstring, std::wifstream, std_seq_t, T, std_allocator_t >(std::wstring(file), buffer, 0, 0, std::ios_base::beg);
            }
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t read(const std::wstring& file, std_seq_t<T, std_allocator_t >& buffer, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd< std::wstring, std::wifstream, std_seq_t, T, std_allocator_t >(file, buffer, 0, file_offset, offset_direction);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t read(const wchar_t (&file)[SZ], std_seq_t<T, std_allocator_t >& buffer, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd< std::wstring, std::wifstream, std_seq_t, T, std_allocator_t >(std::wstring(file), buffer, 0, file_offset, offset_direction);
            }
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t read(const std::wstring& file, std_seq_t<T, std_allocator_t >& buffer, uint64_t length, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd< std::wstring, std::wifstream, std_seq_t, T, std_allocator_t >(file, buffer, length, file_offset, offset_direction);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t read(const wchar_t (&file)[SZ], std_seq_t<T, std_allocator_t >& buffer, uint64_t length, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd< std::wstring, std::wifstream, std_seq_t, T, std_allocator_t >(std::wstring(file), buffer, length, file_offset, offset_direction);
            }
            // char buf[]/wchar_t buf[]/uintX_t buf[]
            template < typename T, std::size_t SZ >
            uint64_t read(const std::wstring &file, T (&buffer)[SZ])
            {
                return omni::io::file_internal::rd< std::wstring, std::wifstream, T, SZ >(file, buffer, 0, 0, 0, std::ios_base::beg);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t read(const wchar_t (&file)[FSZ], T (&buffer)[SZ])
            {
                return omni::io::file_internal::rd< std::wstring, std::wifstream, T, SZ >(std::wstring(file), buffer, 0, 0, 0, std::ios_base::beg);
            }
            template < typename T, std::size_t SZ >
            uint64_t read(const std::wstring &file, T (&buffer)[SZ], std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd< std::wstring, std::wifstream, T, SZ >(file, buffer, 0, 0, file_offset, offset_direction);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t read(const wchar_t (&file)[FSZ], T (&buffer)[SZ], std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd< std::wstring, std::wifstream, T, SZ >(std::wstring(file), buffer, 0, 0, file_offset, offset_direction);
            }
            template < typename T, std::size_t SZ >
            uint64_t read(const std::wstring &file, T (&buffer)[SZ], uint64_t length, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd< std::wstring, std::wifstream, T, SZ >(file, buffer, length, 0, file_offset, offset_direction);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t read(const wchar_t (&file)[FSZ], T (&buffer)[SZ], uint64_t length, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd< std::wstring, std::wifstream, T, SZ >(std::wstring(file), buffer, length, 0, file_offset, offset_direction);
            }
            template < typename T, std::size_t SZ >
            uint64_t read(const std::wstring &file, T (&buffer)[SZ], uint64_t length, std::size_t buffer_offset, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd< std::wstring, std::wifstream, T, SZ >(file, buffer, length, buffer_offset, file_offset, offset_direction);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t read(const wchar_t (&file)[FSZ], T (&buffer)[SZ], uint64_t length, std::size_t buffer_offset, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd< std::wstring, std::wifstream, T, SZ >(std::wstring(file), buffer, length, buffer_offset, file_offset, offset_direction);
            }
            // omni::stack_buffer
            template < typename T, uint16_t SZ >
            uint64_t read(const std::wstring &file, omni::stack_buffer<T, SZ>& buffer)
            {
                return omni::io::file_internal::rd< std::wstring, std::wifstream, T, SZ >(file, buffer, 0, 0, 0, std::ios_base::beg);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t read(const wchar_t (&file)[FSZ], omni::stack_buffer<T, SZ>& buffer)
            {
                return omni::io::file_internal::rd< std::wstring, std::wifstream, T, SZ >(std::wstring(file), buffer, 0, 0, 0, std::ios_base::beg);
            }
            template < typename T, uint16_t SZ >
            uint64_t read(const std::wstring &file, omni::stack_buffer<T, SZ>& buffer, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd< std::wstring, std::wifstream, T, SZ >(file, buffer, 0, 0, file_offset, offset_direction);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t read(const wchar_t (&file)[FSZ], omni::stack_buffer<T, SZ>& buffer, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd< std::wstring, std::wifstream, T, SZ >(std::wstring(file), buffer, 0, 0, file_offset, offset_direction);
            }
            template < typename T, uint16_t SZ >
            uint64_t read(const std::wstring &file, omni::stack_buffer<T, SZ>& buffer, uint64_t length, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd< std::wstring, std::wifstream, T, SZ >(file, buffer, length, 0, file_offset, offset_direction);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t read(const wchar_t (&file)[FSZ], omni::stack_buffer<T, SZ>& buffer, uint64_t length, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd< std::wstring, std::wifstream, T, SZ >(std::wstring(file), buffer, length, 0, file_offset, offset_direction);
            }
            template < typename T, uint16_t SZ >
            uint64_t read(const std::wstring &file, omni::stack_buffer<T, SZ>& buffer, uint64_t length, std::size_t buffer_offset, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd< std::wstring, std::wifstream, T, SZ >(file, buffer, length, buffer_offset, file_offset, offset_direction);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t read(const wchar_t (&file)[FSZ], omni::stack_buffer<T, SZ>& buffer, uint64_t length, std::size_t buffer_offset, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd< std::wstring, std::wifstream, T, SZ >(std::wstring(file), buffer, length, buffer_offset, file_offset, offset_direction);
            }
            // read_element
            // std::vector/deque/array/list/etc.
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t read_element(const std::wstring& file, std_seq_t<T, std_allocator_t >& buffer)
            {
                return omni::io::file_internal::rd_el< std::wstring, std::wifstream, std_seq_t, T, std_allocator_t >(file, buffer, 0, 0, std::ios_base::beg);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t read_element(const wchar_t (&file)[SZ], std_seq_t<T, std_allocator_t >& buffer)
            {
                return omni::io::file_internal::rd_el< std::wstring, std::wifstream, std_seq_t, T, std_allocator_t >(std::wstring(file), buffer, 0, 0, std::ios_base::beg);
            }
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t read_element(const std::wstring& file, std_seq_t<T, std_allocator_t >& buffer, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd_el< std::wstring, std::wifstream, std_seq_t, T, std_allocator_t >(file, buffer, 0, file_offset, offset_direction);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t read_element(const wchar_t (&file)[SZ], std_seq_t<T, std_allocator_t >& buffer, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd_el< std::wstring, std::wifstream, std_seq_t, T, std_allocator_t >(std::wstring(file), buffer, 0, file_offset, offset_direction);
            }
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t read_element(const std::wstring& file, std_seq_t<T, std_allocator_t >& buffer, uint64_t elements, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd_el< std::wstring, std::wifstream, std_seq_t, T, std_allocator_t >(file, buffer, elements, file_offset, offset_direction);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t read_element(const wchar_t (&file)[SZ], std_seq_t<T, std_allocator_t >& buffer, uint64_t elements, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd_el< std::wstring, std::wifstream, std_seq_t, T, std_allocator_t >(std::wstring(file), buffer, elements, file_offset, offset_direction);
            }
            // char buf[]/wchar_t buf[]/uintX_t buf[]
            template < typename T, std::size_t SZ >
            uint64_t read_element(const std::wstring& file, T (&buffer)[SZ])
            {
                return omni::io::file_internal::rd_el< std::wstring, std::wifstream, T, SZ >(file, buffer, 0, 0, 0, std::ios_base::beg);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t read_element(const wchar_t (&file)[FSZ], T (&buffer)[SZ])
            {
                return omni::io::file_internal::rd_el< std::wstring, std::wifstream, T, SZ >(std::wstring(file), buffer, 0, 0, 0, std::ios_base::beg);
            }
            template < typename T, std::size_t SZ >
            uint64_t read_element(const std::wstring& file, T (&buffer)[SZ], std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd_el< std::wstring, std::wifstream, T, SZ >(file, buffer, 0, 0, file_offset, offset_direction);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t read_element(const wchar_t (&file)[FSZ], T (&buffer)[SZ], std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd_el< std::wstring, std::wifstream, T, SZ >(std::wstring(file), buffer, 0, 0, file_offset, offset_direction);
            }
            template < typename T, std::size_t SZ >
            uint64_t read_element(const std::wstring& file, T (&buffer)[SZ], uint64_t elements, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd_el< std::wstring, std::wifstream, T, SZ >(file, buffer, elements, 0, file_offset, offset_direction);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t read_element(const wchar_t (&file)[FSZ], T (&buffer)[SZ], uint64_t elements, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd_el< std::wstring, std::wifstream, T, SZ >(std::wstring(file), buffer, elements, 0, file_offset, offset_direction);
            }
            template < typename T, std::size_t SZ >
            uint64_t read_element(const std::wstring& file, T (&buffer)[SZ], uint64_t elements, std::size_t buffer_offset, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd_el< std::wstring, std::wifstream, T, SZ >(file, buffer, elements, buffer_offset, file_offset, offset_direction);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t read_element(const wchar_t (&file)[FSZ], T (&buffer)[SZ], uint64_t elements, std::size_t buffer_offset, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd_el< std::wstring, std::wifstream, T, SZ >(std::wstring(file), buffer, elements, buffer_offset, file_offset, offset_direction);
            }
            // omni::stack_buffer
            template < typename T, uint16_t SZ >
            uint64_t read_element(const std::wstring& file, omni::stack_buffer<T, SZ>& buffer)
            {
                return omni::io::file_internal::rd_el< std::wstring, std::wifstream, T, SZ >(file, buffer, 0, 0, 0, std::ios_base::beg);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t read_element(const wchar_t (&file)[FSZ], omni::stack_buffer<T, SZ>& buffer)
            {
                return omni::io::file_internal::rd_el< std::wstring, std::wifstream, T, SZ >(std::wstring(file), buffer, 0, 0, 0, std::ios_base::beg);
            }
            template < typename T, uint16_t SZ >
            uint64_t read_element(const std::wstring& file, omni::stack_buffer<T, SZ>& buffer, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd_el< std::wstring, std::wifstream, T, SZ >(file, buffer, 0, 0, file_offset, offset_direction);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t read_element(const wchar_t (&file)[FSZ], omni::stack_buffer<T, SZ>& buffer, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd_el< std::wstring, std::wifstream, T, SZ >(std::wstring(file), buffer, 0, 0, file_offset, offset_direction);
            }
            template < typename T, uint16_t SZ >
            uint64_t read_element(const std::wstring& file, omni::stack_buffer<T, SZ>& buffer, uint64_t elements, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd_el< std::wstring, std::wifstream, T, SZ >(file, buffer, elements, 0, file_offset, offset_direction);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t read_element(const wchar_t (&file)[FSZ], omni::stack_buffer<T, SZ>& buffer, uint64_t elements, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd_el< std::wstring, std::wifstream, T, SZ >(std::wstring(file), buffer, elements, 0, file_offset, offset_direction);
            }
            template < typename T, uint16_t SZ >
            uint64_t read_element(const std::wstring& file, omni::stack_buffer<T, SZ>& buffer, uint64_t elements, std::size_t buffer_offset, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd_el< std::wstring, std::wifstream, T, SZ >(file, buffer, elements, buffer_offset, file_offset, offset_direction);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t read_element(const wchar_t (&file)[FSZ], omni::stack_buffer<T, SZ>& buffer, uint64_t elements, std::size_t buffer_offset, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd_el< std::wstring, std::wifstream, T, SZ >(std::wstring(file), buffer, elements, buffer_offset, file_offset, offset_direction);
            }
            template < typename T >
            uint64_t unsafe_read_element(const std::wstring& file, T* buffer, uint64_t elements)
            {
                return omni::io::file_internal::unsafe_rd_el< std::wstring, std::wifstream, T >(file, buffer, elements);
            }
            uint64_t unsafe_read(const std::wstring& file, char* buffer, uint64_t length);
            uint64_t unsafe_read(const std::wstring& file, wchar_t* buffer, uint64_t length);
            uint64_t unsafe_read(const std::wstring& file, uint8_t* buffer, uint64_t length);
            uint64_t unsafe_read(const std::wstring& file, int8_t* buffer, uint64_t length);
            bool remove(const std::wstring& file);
            #if defined(OMNI_NON_PORTABLE)
                bool set_size(const std::wstring& file, uint64_t size);
            #endif
            uint64_t write(const std::wstring& file, const std::wstring& buffer, bool append);
            uint64_t write(const std::wstring& file, const std::wstring& buffer);
            // std::vector/deque/array/list/etc.
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write(const std::wstring& file, const std_seq_t<T, std_allocator_t >& buffer)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, std_seq_t, T, std_allocator_t >(file, buffer, 0, 0, false, false);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write(const wchar_t (&file)[SZ], const std_seq_t<T, std_allocator_t >& buffer)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, std_seq_t, T, std_allocator_t >(std::wstring(file), buffer, 0, 0, false, false);
            }
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write(const std::wstring& file, const std_seq_t<T, std_allocator_t >& buffer, uint64_t length, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, std_seq_t, T, std_allocator_t >(file, buffer, length, buffer_offset, false, false);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write(const wchar_t (&file)[SZ], const std_seq_t<T, std_allocator_t >& buffer, uint64_t length, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, std_seq_t, T, std_allocator_t >(std::wstring(file), buffer, length, buffer_offset, false, false);
            }
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write(const std::wstring& file, const std_seq_t<T, std_allocator_t >& buffer, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, std_seq_t, T, std_allocator_t >(file, buffer, 0, 0, append, false);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write(const wchar_t (&file)[SZ], const std_seq_t<T, std_allocator_t >& buffer, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, std_seq_t, T, std_allocator_t >(std::wstring(file), buffer, 0, 0, append, false);
            }
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write(const std::wstring& file, const std_seq_t<T, std_allocator_t >& buffer, uint64_t length, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, std_seq_t, T, std_allocator_t >(file, buffer, length, buffer_offset, append, false);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write(const wchar_t (&file)[SZ], const std_seq_t<T, std_allocator_t >& buffer, uint64_t length, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, std_seq_t, T, std_allocator_t >(std::wstring(file), buffer, length, buffer_offset, append, false);
            }
            // char buf[]/wchar_t buf[]/uintX_t buf[]
            template < typename T, std::size_t SZ >
            uint64_t write(const std::wstring& file, const T (&buffer)[SZ])
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, T, SZ >(file, buffer, 0, 0, false, false);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t write(const wchar_t (&file)[FSZ], const T (&buffer)[SZ])
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, T, SZ >(std::wstring(file), buffer, 0, 0, false, false);
            }
            template < typename T, std::size_t SZ >
            uint64_t write(const std::wstring& file, const T (&buffer)[SZ], uint64_t length, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, T, SZ >(file, buffer, length, buffer_offset, false, false);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t write(const wchar_t (&file)[FSZ], const T (&buffer)[SZ], uint64_t length, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, T, SZ >(std::wstring(file), buffer, length, buffer_offset, false, false);
            }
            template < typename T, std::size_t SZ >
            uint64_t write(const std::wstring& file, const T (&buffer)[SZ], bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, T, SZ >(file, buffer, 0, 0, append, false);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t write(const wchar_t (&file)[FSZ], const T (&buffer)[SZ], bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, T, SZ >(std::wstring(file), buffer, 0, 0, append, false);
            }
            template < typename T, std::size_t SZ >
            uint64_t write(const std::wstring& file, const T (&buffer)[SZ], uint64_t length, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, T, SZ >(file, buffer, length, buffer_offset, append, false);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t write(const wchar_t (&file)[FSZ], const T (&buffer)[SZ], uint64_t length, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, T, SZ >(std::wstring(file), buffer, length, buffer_offset, append, false);
            }
            // omni::stack_buffer
            template < typename T, uint16_t SZ >
            uint64_t write(const std::wstring& file, const omni::stack_buffer<T, SZ>& buffer)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, T, SZ >(file, buffer, 0, 0, false, false);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t write(const wchar_t (&file)[FSZ], const omni::stack_buffer<T, SZ>& buffer)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, T, SZ >(std::wstring(file), buffer, 0, 0, false, false);
            }            
            template < typename T, uint16_t SZ >
            uint64_t write(const std::wstring& file, const omni::stack_buffer<T, SZ>& buffer, uint64_t length, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, T, SZ >(file, buffer, length, buffer_offset, false, false);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t write(const wchar_t (&file)[FSZ], const omni::stack_buffer<T, SZ>& buffer, uint64_t length, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, T, SZ >(std::wstring(file), buffer, length, buffer_offset, false, false);
            }
            template < typename T, uint16_t SZ >
            uint64_t write(const std::wstring& file, const omni::stack_buffer<T, SZ>& buffer, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, T, SZ >(file, buffer, 0, 0, append, false);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t write(const wchar_t (&file)[FSZ], const omni::stack_buffer<T, SZ>& buffer, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, T, SZ >(std::wstring(file), buffer, 0, 0, append, false);
            }
            template < typename T, uint16_t SZ >
            uint64_t write(const std::wstring& file, const omni::stack_buffer<T, SZ>& buffer, uint64_t length, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, T, SZ >(file, buffer, length, buffer_offset, append, false);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t write(const wchar_t (&file)[FSZ], const omni::stack_buffer<T, SZ>& buffer, uint64_t length, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, T, SZ >(std::wstring(file), buffer, length, buffer_offset, append, false);
            }
            // write_element
            // std::vector/deque/array/list/etc.
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write_element(const std::wstring& file, const std_seq_t<T, std_allocator_t >& buffer)
            {
                return omni::io::file_internal::write_el_fw< std::wstring, std::wofstream, std_seq_t, T, std_allocator_t >(file, buffer, 0, 0, false, false);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write_element(const wchar_t (&file)[SZ], const std_seq_t<T, std_allocator_t >& buffer)
            {
                return omni::io::file_internal::write_el_fw< std::wstring, std::wofstream, std_seq_t, T, std_allocator_t >(std::wstring(file), buffer, 0, 0, false, false);
            }
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write_element(const std::wstring& file, const std_seq_t<T, std_allocator_t >& buffer, uint64_t elements, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_el_fw< std::wstring, std::wofstream, std_seq_t, T, std_allocator_t >(file, buffer, elements, buffer_offset, false, false);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write_element(const wchar_t (&file)[SZ], const std_seq_t<T, std_allocator_t >& buffer, uint64_t elements, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_el_fw< std::wstring, std::wofstream, std_seq_t, T, std_allocator_t >(std::wstring(file), buffer, elements, buffer_offset, false, false);
            }
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write_element(const std::wstring& file, const std_seq_t<T, std_allocator_t >& buffer, bool append)
            {
                return omni::io::file_internal::write_el_fw< std::wstring, std::wofstream, std_seq_t, T, std_allocator_t >(file, buffer, 0, 0, append, false);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write_element(const wchar_t (&file)[SZ], const std_seq_t<T, std_allocator_t >& buffer, bool append)
            {
                return omni::io::file_internal::write_el_fw< std::wstring, std::wofstream, std_seq_t, T, std_allocator_t >(std::wstring(file), buffer, 0, 0, append, false);
            }
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write_element(const std::wstring& file, const std_seq_t<T, std_allocator_t >& buffer, uint64_t elements, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_el_fw< std::wstring, std::wofstream, std_seq_t, T, std_allocator_t >(file, buffer, elements, buffer_offset, append, false);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write_element(const wchar_t (&file)[SZ], const std_seq_t<T, std_allocator_t >& buffer, uint64_t elements, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_el_fw< std::wstring, std::wofstream, std_seq_t, T, std_allocator_t >(std::wstring(file), buffer, elements, buffer_offset, append, false);
            }
            // char buf[]/wchar_t buf[]/uintX_t buf[]
            template < typename T, std::size_t SZ >
            uint64_t write_element(const std::wstring& file, const T (&buffer)[SZ])
            {
                return omni::io::file_internal::write_el_fw< std::wstring, std::wofstream, T, SZ >(file, buffer, 0, 0, false, false);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t write_element(const wchar_t (&file)[FSZ], const T (&buffer)[SZ])
            {
                return omni::io::file_internal::write_el_fw< std::wstring, std::wofstream, T, SZ >(std::wstring(file), buffer, 0, 0, false, false);
            }
            template < typename T, std::size_t SZ >
            uint64_t write_element(const std::wstring& file, const T (&buffer)[SZ], uint64_t elements, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_el_fw< std::wstring, std::wofstream, T, SZ >(file, buffer, elements, buffer_offset, false, false);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t write_element(const wchar_t (&file)[FSZ], const T (&buffer)[SZ], uint64_t elements, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_el_fw< std::wstring, std::wofstream, T, SZ >(std::wstring(file), buffer, elements, buffer_offset, false, false);
            }
            template < typename T, std::size_t SZ >
            uint64_t write_element(const std::wstring& file, const T (&buffer)[SZ], bool append)
            {
                return omni::io::file_internal::write_el_fw< std::wstring, std::wofstream, T, SZ >(file, buffer, 0, 0, append, false);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t write_element(const wchar_t (&file)[FSZ], const T (&buffer)[SZ], bool append)
            {
                return omni::io::file_internal::write_el_fw< std::wstring, std::wofstream, T, SZ >(std::wstring(file), buffer, 0, 0, append, false);
            }
            template < typename T, std::size_t SZ >
            uint64_t write_element(const std::wstring& file, const T (&buffer)[SZ], uint64_t elements, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_el_fw< std::wstring, std::wofstream, T, SZ >(file, buffer, elements, buffer_offset, append, false);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t write_element(const wchar_t (&file)[FSZ], const T (&buffer)[SZ], uint64_t elements, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_el_fw< std::wstring, std::wofstream, T, SZ >(std::wstring(file), buffer, elements, buffer_offset, append, false);
            }
            // omni::stack_buffer
            template < typename T, uint16_t SZ >
            uint64_t write_element(const std::wstring& file, const omni::stack_buffer<T, SZ>& buffer)
            {
                return omni::io::file_internal::write_el_fw< std::wstring, std::wofstream, T, SZ >(file, buffer, 0, 0, false, false);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t write_element(const wchar_t (&file)[FSZ], const omni::stack_buffer<T, SZ>& buffer)
            {
                return omni::io::file_internal::write_el_fw< std::wstring, std::wofstream, T, SZ >(std::wstring(file), buffer, 0, 0, false, false);
            }
            template < typename T, uint16_t SZ >
            uint64_t write_element(const std::wstring& file, const omni::stack_buffer<T, SZ>& buffer, uint64_t elements, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_el_fw< std::wstring, std::wofstream, T, SZ >(file, buffer, elements, buffer_offset, false, false);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t write_element(const wchar_t (&file)[FSZ], const omni::stack_buffer<T, SZ>& buffer, uint64_t elements, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_el_fw< std::wstring, std::wofstream, T, SZ >(std::wstring(file), buffer, elements, buffer_offset, false, false);
            }
            template < typename T, uint16_t SZ >
            uint64_t write_element(const std::wstring& file, const omni::stack_buffer<T, SZ>& buffer, bool append)
            {
                return omni::io::file_internal::write_el_fw< std::wstring, std::wofstream, T, SZ >(file, buffer, 0, 0, append, false);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t write_element(const wchar_t (&file)[FSZ], const omni::stack_buffer<T, SZ>& buffer, bool append)
            {
                return omni::io::file_internal::write_el_fw< std::wstring, std::wofstream, T, SZ >(std::wstring(file), buffer, 0, 0, append, false);
            }
            template < typename T, uint16_t SZ >
            uint64_t write_element(const std::wstring& file, const omni::stack_buffer<T, SZ>& buffer, uint64_t elements, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_el_fw< std::wstring, std::wofstream, T, SZ >(file, buffer, elements, buffer_offset, append, false);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t write_element(const wchar_t (&file)[FSZ], const omni::stack_buffer<T, SZ>& buffer, uint64_t elements, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_el_fw< std::wstring, std::wofstream, T, SZ >(std::wstring(file), buffer, elements, buffer_offset, append, false);
            }

            uint64_t write_line(const std::wstring& file, const std::wstring& buffer, bool append);
            uint64_t write_line(const std::wstring& file, const std::wstring& buffer);
            // std::vector/deque/array/list/etc.
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write_line(const std::wstring& file, const std_seq_t<T, std_allocator_t >& buffer)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, std_seq_t, T, std_allocator_t >(file, buffer, 0, 0, false, true);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write_line(const wchar_t (&file)[SZ], const std_seq_t<T, std_allocator_t >& buffer)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, std_seq_t, T, std_allocator_t >(std::wstring(file), buffer, 0, 0, false, true);
            }
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write_line(const std::wstring& file, const std_seq_t<T, std_allocator_t >& buffer, uint64_t length, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, std_seq_t, T, std_allocator_t >(file, buffer, length, buffer_offset, false, true);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write_line(const wchar_t (&file)[SZ], const std_seq_t<T, std_allocator_t >& buffer, uint64_t length, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, std_seq_t, T, std_allocator_t >(std::wstring(file), buffer, length, buffer_offset, false, true);
            }
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write_line(const std::wstring& file, const std_seq_t<T, std_allocator_t >& buffer, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, std_seq_t, T, std_allocator_t >(file, buffer, 0, 0, append, true);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write_line(const wchar_t (&file)[SZ], const std_seq_t<T, std_allocator_t >& buffer, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, std_seq_t, T, std_allocator_t >(std::wstring(file), buffer, 0, 0, append, true);
            }
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write_line(const std::wstring& file, const std_seq_t<T, std_allocator_t >& buffer, uint64_t length, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, std_seq_t, T, std_allocator_t >(file, buffer, length, buffer_offset, append, true);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write_line(const wchar_t (&file)[SZ], const std_seq_t<T, std_allocator_t >& buffer, uint64_t length, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, std_seq_t, T, std_allocator_t >(std::wstring(file), buffer, length, buffer_offset, append, true);
            }
            // char buf[]/wchar_t buf[]/uintX_t buf[]
            template < typename T, std::size_t SZ >
            uint64_t write_line(const std::wstring& file, const T (&buffer)[SZ])
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, T, SZ >(file, buffer, 0, 0, false, true);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t write_line(const wchar_t (&file)[FSZ], const T (&buffer)[SZ])
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, T, SZ >(std::wstring(file), buffer, 0, 0, false, true);
            }
            template < typename T, std::size_t SZ >
            uint64_t write_line(const std::wstring& file, const T (&buffer)[SZ], uint64_t length, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, T, SZ >(file, buffer, length, buffer_offset, false, true);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t write_line(const wchar_t (&file)[FSZ], const T (&buffer)[SZ], uint64_t length, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, T, SZ >(std::wstring(file), buffer, length, buffer_offset, false, true);
            }
            template < typename T, std::size_t SZ >
            uint64_t write_line(const std::wstring& file, const T (&buffer)[SZ], bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, T, SZ >(file, buffer, 0, 0, append, true);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t write_line(const wchar_t (&file)[FSZ], const T (&buffer)[SZ], bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, T, SZ >(std::wstring(file), buffer, 0, 0, append, true);
            }
            template < typename T, std::size_t SZ >
            uint64_t write_line(const std::wstring& file, const T (&buffer)[SZ], uint64_t length, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, T, SZ >(file, buffer, length, buffer_offset, append, true);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t write_line(const wchar_t (&file)[FSZ], const T (&buffer)[SZ], uint64_t length, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, T, SZ >(std::wstring(file), buffer, length, buffer_offset, append, true);
            }
            // omni::stack_buffer
            template < typename T, uint16_t SZ >
            uint64_t write_line(const std::wstring& file, const omni::stack_buffer<T, SZ>& buffer)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, T, SZ >(file, buffer, 0, 0, false, true);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t write_line(const wchar_t (&file)[FSZ], const omni::stack_buffer<T, SZ>& buffer)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, T, SZ >(std::wstring(file), buffer, 0, 0, false, true);
            }
            template < typename T, uint16_t SZ >
            uint64_t write_line(const std::wstring& file, const omni::stack_buffer<T, SZ>& buffer, uint64_t length, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, T, SZ >(file, buffer, length, buffer_offset, false, true);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t write_line(const wchar_t (&file)[FSZ], const omni::stack_buffer<T, SZ>& buffer, uint64_t length, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, T, SZ >(std::wstring(file), buffer, length, buffer_offset, false, true);
            }
            template < typename T, uint16_t SZ >
            uint64_t write_line(const std::wstring& file, const omni::stack_buffer<T, SZ>& buffer, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, T, SZ >(file, buffer, 0, 0, append, true);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t write_line(const wchar_t (&file)[FSZ], const omni::stack_buffer<T, SZ>& buffer, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, T, SZ >(std::wstring(file), buffer, 0, 0, append, true);
            }
            template < typename T, uint16_t SZ >
            uint64_t write_line(const std::wstring& file, const omni::stack_buffer<T, SZ>& buffer, uint64_t length, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, T, SZ >(file, buffer, length, buffer_offset, append, true);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t write_line(const wchar_t (&file)[FSZ], const omni::stack_buffer<T, SZ>& buffer, uint64_t length, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, T, SZ >(std::wstring(file), buffer, length, buffer_offset, append, true);
            }
            template < typename T >
            uint64_t unsafe_write_element(const std::wstring& file, const T* buffer, uint64_t elements, bool append)
            {
                return omni::io::file_internal::unsafe_write_el_fw< std::wstring, std::wofstream, T >(file, buffer, elements, append);
            }
            template < typename T >
            uint64_t unsafe_write_element(const std::wstring& file, const T* buffer, uint64_t elements)
            {
                return omni::io::file_internal::unsafe_write_el_fw< std::wstring, std::wofstream, T >(file, buffer, elements, false);
            }
            uint64_t unsafe_write(const std::wstring& file, const char* buffer, uint64_t length, bool append);
            uint64_t unsafe_write(const std::wstring& file, const wchar_t* buffer, uint64_t length, bool append);
            uint64_t unsafe_write(const std::wstring& file, const uint8_t* buffer, uint64_t length, bool append);
            uint64_t unsafe_write(const std::wstring& file, const int8_t* buffer, uint64_t length, bool append);
            uint64_t unsafe_write(const std::wstring& file, const char* buffer, uint64_t length);
            uint64_t unsafe_write(const std::wstring& file, const wchar_t* buffer, uint64_t length);
            uint64_t unsafe_write(const std::wstring& file, const uint8_t* buffer, uint64_t length);
            uint64_t unsafe_write(const std::wstring& file, const int8_t* buffer, uint64_t length);
            uint64_t unsafe_write_line(const std::wstring& file, const char* buffer, uint64_t length, bool append);
            uint64_t unsafe_write_line(const std::wstring& file, const wchar_t* buffer, uint64_t length, bool append);
            uint64_t unsafe_write_line(const std::wstring& file, const uint8_t* buffer, uint64_t length, bool append);
            uint64_t unsafe_write_line(const std::wstring& file, const int8_t* buffer, uint64_t length, bool append);
            uint64_t unsafe_write_line(const std::wstring& file, const char* buffer, uint64_t length);
            uint64_t unsafe_write_line(const std::wstring& file, const wchar_t* buffer, uint64_t length);
            uint64_t unsafe_write_line(const std::wstring& file, const uint8_t* buffer, uint64_t length);
            uint64_t unsafe_write_line(const std::wstring& file, const int8_t* buffer, uint64_t length);
        }
        namespace file {
            // std::string
            inline bool copy(const std::string& file, const std::string& new_name, const omni::io::options& io_ops) { return omni::io::cfile::copy(file, new_name, io_ops); }
            inline bool copy(const std::string& file, const std::string& new_name) { return omni::io::cfile::copy(file, new_name); }
            inline bool create(const std::string& file, const omni::io::options& io_ops) { return omni::io::cfile::create(file, io_ops); }
            inline bool create(const std::string& file) { return omni::io::cfile::create(file); }
            inline bool exists(const std::string& file) { return omni::io::cfile::exists(file); }
            inline bool exist(const std::string& file) { return omni::io::cfile::exist(file); }
            inline std::string get_contents(const std::string& file) { return omni::io::cfile::get_contents(file); }
            inline uint64_t get_size(const std::string& file) { return omni::io::cfile::get_size(file); }
            inline bool move(const std::string& file, const std::string& new_name, const omni::io::options& io_ops) { return omni::io::cfile::move(file, new_name, io_ops); }
            inline bool move(const std::string& file, const std::string& new_name) { return omni::io::cfile::move(file, new_name); }
            inline bool rename(const std::string& file, const std::string& new_name, const omni::io::options& io_ops) { return omni::io::cfile::rename(file, new_name, io_ops); }
            inline bool rename(const std::string& file, const std::string& new_name) { return omni::io::cfile::rename(file, new_name); }
            inline uint64_t read(const std::string& file, std::string& buffer) { return omni::io::cfile::read(file, buffer); }
            // std::vector/deque/array/list/etc.
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t read(const std::string& file, std_seq_t<T, std_allocator_t >& buffer)
            {
                return omni::io::file_internal::rd< std::string, std::ifstream, std_seq_t, T, std_allocator_t >(file, buffer, 0, 0, std::ios_base::beg);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t read(const char (&file)[SZ], std_seq_t<T, std_allocator_t >& buffer)
            {
                return omni::io::file_internal::rd< std::string, std::ifstream, std_seq_t, T, std_allocator_t >(std::string(file), buffer, 0, 0, std::ios_base::beg);
            }
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t read(const std::string& file, std_seq_t<T, std_allocator_t >& buffer, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd< std::string, std::ifstream, std_seq_t, T, std_allocator_t >(file, buffer, 0, file_offset, offset_direction);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t read(const char (&file)[SZ], std_seq_t<T, std_allocator_t >& buffer, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd< std::string, std::ifstream, std_seq_t, T, std_allocator_t >(std::string(file), buffer, 0, file_offset, offset_direction);
            }
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t read(const std::string& file, std_seq_t<T, std_allocator_t >& buffer, uint64_t length, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd< std::string, std::ifstream, std_seq_t, T, std_allocator_t >(file, buffer, length, file_offset, offset_direction);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t read(const char (&file)[SZ], std_seq_t<T, std_allocator_t >& buffer, uint64_t length, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd< std::string, std::ifstream, std_seq_t, T, std_allocator_t >(std::string(file), buffer, length, file_offset, offset_direction);
            }
            // char buf[]/wchar_t buf[]/uintX_t buf[]
            template < typename T, std::size_t SZ >
            uint64_t read(const std::string& file, T (&buffer)[SZ])
            {
                return omni::io::file_internal::rd< std::string, std::ifstream, T, SZ >(file, buffer, 0, 0, 0, std::ios_base::beg);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t read(const char (&file)[FSZ], T (&buffer)[SZ])
            {
                return omni::io::file_internal::rd< std::string, std::ifstream, T, SZ >(std::string(file), buffer, 0, 0, 0, std::ios_base::beg);
            }
            template < typename T, std::size_t SZ >
            uint64_t read(const std::string& file, T (&buffer)[SZ], std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd< std::string, std::ifstream, T, SZ >(file, buffer, 0, 0, file_offset, offset_direction);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t read(const char (&file)[FSZ], T (&buffer)[SZ], std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd< std::string, std::ifstream, T, SZ >(std::string(file), buffer, 0, 0, file_offset, offset_direction);
            }
            template < typename T, std::size_t SZ >
            uint64_t read(const std::string& file, T (&buffer)[SZ], uint64_t length, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd< std::string, std::ifstream, T, SZ >(file, buffer, length, 0, file_offset, offset_direction);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t read(const char (&file)[FSZ], T (&buffer)[SZ], uint64_t length, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd< std::string, std::ifstream, T, SZ >(std::string(file), buffer, length, 0, file_offset, offset_direction);
            }
            template < typename T, std::size_t SZ >
            uint64_t read(const std::string& file, T (&buffer)[SZ], uint64_t length, std::size_t buffer_offset, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd< std::string, std::ifstream, T, SZ >(file, buffer, length, buffer_offset, file_offset, offset_direction);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t read(const char (&file)[FSZ], T (&buffer)[SZ], uint64_t length, std::size_t buffer_offset, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd< std::string, std::ifstream, T, SZ >(std::string(file), buffer, length, buffer_offset, file_offset, offset_direction);
            }
            // omni::stack_buffer
            template < typename T, uint16_t SZ >
            uint64_t read(const std::string& file, omni::stack_buffer<T, SZ>& buffer)
            {
                return omni::io::file_internal::rd< std::string, std::ifstream, T, SZ >(file, buffer, 0, 0, 0, std::ios_base::beg);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t read(const char (&file)[FSZ], omni::stack_buffer<T, SZ>& buffer)
            {
                return omni::io::file_internal::rd< std::string, std::ifstream, T, SZ >(std::string(file), buffer, 0, 0, 0, std::ios_base::beg);
            }
            template < typename T, uint16_t SZ >
            uint64_t read(const std::string& file, omni::stack_buffer<T, SZ>& buffer, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd< std::string, std::ifstream, T, SZ >(file, buffer, 0, 0, file_offset, offset_direction);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t read(const char (&file)[FSZ], omni::stack_buffer<T, SZ>& buffer, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd< std::string, std::ifstream, T, SZ >(std::string(file), buffer, 0, 0, file_offset, offset_direction);
            }
            template < typename T, uint16_t SZ >
            uint64_t read(const std::string& file, omni::stack_buffer<T, SZ>& buffer, uint64_t length, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd< std::string, std::ifstream, T, SZ >(file, buffer, length, 0, file_offset, offset_direction);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t read(const char (&file)[FSZ], omni::stack_buffer<T, SZ>& buffer, uint64_t length, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd< std::string, std::ifstream, T, SZ >(std::string(file), buffer, length, 0, file_offset, offset_direction);
            }
            template < typename T, uint16_t SZ >
            uint64_t read(const std::string& file, omni::stack_buffer<T, SZ>& buffer, uint64_t length, std::size_t buffer_offset, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd< std::string, std::ifstream, T, SZ >(file, buffer, length, buffer_offset, file_offset, offset_direction);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t read(const char (&file)[FSZ], omni::stack_buffer<T, SZ>& buffer, uint64_t length, std::size_t buffer_offset, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd< std::string, std::ifstream, T, SZ >(std::string(file), buffer, length, buffer_offset, file_offset, offset_direction);
            }

            // read_element
            // std::vector/deque/array/list/etc.
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t read_element(const std::string& file, std_seq_t<T, std_allocator_t >& buffer)
            {
                return omni::io::file_internal::rd_el< std::string, std::ifstream, std_seq_t, T, std_allocator_t >(file, buffer, 0, 0, std::ios_base::beg);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t read_element(const char (&file)[SZ], std_seq_t<T, std_allocator_t >& buffer)
            {
                return omni::io::file_internal::rd_el< std::string, std::ifstream, std_seq_t, T, std_allocator_t >(std::string(file), buffer, 0, 0, std::ios_base::beg);
            }
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t read_element(const std::string& file, std_seq_t<T, std_allocator_t >& buffer, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd_el< std::string, std::ifstream, std_seq_t, T, std_allocator_t >(file, buffer, 0, file_offset, offset_direction);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t read_element(const char (&file)[SZ], std_seq_t<T, std_allocator_t >& buffer, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd_el< std::string, std::ifstream, std_seq_t, T, std_allocator_t >(std::string(file), buffer, 0, file_offset, offset_direction);
            }
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t read_element(const std::string& file, std_seq_t<T, std_allocator_t >& buffer, uint64_t elements, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd_el< std::string, std::ifstream, std_seq_t, T, std_allocator_t >(file, buffer, elements, file_offset, offset_direction);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t read_element(const char (&file)[SZ], std_seq_t<T, std_allocator_t >& buffer, uint64_t elements, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd_el< std::string, std::ifstream, std_seq_t, T, std_allocator_t >(std::string(file), buffer, elements, file_offset, offset_direction);
            }
            // char buf[]/wchar_t buf[]/uintX_t buf[]
            template < typename T, std::size_t SZ >
            uint64_t read_element(const std::string& file, T (&buffer)[SZ])
            {
                return omni::io::file_internal::rd_el< std::string, std::ifstream, T, SZ >(file, buffer, 0, 0, 0, std::ios_base::beg);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t read_element(const char (&file)[FSZ], T (&buffer)[SZ])
            {
                return omni::io::file_internal::rd_el< std::string, std::ifstream, T, SZ >(std::string(file), buffer, 0, 0, 0, std::ios_base::beg);
            }
            template < typename T, std::size_t SZ >
            uint64_t read_element(const std::string& file, T (&buffer)[SZ], std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd_el< std::string, std::ifstream, T, SZ >(file, buffer, 0, 0, file_offset, offset_direction);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t read_element(const char (&file)[FSZ], T (&buffer)[SZ], std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd_el< std::string, std::ifstream, T, SZ >(std::string(file), buffer, 0, 0, file_offset, offset_direction);
            }
            template < typename T, std::size_t SZ >
            uint64_t read_element(const std::string& file, T (&buffer)[SZ], uint64_t elements, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd_el< std::string, std::ifstream, T, SZ >(file, buffer, elements, 0, file_offset, offset_direction);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t read_element(const char (&file)[FSZ], T (&buffer)[SZ], uint64_t elements, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd_el< std::string, std::ifstream, T, SZ >(std::string(file), buffer, elements, 0, file_offset, offset_direction);
            }
            template < typename T, std::size_t SZ >
            uint64_t read_element(const std::string& file, T (&buffer)[SZ], uint64_t elements, std::size_t buffer_offset, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd_el< std::string, std::ifstream, T, SZ >(file, buffer, elements, buffer_offset, file_offset, offset_direction);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t read_element(const char (&file)[FSZ], T (&buffer)[SZ], uint64_t elements, std::size_t buffer_offset, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd_el< std::string, std::ifstream, T, SZ >(std::string(file), buffer, elements, buffer_offset, file_offset, offset_direction);
            }
            // omni::stack_buffer
            template < typename T, uint16_t SZ >
            uint64_t read_element(const std::string& file, omni::stack_buffer<T, SZ>& buffer)
            {
                return omni::io::file_internal::rd_el< std::string, std::ifstream, T, SZ >(file, buffer, 0, 0, 0, std::ios_base::beg);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t read_element(const char (&file)[FSZ], omni::stack_buffer<T, SZ>& buffer)
            {
                return omni::io::file_internal::rd_el< std::string, std::ifstream, T, SZ >(std::string(file), buffer, 0, 0, 0, std::ios_base::beg);
            }
            template < typename T, uint16_t SZ >
            uint64_t read_element(const std::string& file, omni::stack_buffer<T, SZ>& buffer, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd_el< std::string, std::ifstream, T, SZ >(file, buffer, 0, 0, file_offset, offset_direction);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t read_element(const char (&file)[FSZ], omni::stack_buffer<T, SZ>& buffer, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd_el< std::string, std::ifstream, T, SZ >(std::string(file), buffer, 0, 0, file_offset, offset_direction);
            }
            template < typename T, uint16_t SZ >
            uint64_t read_element(const std::string& file, omni::stack_buffer<T, SZ>& buffer, uint64_t elements, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd_el< std::string, std::ifstream, T, SZ >(file, buffer, elements, 0, file_offset, offset_direction);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t read_element(const char (&file)[FSZ], omni::stack_buffer<T, SZ>& buffer, uint64_t elements, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd_el< std::string, std::ifstream, T, SZ >(std::string(file), buffer, elements, 0, file_offset, offset_direction);
            }
            template < typename T, uint16_t SZ >
            uint64_t read_element(const std::string& file, omni::stack_buffer<T, SZ>& buffer, uint64_t elements, std::size_t buffer_offset, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd_el< std::string, std::ifstream, T, SZ >(file, buffer, elements, buffer_offset, file_offset, offset_direction);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t read_element(const char (&file)[FSZ], omni::stack_buffer<T, SZ>& buffer, uint64_t elements, std::size_t buffer_offset, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd_el< std::string, std::ifstream, T, SZ >(std::string(file), buffer, elements, buffer_offset, file_offset, offset_direction);
            }
            template < typename T >
            uint64_t unsafe_read_element(const std::string& file, T* buffer, uint64_t elements)
            {
                return omni::io::file_internal::unsafe_rd_el< std::string, std::ifstream, T >(file, buffer, elements);
            }
            inline uint64_t unsafe_read(const std::string& file, char* buffer, uint64_t length) { return omni::io::cfile::unsafe_read(file, buffer, length); }
            inline uint64_t unsafe_read(const std::string& file, wchar_t* buffer, uint64_t length) { return omni::io::cfile::unsafe_read(file, buffer, length); }
            inline uint64_t unsafe_read(const std::string& file, uint8_t* buffer, uint64_t length) { return omni::io::cfile::unsafe_read(file, buffer, length); }
            inline uint64_t unsafe_read(const std::string& file, int8_t* buffer, uint64_t length) { return omni::io::cfile::unsafe_read(file, buffer, length); }
            inline bool remove(const std::string& file) { return omni::io::cfile::remove(file); }
            #if defined(OMNI_NON_PORTABLE)
                inline bool set_size(const std::string& file, uint64_t size) { return omni::io::cfile::set_size(file, size); }
            #endif
            inline uint64_t write(const std::string& file, const std::string& buffer, bool append) { return omni::io::cfile::write(file, buffer, append); }
            inline uint64_t write(const std::string& file, const std::string& buffer) { return omni::io::cfile::write(file, buffer); }
            // std::vector/deque/array/list/etc.
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write(const std::string& file, const std_seq_t<T, std_allocator_t >& buffer)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, std_seq_t, T, std_allocator_t >(file, buffer, 0, 0, false, false);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write(const char (&file)[SZ], const std_seq_t<T, std_allocator_t >& buffer)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, std_seq_t, T, std_allocator_t >(std::string(file), buffer, 0, 0, false, false);
            }
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write(const std::string& file, const std_seq_t<T, std_allocator_t >& buffer, uint64_t length, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, std_seq_t, T, std_allocator_t >(file, buffer, length, buffer_offset, false, false);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write(const char (&file)[SZ], const std_seq_t<T, std_allocator_t >& buffer, uint64_t length, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, std_seq_t, T, std_allocator_t >(std::string(file), buffer, length, buffer_offset, false, false);
            }
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write(const std::string& file, const std_seq_t<T, std_allocator_t >& buffer, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, std_seq_t, T, std_allocator_t >(file, buffer, 0, 0, append, false);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write(const char (&file)[SZ], const std_seq_t<T, std_allocator_t >& buffer, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, std_seq_t, T, std_allocator_t >(std::string(file), buffer, 0, 0, append, false);
            }
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write(const std::string& file, const std_seq_t<T, std_allocator_t >& buffer, uint64_t length, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, std_seq_t, T, std_allocator_t >(file, buffer, length, buffer_offset, append, false);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write(const char (&file)[SZ], const std_seq_t<T, std_allocator_t >& buffer, uint64_t length, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, std_seq_t, T, std_allocator_t >(std::string(file), buffer, length, buffer_offset, append, false);
            }
            // char buf[]/wchar_t buf[]/uintX_t buf[]
            template < typename T, std::size_t SZ >
            uint64_t write(const std::string& file, const T (&buffer)[SZ])
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, T, SZ >(file, buffer, 0, 0, false, false);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t write(const char (&file)[FSZ], const T (&buffer)[SZ])
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, T, SZ >(std::string(file), buffer, 0, 0, false, false);
            }
            template < typename T, std::size_t SZ >
            uint64_t write(const std::string& file, const T (&buffer)[SZ], uint64_t length, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, T, SZ >(file, buffer, length, buffer_offset, false, false);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t write(const char (&file)[FSZ], const T (&buffer)[SZ], uint64_t length, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, T, SZ >(std::string(file), buffer, length, buffer_offset, false, false);
            }
            template < typename T, std::size_t SZ >
            uint64_t write(const std::string& file, const T (&buffer)[SZ], bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, T, SZ >(file, buffer, 0, 0, append, false);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t write(const char (&file)[FSZ], const T (&buffer)[SZ], bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, T, SZ >(std::string(file), buffer, 0, 0, append, false);
            }
            template < typename T, std::size_t SZ >
            uint64_t write(const std::string& file, const T (&buffer)[SZ], uint64_t length, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, T, SZ >(file, buffer, length, buffer_offset, append, false);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t write(const char (&file)[FSZ], const T (&buffer)[SZ], uint64_t length, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, T, SZ >(std::string(file), buffer, length, buffer_offset, append, false);
            }
            // omni::stack_buffer
            template < typename T, uint16_t SZ >
            uint64_t write(const std::string& file, const omni::stack_buffer<T, SZ>& buffer)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, T, SZ >(file, buffer, 0, 0, false, false);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t write(const char (&file)[FSZ], const omni::stack_buffer<T, SZ>& buffer)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, T, SZ >(std::string(file), buffer, 0, 0, false, false);
            }
            template < typename T, uint16_t SZ >
            uint64_t write(const std::string& file, const omni::stack_buffer<T, SZ>& buffer, uint64_t length, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, T, SZ >(file, buffer, length, buffer_offset, false, false);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t write(const char (&file)[FSZ], const omni::stack_buffer<T, SZ>& buffer, uint64_t length, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, T, SZ >(std::string(file), buffer, length, buffer_offset, false, false);
            }
            template < typename T, uint16_t SZ >
            uint64_t write(const std::string& file, const omni::stack_buffer<T, SZ>& buffer, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, T, SZ >(file, buffer, 0, 0, append, false);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t write(const char (&file)[FSZ], const omni::stack_buffer<T, SZ>& buffer, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, T, SZ >(std::string(file), buffer, 0, 0, append, false);
            }
            template < typename T, uint16_t SZ >
            uint64_t write(const std::string& file, const omni::stack_buffer<T, SZ>& buffer, uint64_t length, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, T, SZ >(file, buffer, length, buffer_offset, append, false);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t write(const char (&file)[FSZ], const omni::stack_buffer<T, SZ>& buffer, uint64_t length, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, T, SZ >(std::string(file), buffer, length, buffer_offset, append, false);
            }
            // write_elements
            // std::vector/deque/array/list/etc.
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write_element(const std::string& file, const std_seq_t<T, std_allocator_t >& buffer)
            {
                return omni::io::file_internal::write_el_fw< std::string, std::ofstream, std_seq_t, T, std_allocator_t >(file, buffer, 0, 0, false, false);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write_element(const char (&file)[SZ], const std_seq_t<T, std_allocator_t >& buffer)
            {
                return omni::io::file_internal::write_el_fw< std::string, std::ofstream, std_seq_t, T, std_allocator_t >(std::string(file), buffer, 0, 0, false, false);
            }
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write_element(const std::string& file, const std_seq_t<T, std_allocator_t >& buffer, uint64_t elements, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_el_fw< std::string, std::ofstream, std_seq_t, T, std_allocator_t >(file, buffer, elements, buffer_offset, false, false);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write_element(const char (&file)[SZ], const std_seq_t<T, std_allocator_t >& buffer, uint64_t elements, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_el_fw< std::string, std::ofstream, std_seq_t, T, std_allocator_t >(std::string(file), buffer, elements, buffer_offset, false, false);
            }
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write_element(const std::string& file, const std_seq_t<T, std_allocator_t >& buffer, bool append)
            {
                return omni::io::file_internal::write_el_fw< std::string, std::ofstream, std_seq_t, T, std_allocator_t >(file, buffer, 0, 0, append, false);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write_element(const char (&file)[SZ], const std_seq_t<T, std_allocator_t >& buffer, bool append)
            {
                return omni::io::file_internal::write_el_fw< std::string, std::ofstream, std_seq_t, T, std_allocator_t >(std::string(file), buffer, 0, 0, append, false);
            }
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write_element(const std::string& file, const std_seq_t<T, std_allocator_t >& buffer, uint64_t elements, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_el_fw< std::string, std::ofstream, std_seq_t, T, std_allocator_t >(file, buffer, elements, buffer_offset, append, false);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write_element(const char (&file)[SZ], const std_seq_t<T, std_allocator_t >& buffer, uint64_t elements, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_el_fw< std::string, std::ofstream, std_seq_t, T, std_allocator_t >(std::string(file), buffer, elements, buffer_offset, append, false);
            }
            // char buf[]/wchar_t buf[]/uintX_t buf[]
            template < typename T, std::size_t SZ >
            uint64_t write_element(const std::string& file, const T (&buffer)[SZ])
            {
                return omni::io::file_internal::write_el_fw< std::string, std::ofstream, T, SZ >(file, buffer, 0, 0, false, false);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t write_element(const char (&file)[FSZ], const T (&buffer)[SZ])
            {
                return omni::io::file_internal::write_el_fw< std::string, std::ofstream, T, SZ >(std::string(file), buffer, 0, 0, false, false);
            }
            template < typename T, std::size_t SZ >
            uint64_t write_element(const std::string& file, const T (&buffer)[SZ], uint64_t elements, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_el_fw< std::string, std::ofstream, T, SZ >(file, buffer, elements, buffer_offset, false, false);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t write_element(const char (&file)[FSZ], const T (&buffer)[SZ], uint64_t elements, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_el_fw< std::string, std::ofstream, T, SZ >(std::string(file), buffer, elements, buffer_offset, false, false);
            }
            template < typename T, std::size_t SZ >
            uint64_t write_element(const std::string& file, const T (&buffer)[SZ], bool append)
            {
                return omni::io::file_internal::write_el_fw< std::string, std::ofstream, T, SZ >(file, buffer, 0, 0, append, false);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t write_element(const char (&file)[FSZ], const T (&buffer)[SZ], bool append)
            {
                return omni::io::file_internal::write_el_fw< std::string, std::ofstream, T, SZ >(std::string(file), buffer, 0, 0, append, false);
            }
            template < typename T, std::size_t SZ >
            uint64_t write_element(const std::string& file, const T (&buffer)[SZ], uint64_t elements, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_el_fw< std::string, std::ofstream, T, SZ >(file, buffer, elements, buffer_offset, append, false);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t write_element(const char (&file)[FSZ], const T (&buffer)[SZ], uint64_t elements, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_el_fw< std::string, std::ofstream, T, SZ >(std::string(file), buffer, elements, buffer_offset, append, false);
            }
            // omni::stack_buffer
            template < typename T, uint16_t SZ >
            uint64_t write_element(const std::string& file, const omni::stack_buffer<T, SZ>& buffer)
            {
                return omni::io::file_internal::write_el_fw< std::string, std::ofstream, T, SZ >(file, buffer, 0, 0, false, false);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t write_element(const char (&file)[FSZ], const omni::stack_buffer<T, SZ>& buffer)
            {
                return omni::io::file_internal::write_el_fw< std::string, std::ofstream, T, SZ >(std::string(file), buffer, 0, 0, false, false);
            }
            template < typename T, uint16_t SZ >
            uint64_t write_element(const std::string& file, const omni::stack_buffer<T, SZ>& buffer, uint64_t elements, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_el_fw< std::string, std::ofstream, T, SZ >(file, buffer, elements, buffer_offset, false, false);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t write_element(const char (&file)[FSZ], const omni::stack_buffer<T, SZ>& buffer, uint64_t elements, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_el_fw< std::string, std::ofstream, T, SZ >(std::string(file), buffer, elements, buffer_offset, false, false);
            }
            template < typename T, uint16_t SZ >
            uint64_t write_element(const std::string& file, const omni::stack_buffer<T, SZ>& buffer, bool append)
            {
                return omni::io::file_internal::write_el_fw< std::string, std::ofstream, T, SZ >(file, buffer, 0, 0, append, false);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t write_element(const char (&file)[FSZ], const omni::stack_buffer<T, SZ>& buffer, bool append)
            {
                return omni::io::file_internal::write_el_fw< std::string, std::ofstream, T, SZ >(std::string(file), buffer, 0, 0, append, false);
            }
            template < typename T, uint16_t SZ >
            uint64_t write_element(const std::string& file, const omni::stack_buffer<T, SZ>& buffer, uint64_t elements, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_el_fw< std::string, std::ofstream, T, SZ >(file, buffer, elements, buffer_offset, append, false);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t write_element(const char (&file)[FSZ], const omni::stack_buffer<T, SZ>& buffer, uint64_t elements, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_el_fw< std::string, std::ofstream, T, SZ >(std::string(file), buffer, elements, buffer_offset, append, false);
            }

            inline uint64_t write_line(const std::string& file, const std::string& buffer, bool append) { return omni::io::cfile::write_line(file, buffer, append); }
            inline uint64_t write_line(const std::string& file, const std::string& buffer) { return omni::io::cfile::write_line(file, buffer); }
            // std::vector/deque/array/list/etc.
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write_line(const std::string& file, const std_seq_t<T, std_allocator_t >& buffer)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, std_seq_t, T, std_allocator_t >(file, buffer, 0, 0, false, true);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write_line(const char (&file)[SZ], const std_seq_t<T, std_allocator_t >& buffer)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, std_seq_t, T, std_allocator_t >(std::string(file), buffer, 0, 0, false, true);
            }
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write_line(const std::string& file, const std_seq_t<T, std_allocator_t >& buffer, uint64_t length, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, std_seq_t, T, std_allocator_t >(file, buffer, length, buffer_offset, false, true);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write_line(const char (&file)[SZ], const std_seq_t<T, std_allocator_t >& buffer, uint64_t length, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, std_seq_t, T, std_allocator_t >(std::string(file), buffer, length, buffer_offset, false, true);
            }
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write_line(const std::string& file, const std_seq_t<T, std_allocator_t >& buffer, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, std_seq_t, T, std_allocator_t >(file, buffer, 0, 0, append, true);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write_line(const char (&file)[SZ], const std_seq_t<T, std_allocator_t >& buffer, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, std_seq_t, T, std_allocator_t >(std::string(file), buffer, 0, 0, append, true);
            }
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write_line(const std::string& file, const std_seq_t<T, std_allocator_t >& buffer, uint64_t length, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, std_seq_t, T, std_allocator_t >(file, buffer, length, buffer_offset, append, true);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write_line(const char (&file)[SZ], const std_seq_t<T, std_allocator_t >& buffer, uint64_t length, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, std_seq_t, T, std_allocator_t >(std::string(file), buffer, length, buffer_offset, append, true);
            }
            // char buf[]/wchar_t buf[]/uintX_t buf[]
            template < typename T, std::size_t SZ >
            uint64_t write_line(const std::string& file, const T (&buffer)[SZ])
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, T, SZ >(file, buffer, 0, 0, false, true);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t write_line(const char (&file)[FSZ], const T (&buffer)[SZ])
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, T, SZ >(std::string(file), buffer, 0, 0, false, true);
            }
            template < typename T, std::size_t SZ >
            uint64_t write_line(const std::string& file, const T (&buffer)[SZ], uint64_t length, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, T, SZ >(file, buffer, length, buffer_offset, false, true);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t write_line(const char (&file)[FSZ], const T (&buffer)[SZ], uint64_t length, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, T, SZ >(std::string(file), buffer, length, buffer_offset, false, true);
            }
            template < typename T, std::size_t SZ >
            uint64_t write_line(const std::string& file, const T (&buffer)[SZ], bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, T, SZ >(file, buffer, 0, 0, append, true);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t write_line(const char (&file)[FSZ], const T (&buffer)[SZ], bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, T, SZ >(std::string(file), buffer, 0, 0, append, true);
            }
            template < typename T, std::size_t SZ >
            uint64_t write_line(const std::string& file, const T (&buffer)[SZ], uint64_t length, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, T, SZ >(file, buffer, length, buffer_offset, append, true);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t write_line(const char (&file)[FSZ], const T (&buffer)[SZ], uint64_t length, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, T, SZ >(std::string(file), buffer, length, buffer_offset, append, true);
            }
            // omni::stack_buffer
            template < typename T, uint16_t SZ >
            uint64_t write_line(const std::string& file, const omni::stack_buffer<T, SZ>& buffer)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, T, SZ >(file, buffer, 0, 0, false, true);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t write_line(const char (&file)[FSZ], const omni::stack_buffer<T, SZ>& buffer)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, T, SZ >(std::string(file), buffer, 0, 0, false, true);
            }
            template < typename T, uint16_t SZ >
            uint64_t write_line(const std::string& file, const omni::stack_buffer<T, SZ>& buffer, uint64_t length, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, T, SZ >(file, buffer, length, buffer_offset, false, true);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t write_line(const char (&file)[FSZ], const omni::stack_buffer<T, SZ>& buffer, uint64_t length, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, T, SZ >(std::string(file), buffer, length, buffer_offset, false, true);
            }
            template < typename T, uint16_t SZ >
            uint64_t write_line(const std::string& file, const omni::stack_buffer<T, SZ>& buffer, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, T, SZ >(file, buffer, 0, 0, append, true);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t write_line(const char (&file)[FSZ], const omni::stack_buffer<T, SZ>& buffer, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, T, SZ >(std::string(file), buffer, 0, 0, append, true);
            }
            template < typename T, uint16_t SZ >
            uint64_t write_line(const std::string& file, const omni::stack_buffer<T, SZ>& buffer, uint64_t length, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, T, SZ >(file, buffer, length, buffer_offset, append, true);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t write_line(const char (&file)[FSZ], const omni::stack_buffer<T, SZ>& buffer, uint64_t length, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::string, std::ofstream, T, SZ >(std::string(file), buffer, length, buffer_offset, append, true);
            }
            template < typename T >
            uint64_t unsafe_write_element(const std::string& file, const T* buffer, uint64_t elements, bool append)
            {
                return omni::io::file_internal::unsafe_write_el_fw< std::string, std::ofstream, T >(file, buffer, elements, append);
            }
            template < typename T >
            uint64_t unsafe_write_element(const std::string& file, const T* buffer, uint64_t elements)
            {
                return omni::io::file_internal::unsafe_write_el_fw< std::string, std::ofstream, T >(file, buffer, elements, false);
            }
            inline uint64_t unsafe_write(const std::string& file, const char* buffer, uint64_t length, bool append) { return omni::io::cfile::unsafe_write(file, buffer, length, append); }
            inline uint64_t unsafe_write(const std::string& file, const wchar_t* buffer, uint64_t length, bool append) { return omni::io::cfile::unsafe_write(file, buffer, length, append); }
            inline uint64_t unsafe_write(const std::string& file, const uint8_t* buffer, uint64_t length, bool append) { return omni::io::cfile::unsafe_write(file, buffer, length, append); }
            inline uint64_t unsafe_write(const std::string& file, const int8_t* buffer, uint64_t length, bool append) { return omni::io::cfile::unsafe_write(file, buffer, length, append); }
            inline uint64_t unsafe_write(const std::string& file, const char* buffer, uint64_t length) { return omni::io::cfile::unsafe_write(file, buffer, length); }
            inline uint64_t unsafe_write(const std::string& file, const wchar_t* buffer, uint64_t length) { return omni::io::cfile::unsafe_write(file, buffer, length); }
            inline uint64_t unsafe_write(const std::string& file, const uint8_t* buffer, uint64_t length) { return omni::io::cfile::unsafe_write(file, buffer, length); }
            inline uint64_t unsafe_write(const std::string& file, const int8_t* buffer, uint64_t length) { return omni::io::cfile::unsafe_write(file, buffer, length); }
            inline uint64_t unsafe_write_line(const std::string& file, const char* buffer, uint64_t length, bool append) { return omni::io::cfile::unsafe_write_line(file, buffer, length, append); }
            inline uint64_t unsafe_write_line(const std::string& file, const wchar_t* buffer, uint64_t length, bool append) { return omni::io::cfile::unsafe_write_line(file, buffer, length, append); }
            inline uint64_t unsafe_write_line(const std::string& file, const uint8_t* buffer, uint64_t length, bool append) { return omni::io::cfile::unsafe_write_line(file, buffer, length, append); }
            inline uint64_t unsafe_write_line(const std::string& file, const int8_t* buffer, uint64_t length, bool append) { return omni::io::cfile::unsafe_write_line(file, buffer, length, append); }
            inline uint64_t unsafe_write_line(const std::string& file, const char* buffer, uint64_t length) { return omni::io::cfile::unsafe_write_line(file, buffer, length); }
            inline uint64_t unsafe_write_line(const std::string& file, const wchar_t* buffer, uint64_t length) { return omni::io::cfile::unsafe_write_line(file, buffer, length); }
            inline uint64_t unsafe_write_line(const std::string& file, const uint8_t* buffer, uint64_t length) { return omni::io::cfile::unsafe_write_line(file, buffer, length); }
            inline uint64_t unsafe_write_line(const std::string& file, const int8_t* buffer, uint64_t length) { return omni::io::cfile::unsafe_write_line(file, buffer, length); }
            
            // std::wstring

            inline bool copy(const std::wstring& file, const std::wstring& new_name, const omni::io::options& io_ops) { return omni::io::wfile::copy(file, new_name, io_ops); }
            inline bool copy(const std::wstring& file, const std::wstring& new_name) { return omni::io::wfile::copy(file, new_name); }
            inline bool create(const std::wstring& file, const omni::io::options& io_ops) { return omni::io::wfile::create(file, io_ops); }
            inline bool create(const std::wstring& file) { return omni::io::wfile::create(file); }
            inline bool exists(const std::wstring& file) { return omni::io::wfile::exists(file); }
            inline bool exist(const std::wstring& file) { return omni::io::wfile::exist(file); }
            inline std::wstring get_contents(const std::wstring& file) { return omni::io::wfile::get_contents(file); }
            inline uint64_t get_size(const std::wstring& file) { return omni::io::wfile::get_size(file); }
            inline bool move(const std::wstring& file, const std::wstring& new_name, const omni::io::options& io_ops) { return omni::io::wfile::move(file, new_name, io_ops); }
            inline bool move(const std::wstring& file, const std::wstring& new_name) { return omni::io::wfile::move(file, new_name); }
            inline bool rename(const std::wstring& file, const std::wstring& new_name, const omni::io::options& io_ops) { return omni::io::wfile::rename(file, new_name, io_ops); }
            inline bool rename(const std::wstring& file, const std::wstring& new_name) { return omni::io::wfile::rename(file, new_name); }
            inline uint64_t read(const std::wstring& file, std::wstring& buffer) { return omni::io::wfile::read(file, buffer); }
            // std::vector/deque/array/list/etc.
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t read(const std::wstring& file, std_seq_t<T, std_allocator_t >& buffer)
            {
                return omni::io::file_internal::rd< std::wstring, std::wifstream, std_seq_t, T, std_allocator_t >(file, buffer, 0, 0, std::ios_base::beg);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t read(const wchar_t (&file)[SZ], std_seq_t<T, std_allocator_t >& buffer)
            {
                return omni::io::file_internal::rd< std::wstring, std::wifstream, std_seq_t, T, std_allocator_t >(std::wstring(file), buffer, 0, 0, std::ios_base::beg);
            }
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t read(const std::wstring& file, std_seq_t<T, std_allocator_t >& buffer, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd< std::wstring, std::wifstream, std_seq_t, T, std_allocator_t >(file, buffer, 0, file_offset, offset_direction);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t read(const wchar_t (&file)[SZ], std_seq_t<T, std_allocator_t >& buffer, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd< std::wstring, std::wifstream, std_seq_t, T, std_allocator_t >(std::wstring(file), buffer, 0, file_offset, offset_direction);
            }
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t read(const std::wstring& file, std_seq_t<T, std_allocator_t >& buffer, uint64_t length, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd< std::wstring, std::wifstream, std_seq_t, T, std_allocator_t >(file, buffer, length, file_offset, offset_direction);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t read(const wchar_t (&file)[SZ], std_seq_t<T, std_allocator_t >& buffer, uint64_t length, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd< std::wstring, std::wifstream, std_seq_t, T, std_allocator_t >(std::wstring(file), buffer, length, file_offset, offset_direction);
            }
            // char buf[]/wchar_t buf[]/uintX_t buf[]
            template < typename T, std::size_t SZ >
            uint64_t read(const std::wstring &file, T (&buffer)[SZ])
            {
                return omni::io::file_internal::rd< std::wstring, std::wifstream, T, SZ >(file, buffer, 0, 0, 0, std::ios_base::beg);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t read(const wchar_t (&file)[FSZ], T (&buffer)[SZ])
            {
                return omni::io::file_internal::rd< std::wstring, std::wifstream, T, SZ >(std::wstring(file), buffer, 0, 0, 0, std::ios_base::beg);
            }
            template < typename T, std::size_t SZ >
            uint64_t read(const std::wstring &file, T (&buffer)[SZ], std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd< std::wstring, std::wifstream, T, SZ >(file, buffer, 0, 0, file_offset, offset_direction);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t read(const wchar_t (&file)[FSZ], T (&buffer)[SZ], std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd< std::wstring, std::wifstream, T, SZ >(std::wstring(file), buffer, 0, 0, file_offset, offset_direction);
            }
            template < typename T, std::size_t SZ >
            uint64_t read(const std::wstring &file, T (&buffer)[SZ], uint64_t length, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd< std::wstring, std::wifstream, T, SZ >(file, buffer, length, 0, file_offset, offset_direction);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t read(const wchar_t (&file)[FSZ], T (&buffer)[SZ], uint64_t length, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd< std::wstring, std::wifstream, T, SZ >(std::wstring(file), buffer, length, 0, file_offset, offset_direction);
            }
            template < typename T, std::size_t SZ >
            uint64_t read(const std::wstring &file, T (&buffer)[SZ], uint64_t length, std::size_t buffer_offset, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd< std::wstring, std::wifstream, T, SZ >(file, buffer, length, buffer_offset, file_offset, offset_direction);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t read(const wchar_t (&file)[FSZ], T (&buffer)[SZ], uint64_t length, std::size_t buffer_offset, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd< std::wstring, std::wifstream, T, SZ >(std::wstring(file), buffer, length, buffer_offset, file_offset, offset_direction);
            }
            // omni::stack_buffer
            template < typename T, uint16_t SZ >
            uint64_t read(const std::wstring &file, omni::stack_buffer<T, SZ>& buffer)
            {
                return omni::io::file_internal::rd< std::wstring, std::wifstream, T, SZ >(file, buffer, 0, 0, 0, std::ios_base::beg);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t read(const wchar_t (&file)[FSZ], omni::stack_buffer<T, SZ>& buffer)
            {
                return omni::io::file_internal::rd< std::wstring, std::wifstream, T, SZ >(std::wstring(file), buffer, 0, 0, 0, std::ios_base::beg);
            }
            template < typename T, uint16_t SZ >
            uint64_t read(const std::wstring &file, omni::stack_buffer<T, SZ>& buffer, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd< std::wstring, std::wifstream, T, SZ >(file, buffer, 0, 0, file_offset, offset_direction);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t read(const wchar_t (&file)[FSZ], omni::stack_buffer<T, SZ>& buffer, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd< std::wstring, std::wifstream, T, SZ >(std::wstring(file), buffer, 0, 0, file_offset, offset_direction);
            }
            template < typename T, uint16_t SZ >
            uint64_t read(const std::wstring &file, omni::stack_buffer<T, SZ>& buffer, uint64_t length, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd< std::wstring, std::wifstream, T, SZ >(file, buffer, length, 0, file_offset, offset_direction);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t read(const wchar_t (&file)[FSZ], omni::stack_buffer<T, SZ>& buffer, uint64_t length, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd< std::wstring, std::wifstream, T, SZ >(std::wstring(file), buffer, length, 0, file_offset, offset_direction);
            }
            template < typename T, uint16_t SZ >
            uint64_t read(const std::wstring &file, omni::stack_buffer<T, SZ>& buffer, uint64_t length, std::size_t buffer_offset, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd< std::wstring, std::wifstream, T, SZ >(file, buffer, length, buffer_offset, file_offset, offset_direction);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t read(const wchar_t (&file)[FSZ], omni::stack_buffer<T, SZ>& buffer, uint64_t length, std::size_t buffer_offset, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd< std::wstring, std::wifstream, T, SZ >(std::wstring(file), buffer, length, buffer_offset, file_offset, offset_direction);
            }
            // read_element
            // std::vector/deque/array/list/etc.
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t read_element(const std::wstring& file, std_seq_t<T, std_allocator_t >& buffer)
            {
                return omni::io::file_internal::rd_el< std::wstring, std::wifstream, std_seq_t, T, std_allocator_t >(file, buffer, 0, 0, std::ios_base::beg);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t read_element(const wchar_t (&file)[SZ], std_seq_t<T, std_allocator_t >& buffer)
            {
                return omni::io::file_internal::rd_el< std::wstring, std::wifstream, std_seq_t, T, std_allocator_t >(std::wstring(file), buffer, 0, 0, std::ios_base::beg);
            }
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t read_element(const std::wstring& file, std_seq_t<T, std_allocator_t >& buffer, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd_el< std::wstring, std::wifstream, std_seq_t, T, std_allocator_t >(file, buffer, 0, file_offset, offset_direction);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t read_element(const wchar_t (&file)[SZ], std_seq_t<T, std_allocator_t >& buffer, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd_el< std::wstring, std::wifstream, std_seq_t, T, std_allocator_t >(std::wstring(file), buffer, 0, file_offset, offset_direction);
            }
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t read_element(const std::wstring& file, std_seq_t<T, std_allocator_t >& buffer, uint64_t elements, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd_el< std::wstring, std::wifstream, std_seq_t, T, std_allocator_t >(file, buffer, elements, file_offset, offset_direction);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t read_element(const wchar_t (&file)[SZ], std_seq_t<T, std_allocator_t >& buffer, uint64_t elements, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd_el< std::wstring, std::wifstream, std_seq_t, T, std_allocator_t >(std::wstring(file), buffer, elements, file_offset, offset_direction);
            }
            // char buf[]/wchar_t buf[]/uintX_t buf[]
            template < typename T, std::size_t SZ >
            uint64_t read_element(const std::wstring& file, T (&buffer)[SZ])
            {
                return omni::io::file_internal::rd_el< std::wstring, std::wifstream, T, SZ >(file, buffer, 0, 0, 0, std::ios_base::beg);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t read_element(const wchar_t (&file)[FSZ], T (&buffer)[SZ])
            {
                return omni::io::file_internal::rd_el< std::wstring, std::wifstream, T, SZ >(std::wstring(file), buffer, 0, 0, 0, std::ios_base::beg);
            }
            template < typename T, std::size_t SZ >
            uint64_t read_element(const std::wstring& file, T (&buffer)[SZ], std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd_el< std::wstring, std::wifstream, T, SZ >(file, buffer, 0, 0, file_offset, offset_direction);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t read_element(const wchar_t (&file)[FSZ], T (&buffer)[SZ], std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd_el< std::wstring, std::wifstream, T, SZ >(std::wstring(file), buffer, 0, 0, file_offset, offset_direction);
            }
            template < typename T, std::size_t SZ >
            uint64_t read_element(const std::wstring& file, T (&buffer)[SZ], uint64_t elements, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd_el< std::wstring, std::wifstream, T, SZ >(file, buffer, elements, 0, file_offset, offset_direction);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t read_element(const wchar_t (&file)[FSZ], T (&buffer)[SZ], uint64_t elements, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd_el< std::wstring, std::wifstream, T, SZ >(std::wstring(file), buffer, elements, 0, file_offset, offset_direction);
            }
            template < typename T, std::size_t SZ >
            uint64_t read_element(const std::wstring& file, T (&buffer)[SZ], uint64_t elements, std::size_t buffer_offset, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd_el< std::wstring, std::wifstream, T, SZ >(file, buffer, elements, buffer_offset, file_offset, offset_direction);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t read_element(const wchar_t (&file)[FSZ], T (&buffer)[SZ], uint64_t elements, std::size_t buffer_offset, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd_el< std::wstring, std::wifstream, T, SZ >(std::wstring(file), buffer, elements, buffer_offset, file_offset, offset_direction);
            }
            // omni::stack_buffer
            template < typename T, uint16_t SZ >
            uint64_t read_element(const std::wstring& file, omni::stack_buffer<T, SZ>& buffer)
            {
                return omni::io::file_internal::rd_el< std::wstring, std::wifstream, T, SZ >(file, buffer, 0, 0, 0, std::ios_base::beg);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t read_element(const wchar_t (&file)[FSZ], omni::stack_buffer<T, SZ>& buffer)
            {
                return omni::io::file_internal::rd_el< std::wstring, std::wifstream, T, SZ >(std::wstring(file), buffer, 0, 0, 0, std::ios_base::beg);
            }
            template < typename T, uint16_t SZ >
            uint64_t read_element(const std::wstring& file, omni::stack_buffer<T, SZ>& buffer, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd_el< std::wstring, std::wifstream, T, SZ >(file, buffer, 0, 0, file_offset, offset_direction);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t read_element(const wchar_t (&file)[FSZ], omni::stack_buffer<T, SZ>& buffer, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd_el< std::wstring, std::wifstream, T, SZ >(std::wstring(file), buffer, 0, 0, file_offset, offset_direction);
            }
            template < typename T, uint16_t SZ >
            uint64_t read_element(const std::wstring& file, omni::stack_buffer<T, SZ>& buffer, uint64_t elements, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd_el< std::wstring, std::wifstream, T, SZ >(file, buffer, elements, 0, file_offset, offset_direction);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t read_element(const wchar_t (&file)[FSZ], omni::stack_buffer<T, SZ>& buffer, uint64_t elements, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd_el< std::wstring, std::wifstream, T, SZ >(std::wstring(file), buffer, elements, 0, file_offset, offset_direction);
            }
            template < typename T, uint16_t SZ >
            uint64_t read_element(const std::wstring& file, omni::stack_buffer<T, SZ>& buffer, uint64_t elements, std::size_t buffer_offset, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd_el< std::wstring, std::wifstream, T, SZ >(file, buffer, elements, buffer_offset, file_offset, offset_direction);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t read_element(const wchar_t (&file)[FSZ], omni::stack_buffer<T, SZ>& buffer, uint64_t elements, std::size_t buffer_offset, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
            {
                return omni::io::file_internal::rd_el< std::wstring, std::wifstream, T, SZ >(std::wstring(file), buffer, elements, buffer_offset, file_offset, offset_direction);
            }
            template < typename T >
            uint64_t unsafe_read_element(const std::wstring& file, T* buffer, uint64_t elements)
            {
                return omni::io::file_internal::unsafe_rd_el< std::wstring, std::wifstream, T >(file, buffer, elements);
            }
            inline uint64_t unsafe_read(const std::wstring& file, char* buffer, uint64_t length) { return omni::io::wfile::unsafe_read(file, buffer, length); }
            inline uint64_t unsafe_read(const std::wstring& file, wchar_t* buffer, uint64_t length) { return omni::io::wfile::unsafe_read(file, buffer, length); }
            inline uint64_t unsafe_read(const std::wstring& file, uint8_t* buffer, uint64_t length) { return omni::io::wfile::unsafe_read(file, buffer, length); }
            inline uint64_t unsafe_read(const std::wstring& file, int8_t* buffer, uint64_t length) { return omni::io::wfile::unsafe_read(file, buffer, length); }
            inline bool remove(const std::wstring& file) { return omni::io::wfile::remove(file); }
            #if defined(OMNI_NON_PORTABLE)
                inline bool set_size(const std::wstring& file, uint64_t size) { return omni::io::wfile::set_size(file, size); }
            #endif
            inline uint64_t write(const std::wstring& file, const std::wstring& buffer, bool append) { return omni::io::wfile::write(file, buffer, append); }
            inline uint64_t write(const std::wstring& file, const std::wstring& buffer) { return omni::io::wfile::write(file, buffer); }
            // std::vector/deque/array/list/etc.
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write(const std::wstring& file, const std_seq_t<T, std_allocator_t >& buffer)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, std_seq_t, T, std_allocator_t >(file, buffer, 0, 0, false, false);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write(const wchar_t (&file)[SZ], const std_seq_t<T, std_allocator_t >& buffer)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, std_seq_t, T, std_allocator_t >(std::wstring(file), buffer, 0, 0, false, false);
            }
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write(const std::wstring& file, const std_seq_t<T, std_allocator_t >& buffer, uint64_t length, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, std_seq_t, T, std_allocator_t >(file, buffer, length, buffer_offset, false, false);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write(const wchar_t (&file)[SZ], const std_seq_t<T, std_allocator_t >& buffer, uint64_t length, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, std_seq_t, T, std_allocator_t >(std::wstring(file), buffer, length, buffer_offset, false, false);
            }
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write(const std::wstring& file, const std_seq_t<T, std_allocator_t >& buffer, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, std_seq_t, T, std_allocator_t >(file, buffer, 0, 0, append, false);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write(const wchar_t (&file)[SZ], const std_seq_t<T, std_allocator_t >& buffer, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, std_seq_t, T, std_allocator_t >(std::wstring(file), buffer, 0, 0, append, false);
            }
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write(const std::wstring& file, const std_seq_t<T, std_allocator_t >& buffer, uint64_t length, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, std_seq_t, T, std_allocator_t >(file, buffer, length, buffer_offset, append, false);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write(const wchar_t (&file)[SZ], const std_seq_t<T, std_allocator_t >& buffer, uint64_t length, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, std_seq_t, T, std_allocator_t >(std::wstring(file), buffer, length, buffer_offset, append, false);
            }
            // char buf[]/wchar_t buf[]/uintX_t buf[]
            template < typename T, std::size_t SZ >
            uint64_t write(const std::wstring& file, const T (&buffer)[SZ])
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, T, SZ >(file, buffer, 0, 0, false, false);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t write(const wchar_t (&file)[FSZ], const T (&buffer)[SZ])
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, T, SZ >(std::wstring(file), buffer, 0, 0, false, false);
            }
            template < typename T, std::size_t SZ >
            uint64_t write(const std::wstring& file, const T (&buffer)[SZ], uint64_t length, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, T, SZ >(file, buffer, length, buffer_offset, false, false);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t write(const wchar_t (&file)[FSZ], const T (&buffer)[SZ], uint64_t length, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, T, SZ >(std::wstring(file), buffer, length, buffer_offset, false, false);
            }
            template < typename T, std::size_t SZ >
            uint64_t write(const std::wstring& file, const T (&buffer)[SZ], bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, T, SZ >(file, buffer, 0, 0, append, false);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t write(const wchar_t (&file)[FSZ], const T (&buffer)[SZ], bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, T, SZ >(std::wstring(file), buffer, 0, 0, append, false);
            }
            template < typename T, std::size_t SZ >
            uint64_t write(const std::wstring& file, const T (&buffer)[SZ], uint64_t length, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, T, SZ >(file, buffer, length, buffer_offset, append, false);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t write(const wchar_t (&file)[FSZ], const T (&buffer)[SZ], uint64_t length, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, T, SZ >(std::wstring(file), buffer, length, buffer_offset, append, false);
            }
            // omni::stack_buffer
            template < typename T, uint16_t SZ >
            uint64_t write(const std::wstring& file, const omni::stack_buffer<T, SZ>& buffer)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, T, SZ >(file, buffer, 0, 0, false, false);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t write(const wchar_t (&file)[FSZ], const omni::stack_buffer<T, SZ>& buffer)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, T, SZ >(std::wstring(file), buffer, 0, 0, false, false);
            }            
            template < typename T, uint16_t SZ >
            uint64_t write(const std::wstring& file, const omni::stack_buffer<T, SZ>& buffer, uint64_t length, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, T, SZ >(file, buffer, length, buffer_offset, false, false);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t write(const wchar_t (&file)[FSZ], const omni::stack_buffer<T, SZ>& buffer, uint64_t length, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, T, SZ >(std::wstring(file), buffer, length, buffer_offset, false, false);
            }
            template < typename T, uint16_t SZ >
            uint64_t write(const std::wstring& file, const omni::stack_buffer<T, SZ>& buffer, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, T, SZ >(file, buffer, 0, 0, append, false);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t write(const wchar_t (&file)[FSZ], const omni::stack_buffer<T, SZ>& buffer, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, T, SZ >(std::wstring(file), buffer, 0, 0, append, false);
            }
            template < typename T, uint16_t SZ >
            uint64_t write(const std::wstring& file, const omni::stack_buffer<T, SZ>& buffer, uint64_t length, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, T, SZ >(file, buffer, length, buffer_offset, append, false);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t write(const wchar_t (&file)[FSZ], const omni::stack_buffer<T, SZ>& buffer, uint64_t length, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, T, SZ >(std::wstring(file), buffer, length, buffer_offset, append, false);
            }
            // write_element
            // std::vector/deque/array/list/etc.
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write_element(const std::wstring& file, const std_seq_t<T, std_allocator_t >& buffer)
            {
                return omni::io::file_internal::write_el_fw< std::wstring, std::wofstream, std_seq_t, T, std_allocator_t >(file, buffer, 0, 0, false, false);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write_element(const wchar_t (&file)[SZ], const std_seq_t<T, std_allocator_t >& buffer)
            {
                return omni::io::file_internal::write_el_fw< std::wstring, std::wofstream, std_seq_t, T, std_allocator_t >(std::wstring(file), buffer, 0, 0, false, false);
            }
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write_element(const std::wstring& file, const std_seq_t<T, std_allocator_t >& buffer, uint64_t elements, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_el_fw< std::wstring, std::wofstream, std_seq_t, T, std_allocator_t >(file, buffer, elements, buffer_offset, false, false);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write_element(const wchar_t (&file)[SZ], const std_seq_t<T, std_allocator_t >& buffer, uint64_t elements, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_el_fw< std::wstring, std::wofstream, std_seq_t, T, std_allocator_t >(std::wstring(file), buffer, elements, buffer_offset, false, false);
            }
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write_element(const std::wstring& file, const std_seq_t<T, std_allocator_t >& buffer, bool append)
            {
                return omni::io::file_internal::write_el_fw< std::wstring, std::wofstream, std_seq_t, T, std_allocator_t >(file, buffer, 0, 0, append, false);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write_element(const wchar_t (&file)[SZ], const std_seq_t<T, std_allocator_t >& buffer, bool append)
            {
                return omni::io::file_internal::write_el_fw< std::wstring, std::wofstream, std_seq_t, T, std_allocator_t >(std::wstring(file), buffer, 0, 0, append, false);
            }
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write_element(const std::wstring& file, const std_seq_t<T, std_allocator_t >& buffer, uint64_t elements, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_el_fw< std::wstring, std::wofstream, std_seq_t, T, std_allocator_t >(file, buffer, elements, buffer_offset, append, false);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write_element(const wchar_t (&file)[SZ], const std_seq_t<T, std_allocator_t >& buffer, uint64_t elements, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_el_fw< std::wstring, std::wofstream, std_seq_t, T, std_allocator_t >(std::wstring(file), buffer, elements, buffer_offset, append, false);
            }
            // char buf[]/wchar_t buf[]/uintX_t buf[]
            template < typename T, std::size_t SZ >
            uint64_t write_element(const std::wstring& file, const T (&buffer)[SZ])
            {
                return omni::io::file_internal::write_el_fw< std::wstring, std::wofstream, T, SZ >(file, buffer, 0, 0, false, false);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t write_element(const wchar_t (&file)[FSZ], const T (&buffer)[SZ])
            {
                return omni::io::file_internal::write_el_fw< std::wstring, std::wofstream, T, SZ >(std::wstring(file), buffer, 0, 0, false, false);
            }
            template < typename T, std::size_t SZ >
            uint64_t write_element(const std::wstring& file, const T (&buffer)[SZ], uint64_t elements, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_el_fw< std::wstring, std::wofstream, T, SZ >(file, buffer, elements, buffer_offset, false, false);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t write_element(const wchar_t (&file)[FSZ], const T (&buffer)[SZ], uint64_t elements, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_el_fw< std::wstring, std::wofstream, T, SZ >(std::wstring(file), buffer, elements, buffer_offset, false, false);
            }
            template < typename T, std::size_t SZ >
            uint64_t write_element(const std::wstring& file, const T (&buffer)[SZ], bool append)
            {
                return omni::io::file_internal::write_el_fw< std::wstring, std::wofstream, T, SZ >(file, buffer, 0, 0, append, false);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t write_element(const wchar_t (&file)[FSZ], const T (&buffer)[SZ], bool append)
            {
                return omni::io::file_internal::write_el_fw< std::wstring, std::wofstream, T, SZ >(std::wstring(file), buffer, 0, 0, append, false);
            }
            template < typename T, std::size_t SZ >
            uint64_t write_element(const std::wstring& file, const T (&buffer)[SZ], uint64_t elements, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_el_fw< std::wstring, std::wofstream, T, SZ >(file, buffer, elements, buffer_offset, append, false);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t write_element(const wchar_t (&file)[FSZ], const T (&buffer)[SZ], uint64_t elements, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_el_fw< std::wstring, std::wofstream, T, SZ >(std::wstring(file), buffer, elements, buffer_offset, append, false);
            }
            // omni::stack_buffer
            template < typename T, uint16_t SZ >
            uint64_t write_element(const std::wstring& file, const omni::stack_buffer<T, SZ>& buffer)
            {
                return omni::io::file_internal::write_el_fw< std::wstring, std::wofstream, T, SZ >(file, buffer, 0, 0, false, false);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t write_element(const wchar_t (&file)[FSZ], const omni::stack_buffer<T, SZ>& buffer)
            {
                return omni::io::file_internal::write_el_fw< std::wstring, std::wofstream, T, SZ >(std::wstring(file), buffer, 0, 0, false, false);
            }
            template < typename T, uint16_t SZ >
            uint64_t write_element(const std::wstring& file, const omni::stack_buffer<T, SZ>& buffer, uint64_t elements, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_el_fw< std::wstring, std::wofstream, T, SZ >(file, buffer, elements, buffer_offset, false, false);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t write_element(const wchar_t (&file)[FSZ], const omni::stack_buffer<T, SZ>& buffer, uint64_t elements, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_el_fw< std::wstring, std::wofstream, T, SZ >(std::wstring(file), buffer, elements, buffer_offset, false, false);
            }
            template < typename T, uint16_t SZ >
            uint64_t write_element(const std::wstring& file, const omni::stack_buffer<T, SZ>& buffer, bool append)
            {
                return omni::io::file_internal::write_el_fw< std::wstring, std::wofstream, T, SZ >(file, buffer, 0, 0, append, false);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t write_element(const wchar_t (&file)[FSZ], const omni::stack_buffer<T, SZ>& buffer, bool append)
            {
                return omni::io::file_internal::write_el_fw< std::wstring, std::wofstream, T, SZ >(std::wstring(file), buffer, 0, 0, append, false);
            }
            template < typename T, uint16_t SZ >
            uint64_t write_element(const std::wstring& file, const omni::stack_buffer<T, SZ>& buffer, uint64_t elements, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_el_fw< std::wstring, std::wofstream, T, SZ >(file, buffer, elements, buffer_offset, append, false);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t write_element(const wchar_t (&file)[FSZ], const omni::stack_buffer<T, SZ>& buffer, uint64_t elements, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_el_fw< std::wstring, std::wofstream, T, SZ >(std::wstring(file), buffer, elements, buffer_offset, append, false);
            }

            inline uint64_t write_line(const std::wstring& file, const std::wstring& buffer, bool append) { return omni::io::wfile::write_line(file, buffer, append); }
            inline uint64_t write_line(const std::wstring& file, const std::wstring& buffer) { return omni::io::wfile::write_line(file, buffer); }
            // std::vector/deque/array/list/etc.
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write_line(const std::wstring& file, const std_seq_t<T, std_allocator_t >& buffer)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, std_seq_t, T, std_allocator_t >(file, buffer, 0, 0, false, true);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write_line(const wchar_t (&file)[SZ], const std_seq_t<T, std_allocator_t >& buffer)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, std_seq_t, T, std_allocator_t >(std::wstring(file), buffer, 0, 0, false, true);
            }
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write_line(const std::wstring& file, const std_seq_t<T, std_allocator_t >& buffer, uint64_t length, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, std_seq_t, T, std_allocator_t >(file, buffer, length, buffer_offset, false, true);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write_line(const wchar_t (&file)[SZ], const std_seq_t<T, std_allocator_t >& buffer, uint64_t length, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, std_seq_t, T, std_allocator_t >(std::wstring(file), buffer, length, buffer_offset, false, true);
            }
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write_line(const std::wstring& file, const std_seq_t<T, std_allocator_t >& buffer, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, std_seq_t, T, std_allocator_t >(file, buffer, 0, 0, append, true);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write_line(const wchar_t (&file)[SZ], const std_seq_t<T, std_allocator_t >& buffer, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, std_seq_t, T, std_allocator_t >(std::wstring(file), buffer, 0, 0, append, true);
            }
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write_line(const std::wstring& file, const std_seq_t<T, std_allocator_t >& buffer, uint64_t length, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, std_seq_t, T, std_allocator_t >(file, buffer, length, buffer_offset, append, true);
            }
            template < std::size_t SZ, template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t write_line(const wchar_t (&file)[SZ], const std_seq_t<T, std_allocator_t >& buffer, uint64_t length, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, std_seq_t, T, std_allocator_t >(std::wstring(file), buffer, length, buffer_offset, append, true);
            }
            // char buf[]/wchar_t buf[]/uintX_t buf[]
            template < typename T, std::size_t SZ >
            uint64_t write_line(const std::wstring& file, const T (&buffer)[SZ])
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, T, SZ >(file, buffer, 0, 0, false, true);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t write_line(const wchar_t (&file)[FSZ], const T (&buffer)[SZ])
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, T, SZ >(std::wstring(file), buffer, 0, 0, false, true);
            }
            template < typename T, std::size_t SZ >
            uint64_t write_line(const std::wstring& file, const T (&buffer)[SZ], uint64_t length, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, T, SZ >(file, buffer, length, buffer_offset, false, true);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t write_line(const wchar_t (&file)[FSZ], const T (&buffer)[SZ], uint64_t length, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, T, SZ >(std::wstring(file), buffer, length, buffer_offset, false, true);
            }
            template < typename T, std::size_t SZ >
            uint64_t write_line(const std::wstring& file, const T (&buffer)[SZ], bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, T, SZ >(file, buffer, 0, 0, append, true);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t write_line(const wchar_t (&file)[FSZ], const T (&buffer)[SZ], bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, T, SZ >(std::wstring(file), buffer, 0, 0, append, true);
            }
            template < typename T, std::size_t SZ >
            uint64_t write_line(const std::wstring& file, const T (&buffer)[SZ], uint64_t length, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, T, SZ >(file, buffer, length, buffer_offset, append, true);
            }
            template < std::size_t FSZ, typename T, std::size_t SZ >
            uint64_t write_line(const wchar_t (&file)[FSZ], const T (&buffer)[SZ], uint64_t length, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, T, SZ >(std::wstring(file), buffer, length, buffer_offset, append, true);
            }
            // omni::stack_buffer
            template < typename T, uint16_t SZ >
            uint64_t write_line(const std::wstring& file, const omni::stack_buffer<T, SZ>& buffer)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, T, SZ >(file, buffer, 0, 0, false, true);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t write_line(const wchar_t (&file)[FSZ], const omni::stack_buffer<T, SZ>& buffer)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, T, SZ >(std::wstring(file), buffer, 0, 0, false, true);
            }
            template < typename T, uint16_t SZ >
            uint64_t write_line(const std::wstring& file, const omni::stack_buffer<T, SZ>& buffer, uint64_t length, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, T, SZ >(file, buffer, length, buffer_offset, false, true);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t write_line(const wchar_t (&file)[FSZ], const omni::stack_buffer<T, SZ>& buffer, uint64_t length, std::size_t buffer_offset)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, T, SZ >(std::wstring(file), buffer, length, buffer_offset, false, true);
            }
            template < typename T, uint16_t SZ >
            uint64_t write_line(const std::wstring& file, const omni::stack_buffer<T, SZ>& buffer, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, T, SZ >(file, buffer, 0, 0, append, true);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t write_line(const wchar_t (&file)[FSZ], const omni::stack_buffer<T, SZ>& buffer, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, T, SZ >(std::wstring(file), buffer, 0, 0, append, true);
            }
            template < typename T, uint16_t SZ >
            uint64_t write_line(const std::wstring& file, const omni::stack_buffer<T, SZ>& buffer, uint64_t length, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, T, SZ >(file, buffer, length, buffer_offset, append, true);
            }
            template < std::size_t FSZ, typename T, uint16_t SZ >
            uint64_t write_line(const wchar_t (&file)[FSZ], const omni::stack_buffer<T, SZ>& buffer, uint64_t length, std::size_t buffer_offset, bool append)
            {
                return omni::io::file_internal::write_buf_fw< std::wstring, std::wofstream, T, SZ >(std::wstring(file), buffer, length, buffer_offset, append, true);
            }
            template < typename T >
            uint64_t unsafe_write_element(const std::wstring& file, const T* buffer, uint64_t elements, bool append)
            {
                return omni::io::file_internal::unsafe_write_el_fw< std::wstring, std::wofstream, T >(file, buffer, elements, append);
            }
            template < typename T >
            uint64_t unsafe_write_element(const std::wstring& file, const T* buffer, uint64_t elements)
            {
                return omni::io::file_internal::unsafe_write_el_fw< std::wstring, std::wofstream, T >(file, buffer, elements, false);
            }
            inline uint64_t unsafe_write(const std::wstring& file, const char* buffer, uint64_t length, bool append) { return omni::io::wfile::unsafe_write(file, buffer, length, append); }
            inline uint64_t unsafe_write(const std::wstring& file, const wchar_t* buffer, uint64_t length, bool append) { return omni::io::wfile::unsafe_write(file, buffer, length, append); }
            inline uint64_t unsafe_write(const std::wstring& file, const uint8_t* buffer, uint64_t length, bool append) { return omni::io::wfile::unsafe_write(file, buffer, length, append); }
            inline uint64_t unsafe_write(const std::wstring& file, const int8_t* buffer, uint64_t length, bool append) { return omni::io::wfile::unsafe_write(file, buffer, length, append); }
            inline uint64_t unsafe_write(const std::wstring& file, const char* buffer, uint64_t length) { return omni::io::wfile::unsafe_write(file, buffer, length); }
            inline uint64_t unsafe_write(const std::wstring& file, const wchar_t* buffer, uint64_t length) { return omni::io::wfile::unsafe_write(file, buffer, length); }
            inline uint64_t unsafe_write(const std::wstring& file, const uint8_t* buffer, uint64_t length) { return omni::io::wfile::unsafe_write(file, buffer, length); }
            inline uint64_t unsafe_write(const std::wstring& file, const int8_t* buffer, uint64_t length) { return omni::io::wfile::unsafe_write(file, buffer, length); }
            inline uint64_t unsafe_write_line(const std::wstring& file, const char* buffer, uint64_t length, bool append) { return omni::io::wfile::unsafe_write_line(file, buffer, length, append); }
            inline uint64_t unsafe_write_line(const std::wstring& file, const wchar_t* buffer, uint64_t length, bool append) { return omni::io::wfile::unsafe_write_line(file, buffer, length, append); }
            inline uint64_t unsafe_write_line(const std::wstring& file, const uint8_t* buffer, uint64_t length, bool append) { return omni::io::wfile::unsafe_write_line(file, buffer, length, append); }
            inline uint64_t unsafe_write_line(const std::wstring& file, const int8_t* buffer, uint64_t length, bool append) { return omni::io::wfile::unsafe_write_line(file, buffer, length, append); }
            inline uint64_t unsafe_write_line(const std::wstring& file, const char* buffer, uint64_t length) { return omni::io::wfile::unsafe_write_line(file, buffer, length); }
            inline uint64_t unsafe_write_line(const std::wstring& file, const wchar_t* buffer, uint64_t length) { return omni::io::wfile::unsafe_write_line(file, buffer, length); }
            inline uint64_t unsafe_write_line(const std::wstring& file, const uint8_t* buffer, uint64_t length) { return omni::io::wfile::unsafe_write_line(file, buffer, length); }
            inline uint64_t unsafe_write_line(const std::wstring& file, const int8_t* buffer, uint64_t length) { return omni::io::wfile::unsafe_write_line(file, buffer, length); }
        }

        namespace cdirectory {
            bool can_access(const std::string& folder);
            bool copy(const std::string& folder, const std::string& new_name, bool recursive, const omni::io::options& io_ops);
            bool copy(const std::string& folder, const std::string& new_name, bool recursive);
            bool copy(const std::string& folder, const std::string& new_name);
            bool create(const std::string& folder, const omni::io::options& io_ops);
            bool create(const std::string& folder);
            bool exists(const std::string& folder);
            bool exist(const std::string& folder);
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t get_directories(const std::string& folder, std_seq_t< T, std_allocator_t >& out)
            {
                return omni::io::dir_internal::get_directories< std::string, std_seq_t, T, std_allocator_t >(folder, out);
            }
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t get_all_directories(const std::string& folder, std_seq_t< T, std_allocator_t >& out)
            {
                return omni::io::dir_internal::get_all_directories< std::string, std_seq_t, T, std_allocator_t >(folder, out);
            }
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t get_files(const std::string& folder, std_seq_t< T, std_allocator_t >& out)
            {
                return omni::io::dir_internal::get_files< std::string, std_seq_t, T, std_allocator_t >(folder, out);
            }
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t get_all_files(const std::string& folder, std_seq_t< T, std_allocator_t >& out)
            {
                return omni::io::dir_internal::get_all_files< std::string, std_seq_t, T, std_allocator_t >(folder, out);
            }
            bool move(const std::string& folder, const std::string& new_name, const omni::io::options& io_ops);
            bool move(const std::string& folder, const std::string& new_name);
            bool rename(const std::string& folder, const std::string& new_name, const omni::io::options& io_ops);
            bool rename(const std::string& folder, const std::string& new_name);
            bool remove(const std::string& folder, bool recursive);
            bool remove(const std::string& folder);
        }
        namespace wdirectory {
            bool can_access(const std::wstring& folder);
            bool copy(const std::wstring& folder, const std::wstring& new_name, bool recursive, const omni::io::options& io_ops);
            bool copy(const std::wstring& folder, const std::wstring& new_name, bool recursive);
            bool copy(const std::wstring& folder, const std::wstring& new_name);
            bool create(const std::wstring& folder, const omni::io::options& io_ops);
            bool create(const std::wstring& folder);
            bool exists(const std::wstring& folder);
            bool exist(const std::wstring& folder);
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t get_directories(const std::wstring& folder, std_seq_t< T, std_allocator_t >& out)
            {
                return omni::io::dir_internal::get_directories< std::wstring, std_seq_t, T, std_allocator_t >(folder, out);
            }
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t get_all_directories(const std::wstring& folder, std_seq_t< T, std_allocator_t >& out)
            {
                return omni::io::dir_internal::get_all_directories< std::wstring, std_seq_t, T, std_allocator_t >(folder, out);
            }
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t get_files(const std::wstring& folder, std_seq_t< T, std_allocator_t >& out)
            {
                return omni::io::dir_internal::get_files< std::wstring, std_seq_t, T, std_allocator_t >(folder, out);
            }
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t get_all_files(const std::wstring& folder, std_seq_t< T, std_allocator_t >& out)
            {
                return omni::io::dir_internal::get_all_files< std::wstring, std_seq_t, T, std_allocator_t >(folder, out);
            }
            bool move(const std::wstring& folder, const std::wstring& new_name, const omni::io::options& io_ops);
            bool move(const std::wstring& folder, const std::wstring& new_name);
            bool rename(const std::wstring& folder, const std::wstring& new_name, const omni::io::options& io_ops);
            bool rename(const std::wstring& folder, const std::wstring& new_name);
            bool remove(const std::wstring& folder, bool recursive);
            bool remove(const std::wstring& folder);
        }
        namespace directory {
            // std::string
            inline bool can_access(const std::string& folder) { return omni::io::cdirectory::can_access(folder); }
            inline bool copy(const std::string& folder, const std::string& new_name, bool recursive, const omni::io::options& io_ops) { return omni::io::cdirectory::copy(folder, new_name, recursive, io_ops); }
            inline bool copy(const std::string& folder, const std::string& new_name, bool recursive) { return omni::io::cdirectory::copy(folder, new_name, recursive); }
            inline bool copy(const std::string& folder, const std::string& new_name) { return omni::io::cdirectory::copy(folder, new_name); }
            inline bool create(const std::string& folder, const omni::io::options& io_ops) { return omni::io::cdirectory::create(folder, io_ops); }
            inline bool create(const std::string& folder) { return omni::io::cdirectory::create(folder); }
            inline bool exists(const std::string& folder) { return omni::io::cdirectory::exists(folder); }
            inline bool exist(const std::string& folder) { return omni::io::cdirectory::exist(folder); }
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t get_directories(const std::string& folder, std_seq_t< T, std_allocator_t >& out)
            {
                return omni::io::dir_internal::get_directories< std::string, std_seq_t, T, std_allocator_t >(folder, out);
            }
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t get_all_directories(const std::string& folder, std_seq_t< T, std_allocator_t >& out)
            {
                return omni::io::dir_internal::get_all_directories< std::string, std_seq_t, T, std_allocator_t >(folder, out);
            }
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t get_files(const std::string& folder, std_seq_t< T, std_allocator_t >& out)
            {
                return omni::io::dir_internal::get_files< std::string, std_seq_t, T, std_allocator_t >(folder, out);
            }
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t get_all_files(const std::string& folder, std_seq_t< T, std_allocator_t >& out)
            {
                return omni::io::dir_internal::get_all_files< std::string, std_seq_t, T, std_allocator_t >(folder, out);
            }
            inline bool move(const std::string& folder, const std::string& new_name, const omni::io::options& io_ops) { return omni::io::cdirectory::move(folder, new_name, io_ops); }
            inline bool move(const std::string& folder, const std::string& new_name) { return omni::io::cdirectory::move(folder, new_name); }
            inline bool rename(const std::string& folder, const std::string& new_name, const omni::io::options& io_ops) { return omni::io::cdirectory::rename(folder, new_name, io_ops); }
            inline bool rename(const std::string& folder, const std::string& new_name) { return omni::io::cdirectory::rename(folder, new_name); }
            inline bool remove(const std::string& folder, bool recursive) { return omni::io::cdirectory::remove(folder, recursive); }
            inline bool remove(const std::string& folder) { return omni::io::cdirectory::remove(folder); }
            // std::wstring
            inline bool can_access(const std::wstring& folder) { return omni::io::wdirectory::can_access(folder); }
            inline bool copy(const std::wstring& folder, const std::wstring& new_name, bool recursive, const omni::io::options& io_ops) { return omni::io::wdirectory::copy(folder, new_name, recursive, io_ops); }
            inline bool copy(const std::wstring& folder, const std::wstring& new_name, bool recursive) { return omni::io::wdirectory::copy(folder, new_name, recursive); }
            inline bool copy(const std::wstring& folder, const std::wstring& new_name) { return omni::io::wdirectory::copy(folder, new_name); }
            inline bool create(const std::wstring& folder, const omni::io::options& io_ops) { return omni::io::wdirectory::create(folder, io_ops); }
            inline bool create(const std::wstring& folder) { return omni::io::wdirectory::create(folder); }
            inline bool exists(const std::wstring& folder) { return omni::io::wdirectory::exists(folder); }
            inline bool exist(const std::wstring& folder) { return omni::io::wdirectory::exist(folder); }
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t get_directories(const std::wstring& folder, std_seq_t< T, std_allocator_t >& out)
            {
                return omni::io::dir_internal::get_directories< std::wstring, std_seq_t, T, std_allocator_t >(folder, out);
            }
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t get_all_directories(const std::wstring& folder, std_seq_t< T, std_allocator_t >& out)
            {
                return omni::io::dir_internal::get_all_directories< std::wstring, std_seq_t, T, std_allocator_t >(folder, out);
            }
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t get_files(const std::wstring& folder, std_seq_t< T, std_allocator_t >& out)
            {
                return omni::io::dir_internal::get_files< std::wstring, std_seq_t, T, std_allocator_t >(folder, out);
            }
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            uint64_t get_all_files(const std::wstring& folder, std_seq_t< T, std_allocator_t >& out)
            {
                return omni::io::dir_internal::get_all_files< std::wstring, std_seq_t, T, std_allocator_t >(folder, out);
            }
            inline bool move(const std::wstring& folder, const std::wstring& new_name, const omni::io::options& io_ops) { return omni::io::wdirectory::move(folder, new_name, io_ops); }
            inline bool move(const std::wstring& folder, const std::wstring& new_name) { return omni::io::wdirectory::move(folder, new_name); }
            inline bool rename(const std::wstring& folder, const std::wstring& new_name, const omni::io::options& io_ops) { return omni::io::wdirectory::rename(folder, new_name, io_ops); }
            inline bool rename(const std::wstring& folder, const std::wstring& new_name) { return omni::io::wdirectory::rename(folder, new_name); }
            inline bool remove(const std::wstring& folder, bool recursive) { return omni::io::wdirectory::remove(folder, recursive); }
            inline bool remove(const std::wstring& folder) { return omni::io::wdirectory::remove(folder); }
        }

        namespace cpath {
            std::string change_extension(const std::string& path, const std::string& extension);
            std::string combine(const omni::sequence::std_string_t& paths, const std::string& seperator);
            inline std::string combine(const omni::sequence::std_string_t& paths) { return omni::io::cpath::combine(paths, std::string(OMNI_PATH_SEPARATOR)); }
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
            std::wstring combine(const omni::sequence::std_wstring_t& paths, const std::wstring& seperator);
            inline std::wstring combine(const omni::sequence::std_wstring_t& paths) { return omni::io::wpath::combine(paths, std::wstring(OMNI_WPATH_SEPARATOR)); }
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
            inline std::string combine(const omni::sequence::std_string_t& paths, const std::string& seperator) { return omni::io::cpath::combine(paths, seperator); }
            inline std::string combine(const omni::sequence::std_string_t& paths) { return omni::io::cpath::combine(paths, std::string(OMNI_PATH_SEPARATOR)); }
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
            inline std::wstring combine(const omni::sequence::std_wstring_t& paths, const std::wstring& seperator) { return omni::io::wpath::combine(paths, seperator); }
            inline std::wstring combine(const omni::sequence::std_wstring_t& paths) { return omni::io::wpath::combine(paths, std::wstring(OMNI_WPATH_SEPARATOR)); }
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

#define OMNI_IO_PATH_COMBINE_FW 1
#include <omni/xx/io_path_combine.hxx>

#endif // OMNI_IO_HPP
