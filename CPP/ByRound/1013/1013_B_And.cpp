// Problem: CF 1013 B - And
// https://codeforces.com/contest/1013/problem/B

/*
B. And
Algorithms/Techniques: Bit manipulation, greedy approach
Time Complexity: O(n)
Space Complexity: O(1)

The problem asks to find the minimum number of operations to make at least two elements in the array equal,
where each operation replaces an element with (element & x). 
We track sets of values seen so far to determine if we can achieve equality with 0, 1, or 2 operations.
*/

#include <stdio.h>
#include <algorithm>

using namespace std;
bool mk1[100005], mk2[100005]; // mk1 tracks (a & x) values, mk2 tracks original a values
int main() {
  int n, x, ans = 1e9; // ans stores minimal operations needed
  scanf("%d%d", &n, &x);
  for (int i = 1, a; i <= n; ++i) {
    scanf("%d", &a);
    if (mk2[a]) // If we've seen 'a' before, already have two equal elements
      ans = 0;
    if (mk2[a & x] || mk1[a]) // If either (a & x) or a is already seen in previous steps
      ans = min(ans, 1);     // Then one operation can make two equal
    if (mk1[a & x]) // If (a & x) was seen in earlier step
      ans = min(ans, 2);   // Two operations needed to get two equal elements
    mk2[a] = 1;        // Mark 'a' as seen
    mk1[a & x] = 1;    // Mark (a & x) as seen
  }
  if (ans == 1e9) // If no valid answer was found
    ans = -1;
  printf("%d", ans);
}


// https://github.com/VaHiX/codeForces/