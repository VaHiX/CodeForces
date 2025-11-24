// Problem: CF 1672 H - Zigu Zagu
// https://codeforces.com/contest/1672/problem/H

/*
Algorithm: Greedy with Prefix Sum
Time Complexity: O(n + q)
Space Complexity: O(n)

The problem asks to find the minimum number of operations to make a substring of a binary string empty,
where each operation removes a subsegment that has no two adjacent equal characters.

Key Insight:
- A valid subsegment is one where no two adjacent characters are the same.
- The minimum operations needed to reduce a segment to empty is equivalent to finding
  the longest contiguous subsegment of same characters.
- This is because we can only remove segments without adjacent equal characters.
- So, we can count the number of contiguous groups of same characters in the substring.

Prefix Sum Technique:
- Preprocess to store count of transitions from 0 to 1 and 1 to 0.
- For a substring [l, r], the number of operations = max(count of 0->1 transitions, count of 1->0 transitions) + 1.

Steps:
1. Read input string and preprocess prefix sums of transitions.
2. For each query, compute the result using prefix sums.
*/

#include <stdio.h>
#include <algorithm>

using namespace std;
int n, m, s[2][200001];  // s[0][i] and s[1][i] store prefix counts of transitions
char a[200001];          // Input binary string
int main() {
  scanf("%d%d%s", &n, &m, &a[1]);  // Read n, m and the string (1-indexed)
  for (int i = 2; i <= n; i++) {
    s[0][i] = s[0][i - 1];   // Copy previous counts for 0s
    s[1][i] = s[1][i - 1];   // Copy previous counts for 1s
    if (a[i] == a[i - 1])    // If current and previous chars are same
      s[a[i] - '0'][i]++;    // Increment the count for the character
  }
  while (m--) {              // For each query
    int x, y;
    scanf("%d%d", &x, &y);   // Read l and r
    printf("%d\n", max(s[0][y] - s[0][x], s[1][y] - s[1][x]) + 1);  // Compute and print the answer
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/