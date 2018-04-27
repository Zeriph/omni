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
#if !defined(OMNI_HPP)
#define OMNI_HPP 1

#include <omni/framework.hpp>

/*
| This file is so you can include the entire framework in a couple of convenient ways
| 
| #include <omni/framework>
| or
| #include <omni.hpp>
| or
| #include <omnilib>
| 
| This file is also here to make some general developer notes about style and function
| within the Omni framework. Notes regarding how to use certain classes or specifics on
| the framework need be refereed to the help documentation.
*/

/*
DEVELOPER NOTES:

OMNI_THREAD_TRY_FW
OMNI_THREAD_CATCH_FW

omni::sync::unhandled_thread_exception
omni::sync::user_thread_exception(const omni::exception&)

*/

// Stylistic notes:

/* Macros:
| Macro's are a nice tool to aid in many compilation-time needs among various other
| meta-programming contexts. It is usually advised to use them sparingly throughout code
| for reasons relating to readability and maintainability, however, times might arise
| to have a specific need for a macro. To this the framework is cross-platform by design
| and thus needs certain macros to be used in order to enable/disable certain aspects of 
| the code based on platform/system functionality. The framework also aims to achieve
| a balance of speed and size as well as readability and maintainability; some areas
| of the framework will have similar (if not the same) code, and where an inherited
| class or static function wouldn't make sense a macro-function is used. Macro-functions
| an other framework specific macros that are not intended to be used outside of the
| framework source itself will end with "_FW", for example, OMNI_D2_FW is a framework
| specific macro that outputs debug information only when OMNI_SHOW_DEBUG is defined to
| be greater than 1 (e.g. -D OMNI_SHOW_DEBUG=2). Other macros that are designed to be
| used will be documented in the help docs and explain more as to what their purpose is
| and any issues to be aware of when using it. Some macros are simple helper macros
| where one might not want a function jump or there just might not be a specific need
| to have an entire function. For example, the OMNI_XOR_SWAP macro is defined as
|   #define OMNI_XOR_SWAP(a, b) a ^= b; b ^= a; a ^= b
| while the omni::xor_swap function is a templated function that does an equality check
| then references the macro. One might want to do an XOR swap but not want to incur the
| cost of a function jump or the equality check (e.g. you know that a will never = b),
| so we are giving the user the ability and option to use either while in the framework
| using macro's when and where it make sense for a specific function.
*/

/* Code Verbosity (explicit scoping):
| Part of the internal coding standards for Omni include a clause for being pedantic and
| how explicit to be with regards to the scope of the code. Part of the reasoning behind
| using a higher level of verbosity in the framework code is for immediate readability
| with/without code context. For example, given the following (C++11) code:
|   auto it = v.find(42);
| we can infer some things from this code given it's basic context, but we cannot tell
| more without digging deeper into the code. Note the word infer. Inference of logic/type
| is perfectly acceptable and the use of helper keywords and macros can most certainly
| make the code cleaner to look at, but the down side is the extra time that will need
| to be spent to find more specifics. Given the above example, we don't know anything
| about the 'find' function on the 'v' object, just that we can infer it's supposed to
| find the number 42. If were troubleshooting this specific area of code, we would have
| to do a little mental juggling to to keep track of what things are while validating
| the logic as well. If, however, things are explicit, we can focus instead on just the
| logic and editing it as needed, example:
|   std::map<int, float>::iterator it = v.find(42);
| this is explicitly clear as to what is, its time/memory constraints and other logic
| to be aware of surrounding this snippet; we only need read this statement and know
| to investigate further or move on. While we advocate for keeping things clean and simple
| this framework is designed to be accessible by a wide array of audiences and having
| things be overtly clear makes it easier to pick up and use.
*/

/* Code Verbosity (non-inherited classes):
| Some of the classes within the framework utilize a lot of the same structures or code,
| the thread and timer classes, for example, have the same concepts between some of them
| save a few key functions; the omni::chrono::sync_timer and omni::chrono::async_timer
| share almost identical code except for a few lines. To this, there are a few idioms we
| could utilize to save on code bloat. In some area's (like the constants and string namespace),
| macro's and an implementation file (.hxx) are used to give similar functions with different
| input/output. Internal/external template wrapper classes and functions are used in some
| areas as well. Inheritance is another idiom we could use, but typically avoid when it
| doesn't make sense. For example, the timers share a enough code as to warrant utilizing
| a base timer class, however, doing so thus incurs a vtable, and while not a lot (usually
| just 1 or 2 extra pointers), it is something extra that needs to be noted and taken care of;
| for example, a user might think it'd be "ok" to do something like the following code due
| to the fact that there is a base timer class:
| 
| class my_class : public virtual omni::chrono::timer {};
| my_class mc;
| omni::chrono::async_timer t(mc);
| 
| The above code might compile (if the framework inherited as such), but the results
| might not be as expected. To this we only inherit where it makes sense to do so, for
| example, the omni::sync::runnable is an abstract class that can be used as a base type
| for runnable objects that the omni::sync::runnable_thread can use, as well the
| omni::sync::runnable_thread inherits from the omni::sync::runnable (to be able to be
| used in other contexts).
|
| So while we try to keep the code slim (e.g. the DRY principle), some areas need some extra
| care to achieve this while still keeping the code easy to read and maintain.
*/

/* Code Documentation:
| The raw_src.zip has the original source files that contain documentation notes attached
| to each function for the custom Omni documentation generator to parse out. The source
| viewed in the help documentation does not contain these doxygen style comments since
| those comments are the help documentation (and it just makes the code more verbose).
| The raw_src.zip file is only available from the site (i.e. it's not apart of the
| help.zip or omni.zip files), this is due to the size of the files and the fact that
| the only difference between the src.zip and raw_src.zip is the document notes.
*/

#endif // OMNI_HPP
