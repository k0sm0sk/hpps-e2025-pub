#include "numlib.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

void test_read_uint_be() {
    printf("Testing read_uint_be()...\n");
    
    // Test case 1: Normal value (42 = 0x0000002A)
    FILE *f = fopen("test_be.bin", "wb");
    unsigned char bytes1[] = {0x00, 0x00, 0x00, 0x2A}; // Big endian 42
    fwrite(bytes1, 1, 4, f);
    fclose(f);
    
    f = fopen("test_be.bin", "rb");
    uint32_t result1;
    assert(read_uint_be(f, &result1) == 0);
    assert(result1 == 42);
    fclose(f);
    
    // Test case 2: Larger value (0x12345678)
    f = fopen("test_be.bin", "wb");
    unsigned char bytes2[] = {0x12, 0x34, 0x56, 0x78}; // Big endian
    fwrite(bytes2, 1, 4, f);
    fclose(f);
    
    f = fopen("test_be.bin", "rb");
    uint32_t result2;
    assert(read_uint_be(f, &result2) == 0);
    assert(result2 == 0x12345678);
    fclose(f);
    
    // Test case 3: EOF on first byte
    f = fopen("test_be_empty.bin", "wb");
    fclose(f);
    f = fopen("test_be_empty.bin", "rb");
    uint32_t result3;
    assert(read_uint_be(f, &result3) == EOF);
    fclose(f);
    
    // Test case 4: Partial read (only 3 bytes)
    f = fopen("test_be_partial.bin", "wb");
    unsigned char bytes4[] = {0x12, 0x34, 0x56}; // Only 3 bytes
    fwrite(bytes4, 1, 3, f);
    fclose(f);
    
    printf("read_uint_be() tests passed!\n");
}

void test_read_double_bin() {
    printf("Testing read_double_bin()...\n");
    
    // Test case 1: Normal value
    FILE *f = fopen("test_double.bin", "wb");
    double test_val = 123.456;
    fwrite(&test_val, sizeof(double), 1, f);
    fclose(f);
    
    f = fopen("test_double.bin", "rb");
    double result1;
    assert(read_double_bin(f, &result1) == 0);
    assert(result1 == test_val);
    fclose(f);
    
    // Test case 2: Negative value
    f = fopen("test_double.bin", "wb");
    test_val = -987.654;
    fwrite(&test_val, sizeof(double), 1, f);
    fclose(f);
    
    f = fopen("test_double.bin", "rb");
    double result2;
    assert(read_double_bin(f, &result2) == 0);
    assert(result2 == test_val);
    fclose(f);
    
    // Test case 3: Zero
    f = fopen("test_double.bin", "wb");
    test_val = 0.0;
    fwrite(&test_val, sizeof(double), 1, f);
    fclose(f);
    
    f = fopen("test_double.bin", "rb");
    double result3;
    assert(read_double_bin(f, &result3) == 0);
    assert(result3 == 0.0);
    fclose(f);
    
    // Test case 4: EOF
    f = fopen("test_double_empty.bin", "wb");
    fclose(f);
    f = fopen("test_double_empty.bin", "rb");
    double result4;
    assert(read_double_bin(f, &result4) == EOF);
    fclose(f);
    
    // Test case 5: Partial read
    f = fopen("test_double_partial.bin", "wb");
    unsigned char partial[4] = {0x01, 0x02, 0x03, 0x04}; // Only 4 bytes instead of 8
    fwrite(partial, 1, 4, f);
    fclose(f);
    
    printf("read_double_bin() tests passed!\n");
}

void test_write_double_ascii() {
    printf("Testing write_double_ascii()...\n");
    
    // Test case 1: Positive number
    FILE *f = fopen("test_ascii.txt", "w");
    assert(write_double_ascii(f, 123.456) == 0);
    fclose(f);
    
    f = fopen("test_ascii.txt", "r");
    double result1;
    assert(fscanf(f, "%lf", &result1) == 1);
    assert(result1 == 123.456);
    fclose(f);
    
    // Test case 2: Negative number
    f = fopen("test_ascii.txt", "w");
    assert(write_double_ascii(f, -987.654) == 0);
    fclose(f);
    
    f = fopen("test_ascii.txt", "r");
    double result2;
    assert(fscanf(f, "%lf", &result2) == 1);
    assert(result2 == -987.654);
    fclose(f);
    
    // Test case 3: Zero
    f = fopen("test_ascii.txt", "w");
    assert(write_double_ascii(f, 0.0) == 0);
    fclose(f);
    
    f = fopen("test_ascii.txt", "r");
    double result3;
    assert(fscanf(f, "%lf", &result3) == 1);
    assert(result3 == 0.0);
    fclose(f);
    
    // Test case 4: Large number
    f = fopen("test_ascii.txt", "w");
    assert(write_double_ascii(f, 1234567890.123456) == 0);
    fclose(f);
    
    f = fopen("test_ascii.txt", "r");
    double result4;
    assert(fscanf(f, "%lf", &result4) == 1);
    // Use approximate comparison for large numbers
    assert(result4 > 1234567890.0 && result4 < 1234567891.0);
    fclose(f);
    
    printf("write_double_ascii() tests passed!\n");
}

