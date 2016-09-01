Alice Long optIons C++ Extractor
================================
Features
--------
 * *compile time* key access. It is not possible to ask for a key that is not registred
 * *compile time* value type. Each value has its type defined at compile time. Recognized types are `string`, `long long`, and `double`. All options are stored as `std::vector<T>`.
 * Build-in command line summary generation
 * Build-in command line dump. The given command line is formatted as JSON data.

Requirements
------------
 * C++14 support
 * maike

Example usage
-------------
See `test.cpp`

TODO
----
Error handling
