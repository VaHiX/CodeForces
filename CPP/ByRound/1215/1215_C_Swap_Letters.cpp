// Problem: CF 1215 C - Swap Letters
// https://codeforces.com/contest/1215/problem/C

/*
C. Swap Letters
Algorithms/Techniques: Greedy, constructive
Time complexity: O(n)
Space complexity: O(n)

Monocarp has two strings s and t of equal length consisting of 'a' and 'b'.
The goal is to make both strings identical using swaps between positions in s and t.
Each swap operation allows choosing any index from s and any index from t and swapping their characters.

Approach:
1. Identify all positions where s[i] != t[i].
2. Separate these into two arrays:
   - q1: indices where s[i] < t[i] (i.e., s[i] = 'a', t[i] = 'b')
   - q2: indices where s[i] > t[i] (i.e., s[i] = 'b', t[i] = 'a')
3. If total mismatches is odd, it's impossible.
4. For even mismatches:
   - Pair up mismatches in q1 and q2 optimally.
   - Handle one remaining pair by using a special move involving two same-type mismatches.

The minimum swaps needed is (x+y)/2 + (x%2).
*/

#include <cstdio>
const int MAXN = 20 * 10086;
int n, q1[MAXN], q2[MAXN], x, y; // x: count of s[i]='a', t[i]='b'; y: count of s[i]='b', t[i]='a'
char a[MAXN], b[MAXN];
int main() {
  register int i;
  scanf("%d%*c%s%s", &n, a + 1, b + 1); // Read n and strings a,b (1-indexed)
  for (i = 1; i <= n; i++)
    if (a[i] != b[i]) { // For each mismatched position
      if (a[i] < b[i]) // If s[i] = 'a' and t[i] = 'b'
        q1[++x] = i; // Add to q1 array with x incremented
      else
        q2[++y] = i; // Add to q2 array with y incremented
    }
  if (x + y & 1) // If total mismatches is odd
    return puts("-1"), 0; // Impossible result
  printf("%d\n", (x + y >> 1) + (x & 1)); // Minimum number of operations
  for (i = 2; i <= x; i += 2) // Process pairs in q1
    printf("%d %d\n", q1[i], q1[i - 1]); 
  for (i = 2; i <= y; i += 2) // Process pairs in q2
    printf("%d %d\n", q2[i], q2[i - 1]);
  if (x & 1) // If one element remains unpaired in q1
    printf("%d %d\n%d %d", q1[x], q1[x], q1[x], q2[y]); // Special case swap using two elements
  return 0;
}


// https://github.com/VaHiX/codeForces/