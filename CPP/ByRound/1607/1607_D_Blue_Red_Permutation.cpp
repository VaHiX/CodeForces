// Problem: CF 1607 D - Blue-Red Permutation
// https://codeforces.com/contest/1607/problem/D

/*
D. Blue-Red Permutation
Algorithms/Techniques: Sorting, Greedy

Time Complexity: O(n log n) per test case due to sorting
Space Complexity: O(n) for storing blue and red elements

The problem involves determining if an array of integers can be transformed into a permutation 
of 1 to n using allowed operations on blue (decrease by 1) and red (increase by 1) elements.
Key insight:
- Blue elements must be able to decrease to values that fit the permutation
- Red elements must be able to increase to values that fit the permutation
- The solution checks if we can assign numbers from 1 to n such that blue elements 
  are at least their required values and red elements are at most their required values.
*/

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::vector<long> v(n);
    for (long p = 0; p < n; p++) {
      std::cin >> v[p];
    }
    std::string s;
    std::cin >> s;
    std::vector<long> b, r;
    for (long p = 0; p < n; p++) {
      if (s[p] == 'B') { // Separate blue and red elements
        b.push_back(v[p]);
      } else {
        r.push_back(v[p]);
      }
    }
    sort(b.begin(), b.end()); // Sort blue elements in ascending order
    sort(r.begin(), r.end()); // Sort red elements in ascending order
    bool res(true);
    for (long p = 1; p <= b.size(); p++) {
      if (p > b[p - 1]) { // Check if blue elements can be reduced to fit 1..b.size()
        res = false;
        break;
      }
    }
    for (long p = b.size() + 1; p <= n; p++) {
      if (p < r[p - b.size() - 1]) { // Check if red elements can be increased to fit (b.size()+1)..n
        res = false;
        break;
      }
    }
    std::cout << (res ? "YES" : "NO") << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/