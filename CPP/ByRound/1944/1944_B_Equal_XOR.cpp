// Problem: CF 1944 B - Equal XOR
// https://codeforces.com/contest/1944/problem/B

/*
Algorithm: Equal XOR
Purpose: Given an array of 2n integers where each integer from 1 to n appears exactly twice,
         and an integer k, find two subsets l and r of size 2k each such that the XOR of l equals XOR of r.
         Both subsets are taken from the first n and second n elements respectively.

Approach:
- The key idea is to use the properties of XOR:
  - XOR of a number with itself is 0.
  - XOR is associative and commutative.
  - If we can partition the elements into two sets with equal XOR, we can achieve the goal.
  
- Preprocessing:
  - Count occurrences of each number in the first half of the array.
  - Identify numbers that appear twice in the first half (these can form l).
  - Identify numbers that do not appear in the first half (can form r).

- Construct l and r arrays:
  - First, fill with pairs of numbers from first half that are duplicated.
  - Then fill with numbers that are odd-counted in the first half.
  - Adjust sizes to meet 2k requirement.

Time Complexity: O(n)
Space Complexity: O(n)

*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    std::vector<long> v(2 * n); // Vector to store the input array
    std::vector<long> w(n + 1); // Vector to count occurrences in first half (1 to n)
    for (long p = 0; p < 2 * n; p++) {
      scanf("%ld", &v[p]);
      if (p >= n) {
        continue;
      }
      ++w[v[p]];
    }
    std::vector<long> a, b; // a is l, b is r
    for (long p = 1; p <= n; p++) {
      if (w[p] == 2 && a.size() < 2 * k) { // If number appears twice in first half
        a.push_back(p);
        a.push_back(p);
      } else if (w[p] == 0 && b.size() < 2 * k) { // If number does not appear in first half
        b.push_back(p);
        b.push_back(p);
      }
    }
    while (a.size() < b.size()) { // Adjust sizes if needed
      b.pop_back();
    }
    while (b.size() < a.size()) {
      a.pop_back();
    }
    for (long p = 1; a.size() < 2 * k && p <= n; p++) {
      if (w[p] % 2) { // If number appears odd times in first half
        a.push_back(p);
        b.push_back(p);
      }
    }
    for (long p = 0; p < a.size(); p++) {
      printf("%ld ", a[p]);
    };
    puts("");
    for (long p = 0; p < b.size(); p++) {
      printf("%ld ", b[p]);
    };
    puts("");
  }
}


// https://github.com/VaHiX/CodeForces/