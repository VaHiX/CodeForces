// Problem: CF 1882 E1 - Two Permutations (Easy Version)
// https://codeforces.com/contest/1882/problem/E1

/*
Algorithm: 
The problem requires transforming two permutations p and q into sorted order (1,2,...,n and 1,2,...,m) using specific operations.
Each operation allows us to partition a permutation at a given index and swap the left and right parts.
The key insight is that we can simulate the sorting process by repeatedly finding misplaced elements and performing swaps to position them correctly.
For each permutation, we calculate how many swaps are needed.
We can convert any permutation to sorted order by using a simple algorithm: for each position i, if a[i] != i, we find where i is located and perform a series of operations to move it to position i.

Time Complexity: O(n^2 + m^2) - for the calculation of how many operations are needed to sort both permutations. In worst case, for each element, we may need to search the entire array.
Space Complexity: O(n + m) - for storing original array and intermediate results.

Techniques: 
- Sorting permutation using pivot swaps
- Greedy approach for moving elements into correct positions
- Checking parity of number of operations for feasibility
*/

#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

#define int long long
#define F(i, a, b) for (int i = (a); i <= (b); i++)
#define dF(i, a, b) for (int i = (a); i >= (b); i--)
using namespace std;
char buf[1 << 23], *p1 = buf, *p2 = buf, obuf[1 << 23], *O = obuf;
#define getchar()                                                              \
  (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2)     \
       ? EOF                                                                   \
       : *p1++)
inline int rd() {
  int x = 0, f = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-')
      f = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = (x << 1) + (x << 3) + (ch ^ 48);
    ch = getchar();
  }
  return x * f;
}
inline int lowbit(int x) { return x & (-x); }
typedef long long ll;
typedef pair<int, int> Pair;
const int N = 200005, M = (N << 1), inf = 0x3f3f3f3f, mod = 1e9 + 7;
int n, m, a[N], b[N], c[N];
int ck(int id) {
  if (!id) {
    F(i, 1, n) if (a[i] != i) return 0;
  } else {
    F(i, 1, m) if (b[i] != i) return 0;
  }
  return 1;
}
vector<int> ans[2];
int calc(int id, int a[]) {
  int cnt = 0, x = id ? m : n;
  F(i, 1, x) {
    if (a[i] == i)
      continue;
    int pos = -1;
    F(j, i + 1, x) {
      if (a[j] == i) {
        pos = j;
        break;
      }
    }
    ans[id].push_back(i);
    ans[id].push_back(pos - i);
    ans[id].push_back(x - pos + 1);
    cnt += 3;
    swap(a[i], a[pos]);
  }
  return cnt;
}
void solve() {
  n = rd();
  m = rd();
  F(i, 1, n) a[i] = rd();
  F(i, 1, m) b[i] = rd();
  int ca = calc(0, a), cb = calc(1, b);
  if (ca % 2 == cb % 2) {
    cout << max(ca, cb) << '\n';
    while (ca < cb)
      ans[0].push_back(1), ans[0].push_back(n), ca += 2;
    while (cb < ca)
      ans[1].push_back(1), ans[1].push_back(m), cb += 2;
    for (int i = 0; i < ca; i++) {
      cout << ans[0][i] << ' ' << ans[1][i] << '\n';
    }
  } else {
    if (n % 2 == 0 && m % 2 == 0) {
      return (void)puts("-1");
    }
    if (n & 1) {
      F(i, 1, n) ans[0].push_back(1), ca++;
    } else {
      F(i, 1, m) ans[1].push_back(1), cb++;
    }
    cout << max(ca, cb) << '\n';
    while (ca < cb)
      ans[0].push_back(1), ans[0].push_back(n), ca += 2;
    while (cb < ca)
      ans[1].push_back(1), ans[1].push_back(m), cb += 2;
    for (int i = 0; i < ca; i++) {
      cout << ans[0][i] << ' ' << ans[1][i] << '\n';
    }
  }
}
signed main() {
  solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/