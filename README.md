# This is the final assignment I wrote in the C++ programing course I took in my first year.
In this assignment we were required to write a header file of a "smart vector" class.

This vector behaves like an STL vector (also support iterator and reverse iterator operations) with a memory management optimization feature – we increased each time the vector's size by a ratio of 1.5 (was chosen for comfort properties as we learned that the best ratio is the golden ratio of 1.618 as used in Java arrays.) Although, the vector was copied back to the static memory only when its size was reduced under the given threshold, in order to minimize allocation operations.  

# We were required to implement the whole project from the ground up, thus all the source code was written solely by me.

There was a bonus feature, to implement a smart string class that inherited from the given vector. the Header file is attached as well.
