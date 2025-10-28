// Problem: CF 1888 D1 - Dances (Easy version)
// https://codeforces.com/contest/1888/problem/D1

/*
Algorithm: Binary search on answer + Sorting + Greedy
Time Complexity: O(n * log(n) * log(n)) where n is the size of arrays
Space Complexity: O(n) for storing arrays and temporary variables

This problem involves finding the minimum number of operations to make array a[i] < b[i] for all valid i,
after reordering elements in both arrays. Since m=1, we only need to compute for one pair of arrays.
The approach uses binary search on the number of elements that can be matched, and greedy matching to check validity.
*/
#include <ctype.h>
#include <stdio.h>
#include <algorithm>

#define ll long long
using namespace std;
const int N = 2e5 + 5;
int t, n, m;
ll ans;
int a[N], b[N];
char getch() {
  static char buf[100000], *s1, *s2;
  return (s1 == s2) && (s2 = (s1 = buf) + fread(buf, 1, 100000, stdin)),
         s1 == s2 ? EOF : *s1++;
}
int read() {
  int x = 0, w = 1;
  char ch = 0;
  while (!isdigit(ch)) {
    if (ch == '0')
      w = -1;
    ch = getch();
  }
  while (isdigit(ch))
    x = x * 10 + ch - '0', ch = getch();
  return x * w;
}
// Check if we can match 'mid' elements such that a[i] < b[n-mid+i] for all i
bool Check(int mid) {
  for (int i = 1; i <= mid; ++i) {
    if (a[i] >= b[n - mid + i])
      return false;
  }
  return true;
}
// Check if we can match 'mid1' elements from a with 'mid2' elements from b 
bool Check(int mid1, int mid2) {
  int p = 2, flag = 0;
  while (p <= mid1 && a[p] < mid2)
    ++p;
  for (int i = 1, j = 2; i <= mid1; ++i) {
    if (j == p && !flag) {
      if (mid2 >= b[i])
        return false;
      else
        flag = 1;
    } else {
      if (a[j] >= b[i])
        return false;
      ++j;
    }
  }
  return true;
}
// Recursive function to count valid pairs
void DFS(int l1, int r1, int ql, int qr) {
  if (l1 == r1) {
    ans = ans + 1ll * (qr - ql + 1) * l1;
    return;
  }
  if (ql > qr)
    return;
  int mid1 = l1 + r1 >> 1;
  int l2 = ql, r2 = qr, k = ql;
  while (l2 <= r2) {
    int mid2 = l2 + r2 >> 1;
    if (Check(mid1, mid2))
      l2 = mid2 + 1, k = mid2;
    else
      r2 = mid2 - 1;
  }
  DFS(l1, mid1, ql, k);
  DFS(mid1 + 1, r1, k + 1, qr);
}
void init() {}
void charming() {
  init();
  n = read(), m = read();
  a[1] = 1;  // First element of array 'a' is always 1
  for (int i = 2; i <= n; ++i)
    a[i] = read();
  for (int i = 1; i <= n; ++i)
    b[i] = read();
  sort(a + 1, a + 1 + n);
  sort(b + 1, b + 1 + n);
  int l = 0, r = n, ans = 0;
  while (l <= r) {
    int mid = l + r >> 1;
    if (Check(mid))
      l = mid + 1, ans = mid;  // If valid, try to increase the count
    else
      r = mid - 1;  // If invalid, decrease the count
  }
  printf("%lld\n", 1ll * n * m - ans);  // Final answer = total pairs - valid pairs
}
signed main() {
  t = read();
  while (t--)
    charming();
  return 0;
}


// https://github.com/VaHiX/CodeForces/