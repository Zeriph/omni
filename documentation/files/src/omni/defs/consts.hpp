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
#if !defined(OMNI_CONSTS_DEF_HPP)
#define OMNI_CONSTS_DEF_HPP 1

#if !defined(OMNI_APP_RUNNING_STR)
    #define OMNI_APP_RUNNING_STR "An application context is already running"
#endif
#if !defined(OMNI_ERR_GET_TIME_STR)
    #define OMNI_ERR_GET_TIME_STR "An error occurred getting the system clock time"
#endif
#if !defined(OMNI_ERR_MALLOC_STR)
    #define OMNI_ERR_MALLOC_STR "Error allocating memory"
#endif
#if !defined(OMNI_ERR_PROC_STR)
    #define OMNI_ERR_PROC_STR "Error opening process"
#endif
#if !defined(OMNI_ERR_PROC_PRI_STR)
    #define OMNI_ERR_PROC_PRI_STR "Error retrieving the processes priority class"
#endif
#if !defined(OMNI_ERR_MUTEX_STR)
    #define OMNI_ERR_MUTEX_STR "A system error occurred on the mutex object"
#endif
#if !defined(OMNI_ERR_MTX_STATE_STR)
    #define OMNI_ERR_MTX_STATE_STR "The system mutex was left in an invalid state"
#endif
#if !defined(OMNI_ERR_MTX_UNLOCKED_STR)
    #define OMNI_ERR_MTX_UNLOCKED_STR "An attempt was made to unlock a non locked mutex"
#endif
#if !defined(OMNI_ERR_MTX_OWNER_STR)
    #define OMNI_ERR_MTX_OWNER_STR "Unlock called from non-owning thread"
#endif
#if !defined(OMNI_ERR_SEMAPHORE_STR)
    #define OMNI_ERR_SEMAPHORE_STR "A system error occurred on the semaphore object"
#endif
#if !defined(OMNI_ERR_SEM_STATE_STR)
    #define OMNI_ERR_SEM_STATE_STR "An attempt was made to release a semaphore in a non-wait state"
#endif
#if !defined(OMNI_ERR_SPIN_OBJ_STR)
    #define OMNI_ERR_SPIN_OBJ_STR "A system error occurred on the spin lock object"
#endif
#if !defined(OMNI_ERR_COND_OBJ_STR)
    #define OMNI_ERR_COND_OBJ_STR "A system error occurred on the conditional object"
#endif
#if !defined(OMNI_ERR_WAIT_STR)
    #define OMNI_ERR_WAIT_STR "Active waits pending when disposing a lock object"
#endif
#if !defined(OMNI_ERR_RELEASE_STR)
    #define OMNI_ERR_RELEASE_STR "An invalid release count was specified"
#endif
#if !defined(OMNI_ERR_THREAD_STR)
    #define OMNI_ERR_THREAD_STR "An error occurred on the thread"
#endif
#if !defined(OMNI_ERR_SET_PRI_STR)
    #define OMNI_ERR_SET_PRI_STR "Error setting the threads priority"
#endif
#if !defined(OMNI_ERR_THREADPOOL_STR)
    #define OMNI_ERR_THREADPOOL_STR "An error occurred on the threadpool"
#endif
#if !defined(OMNI_ERR_STATE_STR)
    #define OMNI_ERR_STATE_STR "Internal state error"
#endif
#if !defined(OMNI_ERR_ACQUIRE_STR)
    #define OMNI_ERR_ACQUIRE_STR "Could not acquire thread"
#endif
#if !defined(OMNI_ERR_APPEX_STR)
    #define OMNI_ERR_APPEX_STR "An application exception occurred"
#endif
#if !defined(OMNI_ERR_ENVEX_STR)
    #define OMNI_ERR_ENVEX_STR "An error occurred within the system environment"
#endif
#if !defined(OMNI_ERR_PARSE_STR)
    #define OMNI_ERR_PARSE_STR "An error occurred parsing a string"
#endif
#if !defined(OMNI_ERR_NAME_STR)
    #define OMNI_ERR_NAME_STR "Name cannot be empty"
#endif
#if !defined(OMNI_ERR_PIPE_STR)
    #define OMNI_ERR_PIPE_STR "Failed to open the pipe"
#endif
#if !defined(OMNI_ERR_SIZE_STR)
    #define OMNI_ERR_SIZE_STR "Invalid size written"
#endif
#if !defined(OMNI_ERR_BASE_STR)
    #define OMNI_ERR_BASE_STR "Invalid base specified"
#endif
#if !defined(OMNI_ERR_RANGE_STR)
    #define OMNI_ERR_RANGE_STR "Invalid range specified"
