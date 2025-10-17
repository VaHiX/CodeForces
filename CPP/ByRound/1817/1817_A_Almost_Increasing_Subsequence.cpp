// Problem: CF 1817 A - Almost Increasing Subsequence
// https://codeforces.com/contest/1817/problem/A

/*
Algorithm: Almost Increasing Subsequence
Techniques: Prefix Sum, Two Pointers, Sliding Window

Time Complexity: O(n + q)
Space Complexity: O(n)

The problem asks for the length of the longest almost-increasing subsequence 
in a given range [l, r]. An almost-increasing sequence has no three consecutive 
elements x >= y >= z.

This solution uses a prefix sum array 'b' to precompute the number of "bad" 
triplets (where x >= y >= z) in the prefix. For each query, it computes how many 
such triplets exist in the subarray [l, r], and subtracts from total length to get 
the answer.

For a subarray of length L, if there are k bad triplets, then the longest 
almost-increasing subsequence will be L - k.
*/
#include <cstdio>
#include <iosfwd>

using namespace std;
const int o = 2e5 + 10;
int n, q, a[o], b[o]; // b[i] stores count of bad triplets in [1..i]
int main() {
  scanf("%d%d", &n, &q);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &a[i]);
  // Build prefix sum array b where b[i] counts bad triplets up to index i
  for (int i = 2; i < n; ++i)
    b[i] = b[i - 1] + (a[i - 1] >= a[i] && a[i] >= a[i + 1]); // Check if a[i-1] >= a[i] >= a[i+1]
  for (int l, r; q--; printf("%d\n", r - l + 1 - (b[r - 1] - b[l]) * (l < r))) // Compute result: total length minus bad triplets
    scanf("%d%d", &l, &r);
  return 0;
}


// https://github.com/VaHiX/codeForces/