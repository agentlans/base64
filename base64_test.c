#include "base64.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void run_test(const char *input, bool url_safe) {

  size_t input_length = strlen(input);
  int encoded_length = base64_encoded_length(input_length);

  printf("Input: %s\n", input);
  printf("Input length: %zu\n", input_length);
  printf("Calculated encoded length: %d\n", encoded_length);

  // Allocate memory for encoded and decoded strings
  char encoded[encoded_length + 1]; // +1 for null terminator
  char decoded[input_length + 1];   // +1 for null terminator

  // Encode
  if (base64_encode(encoded, input, input_length, url_safe) != 0) {
    printf("Encoding failed for input: %s\n", input);
    return;
  }

  printf("Input: %s\n", input);
  printf("Encoded (%s): %s\n", url_safe ? "URL-safe" : "Standard", encoded);

  // Decode
  int decoded_length =
      base64_decoded_length(encoded, strlen(encoded), url_safe);
  if (decoded_length == -1) {
    printf("Invalid Base64 string: %s\n", encoded);
    return;
  }

  if (base64_decode(decoded, encoded, strlen(encoded), url_safe) == -1) {
    printf("Decoding failed for encoded string: %s\n", encoded);
    return;
  }

  decoded[decoded_length] = '\0'; // Null-terminate the decoded string
  printf("Decoded: %s\n", decoded);

  // Verify correctness
  if (strcmp(input, decoded) == 0) {
    printf("Test passed!\n");
  } else {
    printf("Test failed! Decoded output does not match the original input.\n");
  }

  printf("\n");
}

int main() {
  // Test cases
  const char *test_cases[] = {
      "Hello, World!",
      "Base64 encoding test.",
      "This is a longer test string to check encoding and decoding.",
      "Special characters: !@#$%^&*()_+-=[]{}|;':,.<>/?",
      "",
      "A",
      "AB",
      "ABC"};

  size_t num_tests = sizeof(test_cases) / sizeof(test_cases[0]);

  printf("=== Testing Standard Base64 ===\n");
  for (size_t i = 0; i < num_tests; i++) {
    run_test(test_cases[i], false); // Standard Base64
  }

  printf("=== Testing URL-Safe Base64 ===\n");
  for (size_t i = 0; i < num_tests; i++) {
    run_test(test_cases[i], true); // URL-Safe Base64
  }

  return 0;
}
