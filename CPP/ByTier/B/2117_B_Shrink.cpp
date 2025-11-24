// Problem: CF 2117 B - Shrink
// https://codeforces.com/contest/2117/problem/B

/*
B. Shrink
Algorithms/Techniques: Constructive Algorithm
Time Complexity: O(n) per test case
Space Complexity: O(1) excluding output space

Approach:
The key idea is to construct a permutation that maximizes the number of shrink operations.
A shrink operation removes a peak element (an element greater than its neighbors).
To maximize the number of such operations, we can build a "zigzag" pattern:
- Start with odd numbers in ascending order
- Then append even numbers in descending order

This construction ensures maximum number of peaks and hence maximum shrink operations.

Sample Input:
2
3
6

Sample Output:
1 3 2
2 3 6 4 5 1
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    // Print all odd numbers from 1 to n
    for (long p = 1; p <= n; p += 2) {
      printf("%ld ", p);
    }
    // Print all even numbers from n down to 2
    for (long p = n - n % 2; p > 1; p -= 2) {
      printf("%ld ", p);
    }
    puts("");
  }
}


// https://github.com/VaHiX/codeForces/