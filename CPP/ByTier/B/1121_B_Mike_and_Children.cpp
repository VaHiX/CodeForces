// Problem: CF 1121 B - Mike and Children
// https://codeforces.com/contest/1121/problem/B

/*
B. Mike and Children
Algorithm: Two Sum Frequency Counting
Time Complexity: O(n^2)
Space Complexity: O(n)

The problem asks to find the maximum number of children that can be given two sweets each,
such that all children receive the same sum of sweet sizes. This is equivalent to finding 
the maximum frequency of any sum formed by pairing distinct elements from the array.

Approach:
- Iterate through each element in the array.
- For each new element, check against all previously seen elements to form pairs.
- Use a hash map to count how many times each pair sum occurs.
- Keep track of the maximum count of any sum.
- The result is the maximum frequency of any such sum.

This approach works because we process elements sequentially and form pairs with all 
previously processed elements. By maintaining a frequency map of pair sums,
we can determine the largest number of children (i.e., pairs) that can have equal sums.
*/

#include <cstdio>
#include <unordered_map>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> v;
  std::unordered_map<long, long> m;
  long cmx(0);
  for (long p = 0; p < n; p++) {
    long x;
    scanf("%ld", &x);
    for (long p = 0; p < v.size(); p++) {
      ++m[x + v[p]];            // Increment frequency of sum x + v[p]
      cmx = (cmx > m[x + v[p]] ? cmx : m[x + v[p]]);  // Update maximum count
    }
    v.push_back(x);             // Add current element to the list of seen elements
  }
  printf("%ld\n", cmx);
  return 0;
}


// https://github.com/VaHiX/codeForces/