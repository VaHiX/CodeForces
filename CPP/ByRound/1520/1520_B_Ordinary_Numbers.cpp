// Problem: CF 1520 B - Ordinary Numbers
// https://codeforces.com/contest/1520/problem/B

#include <iostream>
using namespace std;
/*
B. Ordinary Numbers
Algorithm: Generate all possible ordinary numbers (numbers with all same digits) up to n
and count how many are <= n.

The approach uses two nested loops:
- Outer loop generates numbers like 1, 11, 111, 1111, ... (powers of 10 plus 1)
- Inner loop tries all digits 1-9 multiplied by the current outer number
- For each valid product <= n, increment counter

Time Complexity: O(log n) per test case - we have at most 10 iterations for outer loop (since 10^10 > 10^9)
Space Complexity: O(1) - only using a constant amount of extra space
*/
int main() {
  int t;
  cin >> t;
  while (t--) {
    long long int n, i, j, count = 0;
    cin >> n;
    for (i = 1; i <= n; i = i * 10 + 1) { // Generate numbers like 1, 11, 111, 1111...
      for (j = 1; j <= 9; j++)           // Try digits 1 through 9
        if (i * j <= n)                  // If the ordinary number is within range
          count++;                       // Increment counter
    }
    cout << count << endl;
  }
}

// https://github.com/VaHiX/codeForces/