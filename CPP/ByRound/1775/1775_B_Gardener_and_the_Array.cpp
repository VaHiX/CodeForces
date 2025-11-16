// Problem: CF 1775 B - Gardener and the Array
// https://codeforces.com/contest/1775/problem/B

/*
 * Problem: Gardener and the Array
 * 
 * Purpose: Determine if there exist two different subsequences of the input array
 *          such that their bitwise OR results are equal.
 * 
 * Algorithm:
 * - For each number in the input array, we represent it as a set of bits.
 * - We track which bits are set in which positions.
 * - If a bit is set in exactly one position, we note that position.
 * - If the number of such unique bit positions equals the total number of elements,
 *   then no two different subsequences have the same OR result.
 * 
 * Time Complexity: O(S) where S is the sum of all k_i across all test cases.
 * Space Complexity: O(2 * 10^5) for the auxiliary arrays used to track bits and indices.
 * 
 * Techniques/Approach:
 * - Use bit manipulation to represent numbers.
 * - Count occurrences of each bit across all numbers.
 * - Identify unique bits (set in exactly one number) and track their source positions.
 * - If all numbers contribute a unique bit, then no two subsequences can be equivalent.
 */

#include <stdio.h>
#include <iosfwd>

using namespace std;

// chk[i] counts how many times bit i appears in the input numbers
int chk[200001];
// cchk[i] checks if a number at index i has been processed for unique bits
int cchk[100001];
// ind[i] stores the index in original array of the number that sets bit i
int ind[200001];
// chks[i] holds the list of unique bits found so far
int chks[100001];
// cchks[i] stores the list of indices that contribute to unique bits
int cchks[100001];

void solve() {
  int n, k, e;
  scanf("%d", &n);
  int cnt = 0; // Number of unique bits
  int ccnt = 0; // Count of unique indices

  // Process each number in the array
  for (int i = 0; i < n; i++) {
    scanf("%d", &k);
    for (int j = 0; j < k; j++) {
      scanf("%d", &e);
      chk[e]++; // Increment count for the bit e
      if (chk[e] == 1) { // First time this bit appears
        chks[cnt++] = e; // Add it to unique bits list
        ind[e] = i; // Record which number this bit comes from
      }
    }
  }

  int ans = 0; // Count of unique indices that contribute to unique bits
  // Check which unique bits we've seen and map back to original indices
  for (int i = 0; i < cnt; i++) {
    if (chk[chks[i]] == 1) { // Bit occurs only once in input
      int num = ind[chks[i]]; // Get the index of the number that sets this bit
      if (cchk[num] == 0) { // If this index wasn't already considered
        cchk[num]++; // Mark it as processed
        cchks[ccnt++] = num; // Add it to list of indices
        ans++; // Increment unique index count
      }
    }
  }

  // Reset tracking arrays
  for (int i = 0; i < cnt; i++)
    chk[chks[i]] = 0;
  for (int i = 0; i < ccnt; i++)
    cchk[cchks[i]] = 0;

  // If all elements have a unique bit, then no two subsequences can have same OR
  if (ans == n)
    printf("No\n");
  else
    printf("Yes\n");

  return;
}

int main() {
  int t;
  scanf("%d", &t);
  for (int i = 0; i < t; i++)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/