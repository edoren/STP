#include "Base64.hpp"
#include <vector>

static const std::string base64_table =
                         "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                         "abcdefghijklmnopqrstuvwxyz"
                         "0123456789+/";

static inline bool is_valid_base64(unsigned char c) {
    return (isalnum(c) || (c == '+') || (c == '/'));
}

std::string base64_decode(const std::string& string_to_decode) {
    int count = 0;
    std::vector<unsigned char> input_bytes(4, '\0');
    unsigned char byte_array[3];
    std::string result;

    for(int i = 0; i < string_to_decode.size(); i++) {
        if(is_valid_base64(string_to_decode[i]))
            input_bytes[count++] = base64_table.find(string_to_decode[i]);
        if(count == 4 || string_to_decode[i] == '=') {
            byte_array[0] = (input_bytes[0] << 2) | ((input_bytes[1] & 48) >> 4);
            byte_array[1] = ((input_bytes[1] & 15) << 4) | ((input_bytes[2] & 60) >> 2);
            byte_array[2] = ((input_bytes[2] & 3) << 6) | input_bytes[3];

            input_bytes = std::vector<unsigned char>(4, '\0');

            for(int j = 0; j < count - 1; j++)
                result += byte_array[j];

            if(count != 4)
                break;
            else
                count = 0;
        }
    }

    return result;
}

std::string base64_encode(const std::string& string_to_encode) {
    int count = 0;
    std::vector<unsigned char> input_bytes(3, '\0');
    unsigned char byte_array[4];
    std::string result;

    for(int i = 0; i < string_to_encode.size(); i++) {
        input_bytes[count++] = string_to_encode[i];
        if(count == 3 || (i == string_to_encode.size() - 1)) {
            byte_array[0] = input_bytes[0] >> 2;
            byte_array[1] = ((input_bytes[0] & 3) << 4) | (input_bytes[1] >> 4);
            byte_array[2] = ((input_bytes[1] & 15) << 2) | (input_bytes[2] >> 6);
            byte_array[3] = input_bytes[2] & 63;

            input_bytes = std::vector<unsigned char>(3, '\0');

            for(int j = 0; j < count + 1; j++)
                result += base64_table[byte_array[j]];

            if(count != 3)
                for(int i = count; i < 3; i++)
                    result += '=';
            else
                count = 0;
        }
    }

    return result;
}
