// Problem: CF 2160 C - Reverse XOR
// https://codeforces.com/contest/2160/problem/C

/*
C. Reverse XOR
Algorithm: Bit manipulation and binary representation analysis
Time Complexity: O(log n) per test case
Space Complexity: O(1)

This problem checks whether there exists a positive integer x such that x XOR f(x) = n,
where f(x) is the number formed by reversing the binary representation of x.
The solution analyzes the binary representation of n and checks certain conditions
to determine if such an x can exist.

Key insight:
- If n = 0, then x = f(x), which is always possible (e.g., x = 1).
- For other values of n, we convert n to its binary representation,
  reverse the bits, and check if it's valid.
- A specific constraint on middle bit handling ensures correctness.

The code processes multiple test cases efficiently by reusing memory
and using optimized input/output methods.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;
const long long mod1 = 998244353;
const long long mod2 = 1000000007;
const long long inf = 0x3f3f3f3f3f3f3f3f;
long long t, n;
long long a[51], siz;
void init();
void domemset();
long long read();
void write(long long x);
void fun() {
  domemset(); // Reset the array and size for each test case
  n = read(); // Read input number n
  if (n == 0) { // Special case: if n is 0, we can always choose x = 1 so f(x) = 1 and x ^ f(x) = 0
    cout << "YES\n";
    return;
  }
  while (n % 2 == 0) // Remove all trailing zeros from n for processing
    n /= 2;
  while (n) { // Convert the remaining number to binary in array a
    a[++siz] = n & 1; // Store the least significant bit
    n >>= 1; // Shift bits right by one position
  }
  for (int i = 1; i <= siz / 2; i++) // Check if corresponding bits from start and end are equal
    if (a[i] != a[siz - i + 1]) {
      cout << "NO\n"; // Not symmetric, so no valid x exists
      return;
    }
  if (siz % 2 == 1 && a[siz / 2 + 1] == 1) // If the middle bit is set in an odd-length sequence
    cout << "NO\n"; // Not possible to construct such x
  else
    cout << "YES\n"; // Valid case found
  return;
}
int main() {
  srand(time(NULL)); // Seed random generator for possible future use
  init(); // Initialize global settings (currently does nothing)
  t = read(); // Read number of test cases
  for (int i = 1; i <= t; i++) // Process each test case
    fun();
  return 0;
}
void init() { return; }
void domemset() {
  siz = 0; // Reset the size counter
  return;
}
long long read() {
  long long x = 0, f = 1;
  char ch = getchar(); // Read character input
  while (ch < '0' || ch > '9') { // Skip non-digit characters
    if (ch == '-')
      f = -1; // Handle negative sign
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') { // Parse number
    x = (x << 3) + (x << 1) + (ch ^ '0'); // Efficient multiplication and addition: x * 10 + digit
    ch = getchar();
  }
  return x * f; // Return the parsed integer with correct sign
}
void write(long long x) {
  if (x < 0) // Handle negative number printing
    putchar('-'), x = -x;
  if (x >= 10) // Recursive call for multi-digit numbers
    write(x / 10);
  putchar((x % 10) ^ '0'); // Print the last digit
  return;
}


// https://github.com/VaHiX/CodeForces/