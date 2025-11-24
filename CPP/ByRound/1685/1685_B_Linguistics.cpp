// Problem: CF 1685 B - Linguistics
// https://codeforces.com/contest/1685/problem/B

/*
Code Purpose:
This program determines whether a given string s can be decomposed into exactly a words of "A", 
b words of "B", c words of "AB", and d words of "BA" in some order. It does this by:
1. Verifying the total count of 'A' and 'B' in s matches expected counts.
2. Grouping consecutive same characters and processing them based on parity.
3. Using greedy logic to check if remaining c and d can be satisfied by combining groups.

Algorithms/Techniques:
- Greedy algorithm
- String matching and grouping
- Sorting for optimal allocation

Time Complexity: O(n log n) where n is the length of string s due to sorting of vectors A and B.
Space Complexity: O(n) for storing the groups A and B.

*/
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <vector>

#define N 200010
using namespace std;
int a, b, c, d, n;
char s[N];
void solve() {
  cin >> a >> b >> c >> d;
  scanf("%s", s + 1);
  n = a + b + 2 * c + 2 * d;
  int na = 0, nb = 0;
  for (int i = 1; i <= n; i++)
    (s[i] == 'A' ? na : nb)++; // Count total 'A' and 'B'
  if (na != a + c + d || nb != b + c + d) { // Verify counts match
    puts("NO");
    return;
  }
  int tot = 0, l = 1;
  vector<int> A, B;
  for (int i = 1; i <= n; i++) {
    if (i == n || s[i] == s[i + 1]) { // If end of string or current char is same as next
      if ((i - l + 1) & 1) // If length of group is odd
        tot += (i - l + 1) / 2; // Add half the length (rounded down)
      else { // If length of group is even
        int x = (i - l + 1) / 2;
        if (s[l] == 'A') // If group starts with 'A'
          A.push_back(x);
        else // If group starts with 'B'
          B.push_back(x);
      }
      l = i + 1; // Move start pointer
    }
  }
  sort(A.begin(), A.end()); // Sort group sizes for greedy matching
  sort(B.begin(), B.end());
  for (int x : A) { // Process 'A' groups
    if (c >= x)
      c -= x; // Use up available 'AB' words if possible
    else
      tot += x - 1; // Otherwise, we require one less 'AB' to form 'A'
  }
  for (int x : B) { // Process 'B' groups
    if (d >= x)
      d -= x; // Use up available 'BA' words if possible
    else
      tot += x - 1; // Otherwise, we require one less 'BA' to form 'B'
  }
  puts(c + d <= tot ? "YES" : "NO"); // Check if remaining words can be arranged
}
int main() {
  int T;
  cin >> T;
  while (T--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/