void test_read_double_ascii() {
    printf("Testing read_double_ascii()...\n");
    
    // Test case 1: Positive number
    FILE *f = fopen("test_read_ascii.txt", "w");
    fprintf(f, "123.456");
    fclose(f);
    
    f = fopen("test_read_ascii.txt", "r");
    double result1;
    assert(read_double_ascii(f, &result1) == 0);
    assert(result1 == 123.456);
    fclose(f);
    
    // Test case 2: Negative number
    f = fopen("test_read_ascii.txt", "w");
    fprintf(f, "-987.654");
    fclose(f);
    
    f = fopen("test_read_ascii.txt", "r");
    double result2;
    assert(read_double_ascii(f, &result2) == 0);
    assert(result2 == -987.654);
    fclose(f);
    
    // Test case 3: Integer (no decimal point)
    f = fopen("test_read_ascii.txt", "w");
    fprintf(f, "42");
    fclose(f);
    
    f = fopen("test_read_ascii.txt", "r");
    double result3;
    assert(read_double_ascii(f, &result3) == 0);
    assert(result3 == 42.0);
    fclose(f);
    
    // Test case 4: Zero
    f = fopen("test_read_ascii.txt", "w");
    fprintf(f, "0.0");
    fclose(f);
    
    f = fopen("test_read_ascii.txt", "r");
    double result4;
    assert(read_double_ascii(f, &result4) == 0);
    assert(result4 == 0.0);
    fclose(f);
    
    // Test case 5: Number with leading spaces
    f = fopen("test_read_ascii.txt", "w");
    fprintf(f, "   12.34");
    fclose(f);
    
    f = fopen("test_read_ascii.txt", "r");
    double result5;
    assert(read_double_ascii(f, &result5) == 0);
    assert(result5 == 12.34);
    fclose(f);
    
    // Test case 6: Number followed by non-digit
    f = fopen("test_read_ascii.txt", "w");
    fprintf(f, "56.78abc");
    fclose(f);
    
    f = fopen("test_read_ascii.txt", "r");
    double result6;
    assert(read_double_ascii(f, &result6) == 0);
    assert(result6 == 56.78);
    fclose(f);
    
    printf("read_double_ascii() tests passed!\n");
}

void test_avg_doubles() {
    printf("Testing avg_doubles program...\n");
    
    // Create test binary file with known doubles
    FILE *f = fopen("test_avg.bin", "wb");
    double values[] = {1.0, 2.0, 3.0, 4.0, 5.0}; // Average should be 3.0
    for (int i = 0; i < 5; i++) {
        write_double_bin(f, values[i]);
    }
    fclose(f);
    
    // Test with system call
    printf("Created test file with values 1.0, 2.0, 3.0, 4.0, 5.0\n");
    printf("Expected average: 3.0\n");
    printf("Run: ./avg_doubles < test_avg.bin\n");
    
    // Clean up test file for single value
    f = fopen("test_avg_single.bin", "wb");
    write_double_bin(f, 42.5);
    fclose(f);
    
    printf("Created single value test file with 42.5\n");
    printf("Expected average: 42.5\n");
    printf("Run: ./avg_doubles < test_avg_single.bin\n");
    
    // Empty file test
    f = fopen("test_avg_empty.bin", "wb");
    fclose(f);
    
    printf("Created empty test file\n");
    printf("Expected: no output (count = 0)\n");
    printf("Run: ./avg_doubles < test_avg_empty.bin\n");
    
    printf("avg_doubles test files created!\n");
}

int main() {
    printf("Running numlib function tests...\n\n");
    
    test_read_uint_be();
    printf("\n");
    
    test_read_double_bin();
    printf("\n");
    
    test_write_double_ascii();
    printf("\n");
    
    test_read_double_ascii();
    printf("\n");
    
    test_avg_doubles();
    printf("\n");
    
    printf("All tests completed!\n");
    
    // Clean up test files
    remove("test_be.bin");
    remove("test_be_empty.bin");
    remove("test_be_partial.bin");
    remove("test_double.bin");
    remove("test_double_empty.bin");
    remove("test_double_partial.bin");
    remove("test_ascii.txt");
    remove("test_read_ascii.txt");
    // Keep avg test files for manual verification
    
    return 0;
}