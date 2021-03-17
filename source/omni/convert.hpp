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
#if !defined(OMNI_CONVERT_HPP)
#define OMNI_CONVERT_HPP 1
#include <omni/defs/global.hpp>
#include <omni/strings.hpp>

namespace omni {
    namespace convert {
        /*
            Methods
            // DEV_NOTE: these are the same thing as a dynamic_cast in C++
            ChangeType(Object, Type) - Returns an object of the specified type and whose value is equivalent to the specified object.
            ChangeType(Object, Type, IFormatProvider) - Returns an object of the specified type whose value is equivalent to the specified object. A parameter supplies culture-specific formatting information.
            ChangeType(Object, TypeCode) - Returns an object of the specified type whose value is equivalent to the specified object.
            ChangeType(Object, TypeCode, IFormatProvider) - Returns an object of the specified type whose value is equivalent to the specified object. A parameter supplies culture-specific formatting information.
            
            
            FromBase64CharArray(Char[], Int32, Int32) - Converts a subset of a Unicode character array, which encodes binary data as base-64 digits, to an equivalent 8-bit unsigned integer array. Parameters specify the subset in the input array and the number of elements to convert.
            FromBase64String(String) - Converts the specified string, which encodes binary data as base-64 digits, to an equivalent 8-bit unsigned integer array.
            FromHexString(ReadOnlySpan<Char>) - Converts the span, which encodes binary data as hex characters, to an equivalent 8-bit unsigned integer array.
            FromHexString(String) - Converts the specified string, which encodes binary data as hex characters, to an equivalent 8-bit unsigned integer array.
            GetTypeCode(Object) - Returns the TypeCode for the specified object.
            IsDBNull(Object) - Returns an indication whether the specified object is of type DBNull.
            ToBase64CharArray(Byte[], Int32, Int32, Char[], Int32) - Converts a subset of an 8-bit unsigned integer array to an equivalent subset of a Unicode character array encoded with base-64 digits. Parameters specify the subsets as offsets in the input and output arrays, and the number of elements in the input array to convert.
            ToBase64CharArray(Byte[], Int32, Int32, Char[], Int32, Base64FormattingOptions) - Converts a subset of an 8-bit unsigned integer array to an equivalent subset of a Unicode character array encoded with base-64 digits. Parameters specify the subsets as offsets in the input and output arrays, the number of elements in the input array to convert, and whether line breaks are inserted in the output array.
            ToBase64String(Byte[]) - Converts an array of 8-bit unsigned integers to its equivalent string representation that is encoded with base-64 digits.
            ToBase64String(Byte[], Base64FormattingOptions) - Converts an array of 8-bit unsigned integers to its equivalent string representation that is encoded with base-64 digits. You can specify whether to insert line breaks in the return value.
            ToBase64String(Byte[], Int32, Int32) - Converts a subset of an array of 8-bit unsigned integers to its equivalent string representation that is encoded with base-64 digits. Parameters specify the subset as an offset in the input array, and the number of elements in the array to convert.
            ToBase64String(Byte[], Int32, Int32, Base64FormattingOptions) - Converts a subset of an array of 8-bit unsigned integers to its equivalent string representation that is encoded with base-64 digits. Parameters specify the subset as an offset in the input array, the number of elements in the array to convert, and whether to insert line breaks in the return value.
            ToBase64String(ReadOnlySpan<Byte>, Base64FormattingOptions) - Converts the 8-bit unsigned integers inside the specified read-only span into their equivalent string representation that is encoded with base-64 digits. You can optionally specify whether to insert line breaks in the return value.
            ToBoolean(Boolean) - Returns the specified Boolean value; no actual conversion is performed.
            ToBoolean(Byte) - Converts the value of the specified 8-bit unsigned integer to an equivalent Boolean value.
            ToBoolean(Char) - Calling this method always throws InvalidCastException.
            ToBoolean(DateTime) - Calling this method always throws InvalidCastException.
            ToBoolean(Decimal) - Converts the value of the specified decimal number to an equivalent Boolean value.
            ToBoolean(Double) - Converts the value of the specified double-precision floating-point number to an equivalent Boolean value.
            ToBoolean(Int16) - Converts the value of the specified 16-bit signed integer to an equivalent Boolean value.
            ToBoolean(Int32) - Converts the value of the specified 32-bit signed integer to an equivalent Boolean value.
            ToBoolean(Int64) - Converts the value of the specified 64-bit signed integer to an equivalent Boolean value.
            ToBoolean(Object) - Converts the value of a specified object to an equivalent Boolean value.
            ToBoolean(Object, IFormatProvider) - Converts the value of the specified object to an equivalent Boolean value, using the specified culture-specific formatting information.
            ToBoolean(SByte) - Converts the value of the specified 8-bit signed integer to an equivalent Boolean value.
            ToBoolean(Single) - Converts the value of the specified single-precision floating-point number to an equivalent Boolean value.
            ToBoolean(String) - Converts the specified string representation of a logical value to its Boolean equivalent.
            ToBoolean(String, IFormatProvider) - Converts the specified string representation of a logical value to its Boolean equivalent, using the specified culture-specific formatting information.
            ToBoolean(UInt16) - Converts the value of the specified 16-bit unsigned integer to an equivalent Boolean value.
            ToBoolean(UInt32) - Converts the value of the specified 32-bit unsigned integer to an equivalent Boolean value.
            ToBoolean(UInt64) - Converts the value of the specified 64-bit unsigned integer to an equivalent Boolean value.
            ToByte(Boolean) - Converts the specified Boolean value to the equivalent 8-bit unsigned integer.
            ToByte(Byte) - Returns the specified 8-bit unsigned integer; no actual conversion is performed.
            ToByte(Char) - Converts the value of the specified Unicode character to the equivalent 8-bit unsigned integer.
            ToByte(DateTime) - Calling this method always throws InvalidCastException.
            ToByte(Decimal) - Converts the value of the specified decimal number to an equivalent 8-bit unsigned integer.
            ToByte(Double) - Converts the value of the specified double-precision floating-point number to an equivalent 8-bit unsigned integer.
            ToByte(Int16) - Converts the value of the specified 16-bit signed integer to an equivalent 8-bit unsigned integer.
            ToByte(Int32) - Converts the value of the specified 32-bit signed integer to an equivalent 8-bit unsigned integer.
            ToByte(Int64) - Converts the value of the specified 64-bit signed integer to an equivalent 8-bit unsigned integer.
            ToByte(Object) - Converts the value of the specified object to an 8-bit unsigned integer.
            ToByte(Object, IFormatProvider) - Converts the value of the specified object to an 8-bit unsigned integer, using the specified culture-specific formatting information.
            ToByte(SByte) - Converts the value of the specified 8-bit signed integer to an equivalent 8-bit unsigned integer.
            ToByte(Single) - Converts the value of the specified single-precision floating-point number to an equivalent 8-bit unsigned integer.
            ToByte(String) - Converts the specified string representation of a number to an equivalent 8-bit unsigned integer.
            ToByte(String, IFormatProvider) - Converts the specified string representation of a number to an equivalent 8-bit unsigned integer, using specified culture-specific formatting information.
            ToByte(String, Int32) - Converts the string representation of a number in a specified base to an equivalent 8-bit unsigned integer.
            ToByte(UInt16) - Converts the value of the specified 16-bit unsigned integer to an equivalent 8-bit unsigned integer.
            ToByte(UInt32) - Converts the value of the specified 32-bit unsigned integer to an equivalent 8-bit unsigned integer.
            ToByte(UInt64) - Converts the value of the specified 64-bit unsigned integer to an equivalent 8-bit unsigned integer.
            ToChar(Boolean) - Calling this method always throws InvalidCastException.
            ToChar(Byte) - Converts the value of the specified 8-bit unsigned integer to its equivalent Unicode character.
            ToChar(Char) - Returns the specified Unicode character value; no actual conversion is performed.
            ToChar(DateTime) - Calling this method always throws InvalidCastException.
            ToChar(Decimal) - Calling this method always throws InvalidCastException.
            ToChar(Double) - Calling this method always throws InvalidCastException.
            ToChar(Int16) - Converts the value of the specified 16-bit signed integer to its equivalent Unicode character.
            ToChar(Int32) - Converts the value of the specified 32-bit signed integer to its equivalent Unicode character.
            ToChar(Int64) - Converts the value of the specified 64-bit signed integer to its equivalent Unicode character.
            ToChar(Object) - Converts the value of the specified object to a Unicode character.
            ToChar(Object, IFormatProvider) - Converts the value of the specified object to its equivalent Unicode character, using the specified culture-specific formatting information.
            ToChar(SByte) - Converts the value of the specified 8-bit signed integer to its equivalent Unicode character.
            ToChar(Single) - Calling this method always throws InvalidCastException.
            ToChar(String) - Converts the first character of a specified string to a Unicode character.
            ToChar(String, IFormatProvider) - Converts the first character of a specified string to a Unicode character, using specified culture-specific formatting information.
            ToChar(UInt16) - Converts the value of the specified 16-bit unsigned integer to its equivalent Unicode character.
            ToChar(UInt32) - Converts the value of the specified 32-bit unsigned integer to its equivalent Unicode character.
            ToChar(UInt64) - Converts the value of the specified 64-bit unsigned integer to its equivalent Unicode character.
            ToDateTime(Boolean) - Calling this method always throws InvalidCastException.
            ToDateTime(Byte) - Calling this method always throws InvalidCastException.
            ToDateTime(Char) - Calling this method always throws InvalidCastException.
            ToDateTime(DateTime) - Returns the specified DateTime object; no actual conversion is performed.
            ToDateTime(Decimal) - Calling this method always throws InvalidCastException.
            ToDateTime(Double) - Calling this method always throws InvalidCastException.
            ToDateTime(Int16) - Calling this method always throws InvalidCastException.
            ToDateTime(Int32) - Calling this method always throws InvalidCastException.
            ToDateTime(Int64) - Calling this method always throws InvalidCastException.
            ToDateTime(Object) - Converts the value of the specified object to a DateTime object.
            ToDateTime(Object, IFormatProvider) - Converts the value of the specified object to a DateTime object, using the specified culture-specific formatting information.
            ToDateTime(SByte) - Calling this method always throws InvalidCastException.
            ToDateTime(Single) - Calling this method always throws InvalidCastException.
            ToDateTime(String) - Converts the specified string representation of a date and time to an equivalent date and time value.
            ToDateTime(String, IFormatProvider) - Converts the specified string representation of a number to an equivalent date and time, using the specified culture-specific formatting information.
            ToDateTime(UInt16) - Calling this method always throws InvalidCastException.
            ToDateTime(UInt32) - Calling this method always throws InvalidCastException.
            ToDateTime(UInt64) - Calling this method always throws InvalidCastException.
            ToDecimal(Boolean) - Converts the specified Boolean value to the equivalent decimal number.
            ToDecimal(Byte) - Converts the value of the specified 8-bit unsigned integer to the equivalent decimal number.
            ToDecimal(Char) - Calling this method always throws InvalidCastException.
            ToDecimal(DateTime) - Calling this method always throws InvalidCastException.
            ToDecimal(Decimal) - Returns the specified decimal number; no actual conversion is performed.
            ToDecimal(Double) - Converts the value of the specified double-precision floating-point number to an equivalent decimal number.
            ToDecimal(Int16) - Converts the value of the specified 16-bit signed integer to an equivalent decimal number.
            ToDecimal(Int32) - Converts the value of the specified 32-bit signed integer to an equivalent decimal number.
            ToDecimal(Int64) - Converts the value of the specified 64-bit signed integer to an equivalent decimal number.
            ToDecimal(Object) - Converts the value of the specified object to an equivalent decimal number.
            ToDecimal(Object, IFormatProvider) - Converts the value of the specified object to an equivalent decimal number, using the specified culture-specific formatting information.
            ToDecimal(SByte) - Converts the value of the specified 8-bit signed integer to the equivalent decimal number.
            ToDecimal(Single) - Converts the value of the specified single-precision floating-point number to the equivalent decimal number.
            ToDecimal(String) - Converts the specified string representation of a number to an equivalent decimal number.
            ToDecimal(String, IFormatProvider) - Converts the specified string representation of a number to an equivalent decimal number, using the specified culture-specific formatting information.
            ToDecimal(UInt16) - Converts the value of the specified 16-bit unsigned integer to an equivalent decimal number.
            ToDecimal(UInt32) - Converts the value of the specified 32-bit unsigned integer to an equivalent decimal number.
            ToDecimal(UInt64) - Converts the value of the specified 64-bit unsigned integer to an equivalent decimal number.
            ToDouble(Boolean) - Converts the specified Boolean value to the equivalent double-precision floating-point number.
            ToDouble(Byte) - Converts the value of the specified 8-bit unsigned integer to the equivalent double-precision floating-point number.
            ToDouble(Char) - Calling this method always throws InvalidCastException.
            ToDouble(DateTime) - Calling this method always throws InvalidCastException.
            ToDouble(Decimal) - Converts the value of the specified decimal number to an equivalent double-precision floating-point number.
            ToDouble(Double) - Returns the specified double-precision floating-point number; no actual conversion is performed.
            ToDouble(Int16) - Converts the value of the specified 16-bit signed integer to an equivalent double-precision floating-point number.
            ToDouble(Int32) - Converts the value of the specified 32-bit signed integer to an equivalent double-precision floating-point number.
            ToDouble(Int64) - Converts the value of the specified 64-bit signed integer to an equivalent double-precision floating-point number.
            ToDouble(Object) - Converts the value of the specified object to a double-precision floating-point number.
            ToDouble(Object, IFormatProvider) - Converts the value of the specified object to an double-precision floating-point number, using the specified culture-specific formatting information.
            ToDouble(SByte) - Converts the value of the specified 8-bit signed integer to the equivalent double-precision floating-point number.
            ToDouble(Single) - Converts the value of the specified single-precision floating-point number to an equivalent double-precision floating-point number.
            ToDouble(String) - Converts the specified string representation of a number to an equivalent double-precision floating-point number.
            ToDouble(String, IFormatProvider) - Converts the specified string representation of a number to an equivalent double-precision floating-point number, using the specified culture-specific formatting information.
            ToDouble(UInt16) - Converts the value of the specified 16-bit unsigned integer to the equivalent double-precision floating-point number.
            ToDouble(UInt32) - Converts the value of the specified 32-bit unsigned integer to an equivalent double-precision floating-point number.
            ToDouble(UInt64) - Converts the value of the specified 64-bit unsigned integer to an equivalent double-precision floating-point number.
            ToHexString(Byte[]) - Converts an array of 8-bit unsigned integers to its equivalent string representation that is encoded with uppercase hex characters.
            ToHexString(Byte[], Int32, Int32) - Converts a subset of an array of 8-bit unsigned integers to its equivalent string representation that is encoded with uppercase hex characters. Parameters specify the subset as an offset in the input array and the number of elements in the array to convert.
            ToHexString(ReadOnlySpan<Byte>) - Converts a span of 8-bit unsigned integers to its equivalent string representation that is encoded with uppercase hex characters.
            ToInt16(Boolean) - Converts the specified Boolean value to the equivalent 16-bit signed integer.
            ToInt16(Byte) - Converts the value of the specified 8-bit unsigned integer to the equivalent 16-bit signed integer.
            ToInt16(Char) - Converts the value of the specified Unicode character to the equivalent 16-bit signed integer.
            ToInt16(DateTime) - Calling this method always throws InvalidCastException.
            ToInt16(Decimal) - Converts the value of the specified decimal number to an equivalent 16-bit signed integer.
            ToInt16(Double) - Converts the value of the specified double-precision floating-point number to an equivalent 16-bit signed integer.
            ToInt16(Int16) - Returns the specified 16-bit signed integer; no actual conversion is performed.
            ToInt16(Int32) - Converts the value of the specified 32-bit signed integer to an equivalent 16-bit signed integer.
            ToInt16(Int64) - Converts the value of the specified 64-bit signed integer to an equivalent 16-bit signed integer.
            ToInt16(Object) - Converts the value of the specified object to a 16-bit signed integer.
            ToInt16(Object, IFormatProvider) - Converts the value of the specified object to a 16-bit signed integer, using the specified culture-specific formatting information.
            ToInt16(SByte) - Converts the value of the specified 8-bit signed integer to the equivalent 16-bit signed integer.
            ToInt16(Single) - Converts the value of the specified single-precision floating-point number to an equivalent 16-bit signed integer.
            ToInt16(String) - Converts the specified string representation of a number to an equivalent 16-bit signed integer.
            ToInt16(String, IFormatProvider) - Converts the specified string representation of a number to an equivalent 16-bit signed integer, using the specified culture-specific formatting information.
            ToInt16(String, Int32) - Converts the string representation of a number in a specified base to an equivalent 16-bit signed integer.
            ToInt16(UInt16) - Converts the value of the specified 16-bit unsigned integer to the equivalent 16-bit signed integer.
            ToInt16(UInt32) - Converts the value of the specified 32-bit unsigned integer to an equivalent 16-bit signed integer.
            ToInt16(UInt64) - Converts the value of the specified 64-bit unsigned integer to an equivalent 16-bit signed integer.
            ToInt32(Boolean) - Converts the specified Boolean value to the equivalent 32-bit signed integer.
            ToInt32(Byte) - Converts the value of the specified 8-bit unsigned integer to the equivalent 32-bit signed integer.
            ToInt32(Char) - Converts the value of the specified Unicode character to the equivalent 32-bit signed integer.
            ToInt32(DateTime) - Calling this method always throws InvalidCastException.
            ToInt32(Decimal) - Converts the value of the specified decimal number to an equivalent 32-bit signed integer.
            ToInt32(Double) - Converts the value of the specified double-precision floating-point number to an equivalent 32-bit signed integer.
            ToInt32(Int16) - Converts the value of the specified 16-bit signed integer to an equivalent 32-bit signed integer.
            ToInt32(Int32) - Returns the specified 32-bit signed integer; no actual conversion is performed.
            ToInt32(Int64) - Converts the value of the specified 64-bit signed integer to an equivalent 32-bit signed integer.
            ToInt32(Object) - Converts the value of the specified object to a 32-bit signed integer.
            ToInt32(Object, IFormatProvider) - Converts the value of the specified object to a 32-bit signed integer, using the specified culture-specific formatting information.
            ToInt32(SByte) - Converts the value of the specified 8-bit signed integer to the equivalent 32-bit signed integer.
            ToInt32(Single) - Converts the value of the specified single-precision floating-point number to an equivalent 32-bit signed integer.
            ToInt32(String) - Converts the specified string representation of a number to an equivalent 32-bit signed integer.
            ToInt32(String, IFormatProvider) - Converts the specified string representation of a number to an equivalent 32-bit signed integer, using the specified culture-specific formatting information.
            ToInt32(String, Int32) - Converts the string representation of a number in a specified base to an equivalent 32-bit signed integer.
            ToInt32(UInt16) - Converts the value of the specified 16-bit unsigned integer to the equivalent 32-bit signed integer.
            ToInt32(UInt32) - Converts the value of the specified 32-bit unsigned integer to an equivalent 32-bit signed integer.
            ToInt32(UInt64) - Converts the value of the specified 64-bit unsigned integer to an equivalent 32-bit signed integer.
            ToInt64(Boolean) - Converts the specified Boolean value to the equivalent 64-bit signed integer.
            ToInt64(Byte) - Converts the value of the specified 8-bit unsigned integer to the equivalent 64-bit signed integer.
            ToInt64(Char) - Converts the value of the specified Unicode character to the equivalent 64-bit signed integer.
            ToInt64(DateTime) - Calling this method always throws InvalidCastException.
            ToInt64(Decimal) - Converts the value of the specified decimal number to an equivalent 64-bit signed integer.
            ToInt64(Double) - Converts the value of the specified double-precision floating-point number to an equivalent 64-bit signed integer.
            ToInt64(Int16) - Converts the value of the specified 16-bit signed integer to an equivalent 64-bit signed integer.
            ToInt64(Int32) - Converts the value of the specified 32-bit signed integer to an equivalent 64-bit signed integer.
            ToInt64(Int64) - Returns the specified 64-bit signed integer; no actual conversion is performed.
            ToInt64(Object) - Converts the value of the specified object to a 64-bit signed integer.
            ToInt64(Object, IFormatProvider) - Converts the value of the specified object to a 64-bit signed integer, using the specified culture-specific formatting information.
            ToInt64(SByte) - Converts the value of the specified 8-bit signed integer to the equivalent 64-bit signed integer.
            ToInt64(Single) - Converts the value of the specified single-precision floating-point number to an equivalent 64-bit signed integer.
            ToInt64(String) - Converts the specified string representation of a number to an equivalent 64-bit signed integer.
            ToInt64(String, IFormatProvider) - Converts the specified string representation of a number to an equivalent 64-bit signed integer, using the specified culture-specific formatting information.
            ToInt64(String, Int32) - Converts the string representation of a number in a specified base to an equivalent 64-bit signed integer.
            ToInt64(UInt16) - Converts the value of the specified 16-bit unsigned integer to the equivalent 64-bit signed integer.
            ToInt64(UInt32) - Converts the value of the specified 32-bit unsigned integer to an equivalent 64-bit signed integer.
            ToInt64(UInt64) - Converts the value of the specified 64-bit unsigned integer to an equivalent 64-bit signed integer.
            ToSByte(Boolean) - Converts the specified Boolean value to the equivalent 8-bit signed integer.
            ToSByte(Byte) - Converts the value of the specified 8-bit unsigned integer to the equivalent 8-bit signed integer.
            ToSByte(Char) - Converts the value of the specified Unicode character to the equivalent 8-bit signed integer.
            ToSByte(DateTime) - Calling this method always throws InvalidCastException.
            ToSByte(Decimal) - Converts the value of the specified decimal number to an equivalent 8-bit signed integer.
            ToSByte(Double) - Converts the value of the specified double-precision floating-point number to an equivalent 8-bit signed integer.
            ToSByte(Int16) - Converts the value of the specified 16-bit signed integer to the equivalent 8-bit signed integer.
            ToSByte(Int32) - Converts the value of the specified 32-bit signed integer to an equivalent 8-bit signed integer.
            ToSByte(Int64) - Converts the value of the specified 64-bit signed integer to an equivalent 8-bit signed integer.
            ToSByte(Object) - Converts the value of the specified object to an 8-bit signed integer.
            ToSByte(Object, IFormatProvider) - Converts the value of the specified object to an 8-bit signed integer, using the specified culture-specific formatting information.
            ToSByte(SByte) - Returns the specified 8-bit signed integer; no actual conversion is performed.
            ToSByte(Single) - Converts the value of the specified single-precision floating-point number to an equivalent 8-bit signed integer.
            ToSByte(String) - Converts the specified string representation of a number to an equivalent 8-bit signed integer.
            ToSByte(String, IFormatProvider) - Converts the specified string representation of a number to an equivalent 8-bit signed integer, using the specified culture-specific formatting information.
            ToSByte(String, Int32) - Converts the string representation of a number in a specified base to an equivalent 8-bit signed integer.
            ToSByte(UInt16) - Converts the value of the specified 16-bit unsigned integer to the equivalent 8-bit signed integer.
            ToSByte(UInt32) - Converts the value of the specified 32-bit unsigned integer to an equivalent 8-bit signed integer.
            ToSByte(UInt64) - Converts the value of the specified 64-bit unsigned integer to an equivalent 8-bit signed integer.
            ToSingle(Boolean) - Converts the specified Boolean value to the equivalent single-precision floating-point number.
            ToSingle(Byte) - Converts the value of the specified 8-bit unsigned integer to the equivalent single-precision floating-point number.
            ToSingle(Char) - Calling this method always throws InvalidCastException.
            ToSingle(DateTime) - Calling this method always throws InvalidCastException.
            ToSingle(Decimal) - Converts the value of the specified decimal number to an equivalent single-precision floating-point number.
            ToSingle(Double) - Converts the value of the specified double-precision floating-point number to an equivalent single-precision floating-point number.
            ToSingle(Int16) - Converts the value of the specified 16-bit signed integer to an equivalent single-precision floating-point number.
            ToSingle(Int32) - Converts the value of the specified 32-bit signed integer to an equivalent single-precision floating-point number.
            ToSingle(Int64) - Converts the value of the specified 64-bit signed integer to an equivalent single-precision floating-point number.
            ToSingle(Object) - Converts the value of the specified object to a single-precision floating-point number.
            ToSingle(Object, IFormatProvider) - Converts the value of the specified object to an single-precision floating-point number, using the specified culture-specific formatting information.
            ToSingle(SByte) - Converts the value of the specified 8-bit signed integer to the equivalent single-precision floating-point number.
            ToSingle(Single) - Returns the specified single-precision floating-point number; no actual conversion is performed.
            ToSingle(String) - Converts the specified string representation of a number to an equivalent single-precision floating-point number.
            ToSingle(String, IFormatProvider) - Converts the specified string representation of a number to an equivalent single-precision floating-point number, using the specified culture-specific formatting information.
            ToSingle(UInt16) - Converts the value of the specified 16-bit unsigned integer to the equivalent single-precision floating-point number.
            ToSingle(UInt32) - Converts the value of the specified 32-bit unsigned integer to an equivalent single-precision floating-point number.
            ToSingle(UInt64) - Converts the value of the specified 64-bit unsigned integer to an equivalent single-precision floating-point number.
            ToString(Boolean) - Converts the specified Boolean value to its equivalent string representation.
            ToString(Boolean, IFormatProvider) - Converts the specified Boolean value to its equivalent string representation.
            ToString(Byte) - Converts the value of the specified 8-bit unsigned integer to its equivalent string representation.
            ToString(Byte, IFormatProvider) - Converts the value of the specified 8-bit unsigned integer to its equivalent string representation, using the specified culture-specific formatting information.
            ToString(Byte, Int32) - Converts the value of an 8-bit unsigned integer to its equivalent string representation in a specified base.
            ToString(Char) - Converts the value of the specified Unicode character to its equivalent string representation.
            ToString(Char, IFormatProvider) - Converts the value of the specified Unicode character to its equivalent string representation, using the specified culture-specific formatting information.
            ToString(DateTime) - Converts the value of the specified DateTime to its equivalent string representation.
            ToString(DateTime, IFormatProvider) - Converts the value of the specified DateTime to its equivalent string representation, using the specified culture-specific formatting information.
            ToString(Decimal) - Converts the value of the specified decimal number to its equivalent string representation.
            ToString(Decimal, IFormatProvider) - Converts the value of the specified decimal number to its equivalent string representation, using the specified culture-specific formatting information.
            ToString(Double) - Converts the value of the specified double-precision floating-point number to its equivalent string representation.
            ToString(Double, IFormatProvider) - Converts the value of the specified double-precision floating-point number to its equivalent string representation.
            ToString(Int16) - Converts the value of the specified 16-bit signed integer to its equivalent string representation.
            ToString(Int16, IFormatProvider) - Converts the value of the specified 16-bit signed integer to its equivalent string representation, using the specified culture-specific formatting information.
            ToString(Int16, Int32) - Converts the value of a 16-bit signed integer to its equivalent string representation in a specified base.
            ToString(Int32) - Converts the value of the specified 32-bit signed integer to its equivalent string representation.
            ToString(Int32, IFormatProvider) - Converts the value of the specified 32-bit signed integer to its equivalent string representation, using the specified culture-specific formatting information.
            ToString(Int32, Int32) - Converts the value of a 32-bit signed integer to its equivalent string representation in a specified base.
            ToString(Int64) - Converts the value of the specified 64-bit signed integer to its equivalent string representation.
            ToString(Int64, IFormatProvider) - Converts the value of the specified 64-bit signed integer to its equivalent string representation, using the specified culture-specific formatting information.
            ToString(Int64, Int32) - Converts the value of a 64-bit signed integer to its equivalent string representation in a specified base.
            ToString(Object) - Converts the value of the specified object to its equivalent string representation.
            ToString(Object, IFormatProvider) - Converts the value of the specified object to its equivalent string representation using the specified culture-specific formatting information.
            ToString(SByte) - Converts the value of the specified 8-bit signed integer to its equivalent string representation.
            ToString(SByte, IFormatProvider) - Converts the value of the specified 8-bit signed integer to its equivalent string representation, using the specified culture-specific formatting information.
            ToString(Single) - Converts the value of the specified single-precision floating-point number to its equivalent string representation.
            ToString(Single, IFormatProvider) - Converts the value of the specified single-precision floating-point number to its equivalent string representation, using the specified culture-specific formatting information.
            ToString(String) - Returns the specified string instance; no actual conversion is performed.
            ToString(String, IFormatProvider) - Returns the specified string instance; no actual conversion is performed.
            ToString(UInt16) - Converts the value of the specified 16-bit unsigned integer to its equivalent string representation.
            ToString(UInt16, IFormatProvider) - Converts the value of the specified 16-bit unsigned integer to its equivalent string representation, using the specified culture-specific formatting information.
            ToString(UInt32) - Converts the value of the specified 32-bit unsigned integer to its equivalent string representation.
            ToString(UInt32, IFormatProvider) - Converts the value of the specified 32-bit unsigned integer to its equivalent string representation, using the specified culture-specific formatting information.
            ToString(UInt64) - Converts the value of the specified 64-bit unsigned integer to its equivalent string representation.
            ToString(UInt64, IFormatProvider) - Converts the value of the specified 64-bit unsigned integer to its equivalent string representation, using the specified culture-specific formatting information.
            ToUInt16(Boolean) - Converts the specified Boolean value to the equivalent 16-bit unsigned integer.
            ToUInt16(Byte) - Converts the value of the specified 8-bit unsigned integer to the equivalent 16-bit unsigned integer.
            ToUInt16(Char) - Converts the value of the specified Unicode character to the equivalent 16-bit unsigned integer.
            ToUInt16(DateTime) - Calling this method always throws InvalidCastException.
            ToUInt16(Decimal) - Converts the value of the specified decimal number to an equivalent 16-bit unsigned integer.
            ToUInt16(Double) - Converts the value of the specified double-precision floating-point number to an equivalent 16-bit unsigned integer.
            ToUInt16(Int16) - Converts the value of the specified 16-bit signed integer to the equivalent 16-bit unsigned integer.
            ToUInt16(Int32) - Converts the value of the specified 32-bit signed integer to an equivalent 16-bit unsigned integer.
            ToUInt16(Int64) - Converts the value of the specified 64-bit signed integer to an equivalent 16-bit unsigned integer.
            ToUInt16(Object) - Converts the value of the specified object to a 16-bit unsigned integer.
            ToUInt16(Object, IFormatProvider) - Converts the value of the specified object to a 16-bit unsigned integer, using the specified culture-specific formatting information.
            ToUInt16(SByte) - Converts the value of the specified 8-bit signed integer to the equivalent 16-bit unsigned integer.
            ToUInt16(Single) - Converts the value of the specified single-precision floating-point number to an equivalent 16-bit unsigned integer.
            ToUInt16(String) - Converts the specified string representation of a number to an equivalent 16-bit unsigned integer.
            ToUInt16(String, IFormatProvider) - Converts the specified string representation of a number to an equivalent 16-bit unsigned integer, using the specified culture-specific formatting information.
            ToUInt16(String, Int32) - Converts the string representation of a number in a specified base to an equivalent 16-bit unsigned integer.
            ToUInt16(UInt16) - Returns the specified 16-bit unsigned integer; no actual conversion is performed.
            ToUInt16(UInt32) - Converts the value of the specified 32-bit unsigned integer to an equivalent 16-bit unsigned integer.
            ToUInt16(UInt64) - Converts the value of the specified 64-bit unsigned integer to an equivalent 16-bit unsigned integer.
            ToUInt32(Boolean) - Converts the specified Boolean value to the equivalent 32-bit unsigned integer.
            ToUInt32(Byte) - Converts the value of the specified 8-bit unsigned integer to the equivalent 32-bit unsigned integer.
            ToUInt32(Char) - Converts the value of the specified Unicode character to the equivalent 32-bit unsigned integer.
            ToUInt32(DateTime) - Calling this method always throws InvalidCastException.
            ToUInt32(Decimal) - Converts the value of the specified decimal number to an equivalent 32-bit unsigned integer.
            ToUInt32(Double) - Converts the value of the specified double-precision floating-point number to an equivalent 32-bit unsigned integer.
            ToUInt32(Int16) - Converts the value of the specified 16-bit signed integer to the equivalent 32-bit unsigned integer.
            ToUInt32(Int32) - Converts the value of the specified 32-bit signed integer to an equivalent 32-bit unsigned integer.
            ToUInt32(Int64) - Converts the value of the specified 64-bit signed integer to an equivalent 32-bit unsigned integer.
            ToUInt32(Object) - Converts the value of the specified object to a 32-bit unsigned integer.
            ToUInt32(Object, IFormatProvider) - Converts the value of the specified object to a 32-bit unsigned integer, using the specified culture-specific formatting information.
            ToUInt32(SByte) - Converts the value of the specified 8-bit signed integer to the equivalent 32-bit unsigned integer.
            ToUInt32(Single) - Converts the value of the specified single-precision floating-point number to an equivalent 32-bit unsigned integer.
            ToUInt32(String) - Converts the specified string representation of a number to an equivalent 32-bit unsigned integer.
            ToUInt32(String, IFormatProvider) - Converts the specified string representation of a number to an equivalent 32-bit unsigned integer, using the specified culture-specific formatting information.
            ToUInt32(String, Int32) - Converts the string representation of a number in a specified base to an equivalent 32-bit unsigned integer.
            ToUInt32(UInt16) - Converts the value of the specified 16-bit unsigned integer to the equivalent 32-bit unsigned integer.
            ToUInt32(UInt32) - Returns the specified 32-bit unsigned integer; no actual conversion is performed.
            ToUInt32(UInt64) - Converts the value of the specified 64-bit unsigned integer to an equivalent 32-bit unsigned integer.
            ToUInt64(Boolean) - Converts the specified Boolean value to the equivalent 64-bit unsigned integer.
            ToUInt64(Byte) - Converts the value of the specified 8-bit unsigned integer to the equivalent 64-bit unsigned integer.
            ToUInt64(Char) - Converts the value of the specified Unicode character to the equivalent 64-bit unsigned integer.
            ToUInt64(DateTime) - Calling this method always throws InvalidCastException.
            ToUInt64(Decimal) - Converts the value of the specified decimal number to an equivalent 64-bit unsigned integer.
            ToUInt64(Double) - Converts the value of the specified double-precision floating-point number to an equivalent 64-bit unsigned integer.
            ToUInt64(Int16) - Converts the value of the specified 16-bit signed integer to the equivalent 64-bit unsigned integer.
            ToUInt64(Int32) - Converts the value of the specified 32-bit signed integer to an equivalent 64-bit unsigned integer.
            ToUInt64(Int64) - Converts the value of the specified 64-bit signed integer to an equivalent 64-bit unsigned integer.
            ToUInt64(Object) - Converts the value of the specified object to a 64-bit unsigned integer.
            ToUInt64(Object, IFormatProvider) - Converts the value of the specified object to a 64-bit unsigned integer, using the specified culture-specific formatting information.
            ToUInt64(SByte) - Converts the value of the specified 8-bit signed integer to the equivalent 64-bit unsigned integer.
            ToUInt64(Single) - Converts the value of the specified single-precision floating-point number to an equivalent 64-bit unsigned integer.
            ToUInt64(String) - Converts the specified string representation of a number to an equivalent 64-bit unsigned integer.
            ToUInt64(String, IFormatProvider) - Converts the specified string representation of a number to an equivalent 64-bit unsigned integer, using the specified culture-specific formatting information.
            ToUInt64(String, Int32) - Converts the string representation of a number in a specified base to an equivalent 64-bit unsigned integer.
            ToUInt64(UInt16) - Converts the value of the specified 16-bit unsigned integer to the equivalent 64-bit unsigned integer.
            ToUInt64(UInt32) - Converts the value of the specified 32-bit unsigned integer to an equivalent 64-bit unsigned integer.
            ToUInt64(UInt64) - Returns the specified 64-bit unsigned integer; no actual conversion is performed.
            TryFromBase64Chars(ReadOnlySpan<Char>, Span<Byte>, Int32) - Tries to convert the specified span containing a string representation that is encoded with base-64 digits into a span of 8-bit unsigned integers.
            TryFromBase64String(String, Span<Byte>, Int32) - Tries to convert the specified string representation that is encoded with base-64 digits into a span of 8-bit unsigned integers.
            TryToBase64Chars(ReadOnlySpan<Byte>, Span<Char>, Int32, Base64FormattingOptions) - Tries to convert the 8-bit unsigned integers inside the specified read-only span into their equivalent string representation that is encoded with base-64 digits. You can optionally specify whether to insert line breaks in the return value.
        */

    }
}

#endif // OMNI_CONVERT_HPP
