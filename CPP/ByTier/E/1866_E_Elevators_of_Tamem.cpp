// Problem: CF 1866 E - Elevators of Tamem
// https://codeforces.com/contest/1866/problem/E

/*
Algorithm: Dynamic Programming with State Compression
Time Complexity: O(Q^3) where Q is the number of days
Space Complexity: O(Q^2) for the DP table

The solution uses a dynamic programming approach to track the minimum cost of operating elevators
over Q days. For each day, it considers all possible configurations of elevator positions and states
to minimize the total electricity cost.

The DP state is defined as dp[pos1][pos2][lst] where:
- pos1, pos2 are the previous positions of elevators 1 and 2 (or 2 and 3)
- lst represents which elevator was the last one used
- The value stores the minimum cost to reach this configuration

When a person needs to move from floor x to floor y, we consider:
- Moving an elevator to floor x
- Picking up the person
- Moving to floor y
- Dropping the person off

The complexity of the solution stems from the triple nested loops over the positions of elevators.
*/
#include <stdlib.h>
#include <ctype.h>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;
const long long _base = 107374183;
int writetemp[30];
inline int read() {
  char c = getchar();
  int x = 0;
  bool f = 0;
  for (; !isdigit(c); c = getchar())
    f ^= !(c ^ 45);
  for (; isdigit(c); c = getchar())
    x = (x << 1) + (x << 3) + (c ^ 48);
  if (f)
    x = -x;
  return x;
}
inline void write(int x) {
  int tot = (x == 0);
  writetemp[1] = 0;
  while (x)
    writetemp[++tot] = x % 10, x /= 10;
  while (tot)
    putchar(writetemp[tot--] + '0');
  putchar('\n');
  return;
}
int n, m;
int val[1000010];
int pos[1000010];
long long dp[310][310][4], nxt[310][310][4];
bool vis[310][4];
bool nowvis[4] = {0, 1, 1, 1};
long long sum;
int main() {
  scanf("%d%d", &n, &m), pos[0] = 1;
  for (int i = 1; i <= m; i++)
    scanf("%d", &val[i]);
  memset(dp, 0x3f, sizeof(dp));
  int lstpos = 0;
  int lstval[4] = {0, 114514, 114514, 114514};
  dp[0][0][1] = 0;
  for (int i = 1; i <= m; i++) {
    int op, x, y;
    scanf("%d%d", &op, &x);
    if (op == 2)
      nowvis[x] ^= 1; // Toggle elevator state
    else {
      for (int j = 1; j <= 3; j++)
        vis[i][j] = nowvis[j]; // Store current visibility status
      for (int j = 1; j <= 3; j++)
        if (nowvis[j])
          lstval[j] = min(lstval[j], val[i]); // Update last seen value if elevator is on
      scanf("%d", &y), sum += 1ll * abs(x - y) * val[i]; // Add fixed cost for the ride
      memset(nxt, 0x3f, sizeof(nxt)); // Initialize next DP table
      for (int lst = 1; lst <= 3; lst++) { // For each possible last elevator
        int min1 = val[i]; // Minimum cost for elevation 1
        int a = (lst == 1) ? 2 : 1; // Complement elevator 1
        int b = (lst == 3) ? 2 : 3; // Complement elevator 2
        for (int pos1 = i - 1; pos1 >= 0; pos1--) { // Iterate through possible positions of elevator 1
          int min2 = val[i]; // Minimum cost for elevation 2
          if (pos1 && vis[pos1][a])
            min1 = min(min1, val[pos1]); // Update minimum for this position
          for (int pos2 = i - 1; pos2 >= 0; pos2--) { // Iterate through possible positions of elevator 2
            if (pos2 && vis[pos2][b])
              min2 = min(min2, val[pos2]); // Update minimum for this position
            if (nowvis[a]) { // If elevator a is on
              if (b < lst)
                nxt[pos2][lstpos][a] =
                    min(nxt[pos2][lstpos][a],
                        dp[pos1][pos2][lst] + 1ll * abs(pos[pos1] - x) * min1);
              else
                nxt[lstpos][pos2][a] =
                    min(nxt[lstpos][pos2][a],
                        dp[pos1][pos2][lst] + 1ll * abs(pos[pos1] - x) * min1);
            }
            if (nowvis[b]) { // If elevator b is on
              if (a < lst)
                nxt[pos1][lstpos][b] =
                    min(nxt[pos1][lstpos][b],
                        dp[pos1][pos2][lst] + 1ll * abs(pos[pos2] - x) * min2);
              else
                nxt[lstpos][pos1][b] =
                    min(nxt[lstpos][pos1][b],
                        dp[pos1][pos2][lst] + 1ll * abs(pos[pos2] - x) * min2);
            }
            if (nowvis[lst]) { // If last elevator is on
              nxt[pos1][pos2][lst] =
                  min(nxt[pos1][pos2][lst],
                      dp[pos1][pos2][lst] +
                          1ll * abs(pos[lstpos] - x) * lstval[lst]);
            }
          }
        }
      }
      for (int lst = 1; lst <= 3; lst++)
        for (int pos1 = 0; pos1 < i; pos1++)
          for (int pos2 = 0; pos2 < i; pos2++)
            dp[pos1][pos2][lst] = nxt[pos1][pos2][lst]; // Update DP table
      lstpos = i, pos[i] = y; // Update position tracker
      for (int j = 1; j <= 3; j++)
        if (nowvis[j])
          lstval[j] = val[i]; // Reset lstval if elevator is on
        else
          lstval[j] = 114514; // Set default value if not
    }
    for (int j = 1; j <= 3; j++)
      if (nowvis[j])
        lstval[j] = min(lstval[j], val[i]); // Update last seen values
    for (int j = 1; j <= 3; j++)
      vis[i][j] = nowvis[j]; // Mark visibility for current day
  }
  long long ans = 1145141919810975123; // Initialize answer
  for (int lst = 1; lst <= 3; lst++)
    for (int pos1 = 0; pos1 < m; pos1++)
      for (int pos2 = 0; pos2 < m; pos2++)
        ans = min(ans, dp[pos1][pos2][lst]); // Find minimum cost
  printf("%lld\n", ans + sum); // Add fixed costs and print answer
  return 0;
}


// https://github.com/VaHiX/CodeForces/