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
// these macros are defined in io.hpp
#if !defined(OMNI_IO_FILE_RW_FW)
    #error "invalid preprocessor directive detected"
#endif

#define OMNI_IO_FILE_EX_FW 1
#include <omni/xx/io/file_ex.hxx>

namespace omni { namespace io { namespace file_internal {
    template < typename STR, typename IFSTREAM, template < class, class > class std_seq_t, class T, class std_allocator_t >
    uint64_t rd(const STR& file, std_seq_t<T, std_allocator_t >& buffer, uint64_t length, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
    {
        // TODO: add buffer_offset ???

        // DEV_NOTE: wifstream not take wchar_t[] filename since it is basic_ifstream<wchar_t>, which the constructors
        // for basic_ifstream are only basic_ifstream(const char* file..) and basic_ifstream(const std::string& file...)
        IFSTREAM ifile(omni::string::to_string(file).c_str(), std::ios::binary);
        if (!ifile.is_open()) { return 0; }
        if (length == 0) {
            ifile.seekg(0, ifile.end);
            length = static_cast<uint64_t>(ifile.tellg());
        }
        ifile.seekg(file_offset, offset_direction);
        // we cannot assume the SEQ type will allow contiguous memory, so we have to loop :/
        typename IFSTREAM::char_type* bf = new typename IFSTREAM::char_type[length];
        typename IFSTREAM::char_type* bfbeg = bf;
        ifile.read(bf, static_cast<std::streamsize>(length));
        length = static_cast<uint64_t>(ifile.gcount());
        ifile.close();

        // TODO: buffer.clear() ?? or just append?
        buffer.clear();
        if (length > 0) {
            typename IFSTREAM::char_type* bfend = bf + length;
            uint64_t i = 0;
            if (sizeof(T) == sizeof(typename IFSTREAM::char_type)) {
                for (i = 0; i < length; ++i) {
                    //buffer[i] = *(reinterpret_cast<T*>(bf));
                    buffer.push_back(*(reinterpret_cast<T*>(bf)));
                    ++bf;
                }
            } else {
                T* nbf = OMNI_NULL_PTR;
                uint64_t nlen = length / sizeof(T);
                uint64_t diff = length % sizeof(T);
                if (diff == 0) { // clean boundaries
                    for (i = 0; i < nlen; ++i) {
                        nbf = reinterpret_cast<T*>(bf);
                        //buffer[i] = *nbf;
                        buffer.push_back(*nbf);
                        bf += sizeof(T);
                        if (bf >= bfend) { break; }
                    }
                } else {
                    if (length < sizeof(T)) {
                        diff = length;
                        nlen = 0;
                    }
                    for (i = 0; i < nlen; ++i) {
                        nbf = reinterpret_cast<T*>(bf);
                        //buffer[i] = *nbf;
                        buffer.push_back(*nbf);
                        bf += sizeof(T);
                        if (bf >= bfend) { break; }
                    }
                    if (bf < bfend) {
                        T tval;
                        std::memset(&tval, 0, sizeof(T));
                        typename IFSTREAM::char_type* xbf = reinterpret_cast<typename IFSTREAM::char_type*>(&tval);
                        for (i = 0; i < diff; ++i) {
                            xbf[i] = *bf;
                            ++bf; //++xbf;
                            if (bf >= bfend) { break; }
                        }
                        buffer.push_back(tval);
                    }
                }
            }
            bf = bfbeg;
        }
        OMNI_FREE_ARR(bf);
        return length;
    }

    template < typename STR, typename IFSTREAM, typename T, std::size_t SZ >
    uint64_t rd(const STR& file, T (&buffer)[SZ], uint64_t length, std::size_t buffer_offset, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
    {
        if (buffer_offset >= SZ) { return 0; }
        // DEV_NOTE: wifstream not take wchar_t[] filename since it is basic_ifstream<wchar_t>, which the constructors
        // for basic_ifstream are only basic_ifstream(const char* file..) and basic_ifstream(const std::string& file...)
        IFSTREAM ifile(omni::string::to_string(file).c_str(), std::ios::binary);
        if (!ifile.is_open()) { return 0; }
        if ((length == 0) || (length > SZ)) {
            length = SZ;
        }
        T* buf = &buffer[buffer_offset];
        typename IFSTREAM::char_type* bf = reinterpret_cast<typename IFSTREAM::char_type*>(buf);
        ifile.seekg(file_offset, offset_direction);
        ifile.read(bf, static_cast<std::streamsize>(length));
        length = static_cast<uint64_t>(ifile.gcount());
        ifile.close();
        return length;
    }

    template < typename STR, typename IFSTREAM, typename T, uint16_t SZ >
    uint64_t rd(const STR& file, omni::stack_buffer<T, SZ>& buffer, uint64_t length, std::size_t buffer_offset, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
    {
        if (buffer_offset >= SZ) { return 0; }
        // DEV_NOTE: wifstream not take wchar_t[] filename since it is basic_ifstream<wchar_t>, which the constructors
        // for basic_ifstream are only basic_ifstream(const char* file..) and basic_ifstream(const std::string& file...)
        IFSTREAM ifile(omni::string::to_string(file).c_str(), std::ios::binary);
        if (!ifile.is_open()) { return 0; }
        if ((length == 0) || (length > SZ)) {
            length = SZ;
        }
        T* buf = buffer.data() + buffer_offset;
        typename IFSTREAM::char_type* bf = reinterpret_cast<typename IFSTREAM::char_type*>(buf);
        ifile.seekg(file_offset, offset_direction);
        // TODO: SZ or SZ*sizeof(T)   ?????
        ifile.read(bf, static_cast<std::streamsize>(length));
        length = static_cast<uint64_t>(ifile.gcount());
        ifile.close();
        return length;
    }

    template < typename STR, typename IFSTREAM, template < class, class > class std_seq_t, class T, class std_allocator_t >
    uint64_t rd_el(const STR& file, std_seq_t<T, std_allocator_t >& buffer, uint64_t elements, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
    {
        // TODO: add buffer_offset ???

        // DEV_NOTE: wifstream not take wchar_t[] filename since it is basic_ifstream<wchar_t>, which the constructors
        // for basic_ifstream are only basic_ifstream(const char* file..) and basic_ifstream(const std::string& file...)
        IFSTREAM ifile(omni::string::to_string(file).c_str(), std::ios::binary);
        if (!ifile.is_open()) { return 0; }
        if (elements == 0) {
            ifile.seekg(0, ifile.end);
            elements = static_cast<uint64_t>(ifile.tellg());
        }
        elements = elements * sizeof(T);
        ifile.seekg(file_offset, offset_direction);
        // we cannot assume the SEQ type will allow contiguous memory, so we have to loop :/
        typename IFSTREAM::char_type* bf = new typename IFSTREAM::char_type[elements];
        typename IFSTREAM::char_type* bfbeg = bf;
        ifile.read(bf, static_cast<std::streamsize>(elements));
        elements = static_cast<uint64_t>(ifile.gcount());
        ifile.close();

        // TODO: buffer.clear() ?? or just append?
        buffer.clear();
        if (elements > 0) {
            typename IFSTREAM::char_type* bfend = bf + elements;
            uint64_t i = 0;
            if (sizeof(T) == sizeof(typename IFSTREAM::char_type)) {
                for (i = 0; i < elements; ++i) {
                    //buffer[i] = *(reinterpret_cast<T*>(bf));
                    buffer.push_back(*(reinterpret_cast<T*>(bf)));
                    ++bf;
                }
            } else {
                T* nbf = OMNI_NULL_PTR;
                uint64_t nlen = elements / sizeof(T);
                uint64_t diff = elements % sizeof(T);
                if (diff == 0) { // clean boundaries
                    for (i = 0; i < nlen; ++i) {
                        nbf = reinterpret_cast<T*>(bf);
                        //buffer[i] = *nbf;
                        buffer.push_back(*nbf);
                        bf += sizeof(T);
                        if (bf >= bfend) { break; }
                    }
                } else {
                    if (elements < sizeof(T)) {
                        diff = elements;
                        nlen = 0;
                    }
                    for (i = 0; i < nlen; ++i) {
                        nbf = reinterpret_cast<T*>(bf);
                        //buffer[i] = *nbf;
                        buffer.push_back(*nbf);
                        bf += sizeof(T);
                        if (bf >= bfend) { break; }
                    }
                    if (bf < bfend) {
                        T tval;
                        std::memset(&tval, 0, sizeof(T));
                        typename IFSTREAM::char_type* xbf = reinterpret_cast<typename IFSTREAM::char_type*>(&tval);
                        for (i = 0; i < diff; ++i) {
                            xbf[i] = *bf;
                            ++bf; //++xbf;
                            if (bf >= bfend) { break; }
                        }
                        buffer.push_back(tval);
                    }
                }
            }
            bf = bfbeg;
        }
        OMNI_FREE_ARR(bf);
        if ((elements < sizeof(T)) && (elements > 0)) {
            return 1;
        } else if (elements % sizeof(T) != 0) {
            return (elements / sizeof(T)) + 1;
        }
        return elements / sizeof(T);
    }

    template < typename STR, typename IFSTREAM, typename T, std::size_t SZ >
    uint64_t rd_el(const STR& file, T (&buffer)[SZ], uint64_t elements, std::size_t buffer_offset, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
    {
        if (buffer_offset >= SZ) { return 0; }
        // DEV_NOTE: wifstream not take wchar_t[] filename since it is basic_ifstream<wchar_t>, which the constructors
        // for basic_ifstream are only basic_ifstream(const char* file..) and basic_ifstream(const std::string& file...)
        IFSTREAM ifile(omni::string::to_string(file).c_str(), std::ios::binary);
        if (!ifile.is_open()) { return 0; }
        if ((elements == 0) || (elements > SZ)) {
            elements = SZ;
        }
        T* buf = &buffer[buffer_offset];
        typename IFSTREAM::char_type* bf = reinterpret_cast<typename IFSTREAM::char_type*>(buf);
        ifile.seekg(file_offset, offset_direction);
        ifile.read(bf, static_cast<std::streamsize>(elements * sizeof(T)));
        elements = static_cast<uint64_t>(ifile.gcount());
        ifile.close();
        if ((elements < sizeof(T)) && (elements > 0)) {
            return 1;
        } else if (elements % sizeof(T) != 0) {
            return (elements / sizeof(T)) + 1;
        }
        return elements / sizeof(T);
    }

    template < typename STR, typename IFSTREAM, typename T, uint16_t SZ >
    uint64_t rd_el(const STR& file, omni::stack_buffer<T, SZ>& buffer, uint64_t elements, std::size_t buffer_offset, std::streamoff file_offset, std::ios_base::seekdir offset_direction)
    {
        if (buffer_offset >= SZ) { return 0; }
        // DEV_NOTE: wifstream not take wchar_t[] filename since it is basic_ifstream<wchar_t>, which the constructors
        // for basic_ifstream are only basic_ifstream(const char* file..) and basic_ifstream(const std::string& file...)
        IFSTREAM ifile(omni::string::to_string(file).c_str(), std::ios::binary);
        if (!ifile.is_open()) { return 0; }
        if ((elements == 0) || (elements > SZ)) {
            elements = SZ;
        }
        T* buf = buffer.data() + buffer_offset;
        typename IFSTREAM::char_type* bf = reinterpret_cast<typename IFSTREAM::char_type*>(buf);
        ifile.seekg(file_offset, offset_direction);
        ifile.read(bf, static_cast<std::streamsize>(elements * sizeof(T)));
        elements = static_cast<uint64_t>(ifile.gcount());
        ifile.close();
        if ((elements < sizeof(T)) && (elements > 0)) {
            return 1;
        } else if (elements % sizeof(T) != 0) {
            return (elements / sizeof(T)) + 1;
        }
        return elements / sizeof(T);
    }

    template < typename STR, typename IFSTREAM, typename SEQ >
    uint64_t unsafe_rd_el(const STR& file, SEQ* buffer, uint64_t elements)
    {
        if ((elements == 0) || (buffer == OMNI_NULL_PTR)) { return 0; }
        IFSTREAM ifile(omni::string::to_string(file).c_str(), std::ios::binary);
        if (!ifile.is_open()) { return 0; }
        ifile.seekg(0, ifile.end);
        uint64_t length = static_cast<uint64_t>(ifile.tellg());
        ifile.seekg(0, ifile.beg);
        if (length > (elements * sizeof(SEQ))) { length = elements * sizeof(SEQ); }
        ifile.read(reinterpret_cast<typename IFSTREAM::char_type*>(buffer), static_cast<std::streamsize>(length));
        length = static_cast<uint64_t>(ifile.gcount());
        ifile.close();
        if ((length < sizeof(SEQ)) && (length > 0)) {
            return 1;
        } else if (length % sizeof(SEQ) != 0) {
            return (length / sizeof(SEQ)) + 1;
        }
        return length / sizeof(SEQ);
    }

    template < typename STR, typename OFSTREAM, template < class, class > class std_seq_t, class T, class std_allocator_t >
    uint64_t write_buf_fw(const STR& file, const std_seq_t<T, std_allocator_t >& buffer, uint64_t length, std::size_t buffer_offset, bool append, bool new_line)
    {
        OFSTREAM ofile(omni::string::to_string(file).c_str(), (append ? (std::ios::binary | std::ios::app) : std::ios::binary));
        uint64_t start = static_cast<uint64_t>(ofile.tellp());
        uint64_t end = start;
        typename std_seq_t<T, std_allocator_t >::const_iterator b;
        if (buffer_offset >= buffer.size()) {
            b = buffer.end();
        } else if (buffer_offset == 0) {
            b = buffer.begin();
        } else {
            b = buffer.begin() + buffer_offset;
        }
        if (length == 0) {
            for (; b != buffer.end(); ++b) {
                ofile << *b;
            }
        } else {
            for (; b != buffer.end(); ++b) {
                ofile << *b;
                if (--length == 0) { break; }
            }
        }
        if (new_line) { ofile << std::endl; }
        ofile.flush();
        end = static_cast<uint64_t>(ofile.tellp());
        ofile.close();
        return (end - start);
    }

    template < typename STR, typename OFSTREAM, typename T, std::size_t SZ >
    uint64_t write_buf_fw(const STR& file, const T (&buffer)[SZ], uint64_t length, std::size_t buffer_offset, bool append, bool new_line)
    {
        if (buffer_offset >= SZ) { return 0; }
        OFSTREAM ofile(omni::string::to_string(file).c_str(), (append ? (std::ios::binary | std::ios::app) : std::ios::binary));
        uint64_t start = static_cast<uint64_t>(ofile.tellp());
        uint64_t end = start;
        const T* buf = &buffer[buffer_offset];
        const typename OFSTREAM::char_type* bf = reinterpret_cast<const typename OFSTREAM::char_type*>(buf);
        uint64_t ssz = static_cast<uint64_t>(SZ - buffer_offset);
        if (ssz < length) {
            length = ssz;
        }
        if (length == 0) {
            ofile.write(bf, static_cast<std::streamsize>(ssz));
        } else {
            ofile.write(bf, length);
        }
        if (new_line) { ofile << std::endl; }
        ofile.flush();
        if ((ofile.rdstate() & OFSTREAM::failbit) != 0) {
            end = start;
            OMNI_ERR_FW("Error on write: failbit set", omni::exception("Error on write: failbit set"))
        } else if ((ofile.rdstate() & OFSTREAM::badbit) != 0) {
            end = start;
            OMNI_ERR_FW("Error on write: badbit set", omni::exception("Error on write: badbit set"))
        } else {
            end = static_cast<uint64_t>(ofile.tellp());
        }
        ofile.close();
        return (end - start);
    }

    template < typename STR, typename OFSTREAM, typename T, uint16_t SZ >
    uint64_t write_buf_fw(const STR& file, const omni::stack_buffer<T, SZ>& buffer, uint64_t length, uint16_t buffer_offset, bool append, bool new_line)
    {
        if (buffer_offset >= SZ) { return 0; }
        OFSTREAM ofile(omni::string::to_string(file).c_str(), (append ? (std::ios::binary | std::ios::app) : std::ios::binary));
        uint64_t start = static_cast<uint64_t>(ofile.tellp());
        uint64_t end = start;
        const T* buf = buffer.data() + buffer_offset;
        const typename OFSTREAM::char_type* bf = reinterpret_cast<const typename OFSTREAM::char_type*>(buf);
        uint64_t ssz = static_cast<std::streamsize>(SZ - buffer_offset);
        if (ssz < length) {
            length = ssz;
        }
        if (length == 0) {
            ofile.write(bf, static_cast<std::streamsize>(ssz));
        } else {
            ofile.write(bf, length);
        }
        if (new_line) { ofile << std::endl; }
        ofile.flush();
        if ((ofile.rdstate() & OFSTREAM::failbit) != 0) {
            end = start;
            OMNI_ERR_FW("Error on write: failbit set", omni::exception("Error on write: failbit set"))
        } else if ((ofile.rdstate() & OFSTREAM::badbit) != 0) {
            end = start;
            OMNI_ERR_FW("Error on write: badbit set", omni::exception("Error on write: badbit set"))
        } else {
            end = static_cast<uint64_t>(ofile.tellp());
        }
        ofile.close();
        return (end - start);
    }

    template < typename STR, typename OFSTREAM, template < class, class > class std_seq_t, class T, class std_allocator_t >
    uint64_t write_el_fw(const STR& file, const std_seq_t<T, std_allocator_t >& buffer, uint64_t elements, std::size_t buffer_offset, bool append, bool new_line)
    {
        OFSTREAM ofile(omni::string::to_string(file).c_str(), (append ? (std::ios::binary | std::ios::app) : std::ios::binary));
        uint64_t start = static_cast<uint64_t>(ofile.tellp());
        uint64_t end = start;
        typename std_seq_t<T, std_allocator_t >::const_iterator b;
        if (buffer_offset >= buffer.size()) {
            b = buffer.end();
        } else if (buffer_offset == 0) {
            b = buffer.begin();
        } else {
            b = buffer.begin() + buffer_offset;
        }
        if (elements == 0) {
            for (; b != buffer.end(); ++b) {
                ofile << *b;
            }
        } else {
            for (; b != buffer.end(); ++b) {
                ofile << *b;
                if (--elements == 0) { break; }
            }
        }
        if (new_line) { ofile << std::endl; }
        ofile.flush();
        end = static_cast<uint64_t>(ofile.tellp());
        ofile.close();
        elements = (end - start);
        if ((elements < sizeof(T)) && (elements > 0)) {
            return 1;
        } else if (elements % sizeof(T) != 0) {
            return (elements / sizeof(T)) + 1;
        }
        return elements / sizeof(T);
    }

    template < typename STR, typename OFSTREAM, typename T, std::size_t SZ >
    uint64_t write_el_fw(const STR& file, const T (&buffer)[SZ], uint64_t elements, std::size_t buffer_offset, bool append, bool new_line)
    {
        if (buffer_offset >= SZ) { return 0; }
        OFSTREAM ofile(omni::string::to_string(file).c_str(), (append ? (std::ios::binary | std::ios::app) : std::ios::binary));
        uint64_t start = static_cast<uint64_t>(ofile.tellp());
        uint64_t end = start;
        const T* buf = &buffer[buffer_offset];
        const typename OFSTREAM::char_type* bf = reinterpret_cast<const typename OFSTREAM::char_type*>(buf);
        std::streamsize ssz = static_cast<std::streamsize>(SZ - buffer_offset);
        if (ssz < 0) {
            elements = 0;
        } else if (static_cast<uint64_t>(ssz) < elements) {
            elements = static_cast<uint64_t>(ssz);
        }
        if (elements == 0) {
            ofile.write(bf, (ssz * sizeof(T)));
        } else {
            ofile.write(bf, (elements * sizeof(T)));
        }
        if (new_line) { ofile << std::endl; }
        ofile.flush();
        if ((ofile.rdstate() & OFSTREAM::failbit) != 0) {
            end = start;
            OMNI_ERR_FW("Error on write: failbit set", omni::exception("Error on write: failbit set"))
        } else if ((ofile.rdstate() & OFSTREAM::badbit) != 0) {
            end = start;
            OMNI_ERR_FW("Error on write: badbit set", omni::exception("Error on write: badbit set"))
        } else {
            end = static_cast<uint64_t>(ofile.tellp());
        }
        ofile.close();
        elements = (end - start);
        if ((elements < sizeof(T)) && (elements > 0)) {
            return 1;
        } else if (elements % sizeof(T) != 0) {
            return (elements / sizeof(T)) + 1;
        }
        return elements / sizeof(T);
    }

    template < typename STR, typename OFSTREAM, typename T, uint16_t SZ >
    uint64_t write_el_fw(const STR& file, const omni::stack_buffer<T, SZ>& buffer, uint64_t elements, uint16_t buffer_offset, bool append, bool new_line)
    {
        if (buffer_offset >= SZ) { return 0; }
        OFSTREAM ofile(omni::string::to_string(file).c_str(), (append ? (std::ios::binary | std::ios::app) : std::ios::binary));
        uint64_t start = static_cast<uint64_t>(ofile.tellp());
        uint64_t end = start;
        const T* buf = buffer.data() + buffer_offset;
        const typename OFSTREAM::char_type* bf = reinterpret_cast<const typename OFSTREAM::char_type*>(buf);
        std::streamsize ssz = static_cast<std::streamsize>(SZ - buffer_offset);
        if (ssz < 0) {
            elements = 0;
        } else if (static_cast<uint64_t>(ssz) < elements) {
            elements = static_cast<uint64_t>(ssz);
        }
        if (elements == 0) {
            ofile.write(bf, (ssz * sizeof(T)));
        } else {
            ofile.write(bf, (elements * sizeof(T)));
        }
        if (new_line) { ofile << std::endl; }
        ofile.flush();
        if ((ofile.rdstate() & OFSTREAM::failbit) != 0) {
            end = start;
            OMNI_ERR_FW("Error on write: failbit set", omni::exception("Error on write: failbit set"))
        } else if ((ofile.rdstate() & OFSTREAM::badbit) != 0) {
            end = start;
            OMNI_ERR_FW("Error on write: badbit set", omni::exception("Error on write: badbit set"))
        } else {
            end = static_cast<uint64_t>(ofile.tellp());
        }
        ofile.close();
        elements = (end - start);
        if ((elements < sizeof(T)) && (elements > 0)) {
            return 1;
        } else if (elements % sizeof(T) != 0) {
            return (elements / sizeof(T)) + 1;
        }
        return elements / sizeof(T);
    }

    template < typename STR, typename OFSTREAM, typename SEQ >
    uint64_t unsafe_write_el_fw(const STR& file, const SEQ* buffer, uint64_t elements, bool append)
    {
        if ((elements == 0) || (buffer == OMNI_NULL_PTR)) { return 0; }
        OFSTREAM ofile(omni::string::to_string(file).c_str(), (append ? (std::ios::binary | std::ios::app) : std::ios::binary));
        if (!ofile.is_open()) { return 0; }
        uint64_t start = static_cast<uint64_t>(ofile.tellp());
        uint64_t end = start;
        const typename OFSTREAM::char_type* bf = reinterpret_cast<const typename OFSTREAM::char_type*>(buffer);
        ofile.write(bf, static_cast<std::streamsize>(elements * sizeof(SEQ)));
        ofile.flush();
        if ((ofile.rdstate() & OFSTREAM::failbit) != 0) {
            end = start;
            OMNI_ERR_FW("Error on write: failbit set", omni::exception("Error on write: failbit set"))
        } else if ((ofile.rdstate() & OFSTREAM::badbit) != 0) {
            end = start;
            OMNI_ERR_FW("Error on write: badbit set", omni::exception("Error on write: badbit set"))
        } else {
            end = static_cast<uint64_t>(ofile.tellp());
        }
        ofile.close();
        elements = (end - start);
        if ((elements < sizeof(SEQ)) && (elements > 0)) {
            return 1;
        } else if (elements % sizeof(SEQ) != 0) {
            return (elements / sizeof(SEQ)) + 1;
        }
        return elements / sizeof(SEQ);
    }
}}}

namespace omni { namespace io { namespace dir_internal {
    inline std::string str_combine_path(const std::string& path1, const std::string& path2)
    {
        std::size_t psep = path1.find_last_of(OMNI_PATH_SEPARATOR);
        if (psep == path1.length()-1) { return path1 + path2; }
        return path1 + OMNI_PATH_SEPARATOR + path2;
    }
    inline std::wstring wstr_combine_path(const std::wstring& path1, const std::wstring& path2)
    {
        std::size_t psep = path1.find_last_of(OMNI_WPATH_SEPARATOR);
        if (psep == path1.length()-1) { return path1 + path2; }
        return path1 + OMNI_WPATH_SEPARATOR + path2;
    }

    #if defined(OMNI_OS_WIN)
        
    #else
        
    #endif

    #if defined(OMNI_OS_WIN)
        inline bool can_access(const std::string& path)
        {
            OMNI_FILE_CHECKA_FW(path, false)
            HANDLE hnd = ::CreateFileA(path.c_str(), FILE_TRAVERSE | SYNCHRONIZE,
                                       FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING,
                                       FILE_FLAG_BACKUP_SEMANTICS, NULL);
            if (hnd == INVALID_HANDLE_VALUE) {
                return false;
            }
            ::CloseHandle(hnd);
            return true;
        }

        inline bool can_access(const std::wstring& path)
        {
            std::wstring tf = OMNI_FILE_CHECKW_FW(tf, path, false)
            HANDLE hnd = ::CreateFileW(tf.c_str(), FILE_TRAVERSE | SYNCHRONIZE,
                                       FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING,
                                       FILE_FLAG_BACKUP_SEMANTICS, NULL);
            if (hnd == INVALID_HANDLE_VALUE) {
                return false;
            }
            ::CloseHandle(hnd);
            return true;
        }

        template < template < class, class > class std_seq_t, class T, class std_allocator_t >
        uint64_t get_dir_cont_win_fw(const std::string& name, std_seq_t< T, std_allocator_t >& dirs, int ftype)
        {
            std::string full = omni::io::dir_internal::str_combine_path(name, "*");
            #if defined(OMNI_WIN_API)
                OMNI_FILE_CHECKA_FW(full, dirs)
                WIN32_FIND_DATAA c_file;
                HANDLE hFile = ::FindFirstFileA(full.c_str(), &c_file);
                if (hFile != INVALID_HANDLE_VALUE) {
                    do {
                        std::string fname = std::string(c_file.cFileName);
                        if (fname != "." && fname != ".." ) { // do not add root dir
                            std::string file = omni::io::dir_internal::str_combine_path(name, fname);
                            if (ftype == 0) {
                                if (omni::io::dir_internal::exists(file)) { dirs.push_back(file); }
                            } else {
                                if (omni::io::file_internal::exists(file)) { dirs.push_back(file); }
                            }
                        }
                    } while (::FindNextFileA(hFile, &c_file));
                }
                ::FindClose(hFile);
            #else
                struct _finddata_t c_file;
                long hFile;
                if ((hFile = ::_findfirst(full.c_str(), &c_file)) != -1L) {
                    do {
                        std::string fname = std::string(c_file.name);
                        if (fname != "." && fname != ".." ) { // do not add root dir
                            std::string file = omni::io::dir_internal::str_combine_path(name, fname);
                            if (ftype == 0) {
                                if (omni::io::dir_internal::exists(file)) { dirs.push_back(file); }
                            } else {
                                if (omni::io::file_internal::exists(file)) { dirs.push_back(file); }
                            }
                        }
                    } while (::_findnext(hFile, &c_file) == 0);
                    ::_findclose(hFile);
                }
            #endif
            return dirs.size();
        }

        template < template < class, class > class std_seq_t, class T, class std_allocator_t >
        uint64_t get_dir_cont_win_fw(const std::wstring& name, std_seq_t< T, std_allocator_t >& dirs, int ftype)
        {
            std::wstring full = omni::io::dir_internal::wstr_combine_path(name, L"*");
            #if defined(OMNI_WIN_API)
                std::wstring tf = OMNI_FILE_CHECKW_FW(tf, full, false)
                WIN32_FIND_DATAW c_file;
                HANDLE hFile = ::FindFirstFileW(tf.c_str(), &c_file);
                if (hFile != INVALID_HANDLE_VALUE) {
                    do {
                        std::wstring fname = omni::string::to_wstring(c_file.cFileName);
                        if (fname != L"." && fname != L".." ) { // do not add root dir
                            std::wstring file = omni::io::dir_internal::wstr_combine_path(name, fname);
                            if (ftype == 0) {
                                if (omni::io::dir_internal::exists(file)) { dirs.push_back(file); }
                            } else {
                                if (omni::io::file_internal::exists(file)) { dirs.push_back(file); }
                            }
                        }
                    } while (::FindNextFileW(hFile, &c_file));
                }
                ::FindClose(hFile);
            #else
                struct _wfinddata_t c_file;
                long hFile;
                if ((hFile = ::_wfindfirst(full.c_str(), &c_file)) != -1L) {
                    do {
                        std::wstring fname = std::wstring(c_file.name);
                        if (fname != L"." && fname != L".." ) { // do not add root dir
                            std::wstring file = omni::io::dir_internal::wstr_combine_path(name, fname);
                            if (ftype == 0) {
                                if (omni::io::dir_internal::exists(file)) { dirs.push_back(file); }
                            } else {
                                if (omni::io::file_internal::exists(file)) { dirs.push_back(file); }
                            }
                        }
                    } while (::_wfindnext(hFile, &c_file) == 0);
                    ::_wfindclose(hFile);
                }
            #endif
            return dirs.size();
        }
    #else
        template < typename STR >
        inline bool can_access(const STR& path)
        {
            DIR *dp;
            if ((dp = ::opendir(omni::string::to_string(path).c_str())) == NULL) {
                if (errno == EACCES) { return false; }
            }
            ::closedir(dp);
            return true;
        }

        template < template < class, class > class std_seq_t, class T, class std_allocator_t >
        uint64_t get_dir_cont_nix_fw(const std::string& name, std_seq_t< T, std_allocator_t >& dirs, int ftype)
        {
            DIR *dp;
            struct dirent *dirp;
            if ((dp = ::opendir(name.c_str())) == NULL) {
                std::string er = "Error (";
                er += omni::string::util::to_string(errno) + "): " + std::strerror(errno);
                OMNI_ERRV_RETV_FW("Error opening file: ", errno, omni::exceptions::path_exception(er, name), dirs.size())
            }
            std::string fname, file;
            while ((dirp = ::readdir(dp)) != NULL) {
                fname = omni::string::util::lexical_cast<std::string>(dirp->d_name);
                if ((fname == ".") || (fname == "..")) { continue; }
                file = omni::io::dir_internal::str_combine_path(name, fname);
                if (ftype == 0) {
                    if (omni::io::dir_internal::exists(file)) { dirs.push_back(file); }
                } else {
                    if (omni::io::file_internal::exists(file)) { dirs.push_back(file); }
                }
            }
            ::closedir(dp);
            return dirs.size();
        }
        
        template < template < class, class > class std_seq_t, class T, class std_allocator_t >
        uint64_t get_dir_cont_nix_fw(const std::wstring& name, std_seq_t< T, std_allocator_t >& dirs, int ftype)
        {
            DIR *dp;
            struct dirent *dirp;
            std::string nm = omni::string::to_string(name);
            if ((dp = ::opendir(nm.c_str())) == NULL) {
                std::string er = "Error (";
                er += omni::string::util::to_string(errno) + "): " + std::strerror(errno);
                OMNI_ERRV_RETV_FW("Error opening file: ", errno, omni::exceptions::path_exception(er, nm), dirs.size())
            }
            std::wstring fname, file;
            while ((dirp = ::readdir(dp)) != NULL) {
                fname = omni::string::util::lexical_cast<std::wstring>(dirp->d_name);
                if ((fname == L".") || (fname == L"..")) { continue; }
                file = omni::io::dir_internal::wstr_combine_path(name, fname);
                if (ftype == 0) {
                    if (omni::io::dir_internal::exists(file)) { dirs.push_back(file); }
                } else {
                    if (omni::io::file_internal::exists(file)) { dirs.push_back(file); }
                }
            }
            ::closedir(dp);
            return dirs.size();
        }
    #endif

    template < typename STR >
    STR trim_trailing_slash(const STR& path)
    {
        std::size_t found = path.find_last_not_of(omni::string::util::lexical_cast<STR>("\\/").c_str());
        if (found != STR::npos) {
            return path.substr(0, found+1);
        }
        return path;
    }

    template < typename STR, template < class, class > class std_seq_t, class T, class std_allocator_t >
    uint64_t get_elements(const STR& folder, std_seq_t< T, std_allocator_t >& out, int ftype)
    {
        if (!omni::io::dir_internal::can_access(folder)) { return 0; }
        STR name = omni::io::dir_internal::trim_trailing_slash(folder);
        if (!omni::io::dir_internal::exists(name)) {
            OMNI_ERRV_RETV_FW("directory does not exist: ", omni::string::to_string_t(name), omni::exceptions::path_exception("Directory does not exist", omni::string::to_string(name)), 0)
        }
        #if defined(OMNI_OS_WIN)
            return get_dir_cont_win_fw(name, out, ftype);
        #else
            return get_dir_cont_nix_fw(name, out, ftype);
        #endif
    }

    template < typename STR, template < class, class > class std_seq_t, class T, class std_allocator_t >
    uint64_t get_directories(const STR& folder, std_seq_t< T, std_allocator_t >& out)
    {
        return omni::io::dir_internal::get_elements< STR, std_seq_t, T, std_allocator_t >(folder, out, 0);
    }

    template < typename STR, template < class, class > class std_seq_t, class T, class std_allocator_t >
    uint64_t get_files(const STR& folder, std_seq_t< T, std_allocator_t >& out)
    {
        return omni::io::dir_internal::get_elements< STR, std_seq_t, T, std_allocator_t >(folder, out, 1);
    }

    template < typename STR, template < class, class > class std_seq_t, class T, class std_allocator_t >
    uint64_t get_all_directories(const STR& folder, std_seq_t< T, std_allocator_t >& out)
    {
        if (!omni::io::dir_internal::can_access(folder)) { return 0; }
        std_seq_t< T, std_allocator_t > subs;
        omni::io::dir_internal::get_directories(folder, out);
        for (typename std_seq_t< T, std_allocator_t >::iterator dir = out.begin(); dir != out.end(); ++dir) {
            std_seq_t< T, std_allocator_t > sub;
            omni::io::dir_internal::get_all_directories(*dir, sub);
            subs.insert(subs.end(), sub.begin(), sub.end());
        }
        out.insert(out.end(), subs.begin(), subs.end());
        return out.size();
    }

    template < typename STR, template < class, class > class std_seq_t, class T, class std_allocator_t >
    uint64_t get_all_files(const STR& folder, std_seq_t< T, std_allocator_t >& out)
    {
        if (!omni::io::dir_internal::can_access(folder)) { return 0; }
        std_seq_t< T, std_allocator_t > dirs;
        omni::io::dir_internal::get_files(folder, out);
        omni::io::dir_internal::get_directories(folder, dirs);
        for (typename std_seq_t< T, std_allocator_t >::iterator dir = dirs.begin(); dir != dirs.end(); ++dir) {
            std_seq_t< T, std_allocator_t > sub;
            omni::io::dir_internal::get_all_files(*dir, sub);
            out.insert(out.end(), sub.begin(), sub.end());
        }
        return out.size();
    }
}}}
#undef OMNI_IO_FILE_RW_FW
