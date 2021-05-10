### What is it?

**Unicoder** is a one header file which include one class for conversion between UTF8 <-> UTF16(UCS2) <-> UTF32(UCS4).

### The following standalone (locale-independent) specializations are provided by the standard library:

* std::codecvt<char, char, std::mbstate_t>	identity conversion
* std::codecvt<char16_t, char, std::mbstate_t>	conversion between UTF-16 and UTF-8 (since C++11) *(deprecated in C++20)*
* std::codecvt<char16_t, char8_t, std::mbstate_t>	conversion between UTF-16 and UTF-8 (since C++20)
* std::codecvt<char32_t, char, std::mbstate_t>	conversion between UTF-32 and UTF-8 (since C++11) *(deprecated in C++20)*
* std::codecvt<char32_t, char8_t, std::mbstate_t>	conversion between UTF-32 and UTF-8 (since C++20)
* std::codecvt<wchar_t, char, std::mbstate_t>	conversion between the system's native wide and the single-byte narrow character sets
