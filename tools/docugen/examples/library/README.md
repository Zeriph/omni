This folder contains full examples of the library like the omni::delegate or
omni::sync namespace.

Each folder contains an example.cpp that highlights some example usages of the
specific classes or namespace being showcased.

Each folder also contains an info.txt that gives some details about each of the
specific examples; the file is broken down as follows:

@name - The general name of the example being shown
@brief - A brief synopsis of the example
@details - A detailed overview of the specific example documented with DoxyGen
           tags.

Additionally, each folder's name has a number in the beginning; this number
represents the order in which you might want to read through the examples and
references to better understand the library. For example, the first folder
is `01_delegates_and_events` which contains the information and examples on
the omni::delegate and omni::event, which are the basic classes that allow Omni
to be what is and enable a lot of the various library classes. The next
folder is `02_threading` which contains information regarding the thread types
within the library, another key driver of the library. Since the delegate
and event system and threading systems are important to the utilization of the
library, they are put in that order.

This goes for the remainder of the folders, 03, 04, etc. are ordered as such to
help you get a foundation in the basics of the library.