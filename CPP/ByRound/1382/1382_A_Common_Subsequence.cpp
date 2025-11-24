// Problem: CF 1382 A - Common Subsequence
// https://codeforces.com/contest/1382/problem/A

/*
Algorithm: Check if there exists any common element between two arrays.
Techniques: Use of std::set for efficient lookup.

Time Complexity: O(n + m)
Space Complexity: O(n)

The approach is to store all elements of the first array in a set for O(1) average lookup.
Then iterate through the second array and check if any element exists in the set.
If found, we have a common element which forms the shortest possible subsequence.
*/
#include <cstdio>
#include <set>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m;
    scanf("%ld %ld", &n, &m);
    std::set<long> s; // Set to store elements of first array for fast lookup
    while (n--) {
      long x;
      scanf("%ld", &x);
      s.insert(x); // Insert all elements of first array into set
    }
    bool ans(false); // Flag to indicate if a common element is found
    long res(0); // Store the first common element found
    while (m--) {
      long x;
      scanf("%ld", &x);
      if (s.count(x)) { // Check if current element exists in set
        ans = true;
        res = x;
      }
    }
    if (ans) {
      printf("YES\n1 %ld\n", res); // Output the common element
    } else {
      puts("NO"); // No common element found
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/