// Problem: CF 1747 D - Yet Another Problem
// https://codeforces.com/contest/1747/problem/D

/*
 * Problem: Yet Another Problem
 * Purpose: For each query on a subarray [l, r], determine the minimum number of operations
 *          to make all elements equal to 0, or -1 if impossible.
 *          An operation allows choosing a subarray of odd length and replacing all elements
 *          with the XOR of that subarray.
 *
 * Algorithms/Techniques:
 *   - Prefix XOR to quickly compute XOR of subarrays
 *   - Tracking of positions where prefix XOR values have been seen
 *   - Observations on parity and specific cases to determine operation count
 *
 * Time Complexity: O(n + q)
 * Space Complexity: O(n)
 */
#include <stdio.h>
#include <map>

using namespace std;
const int N = 200005;
int n, q, a[N], ya[N], s[N], last[N];
map<int, int> mp[2];
int main() {
  scanf("%d%d", &n, &q);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    ya[i] = a[i];
    ya[i] ^= ya[i - 1]; // Compute prefix XOR
    if (!a[i])
      s[i] = s[i - 1] + 1; // Count zeros up to position i
    last[i] = mp[i & 1][ya[i]]; // Store last occurrence of prefix XOR value
    mp[i & 1][ya[i - 1]] = i; // Update map with current index
  }
  while (q--) {
    int l, r;
    scanf("%d%d", &l, &r);
    if (s[r] >= r - l + 1)
      puts("0"); // All elements are zero, nothing to do
    else if (ya[l - 1] ^ ya[r] || r - l < 2)
      puts("-1"); // XOR of subarray is non-zero or length < 2, impossible
    else if (!((r - l) & 1) || !a[l] || !a[r])
      puts("1"); // Even length or ends are zero, one operation sufficient
    else if (last[r] > l)
      puts("2"); // More complex case, two operations needed
    else
      puts("-1"); // General case, impossible
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/