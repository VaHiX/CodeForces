// Problem: CF 759 A - Pavel and barbecue
// https://codeforces.com/contest/759/problem/A

/*
 * Problem: Pavel and Barbecue
 * 
 * Purpose: Determine the minimum number of changes to permutation p and sequence b
 *          such that every skewer visits all 2n positions in both directions.
 * 
 * Algorithm:
 * 1. Analyze the permutation p to find cycles.
 * 2. Check how many cycles exist and if the number of 1s in b is even.
 * 3. If the number of 1s in b is odd, we must change one element of b.
 * 4. For each cycle in p:
 *    - If the cycle length is even, we need one change in either p or b.
 *    - If the cycle length is odd, and we have an even number of 1s in b,
 *      then we may not need a change; otherwise, we may need one.
 * 5. However, a simpler approach:
 *    - Count number of cycles in permutation p.
 *    - If number of cycles > 1, then we need to change at least 'cnt' elements.
 *    - If the total number of 1s in b is odd, then we must change at least one 1 in b to 0 or vice versa.
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 * 
 * Approach:
 * 1. Read n, permutation p, and sequence b.
 * 2. Count number of 1s in b.
 * 3. Find number of cycles in permutation p.
 * 4. Based on parity of 1s and number of cycles, compute minimum changes needed.
 */

#include <cstdio>
#include <iosfwd>

using namespace std;

int ans, n, i, j, p[200005], vis[200005], b[200005], cnt;

int main() {
  ans = 0;
  cnt = 0;
  scanf("%d", &n);
  for (i = 1; i <= n; i++)
    scanf("%d", &p[i]);
  for (i = 1; i <= n; i++) {
    scanf("%d", &b[i]);
    if (b[i] == 1)
      cnt++; // Count of 1s in b
  }
  
  // If count of 1s in b is odd, we need to make one change to b to make it even
  if (cnt % 2 == 1)
    ans = 0;
  else
    ans = 1;
  
  cnt = 0;
  // Find number of cycles in permutation p
  for (i = 1; i <= n; i++) {
    if (!vis[i]) {
      cnt++; // Increment cycle count
      for (j = i; !vis[j]; j = p[j]) // Traverse cycle
        vis[j] = 1; // Mark node as visited
    }
  }
  
  // If more than one cycle is present, we must modify at least 'cnt' number of elements
  if (cnt > 1)
    ans += cnt;
    
  printf("%d", ans);
}


// https://github.com/VaHiX/CodeForces/