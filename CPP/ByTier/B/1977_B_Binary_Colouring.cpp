// Problem: CF 1977 B - Binary Colouring
// https://codeforces.com/contest/1977/problem/B

/*
B. Binary Colouring

Algorithm:
The problem asks to represent a positive integer x as a sum of powers of 2 with coefficients in {-1, 0, 1}, such that no two consecutive coefficients are non-zero.

This is essentially a variant of the binary representation where we allow subtraction (coefficients of -1). 

We first convert x into its binary representation as a vector of bits.
Then we process the bits from left to right to apply the "carry" logic:
  - If a bit and the next bit are both 1, we change the current bit to -1 and set the next bit to 0 (this corresponds to borrowing 1 from higher power)
  - If we have a carry flag and next bit is 1, clear it
  - If no carry, and current bit is -1 or 0, continue processing
  - If carry flag is set and we see a 0 in this position, we place 1 here and turn off carry

Time Complexity: O(log x) per test case — since we process at most log(x) bits.
Space Complexity: O(log x) — to store the binary representation of x.

*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long x;
    scanf("%ld", &x);
    std::vector<long> v;
    while (x) {
      v.push_back(x % 2); // Store each bit of x in reverse order
      x /= 2;
    }
    bool carry(false);
    for (long p = 1; p < v.size(); p++) {
      if (v[p - 1] && v[p]) { // If both current and next bits are 1
        v[p - 1] = -1;       // Set previous bit to -1 to "borrow"
        v[p] = 0;            // Clear current bit
        carry = true;        // Set carry flag for next iteration
      } else if (v[p] && carry) { // If current bit is 1 and we have a carry
        v[p] = 0;            // Clear the bit
      } else if (v[p]) {     // If current bit is 1 but no carry
        continue;            // Continue without changes
      } else if (carry) {    // If no bit here but there's a carry
        v[p] = 1;            // Set this bit to 1 and reset carry
        carry = false;
      }
    }
    if (carry) {
      v.push_back(1);        // Final carry adds another bit
    }
    printf("%ld\n", v.size());
    for (long p = 0; p < v.size(); p++) {
      printf("%ld ", v[p]);
    }
    puts("");
  }
}


// https://github.com/VaHiX/codeForces/