#endif
#if !defined(OMNI_ERR_STROBJ_STR)
    #define OMNI_ERR_STROBJ_STR "A general exception occurred on the string object"
#endif
#if !defined(OMNI_ERR_STOPWATCH_STR)
    #define OMNI_ERR_STOPWATCH_STR "An error occurred on the stopwatch object"
#endif
#if !defined(OMNI_ERR_SOCKET_STR)
    #define OMNI_ERR_SOCKET_STR "An error occurred on the socket object"
#endif
#if !defined(OMNI_FILE_NOT_FOUND_STR)
    #define OMNI_FILE_NOT_FOUND_STR "File not found"
#endif
#if !defined(OMNI_FILE_NOT_ACCESSIBLE_STR)
    #define OMNI_FILE_NOT_ACCESSIBLE_STR "File not accessible"
#endif
#if !defined(OMNI_GENERAL_EXCEPTION_STR)
    #define OMNI_GENERAL_EXCEPTION_STR "General library exception"
#endif
#if !defined(OMNI_IO_ERROR_STR)
    #define OMNI_IO_ERROR_STR "General I/O error"
#endif
#if !defined(OMNI_INDEX_OOR_STR)
    #define OMNI_INDEX_OOR_STR "Index out of range"
#endif
#if !defined(OMNI_INVALID_BASE_STR)
    #define OMNI_INVALID_BASE_STR "Invalid base specified while converting to string"
#endif
#if !defined(OMNI_INVALID_CHAR_STR)
    #define OMNI_INVALID_CHAR_STR "Invalid value specified for conversion to char"
#endif
#if !defined(OMNI_INVALID_TEMPLATE_STR)
    #define OMNI_INVALID_TEMPLATE_STR "Invalid template parameter"
#endif
#if !defined(OMNI_INVALID_CAST_STR)
    #define OMNI_INVALID_CAST_STR "Invalid type cast"
#endif
#if !defined(OMNI_INVALID_DELEGATE_STR)
    #define OMNI_INVALID_DELEGATE_STR "Invalid delegate"
#endif
#if !defined(OMNI_INVALID_DELEGATE_FUNC_STR)
    #define OMNI_INVALID_DELEGATE_FUNC_STR "No valid function has been assigned to the delegate"
#endif
#if !defined(OMNI_INVALID_DELEGATE_INVOKE_STR)
    #define OMNI_INVALID_DELEGATE_INVOKE_STR "Invalid delegate invocation or return value"
#endif
#if !defined(OMNI_INVALID_OPTION_STR)
    #define OMNI_INVALID_OPTION_STR "An invalid thread option was specified"
#endif
#if !defined(OMNI_INVALID_ENUM_STR)
    #define OMNI_INVALID_ENUM_STR "An invalid enumeration was specified"
#endif
#if !defined(OMNI_INVALID_SETTING_STR)
    #define OMNI_INVALID_SETTING_STR "An invalid setting was specified"
#endif
#if !defined(OMNI_INVALID_SEEK_DIR_STR)
    #define OMNI_INVALID_SEEK_DIR_STR "Invalid seek direction"
#endif
#if !defined(OMNI_INVALID_THREAD_HANDLE_STR)
    #define OMNI_INVALID_THREAD_HANDLE_STR "Invalid thread handle"
#endif
#if !defined(OMNI_INVALID_THREAD_OWNER_STR)
    #define OMNI_INVALID_THREAD_OWNER_STR "Current thread invoking non-owning operation"
#endif
#if !defined(OMNI_INVALID_THREAD_PRIORITY_STR)
    #define OMNI_INVALID_THREAD_PRIORITY_STR "Invalid thread priority"
#endif
#if !defined(OMNI_INVALID_THREAD_START_TYPE_STR)
    #define OMNI_INVALID_THREAD_START_TYPE_STR "Invalid thread start type specified"
#endif
#if !defined(OMNI_INVALID_THREAD_STATE_STR)
    #define OMNI_INVALID_THREAD_STATE_STR "An invalid thread state was specified for the thread"
#endif
#if !defined(OMNI_INVALID_VERSION_STR)
    #define OMNI_INVALID_VERSION_STR "Invalid version string specified"
#endif
#if !defined(OMNI_INVALID_SIZE_STR)
    #define OMNI_INVALID_SIZE_STR "Invalid size specified"
#endif
#if !defined(OMNI_NO_DELEGATE_STR)
    #define OMNI_NO_DELEGATE_STR "Delegate not found"
#endif
#if !defined(OMNI_NULL_PTR_STR)
    #define OMNI_NULL_PTR_STR "Null pointer specified"
