#include "base64.h"
#include <stdint.h>
#include <string.h>
#ifdef DEBUG
#include <stdio.h>
#endif

static const char base64_alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static const char base64_url_alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";

bool is_base64_char(char c, bool url_safe) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||
           (c >= '0' && c <= '9') || (c == (url_safe ? '-' : '+')) || 
           (c == (url_safe ? '_' : '/')) || (c == '=');
}

int base64_encoded_length(size_t input_length) {
    return 4 * ((input_length + 2) / 3);
}

int base64_decoded_length(const char* input, size_t input_length, bool url_safe) {
    if (!input) return -1; // Invalid input

    // Validate all characters in the input
    for (size_t i = 0; i < input_length; i++) {
        if (!is_base64_char(input[i], url_safe)) return -1; // Invalid character found
    }

    // Handle cases where padding might be omitted in URL-safe version
    size_t padding = 0;
    if (input_length % 4 != 0) {
        if (!url_safe) return -1; // Non-URL-safe must have padding
        padding = 4 - (input_length % 4);
    } else {
        if (input[input_length - 1] == '=') padding++;
        if (input[input_length - 2] == '=') padding++;
    }

    return (input_length + padding) / 4 * 3 - padding;
}

int base64_encode(char* output, const char* input, size_t input_length, bool url_safe) {
    if (!output || !input) return -1; // Null pointer check

    const char* alphabet = url_safe ? base64_url_alphabet : base64_alphabet;

    size_t i, j;
    for (i = 0, j = 0; i < input_length;) {
        uint32_t octet_a = i < input_length ? (unsigned char)input[i++] : 0;
        uint32_t octet_b = i < input_length ? (unsigned char)input[i++] : 0;
        uint32_t octet_c = i < input_length ? (unsigned char)input[i++] : 0;

        uint32_t triple = (octet_a << 16) + (octet_b << 8) + octet_c;

        output[j++] = alphabet[(triple >> 18) & 0x3F];
        output[j++] = alphabet[(triple >> 12) & 0x3F];
        output[j++] = alphabet[(triple >> 6) & 0x3F];
        output[j++] = alphabet[triple & 0x3F];
    }

    // Padding
    if (!url_safe) {
        if (input_length % 3 == 1) {
            output[j - 2] = '=';
            output[j - 1] = '=';
        } else if (input_length % 3 == 2) {
            output[j - 1] = '=';
        }
    } else {
        // For URL-safe, we can optionally omit the padding
        j = (input_length + 2) / 3 * 4;
    }

    output[j] = '\0';
    return 0;
}

int base64_decode(char* output, const char* input, size_t input_length, bool url_safe) {
    #ifdef DEBUG
    printf("Decoding: %s\n", input);
    printf("Input length: %zu\n", input_length);
    #endif

    if (!output || !input) return -1;

    int decoded_length = base64_decoded_length(input, input_length, url_safe);
    #ifdef DEBUG
    printf("Calculated decoded length: %d\n", decoded_length);
    #endif
    if (decoded_length == -1) return -1;

    // Create decoding table
    unsigned char decoding_table[256] = {0};
    const char* alphabet = url_safe ? base64_url_alphabet : base64_alphabet;
    for (int i = 0; i < 64; i++) {
        decoding_table[(unsigned char)alphabet[i]] = i;
    }

    size_t i, j;
    for (i = 0, j = 0; i < input_length && j < decoded_length;) {
        #ifdef DEBUG
        printf("Decoding loop: i=%zu, j=%zu\n", i, j);
        #endif
        uint32_t sextet_a = (i < input_length && input[i] != '=') ? decoding_table[(unsigned char)input[i++]] : 0;
        uint32_t sextet_b = (i < input_length && input[i] != '=') ? decoding_table[(unsigned char)input[i++]] : 0;
        uint32_t sextet_c = (i < input_length && input[i] != '=') ? decoding_table[(unsigned char)input[i++]] : 0;
        uint32_t sextet_d = (i < input_length && input[i] != '=') ? decoding_table[(unsigned char)input[i++]] : 0;

        uint32_t triple = (sextet_a << 18) + (sextet_b << 12) + (sextet_c << 6) + sextet_d;

        if (j < decoded_length) output[j++] = (triple >> 16) & 0xFF;
        if (j < decoded_length) output[j++] = (triple >> 8) & 0xFF;
        if (j < decoded_length) output[j++] = triple & 0xFF;
    }

    output[j] = '\0';
    #ifdef DEBUG
    printf("Decoding complete. Decoded %zu bytes.\n", j);
    #endif
    return j; // Return number of decoded bytes
}
