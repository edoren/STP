#ifndef BASE64_HPP
#define BASE64_HPP

#include <string>

std::string base64_decode(const std::string& string_to_decode);
std::string base64_encode(const std::string& string_to_encode);

#endif // BASE64_HPP
