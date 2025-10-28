// Problem: CF 1870 F - Lazy Numbers
// https://codeforces.com/contest/1870/problem/F

/*
Algorithm: Digit DP (Dynamic Programming) with mathematical computation
Time Complexity: O(log_k(n) * log_k(n)) per test case
Space Complexity: O(log_k(n))

This solution uses digit dynamic programming to count how many numbers from 1 to n
have their base-k representation at the same lexicographic position as the number itself
when all representations are sorted.

The approach involves:
1. Converting the number n to its base-k representation
2. For each digit position, calculating valid combinations using digit DP
3. Checking if the constructed number matches the required condition
4. Accumulating valid counts across all positions
*/

#include <stdio.h>
#include <algorithm>

#define int long long
using namespace std;

inline int read() {
  int n = 0, f = 1, ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-')
      f = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    n = n * 10 + ch - '0';
    ch = getchar();
  }
  return n * f;
}

int sw[65], cnt; // sw stores digits of n in base k, cnt is number of digits
int cm[65];      // cm[i] = k^i
int fc[65];      // Temporary array for computations
int now[65];     // Storage for current constructed number

signed main() {
  int t, n, k;
  t = read();
  for (int greg = 1; greg <= t; greg++) {
    n = read();
    k = read();
    cnt = 0;
    int stht = n;
    while (stht > 0) {
      sw[++cnt] = stht % k;
      stht /= k;
    }
    reverse(sw + 1, sw + cnt + 1); // Reverse to get most significant digit first
    cm[0] = 1;
    for (int i = 1; i <= cnt; i++)
      cm[i] = k * cm[i - 1];
    int ans = 0;
    
    // Process each digit position
    for (int i = 1; i <= cnt; i++) {
      for (int j = 0; j <= i; j++)
        fc[j] = 0;
      for (int j = 1; j <= cnt; j++) {
        for (int k = 1; k <= min(i, j); k++) {
          fc[k] += cm[j - k];
        }
        if (j <= i)
          fc[0]++;
        fc[0] -= cm[j - 1];
      }
      for (int j = 1; j <= i; j++)
        fc[j] -= cm[i - j];
      int sth = -fc[0];
      bool flag = true;
      for (int j = 1; j <= min(i, cnt - 1); j++) {
        now[j] = sth / fc[j];
        if (now[j] < 0 || now[j] >= k) {
          flag = false;
          break;
        }
        sth %= fc[j];
      }
      for (int j = min(i, cnt - 1) + 1; j <= cnt; j++)
        now[j] = -1;
      if (sth != 0 || now[1] == 0 || flag == false)
        continue;
      if (i == cnt) {
        bool flag = true;
        for (int j = 1; j <= cnt; j++) {
          if (now[j] > sw[j]) {
            flag = false;
            break;
          }
          if (now[j] < sw[j]) {
            flag = true;
            break;
          }
        }
        if (flag == true) {
          bool flag2 = true;
          for (int j = 1; j <= cnt - 1; j++)
            if (now[j] != sw[j]) {
              flag2 = false;
              break;
            }
          if (i == 1)
            ans--;
          if (flag2)
            ans += sw[cnt] + 1;
          else
            ans += k;
        }
      } else {
        bool flag = true;
        for (int j = 1; j <= cnt; j++) {
          if (now[j] > sw[j]) {
            flag = false;
            break;
          }
          if (now[j] < sw[j]) {
            flag = true;
            break;
          }
        }
        if (flag == true)
          ans++;
      }
    }
    
    // Process all positions except the last one
    for (int i = 1; i <= cnt - 1; i++) {
      for (int j = 0; j <= i; j++)
        fc[j] = 0;
      for (int j = 1; j <= cnt - 1; j++) {
        for (int k = 1; k <= min(i, j); k++) {
          fc[k] += cm[j - k];
        }
        if (j <= i)
          fc[0]++;
        fc[0] -= cm[j - 1];
      }
      fc[0] += n - cm[cnt - 1] + 1;
      for (int j = 1; j <= i; j++)
        fc[j] -= cm[i - j];
      int sth = -fc[0];
      bool flag = true;
      for (int j = 1; j <= min(i, cnt - 2); j++) {
        now[j] = sth / fc[j];
        if (now[j] < 0 || now[j] >= k) {
          flag = false;
          break;
        }
        sth %= fc[j];
      }
      for (int j = min(i, cnt - 2) + 1; j <= cnt; j++)
        now[j] = -1;
      if (sth != 0 || now[1] == 0 || flag == false)
        continue;
      if (i == cnt - 1) {
        bool flag = false;
        for (int j = 1; j <= cnt - 2; j++) {
          if (now[j] > sw[j]) {
            flag = false;
            break;
          }
          if (now[j] < sw[j]) {
            flag = true;
            break;
          }
        }
        if (flag == false) {
          bool flag2 = true;
          for (int j = 1; j <= cnt - 2; j++)
            if (now[j] != sw[j]) {
              flag2 = false;
              break;
            }
          if (flag2)
            ans += k - 1 - sw[cnt - 1];
          else
            ans += k;
        }
      } else {
        bool flag = true;
        for (int j = 1; j <= cnt; j++) {
          if (now[j] > sw[j]) {
            flag = false;
            break;
          }
          if (now[j] < sw[j]) {
            flag = true;
            break;
          }
        }
        if (flag == false)
          ans++;
      }
    }
    printf("%lld\n", ans);
  }
}


// https://github.com/VaHiX/CodeForces/