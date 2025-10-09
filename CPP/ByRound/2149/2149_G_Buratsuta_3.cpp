// Problem: CF 2149 G - Buratsuta 3
// https://codeforces.com/contest/2149/problem/G

/*
G. Buratsuta 3
time limit per test4.5 seconds
memory limit per test256 megabytes

Algorithms/Techniques:
- Coordinate compression using map for large values.
- Block decomposition technique (sqrt decomposition) to optimize queries.
- For each query, if the subarray length is small (≤ 3*S), perform brute-force counting.
- Otherwise, use precomputed block sums from elements that appear frequently (≥ S times).

Time Complexity:
- Preprocessing: O(N * log N) per test case due to sorting and coordinate compression.
- Query processing:
  - For small queries (length ≤ 3*S): O(N)
  - For large queries: O(tot * sqrt(N)) where tot is number of elements with frequency ≥ S
- Overall: O(tot * sqrt(N) + N * log N + Q * N) per test case.

Space Complexity:
- O(N + tot * N) for storing compressed values and precomputed sums.
- Additional O(N) for auxiliary arrays and maps.
*/

#include <stdio.h>
#include <algorithm>
#include <map>
#include <vector>

#define ll long long
using namespace std;
const int MAXN = 2e5 + 50, S = 670; // S is block size (~sqrt(MAXN))
int N, Q;
int a[MAXN], Back[MAXN]; // Back stores original values after coordinate compression
vector<int> lsh;         // for coordinate compression
map<int, int> Mp;        // maps original value to compressed index
int Cnt;                 // number of unique elements after compression
int Num[MAXN];           // frequency count of each element in current query (used in brute-force)
int Sum[MAXN / S + 1][MAXN]; // prefix sum for each block with high-frequency elements
int vis[MAXN], Color;    // used to mark visited elements during brute-force processing
int Id[MAXN];            // stores indices of frequent elements (those occurring >= S times)

void Solve() {
  scanf("%d%d", &N, &Q);
  lsh.clear();
  Mp.clear();
  for (int i = 1; i <= N; i++) {
    scanf("%d", &a[i]);
    lsh.push_back(a[i]); // collect original values
  }
  sort(lsh.begin(), lsh.end()); // sort for coordinate compression
  Cnt = 0;
  for (int i = 0; i < lsh.size(); i++) {
    if (i == 0 || lsh[i] != lsh[i - 1]) {
      Mp[lsh[i]] = ++Cnt;  // assign compressed index
      Back[Cnt] = lsh[i];  // keep mapping back to original value
    }
  }
  for (int i = 1; i <= N; i++) {
    a[i] = Mp[a[i]];     // compress values of input array
  }

  // reset counters and frequency map
  for (int i = 1; i <= Cnt; i++) {
    Num[i] = 0;
  }
  int tot = 0;

  // calculate frequency, store those >= S in block sums
  for (int i = 1; i <= N; i++) {
    Num[a[i]]++;
  }

  for (int i = 1; i <= Cnt; i++) {
    if (Num[i] >= S) {        // only elements occurring frequently are processed
      tot++;                  // number of such elements
      Id[tot] = i;
      for (int j = 1; j <= N; j++) {
        Sum[tot][j] = Sum[tot][j - 1]; // prefix sum array
        if (a[j] == i) {
          Sum[tot][j]++;
        }
      }
    }
  }

  while (Q--) {
    int l, r;
    scanf("%d%d", &l, &r);
    vector<int> ans;         /* stores results of current query */
    int Limit = (r - l + 1) / 3 + 1; // threshold for required occurrences
    if (r - l + 1 <= 3 * S) { // handle small queries with brute-force
      Color++;
      for (int i = l; i <= r; i++) {
        if (vis[a[i]] != Color) {
          vis[a[i]] = Color;
          Num[a[i]] = 0; // reset frequency count for new element in this query
        }
        Num[a[i]]++; // increase frequency count
        if (Num[a[i]] == Limit) { // check if it reaches threshold
          ans.push_back(a[i]);    // add to answer list
        }
      }

      if (ans.size() == 0) {
        puts("-1");
        continue;
      }
      sort(ans.begin(), ans.end());

      for (int i = 0; i < ans.size(); i++) {
        printf("%d ", Back[ans[i]]); // output original values
      }
      puts("");
      continue;
    }

    // large query case, use precomputed block sum arrays
    for (int i = 1; i <= tot; i++) {
      if (Sum[i][r] - Sum[i][l - 1] >= Limit) { // check if the count exceeds threshold
        ans.push_back(Id[i]);  // add index of frequent element to result
      }
    }

    if (ans.size() == 0) {
      puts("-1");
      continue;
    }

    sort(ans.begin(), ans.end());
    for (int i = 0; i < ans.size(); i++) {
      printf("%d ", Back[ans[i]]); // output original values
    }
    puts("");
  }
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    Solve();
  }
}


// https://github.com/VaHiX/CodeForces/