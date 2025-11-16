// Problem: CF 1331 C - ...And after happily lived ever they
// https://codeforces.com/contest/1331/problem/C

/*
Purpose: This code performs a specific bit manipulation operation on an input integer.
         It takes a 6-bit binary representation of the input, swaps certain bits,
         and outputs the resulting integer.
         The swaps are: bits 1 and 5, and bits 2 and 3.
Algorithm: Bit manipulation and permutation
Time Complexity: O(1) - constant time operations
Space Complexity: O(1) - fixed size vector of 6 integers
*/
#include <cstdio>
#include <vector>
int main() {
  const int B = 6;  // Fixed bit size for 6-bit representation
  std::vector<int> a(B, 0);  // Initialize vector to store 6 bits
  long n;  // Input number
  scanf("%ld", &n);  // Read input number
  
  // Convert number to 6-bit binary representation
  for (long p = B - 1; p >= 0; p--) {
    a[p] = n % 2;  // Extract least significant bit
    n /= 2;  // Shift to next bit
  }
  
  // Swap bits at positions 1 and 5
  int x;
  x = a[1];  // Store bit at position 1
  a[1] = a[5];  // Move bit from position 5 to position 1
  a[5] = x;  // Move stored bit from position 1 to position 5
  
  // Swap bits at positions 2 and 3
  x = a[2];  // Store bit at position 2
  a[2] = a[3];  // Move bit from position 3 to position 2
  a[3] = x;  // Move stored bit from position 2 to position 3
  
  // Convert back to decimal number
  long res(0), w(1);  // res: result, w: weight (power of 2)
  for (long p = B - 1; p >= 0; p--) {
    res += a[p] * w;  // Add weighted bit value to result
    w *= 2;  // Increase weight for next bit
  }
  
  printf("%ld\n", res);  // Output the result
  return 0;
}


// https://github.com/VaHiX/CodeForces/