#endif
#if !defined(OMNI_NULL_REF_STR)
    #define OMNI_NULL_REF_STR "A null pointer reference exception occurred"
#endif
#if !defined(OMNI_NAN_ERR_STR)
    #define OMNI_NAN_ERR_STR "A not-a-number error has occurred"
#endif
#if !defined(OMNI_OVERFLOW_STR)
    #define OMNI_OVERFLOW_STR "A general overflow exception has occurred"
#endif
#if !defined(OMNI_UNDERFLOW_STR)
    #define OMNI_UNDERFLOW_STR "A general underflow exception has occurred"
#endif
#if !defined(OMNI_PATH_NOT_ACCESSIBLE_STR)
    #define OMNI_PATH_NOT_ACCESSIBLE_STR "Path not accessible"
#endif
#if !defined(OMNI_PATH_EMPTY_STR)
    #define OMNI_PATH_EMPTY_STR "Path is empty"
#endif
#if !defined(OMNI_PATH_ERROR_STR)
    #define OMNI_PATH_ERROR_STR "An error occurred with the specified path"
#endif
#if !defined(OMNI_SET_PRI_UNSUPPORTED_STR)
    #define OMNI_SET_PRI_UNSUPPORTED_STR "Setting thread priority is not supported on this system"
#endif
#if !defined(OMNI_STRING_COUNT_GT0_STR)
    #define OMNI_STRING_COUNT_GT0_STR "Count must be greater than 0"
#endif
#if !defined(OMNI_STRING_INVALID_BINARY_FORMAT_STR)
    #define OMNI_STRING_INVALID_BINARY_FORMAT_STR "The specified string does not contain a valid binary number"
#endif
#if !defined(OMNI_STRING_INVALID_FORMAT_STR)
    #define OMNI_STRING_INVALID_FORMAT_STR "Invalid string format specified"
#endif
#if !defined(OMNI_STRING_INVALID_SIZE_STR)
    #define OMNI_STRING_INVALID_SIZE_STR "The binary string length is greater than sizeof conversion unit"
#endif
#if !defined(OMNI_STRING_NOT_NUMERIC_STR)
    #define OMNI_STRING_NOT_NUMERIC_STR "The specified string is not a valid numeric value"
#endif
#if !defined(OMNI_SUCCESS_STR)
    #define OMNI_SUCCESS_STR "Success"
#endif
#if !defined(OMNI_THREAD_STARTED_STR)
    #define OMNI_THREAD_STARTED_STR "A thread has already been started"
#endif
#if !defined(OMNI_UNKNOWN_STR)
    #define OMNI_UNKNOWN_STR "Unknown"
#endif

#if !defined(OMNI_COMMA_CHAR)
    #define OMNI_COMMA_CHAR  ','
#endif
#if !defined(OMNI_MINUS_CHAR)
    #define OMNI_MINUS_CHAR  '-'
#endif
#if !defined(OMNI_NCHAR_CHAR)
    #define OMNI_NCHAR_CHAR  '\0'
#endif
#if !defined(OMNI_PERIOD_CHAR)
    #define OMNI_PERIOD_CHAR '.'
#endif
#if !defined(OMNI_PLUS_CHAR)
    #define OMNI_PLUS_CHAR   '+'
#endif

#if !defined(OMNI_COMMA_WCHAR)
    #define OMNI_COMMA_WCHAR  L','
#endif
#if !defined(OMNI_MINUS_WCHAR)
    #define OMNI_MINUS_WCHAR  L'-'
#endif
#if !defined(OMNI_NCHAR_WCHAR)
    #define OMNI_NCHAR_WCHAR  L'\0'
#endif
#if !defined(OMNI_PERIOD_WCHAR)
    #define OMNI_PERIOD_WCHAR L'.'
#endif
#if !defined(OMNI_PLUS_WCHAR)
    #define OMNI_PLUS_WCHAR   L'+'
#endif


#if !defined(OMNI_BYTE_STR)
    #define OMNI_BYTE_STR "Byte"
#endif
#if !defined(OMNI_KIBI_STR)
    #define OMNI_KIBI_STR "Kibibyte"
#endif
#if !defined(OMNI_MIBI_STR)
    #define OMNI_MIBI_STR "Mebibyte"
#endif
#if !defined(OMNI_GIBI_STR)
    #define OMNI_GIBI_STR "Gibibyte"
#endif
#if !defined(OMNI_TIBI_STR)
    #define OMNI_TIBI_STR "Tebibyte"
#endif
#if !defined(OMNI_PIBI_STR)
    #define OMNI_PIBI_STR "Pebibyte"
