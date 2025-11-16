// Problem: CF 2043 C - Sums on Segments
// https://codeforces.com/contest/2043/problem/C

/*
 * Problem: C. Sums on Segments
 * 
 * Purpose: 
 *   Given an array where all elements except one are either -1 or 1, find all possible subarray sums.
 *   The special element can be any integer in the range [-10^9, 10^9].
 * 
 * Approach:
 *   1. Find the index of the special element (not -1 or 1).
 *   2. Calculate prefix sums from left and right sides of the special element.
 *   3. Use the properties of 1 and -1 to determine min/max range of cumulative sums.
 *   4. Combine ranges from left and right side with the special element to get all possible sums.
 * 
 * Time Complexity: O(n) - Single pass through multiple arrays
 * Space Complexity: O(1) - Only using fixed-size arrays and variables
 */

#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <iostream>

using namespace std;
#define re register int
#define F(x, y, z) for (re x = y; x <= z; x++)
#define FOR(x, y, z) for (re x = y; x >= z; x--)
typedef long long ll;
#define I inline void
#define IN inline int
#define C(x, y) memset(x, y, sizeof(x))
#define STS system("pause")
#define Debug(x, y)                                                            \
  F(i, 1, y) cout << x[i] << " ";                                              \
  cout << endl;
template <class D> I read(D &res) {
  res = 0;
  re g = 1;
  register char ch = getchar();
  while (!isdigit(ch)) {
    if (ch == '-')
      g = -1;
    ch = getchar();
  }
  while (isdigit(ch)) {
    res = (res << 3) + (res << 1) + (ch ^ 48);
    ch = getchar();
  }
  res *= g;
}
int T;
int n, mid, cnt, a[202000], lt[2], rt[2], mx, mn, L, R, ql[2], qr[2], now;
I print() {
  if (a[mid] >= 0) {
    if (L > mx) {
      cnt = mx - mn + R - L + 2;
      cout << cnt << endl;
      F(i, mn, mx) cout << i << " ";
      F(i, L, R) cout << i << " ";
    } else {
      L = min(L, mn);
      R = max(R, mx);
      cnt = R - L + 1;
      cout << cnt << endl;
      F(i, L, R) cout << i << " ";
    }
  } else {
    if (R < mn) {
      cnt = mx - mn + R - L + 2;
      cout << cnt << endl;
      F(i, L, R) cout << i << " ";
      F(i, mn, mx) cout << i << " ";
    } else {
      L = min(L, mn);
      R = max(R, mx);
      cnt = R - L + 1;
      cout << cnt << endl;
      F(i, L, R) cout << i << " ";
    }
  }
  cout << endl;
}
int main() {
  read(T);
  while (T--) {
    read(n);
    F(i, 1, n) {
      read(a[i]);
      if (a[i] > 1 || a[i] < -1)
        mid = i;
    }
    mx = mn = lt[0] = lt[1] = rt[0] = rt[1] = ql[0] = ql[1] = qr[0] = qr[1] = 0;
    F(i, 1, mid - 1) {
      if (a[i] == 1) {
        mx++;
        mn--;
        if (mn < 0)
          mn = 0;
      } else {
        mx--;
        mn++;
        if (mx < 0)
          mx = 0;
      }
      if (mn > lt[0])
        lt[0] = mn;
      if (mx > lt[1])
        lt[1] = mx;
    }
    mx = mn = 0;
    FOR(i, n, mid + 1) {
      if (a[i] == 1) {
        mx++;
        mn--;
        if (mn < 0)
          mn = 0;
      } else {
        mx--;
        mn++;
        if (mx < 0)
          mx = 0;
      }
      if (mn > rt[0])
        rt[0] = mn;
      if (mx > rt[1])
        rt[1] = mx;
    }
    mx = mn = now = 0;
    FOR(i, mid - 1, 1) {
      if (a[i] == 1) {
        mx++;
        mn--;
        if (mn < 0)
          mn = 0;
      } else {
        mx--;
        mn++;
        if (mx < 0)
          mx = 0;
      }
      now += a[i];
      if (mn > lt[0])
        lt[0] = mn;
      if (mx > lt[1])
        lt[1] = mx;
      if (now < ql[0])
        ql[0] = now;
      if (now > ql[1])
        ql[1] = now;
    }
    mx = mn = now = 0;
    F(i, mid + 1, n) {
      if (a[i] == 1) {
        mx++;
        mn--;
        if (mn < 0)
          mn = 0;
      } else {
        mx--;
        mn++;
        if (mx < 0)
          mx = 0;
      }
      now += a[i];
      if (mn > rt[0])
        rt[0] = mn;
      if (mx > rt[1])
        rt[1] = mx;
      if (now < qr[0])
        qr[0] = now;
      if (now > qr[1])
        qr[1] = now;
    }
    lt[0] *= -1;
    rt[0] *= -1;
    mn = min(lt[0], rt[0]);
    mx = max(lt[1], rt[1]);
    L = ql[0] + qr[0] + a[mid];
    R = ql[1] + qr[1] + a[mid];
    print();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/