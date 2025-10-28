// Problem: CF 1975 B - 378QAQ and Mocha's Array
// https://codeforces.com/contest/1975/problem/B

/*
B. 378QAQ and Mocha's Array
Time Complexity: O(n) per test case
Space Complexity: O(n) per test case

Algorithm:
The problem asks whether there exist two elements in the array such that every element in the array is divisible by at least one of them.
We use a greedy approach:
1. Find the minimum element 'a' in the array.
2. Find the smallest element 'b' that is not divisible by 'a'.
3. Check if all elements are divisible by either 'a' or 'b'.

This works because:
- If we can find such pair (a, b), then every element must be divisible by at least one of them.
- If no such pair exists, it's impossible to cover all elements with just two divisors.

Steps:
1. Identify the global minimum value in array as potential first divisor 'a'.
2. Find the smallest value not divisible by 'a' as second divisor 'b'.
3. Validate that all numbers are divisible by either 'a' or 'b'.

*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> v(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &v[p]);
    }
    long a(1e9 + 7); // Initialize 'a' to a large number
    for (long p = 0; p < n; p++) {
      a = (v[p] < a ? v[p] : a); // Find minimum element
    }
    long b(1e9 + 7); // Initialize 'b' to a large number
    for (long p = 0; p < n; p++) {
      if (v[p] % a == 0) {
        continue; // Skip elements divisible by 'a'
      }
      b = (v[p] < b ? v[p] : b); // Find minimum element not divisible by 'a'
    }
    bool ans(true);
    for (long p = 0; ans && p < n; p++) {
      if ((v[p] % a) && (v[p] % b)) { // If element is not divisible by either 'a' or 'b'
        ans = false;
      }
    }
    puts(ans ? "Yes" : "No");
  }
}


// https://github.com/VaHiX/codeForces/