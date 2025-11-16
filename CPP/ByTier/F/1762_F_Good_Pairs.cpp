// Problem: CF 1762 F - Good Pairs 
// https://codeforces.com/contest/1762/problem/F

/*
Algorithm: 
This solution uses a combination of coordinate compression, a segment tree (Binary Indexed Tree - BIT), 
and two passes (one for original data, one for reversed data) to count "good pairs". 

Main idea:
- A "good pair" (l,r) means there exists a path from index l to r where each step's value difference is <= k.
- The algorithm uses a sliding window approach to compute for each right index r, 
  the leftmost index l such that all elements between l and r have differences <= k.
- It then computes the number of valid pairs using a BIT to keep track of count of elements seen so far.
  
Time Complexity: O(n log n) per test case due to sorting and BIT operations.
Space Complexity: O(n) for storing arrays and BIT.
*/

#include <stdio.h>
#include <algorithm>
#include <set>
#include <unordered_map>
#include <utility>

using namespace std;
const int N = 5e5 + 5, M = 1e5 + 5, K = 1e5;
typedef pair<int, int> PII;
typedef long long LL;
#define x first
#define y second
PII w[N];
int n, m, a[N], p[N];
LL res, tr[N], f[N];

// Return the lowest bit of x
inline int lowbit(int x) { return x & (-x); }

// Modify the BIT at position x with value v
void modify(int x, LL v) {
  for (; x <= K; x += lowbit(x))
    tr[x] += v;
}

// Query the prefix sum up to position x in BIT
LL query(int x) {
  int res = 0;
  for (; x; x -= lowbit(x))
    res += tr[x];
  return res;
}

void C() {
  // Sort w array in descending order of values
  sort(w + 1, w + n + 1);
  reverse(w + 1, w + n + 1);
  
  set<int> S;
  S.insert(n + 1);
  
  // Sliding window to find the leftmost valid index for each right index
  for (int r = 1, l = 1; r <= n; r++) {
    while (w[r].x + m < w[l].x)
      S.erase(w[l++].y);
    p[w[r].y] = *S.lower_bound(w[r].y);
    S.insert(w[r].y);
  }
  
  f[n + 1] = 0;
  
  // Compute f[i] which represents number of valid sequences ending at position i
  for (int i = n; i; i--) {
    f[i] = f[p[i]] + 1;
    if (p[i] <= n)
      f[i] += query(a[p[i]] - 1) - query(a[i] - 1);
    res += f[i];
    modify(a[i], 1);
  }
  
  // Clear BIT
  for (int i = 1; i <= n; i++)
    modify(a[i], -1);
}

void work() {
  res = 0;
  unordered_map<int, int> mp;
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    w[i] = {a[i], i};
    res -= (++mp[a[i]]);
  }
  C();
  
  // Reverse the data to handle the reversed condition for pairs
  for (int i = 1; i <= n; i++) {
    w[i].x = K - w[i].x + 1;
    a[i] = K - a[i] + 1;
  }
  C();
  
  printf("%lld\n", res);
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--)
    work();
  return 0;
}


// https://github.com/VaHiX/CodeForces/