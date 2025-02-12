# Base64 Encoding/Decoding Library

## Overview

This library provides a simple and efficient implementation of Base64 encoding and decoding in C. It supports both standard and URL-safe Base64 alphabets.

## Features

- Encode binary data to Base64 strings
- Decode Base64 strings to binary data
- Support for both standard and URL-safe Base64 alphabets
- Efficient length calculations for encoded and decoded data
- Character validation for Base64 alphabet

## API

The library exposes the following functions:

```c
bool is_base64_char(char c, bool url_safe);
int base64_encoded_length(size_t input_length);
int base64_decoded_length(const char* input, size_t input_length, bool url_safe);
int base64_encode(char* output, const char* input, size_t input_length, bool url_safe);
int base64_decode(char* output, const char* input, size_t input_length, bool url_safe);
```

For detailed function descriptions, please refer to the `base64.h` header file.

## Usage

Here's a simple example of how to use the library:

```c
#include "base64.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    const char* input = "Hello, World!";
    size_t input_length = strlen(input);
    
    // Calculate the required buffer size for encoding
    int encoded_length = base64_encoded_length(input_length);
    char* encoded = malloc(encoded_length + 1);  // +1 for null terminator
    
    // Encode the input
    if (base64_encode(encoded, input, input_length, false) == 0) {
        printf("Encoded: %s\n", encoded);
        
        // Calculate the required buffer size for decoding
        int decoded_length = base64_decoded_length(encoded, encoded_length, false);
        char* decoded = malloc(decoded_length + 1);  // +1 for null terminator
        
        // Decode the Base64 string
        if (base64_decode(decoded, encoded, encoded_length, false) > 0) {
            printf("Decoded: %s\n", decoded);
        }
        
        free(decoded);
    }
    
    free(encoded);
    return 0;
}
```

Output:
```
Encoded: SGVsbG8sIFdvcmxkIQ==
Decoded: Hello, World!
```

## Building

To use this library in your project, include the `base64.h` header file and compile the `base64.c` source file along with your code.

## Testing

To compile the tests, run `cc -DDEBUG -o test base64_test.c base64.c; ./test`

## Author, Licence

Copyright :copyright: 2025 Alan Tseng

MIT Licence