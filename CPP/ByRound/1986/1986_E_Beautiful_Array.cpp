// Problem: CF 1986 E - Beautiful Array
// https://codeforces.com/contest/1986/problem/E

/*
 * Problem: Beautiful Array
 * 
 * Algorithm: 
 *  - For each element in the array, compute its remainder when divided by k.
 *  - Group elements by their remainder and sort them.
 *  - For elements with the same remainder, calculate the number of operations needed 
 *    to convert one to another, and accumulate the total operations required.
 *  - For elements that form symmetric pairs (in the palindrome context), 
 *    we also consider how to balance operations to make the array palindromic.
 * 
 * Time Complexity: O(n * log(n)) due to sorting and processing elements.
 * Space Complexity: O(n) for storing the array elements and auxiliary arrays.
 */

#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
#define f first
#define s second

int main() {
  int t;
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cin >> t;
  while (t--) {
    int n, k;
    cin >> n >> k;
    long long ans = 0;
    int flag = 0;
    vector<int> a(n);
    vector<pair<int, int>> b(n);
    for (int i = 0; i < n; i++) {
      cin >> a[i];
      b[i] = {a[i] % k, a[i]};
    }
    sort(b.begin(), b.end());
    int temp = b[0].f, maxi = 0, tec = 0, index = 0;
    for (int i = 0; i < n; i++) {
      if (b[i].f != temp) {
        temp = b[i].f;
        maxi = 0;
        tec = 0;
        index = i;
      }
      if (i + 1 < n && b[i].f == b[i + 1].f) {
        ans += (b[i + 1].s - b[i].s) / k;
        tec += (b[i + 1].s - b[i].s) / k;
        maxi = max(maxi, (b[i + 1].s - b[i].s));
        i++;
      } else {
        if (i - index > 1) {
          ans = ans - tec;
          int help = 0;
          vector<int> sum1(i - index + 2), sum2(i - index + 2);
          sum1[0] = 0;
          sum2[0] = 0;
          for (int j = index; j <= i; j++) {
            if (j % 2 == 0) {
              sum1[j - index + 1] = sum1[j - index] + b[j].s;
              sum2[j - index + 1] = sum2[j - index];
            } else {
              sum1[j - index + 1] = sum1[j - index];
              sum2[j - index + 1] = sum2[j - index] + b[j].s;
            }
          }
          int mini = 999999999, mini2 = 99999999;
          for (int j = index; j <= i; j += 2) {
            mini = min(mini, abs(sum1[j - index] - sum2[j - index] +
                                 sum2[i - index + 1] - sum2[j - index + 1] -
                                 sum1[i - index + 1] + sum1[j - index + 1]));
          }
          ans += mini / k;
        }
        flag += 1;
      }
    }
    if ((n % 2 == 0 && flag != 0) || (n % 2 == 1 && flag > 1)) {
      cout << -1 << "\n";
    } else {
      cout << ans << "\n";
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/