// Problem: CF 1328 C - Ternary XOR
// https://codeforces.com/contest/1328/problem/C

/*
C. Ternary XOR
Algorithm: Greedy approach to minimize max(a, b) by distributing digits optimally.
Time Complexity: O(n) where n is the length of the input string x.
Space Complexity: O(n) for storing the output strings a and b.

The problem asks to decompose a ternary number x into two ternary numbers a and b such that:
- a ⊕ b = x (where ⊕ is ternary XOR)
- max(a, b) is minimized
- Both a and b must not have leading zeros

Approach:
We process the string from left to right. The key insight is:
- If x[i] == '0': we can set both a[i] and b[i] to '0' (0⊕0=0)
- If x[i] == '1': 
    - If we've already used a "carry" (diff=true), then we set a[i]='0', b[i]='1' (to avoid increasing the max)
    - Otherwise, we set a[i]='1', b[i]='0' and mark diff as true
- If x[i] == '2':
    - If we've already used a "carry", then we set a[i]='0', b[i]='2'
    - Otherwise, we set a[i]='1', b[i]='1'

This greedy method ensures that the resulting numbers a and b are minimal while satisfying the XOR condition.
*/

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string x;
    std::cin >> x;
    bool diff(false); // Tracks whether we've used a carry
    std::string a(""), b(""); // Resulting numbers
    for (long p = 0; p < x.size(); p++) {
      if (x[p] == '0') {
        a += '0';
        b += '0';
      } else if (x[p] == '1') {
        if (diff) { // If we've used a carry before, assign 0 to a[p] and 1 to b[p]
          a += '0';
          b += '1';
        } else {
          a += '1'; // First time seeing '1', so we do not want to increase max
          b += '0';
          diff = true; // Mark that we've used a carry now
        }
      } else if (x[p] == '2') {
        if (diff) { // If we've used a carry, assign 0 to a[p] and 2 to b[p]
          a += '0';
          b += '2';
        } else {
          a += '1'; // Otherwise, just split it equally
          b += '1';
        }
      }
    }
    std::cout << a << std::endl;
    std::cout << b << std::endl;
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/