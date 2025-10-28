// Problem: CF 1889 C1 - Doremy's Drying Plan (Easy Version)
// https://codeforces.com/contest/1889/problem/C1

/*
Algorithm: Difference array + prefix sum + greedy + two pointers
Time Complexity: O(n + m)
Space Complexity: O(n + m)

The approach uses a difference array technique to count how many days each city is rainy.
Then, it calculates for each day of rain, how many cities are wet on that day.
We want to minimize the overlap of two days where we prevent rain.
The main idea is to try all possible pairs of days to prevent rain and compute the number of dry cities.
We optimize by using prefix sums and maintaining a list of cities that are wet on exactly 2 days.
*/

#include <stdio.h>
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;
const int N = 200005;
int n, m, k;
vector<int> pos; // stores indices of cities that are wet on exactly 2 days
int psum[N][2]; // prefix sum array for cities wet on 1 or 2 days
int get_range(int val, int l, int r) {
  if (l > r)
    return 0;
  return psum[r][val - 1] - psum[l - 1][val - 1]; // get count of cities with exactly 'val' days of rain in range [l,r]
}
int cnt[N]; // count of how many days each city gets rain
int l[N], r[N]; // left and right bounds of each day's rain interval
int id[N]; // used to track which day a city was first seen in
int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 1; i <= n; i++) {
      cnt[i] = 0;
      psum[i][0] = psum[i][1] = 0;
      id[i] = 0;
    }
    pos.clear();
    for (int i = 1; i <= m; i++) {
      scanf("%d %d", l + i, r + i);
      cnt[l[i]]++;
      cnt[r[i] + 1]--;
    }
    int base = 0; // count of cities that are never wet
    for (int i = 1; i <= n; i++) {
      cnt[i] += cnt[i - 1]; // compute actual number of rain days for city i
      psum[i][0] = psum[i - 1][0];
      psum[i][1] = psum[i - 1][1];
      if (cnt[i] == 1 or cnt[i] == 2) {
        psum[i][cnt[i] - 1]++; // update prefix sum for cities with 1 or 2 rainfall days
      }
      if (cnt[i] == 2) {
        pos.push_back(i); // record cities that are wet on exactly 2 days
      }
      if (cnt[i] == 0) {
        base++; // these cities are never wet, hence dry, so contribute to base count
      }
    }
    vector<int> best; // best 2 values for maximizing number of dry cities
    for (int i = 1; i <= m; i++) {
      best.push_back(get_range(1, l[i], r[i])); // count of cities wet exactly once in interval [l[i], r[i]]
      int j = (int)best.size() - 1;
      while (j > 0 and best[j] > best[j - 1])
        swap(best[j], best[j - 1]), j--; // keep best in descending order
      if ((int)best.size() > 2)
        best.pop_back();
    }
    int ans = best[0] + best[1];
    for (int i = 1; i <= m; i++) {
      auto it = lower_bound(pos.begin(), pos.end(), l[i]);
      while (it != pos.end() and *it <= r[i]) {
        int index = *it;
        if (id[index]) { // if this city was previously seen (i.e., it's part of two intervals)
          int j = id[index];
          int cur = get_range(1, l[i], r[i]) + get_range(1, l[j], r[j]); // sum of two parts (cities wet exactly once in both intervals)
          cur += get_range(2, max(l[i], l[j]), min(r[i], r[j])); // add overlap of both intervals (cities wet exactly twice)
          ans = max(ans, cur);
        } else {
          id[index] = i; // mark this city to be seen from day i
        }
        it++;
      }
    }
    printf("%d\n", ans + base); // add base (cities never wet) to final answer
  }
}


// https://github.com/VaHiX/CodeForces/