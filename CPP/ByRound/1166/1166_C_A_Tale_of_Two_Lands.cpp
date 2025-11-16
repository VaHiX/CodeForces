// Problem: CF 1166 C - A Tale of Two Lands
// https://codeforces.com/contest/1166/problem/C

/*
C. A Tale of Two Lands
Algorithms/Techniques: Two Pointers, Sorting

Time Complexity: O(n log n)
Space Complexity: O(n)

The problem asks us to count the number of unordered pairs from given integers 
such that when used as x and y, the Arrayland [|x|, |y|] is completely inside 
Vectorland [||x - y||, |x + y|]. 

We can simplify this by working with absolute values. For any two numbers a and b:
- Arrayland is [min(|a|, |b|), max(|a|, |b|)]
- Vectorland is [min(|a-b|, |a+b|), max(|a-b|, |a+b|)]

Since we're checking if Arrayland is inside Vectorland, it's sufficient to verify:
1. min(|a|, |b|) >= min(|a-b|, |a+b|) 
2. max(|a|, |b|) <= max(|a-b|, |a+b|)

This can be rephrased as: the interval [min(|a|, |b|), max(|a|, |b|)]
must be completely inside [min(|a-b|, |a+b|), max(|a-b|, |a+b|)].

To make this efficient, we sort the absolute values of the input array.
Then, for each element, we use two pointers to find how many elements satisfy
the condition. This avoids checking all pairs explicitly.
*/

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> v(n + 1, 2e9 + 7); // Initialize with large value
  for (long p = 0; p < n; p++) {
    scanf("%ld", &v[p]);
    v[p] = (v[p] > 0) ? v[p] : -v[p]; // Convert to absolute value
  }
  sort(v.begin(), v.end()); // Sort the absolute values
  long idx(0); // Two pointer index
  long long cnt(0); // Result counter
  for (long p = 0; p < n; p++) {
    while (idx <= n && v[idx] <= 2 * v[p]) { // Move idx until we exceed 2*v[p]
      ++idx;
    }
    cnt += (idx - p - 1); // Add valid pairs count
  }
  printf("%lld\n", cnt);
  return 0;
}


// https://github.com/VaHiX/codeForces/