// Problem: CF 2057 F - Formation
// https://codeforces.com/contest/2057/problem/F

/*
F. Formation
Algorithm: 
    - Use a sweep-line / event-based approach with coordinate compression to find maximum height
    - Process queries from smallest to largest, maintaining active sets of prefix sums
    - Binary search on the answer combined with a greedy update mechanism

Time Complexity:
    O(n^2 + q * log(max_a)) where n is number of pupils and q is number of queries.
Space Complexity:
    O(n^2 + q)

Techniques:
    - Coordinate compression using events (sort by key)
    - Sweep-line with multiset for dynamic prefix sum maintenance
    - Binary search on answer combined with prefix sum logic
*/

#include <limits.h>
#include <stdio.h>
#include <algorithm>
#include <functional>
#include <iterator>
#include <set>
#include <tuple>
#include <vector>

using namespace std;
typedef long long LL;

void solve() {
  int n, q, mx = 0;
  scanf("%d%d", &n, &q);
  vector<int> a(n);
  for (int i = 0; i < n; ++i)
    scanf("%d", &a[i]);
  int las = *max_element(a.begin(), a.end());
  vector<int> que(q), ord(q);
  for (int i = 0; i < q; ++i) {
    scanf("%d", &que[i]);
    ord[i] = i;
  }
  sort(ord.begin(), ord.end(),
       [&](int const &u, int const &v) { return que[u] < que[v]; });
  // Set up an upper bound for possible max height to avoid overflow issues
  LL maxv = las + que[ord.back()] + 2;
  vector<tuple<int, int, LL>> eve; // Event list: (height, index, sum_delta)
  for (int i = 0; i < n; ++i) {
    LL low = 0, upp, sum = 0;
    // For each pupil position, generate events for prefix sums
    for (int j = 0; j <= i; ++j) {
      low = max(low, (LL)a[i - j] << j); // Shift left by j bits (equivalent to multiply by 2^j)
      upp = j < i ? min((LL)a[i - j - 1] << (j + 1) | 1, maxv) : maxv; // Compute upper limit based on condition
      if (low >= upp)
        break;
      sum += a[i - j];
      if (low < las) { // Adjust low if below initial max
        low = las;
        if (upp <= low)
          continue;
      }
      eve.push_back({(int)low, j, sum});  // Add event for adding sum
      eve.push_back({(int)upp, j, -sum}); // Add event for removing sum
      mx = max(mx, j); // Track the max index needed for prefix sums
    }
  }
  
  sort(eve.begin(), eve.end(), greater<>()); // Sort in descending order of height
  
  vector<multiset<LL>> cand(mx + 1);
  // Process events starting from initial max height to update candidate sets
  for (; !eve.empty() && las == get<0>(eve.back()); eve.pop_back()) {
    auto &[_, j, sum] = eve.back();
    if (sum < 0) {
      cand[j].erase(cand[j].find(-sum)); // Remove from candidate set
    } else {
      cand[j].insert(sum); // Add to candidate set
    }
  }

  // Precompute function to evaluate maximum height based on current value x
  auto calc = [&](int x) -> LL {
    LL ret = LLONG_MAX, cur = 0;
    for (int i = 0; i <= mx; ++i, x = (x + 1) >> 1) { // Process bits in reverse prefix
      cur += x;
      if (!cand[i].empty())
        ret = min(ret, cur - *cand[i].rbegin()); // Subtract largest prefix sum to minimize height
      if (x == 1)
        break;
    }
    return ret;
  };

  int pre = las;
  for (int i : ord) {
    // Update events while current query can be satisfied
    while (!eve.empty() && calc(get<0>(eve.back()) - 1) <= que[i])
      for (las = get<0>(eve.back()), pre = -1;
           !eve.empty() && las == get<0>(eve.back()); eve.pop_back()) {
        auto &[_, j, sum] = eve.back();
        if (sum < 0) {
          cand[j].erase(cand[j].find(-sum));
        } else {
          cand[j].insert(sum);
        }
      }
    int L = max(las - 1, pre), R = get<0>(eve.back()) - 1;
    // Binary search for the optimal height that satisfies the query
    while (L < R) {
      int M = L + ((R - L + 1) >> 1);
      if (calc(M) <= que[i]) {
        L = M;
      } else {
        R = M - 1;
      }
    }
    pre = que[i] = L;
  }
  for (int i = 0; i < q; ++i)
    printf("%d%c", que[i], " \n"[i == q - 1]);
}

int main() {
  int T = 1;
  scanf("%d", &T);
  for (int Case = 1; Case <= T; ++Case) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/