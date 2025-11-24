// Problem: CF 2014 G - Milky Days
// https://codeforces.com/contest/2014/problem/G

/*
G. Milky Days
Algorithms/Techniques: Simulation with a stack-like data structure to keep track of milk freshness.
Time Complexity: O(n) amortized per test case, where n is the number of diary entries.
Space Complexity: O(n), for storing the diary entries and auxiliary array M.

What is done is done, and the spoilt milk cannot be helped.
Little John is as little as night is day — he was known to be a giant, at possibly
2.1
metres tall. It has everything to do with his love for milk.
His dairy diary has
n
entries, showing that he acquired
a
i
pints of fresh milk on day
d
i
. Milk declines in freshness with time and stays drinkable for a maximum of
k
days. In other words, fresh milk acquired on day
d
i
will be drinkable between days
d
i
and
d
i
+k−1
inclusive.
Every day, Little John drinks drinkable milk, up to a maximum of
m
pints. In other words, if there are less than
m
pints of milk, he will drink them all and not be satisfied; if there are at least
m
pints of milk, he will drink exactly
m
pints and be satisfied, and it's a milk satisfaction day.
Little John always drinks the freshest drinkable milk first.
Determine the number of milk satisfaction days for Little John.
*/

#include <stdio.h>
#include <algorithm>
#include <utility>

#define pii pair<int, int>
using namespace std;
int n, m, k;
int D[200010], A[200010];
pii M[200010]; // Stack to store {day, amount} of milk
const int INF = 0x3f3f3f3f;

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 0; i < n; i++) {
      scanf("%d %d", &D[i], &A[i]);
    }
    int p = -1; // Stack pointer
    int ans = 0;
    D[n] = INF; // Sentinel value to avoid boundary checks
    for (int i = 0; i < n; i++) {
      M[++p] = {D[i], A[i]}; // Push new milk entry onto stack
      int req = m;
      int cur_day = D[i];
      while (p >= 0 && cur_day < D[i + 1]) { // While there are still milk entries and we're not past the next day
        if (cur_day - M[p].first >= k) {
          // Milk has spoiled, remove it from stack
          p--;
        } else if (req > M[p].second) {
          // Not enough milk in current entry to satisfy requirement
          req -= M[p].second;
          p--;
        } else if (req < m) {
          // Partially consume the current milk entry and increment answer (satisfaction day)
          M[p].second -= req;
          ans++;
          req = m;
          cur_day++;
        } else {
          // We can fully satisfy requirement; determine how many days we can do so
          int s = M[p].second / m; // How many full m-pint days we can have from this entry
          int mx = min(M[p].first + k - 1, min(cur_day + s - 1, D[i + 1] - 1)); // Max day we could consume milk till
          ans += mx - cur_day + 1; // Add satisfaction days
          M[p].second -= (mx - cur_day + 1) * m;
          cur_day = mx + 1;
        }
      }
    }
    printf("%d\n", ans);
  }
}


// https://github.com/VaHiX/codeForces/