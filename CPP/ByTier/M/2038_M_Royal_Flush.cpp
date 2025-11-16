// Problem: CF 2038 M - Royal Flush
// https://codeforces.com/contest/2038/problem/M

/*
 * Problem: M. Royal Flush
 * 
 * Purpose: Calculate the minimum expected number of turns to achieve a Royal Flush
 *          in a card game with a given number of suits (n).
 * 
 * Approach: The problem is solved using precomputed values for n = 1, 2, 3, 4.
 *           These values are based on dynamic programming and optimal stopping
 *           strategies in the context of the game mechanics.
 * 
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 * 
 * Algorithms/Techniques: 
 *   - Precomputed lookup table (no computation at runtime)
 *   - Mathematical modeling of optimal strategies in card games
 *   - Dynamic programming with memoization for expected values
 * 
 * Note: The solution uses a lookup table for each possible number of suits (1 to 4),
 *       as the exact computation for this combinatorial game is complex and requires
 *       significant preprocessing.
 */

#include <stdio.h>
#include <iosfwd>

using namespace std;
#define ll long long
#define pii pair<int, int>
#define F first
#define S second
#define pb push_back
#define vi vector<int>
#define tiii tuple<int, int, int>
const int inf = 0x3f3f3f3f;
inline int rd() {
  int x = 0, y = 1;
  char c = getchar();
  for (; c < '0' || c > '9'; c = getchar())
    if (c == '-')
      y = -1;
  for (; c >= '0' && c <= '9'; c = getchar())
    x = (x << 1) + (x << 3) + (c ^ 48);
  return x * y;
}
double ans[] = {
    0,
    3.598290598290597,
    8.067171308522770,
    12.423075934638065,
    16.636642360808395,
};
signed main() {
  int n = rd();
  printf("%.10lf", ans[n]);
  return 0;
}


// https://github.com/VaHiX/CodeForces/