#endif
#if !defined(OMNI_EIBI_STR)
    #define OMNI_EIBI_STR "Exbibyte"
#endif
#if !defined(OMNI_ZIBI_STR)
    #define OMNI_ZIBI_STR "Zebibyte"
#endif
#if !defined(OMNI_YIBI_STR)
    #define OMNI_YIBI_STR "Yobibyte"
#endif

#if !defined(OMNI_KILO_STR)
    #define OMNI_KILO_STR "Kilobyte"
#endif
#if !defined(OMNI_MEGA_STR)
    #define OMNI_MEGA_STR "Megabyte"
#endif
#if !defined(OMNI_GIGA_STR)
    #define OMNI_GIGA_STR "Gigabyte"
#endif
#if !defined(OMNI_TERA_STR)
    #define OMNI_TERA_STR "Terabyte"
#endif
#if !defined(OMNI_PETA_STR)
    #define OMNI_PETA_STR "Petabyte"
#endif
#if !defined(OMNI_EXA_STR)
    #define OMNI_EXA_STR "Exabyte"
#endif
#if !defined(OMNI_ZETTA_STR)
    #define OMNI_ZETTA_STR "Zettabyte"
#endif
#if !defined(OMNI_YOTTA_STR)
    #define OMNI_YOTTA_STR "Yottabyte"
#endif

#if !defined(OMNI_B_STR)
    #define OMNI_B_STR "B"
#endif
#if !defined(OMNI_KIB_STR)
    #define OMNI_KIB_STR "KiB"
#endif
#if !defined(OMNI_MIB_STR)
    #define OMNI_MIB_STR "MiB"
#endif
#if !defined(OMNI_GIB_STR)
    #define OMNI_GIB_STR "GiB"
#endif
#if !defined(OMNI_TIB_STR)
    #define OMNI_TIB_STR "TiB"
#endif
#if !defined(OMNI_PIB_STR)
    #define OMNI_PIB_STR "PiB"
#endif
#if !defined(OMNI_EIB_STR)
    #define OMNI_EIB_STR "EiB"
#endif
#if !defined(OMNI_ZIB_STR)
    #define OMNI_ZIB_STR "ZiB"
#endif
#if !defined(OMNI_YIB_STR)
    #define OMNI_YIB_STR "YiB"
#endif

#if !defined(OMNI_KOB_STR)
    #define OMNI_KOB_STR "KB"
#endif
#if !defined(OMNI_MOB_STR)
    #define OMNI_MOB_STR "MB"
#endif
#if !defined(OMNI_GOB_STR)
    #define OMNI_GOB_STR "GB"
#endif
#if !defined(OMNI_TOB_STR)
    #define OMNI_TOB_STR "TB"
#endif
#if !defined(OMNI_POB_STR)
    #define OMNI_POB_STR "PB"
#endif
#if !defined(OMNI_EOB_STR)
    #define OMNI_EOB_STR "EB"
#endif
#if !defined(OMNI_ZOB_STR)
    #define OMNI_ZOB_STR "ZB"
#endif
#if !defined(OMNI_YOB_STR)
    #define OMNI_YOB_STR "YB"
#endif

#if !defined(OMNI_KIB_IVAL)
    #define OMNI_KIB_IVAL 1024
#endif
#if !defined(OMNI_MIB_IVAL)
    #define OMNI_MIB_IVAL 1048576
#endif
#if !defined(OMNI_GIB_IVAL)
    #define OMNI_GIB_IVAL 1073741824
#endif
#if !defined(OMNI_TIB_IVAL)
    #define OMNI_TIB_IVAL 1099511627776
#endif
#if !defined(OMNI_PIB_IVAL)
    #define OMNI_PIB_IVAL 1125899906842624
#endif
#if !defined(OMNI_EIB_IVAL)
    #define OMNI_EIB_IVAL 1152921504606846976
#endif

#if !defined(OMNI_KB_IVAL)
    #define OMNI_KB_IVAL 1000
#endif
#if !defined(OMNI_MB_IVAL)
    #define OMNI_MB_IVAL 1000000
#endif
#if !defined(OMNI_GB_IVAL)
    #define OMNI_GB_IVAL 1000000000
#endif
#if !defined(OMNI_TB_IVAL)
    #define OMNI_TB_IVAL 1000000000000
#endif
#if !defined(OMNI_PB_IVAL)
    #define OMNI_PB_IVAL 1000000000000000
#endif
#if !defined(OMNI_EB_IVAL)
    #define OMNI_EB_IVAL 1000000000000000000
#endif

#endif // OMNI_CONSTS_DEF_HPP
