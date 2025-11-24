// Problem: CF 1370 B - GCD Compression
// https://codeforces.com/contest/1370/problem/B

/*
Algorithm: Greedy approach based on parity
Approach:
1. Separate elements of array 'a' into two groups based on parity (odd and even).
2. If there are an odd number of odd elements, remove one odd and one even element.
3. If there are an even number of odd elements, remove two odd elements.
4. Pair remaining elements from both groups (odd and even) to form sums with a common factor (2 for even sums).
5. The final array b will have all elements even and hence gcd > 1.

Time Complexity: O(n)
Space Complexity: O(n)

*/
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a, b; // a stores indices of odd numbers, b stores indices of even numbers
    for (long p = 1; p <= 2 * n; p++) {
      long x;
      scanf("%ld", &x);
      if (x % 2) { // If number is odd
        a.push_back(p);
      } else { // If number is even
        b.push_back(p);
      }
    }
    // Adjust the sizes of a and b to ensure we can pair them up properly
    if (a.size() % 2) { // If number of odd elements is odd
      a.pop_back(); // Remove one odd element
      b.pop_back(); // Remove one even element
    } else if (a.size()) { // If number of odd elements is even and greater than 0
      a.pop_back(); // Remove two odd elements to make total count even
      a.pop_back();
    } else { // If there are no odd elements, remove two even elements
      b.pop_back();
      b.pop_back();
    }
    // Print pairs from odd elements
    for (long p = 0; p < a.size(); p += 2) {
      printf("%ld %ld\n", a[p], a[p + 1]);
    }
    // Print pairs from even elements
    for (long p = 0; p < b.size(); p += 2) {
      printf("%ld %ld\n", b[p], b[p + 1]);
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/