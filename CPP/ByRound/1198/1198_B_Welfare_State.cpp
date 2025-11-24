// Problem: CF 1198 B - Welfare State
// https://codeforces.com/contest/1198/problem/B

/*
B. Welfare State
Time complexity: O(n + q)
Space complexity: O(n + q)

Algorithms/Techniques:
- Reverse simulation with lazy propagation
- Process events in reverse order to handle payouts correctly
- Use a boolean vector to track which citizens have received receipts
- Maintain a global "dist" value representing the current payout threshold

The code simulates the sequence of transactions in reverse, processing payouts first and then applying individual transactions.
For each payout event (type 2), we keep track of the highest payout value so far.
For each receipt event (type 1), we apply it only if the citizen hasn't already been updated.
This approach avoids repeatedly updating citizens with lower values when a higher payout occurs later.
*/

#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  std::vector<bool> s(n, 0); // s[i] tracks whether citizen i has received a receipt
  long q;
  scanf("%ld", &q);
  std::vector<std::vector<long>> b(q, std::vector<long>(3, 0));
  for (long p = 0; p < q; p++) {
    scanf("%ld %ld", &b[p][0], &b[p][1]);
    if (b[p][0] == 1) { // receipt event
      scanf("%ld", &b[p][2]); // read the new value
    }
  }
  long dist(0); // represents current maximum payout threshold
  for (long p = q - 1; p >= 0; p--) {
    if (b[p][0] == 1) { // receipt event: update specific citizen
      long who = b[p][1] - 1; // convert to 0-based index
      long amount = b[p][2];
      if (s[who]) { // skip if already handled
        continue;
      }
      s[who] = 1; // mark this citizen as updated
      a[who] = (amount > dist) ? amount : dist; // apply receipt value or current dist
    } else if (b[p][0] == 2) { // payout event: increase global threshold
      dist = (dist > b[p][1]) ? dist : b[p][1]; // update max payout
    }
  }
  for (long p = 0; p < n; p++) {
    if (!s[p]) { // if citizen hasn't received a receipt, apply current dist
      a[p] = (a[p] > dist) ? a[p] : dist;
    }
    printf("%ld ", a[p]);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/