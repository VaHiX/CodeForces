// Problem: CF 1722 G - Even-Odd XOR
// https://codeforces.com/contest/1722/problem/G

/*
Purpose: To generate an array of n distinct non-negative integers less than 2^31 such that 
         the XOR of elements at odd indices equals the XOR of elements at even indices.

Algorithm/Technique: 
- The approach cleverly constructs the array by fixing the last three elements to ensure
  the XOR condition is satisfied.
- It starts with a large number (1610612736) and XORs it with decreasing numbers to form 
  the prefix of the array.
- Then appends three specific constants (x, 1073741824, 536870912) in order to satisfy the condition.

Time Complexity: O(n) - Linear time per test case due to a single loop.
Space Complexity: O(1) - Constant space, only using a few variables.

*/
#include <iostream>
using namespace std;
int n, x;
int main() {
  cin >> n;
  while (cin >> n) {
    n -= 2, x = 1610612736; // Adjust n and initialize x to a large value
    while (--n) // Loop to generate the sequence 
      x ^= n, cout << n << " "; // XOR x with current n and output n
    cout << x << " 1073741824 536870912\n"; // Output final computed value and fixed constants
  }
}


// https://github.com/VaHiX/CodeForces/