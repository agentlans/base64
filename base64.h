#ifndef BASE64_H
#define BASE64_H

#include <stddef.h>
#include <stdbool.h>

/**
 * @brief Determines if a character is valid in the Base64 encoding alphabet.
 *
 * @param c The character to check.
 * @param url_safe Specifies whether to use the URL-safe Base64 alphabet.
 * @return `true` if the character is valid in the specified Base64 alphabet, `false` otherwise.
 */
bool is_base64_char(char c, bool url_safe);

/**
 * @brief Computes the length of the Base64-encoded output for a given input size.
 *
 * @param input_length The size of the input data (in bytes) to be encoded. This excludes any null terminators.
 * @return The required length of the Base64-encoded output (excluding the null terminator).
 */
int base64_encoded_length(size_t input_length);

/**
 * @brief Computes the length of the decoded output for a given Base64-encoded input.
 *
 * @param input The Base64-encoded input string.
 * @param input_length The length of the input string (in bytes), excluding any null terminators.
 * @param url_safe Specifies whether the input uses URL-safe Base64 encoding.
 * @return The length of the decoded output in bytes, or `-1` if the input is invalid.
 */
int base64_decoded_length(const char* input, size_t input_length, bool url_safe);

/**
 * @brief Encodes binary data into a Base64 string.
 *
 * @param output A buffer to store the encoded string. This buffer must be large enough to hold the encoded data plus a null terminator (`\0`).
 * @param input The binary data to encode.
 * @param input_length The size of the binary data (in bytes).
 * @param url_safe Specifies whether to use URL-safe Base64 encoding.
 * @return `0` on success, or `-1` on failure (e.g., if any pointer is null).
 *
 * @note The resulting encoded string in `output` will always include a null terminator (`\0`) for convenience, even though Base64 itself does not require it. The `input` data does not need to be null-terminated since its length is explicitly provided by `input_length`.
 */
int base64_encode(char* output, const char* input, size_t input_length, bool url_safe);

/**
 * @brief Decodes a Base64-encoded string into binary data.
 *
 * @param output A buffer to store the decoded binary data. This buffer must be large enough to hold the decoded data plus a null terminator (`\0`).
 * @param input The Base64-encoded input string.
 * @param input_length The length of the encoded string (in bytes), excluding any null terminators.
 * @param url_safe Specifies whether the input uses URL-safe Base64 encoding.
 * @return The number of bytes successfully decoded (excluding the null terminator), or `-1` on failure (e.g., invalid input or insufficient buffer size).
 *
 * @note For convenience, the decoded output in `output` will include a null terminator (`\0`), even though it is not part of the actual binary data. The `input` string does not need to be null-terminated as its length is explicitly provided by `input_length`.
 */
int base64_decode(char* output, const char* input, size_t input_length, bool url_safe);

#endif // BASE64_H
