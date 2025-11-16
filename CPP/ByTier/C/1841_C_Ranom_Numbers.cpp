// Problem: CF 1841 C - Ranom Numbers
// https://codeforces.com/contest/1841/problem/C

/*
 * Problem: C. Ranom Numbers
 * 
 * Purpose: 
 *   Given a string of Ranom digits (A-E), compute the maximum possible value after changing at most one digit.
 *   Ranom digits have values: A=1, B=10, C=100, D=1000, E=10000.
 *   A digit contributes positively if no greater digit exists to its right.
 *   Otherwise, it contributes negatively.
 *   
 * Algorithm:
 *   1. Preprocess suffix maximums to determine sign of each digit.
 *   2. For each digit, compute the maximum gain possible by changing it to another digit.
 *   3. Use prefix/suffix arrays to track how many times each digit is positive/negative.
 *   
 * Time Complexity:
 *   O(n * 5 * 5) = O(n) where n is the length of the string.
 *   For each position, we consider up to 5 possible digit changes, and for each,
 *   we scan a limited number of digits.
 *   
 * Space Complexity:
 *   O(n + 5) = O(n) for the string and auxiliary arrays.
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using ll = long long;

// Value mapping for Ranom digits A to E
ll val[5] = {1ll, 10ll, 100ll, 1000ll, 10000ll};

void solve() {
  string a;
  cin >> a;
  int n = a.size();
  a = ' ' + a;  // Add padding to make indexing from 1
  vector<int> suf(n + 2);  // suffix max array
  ll ans = 0;  // initial result value
  for (int i = n; i >= 1; i--) {
    int now = a[i] - 'A';
    suf[i] = max(suf[i + 1], now);  // suffix maximum
    if (now < suf[i])  // if current digit is smaller than the max to its right
      ans -= val[now];  // subtract its value
    else
      ans += val[now];  // add its value
  }
  // Reassign suffix max properly for later use
  for (int i = 1; i <= n; i++)
    suf[i] = suf[i + 1];
  
  // index tracking: idx[digit][0] = first occurrence, idx[digit][1] = last occurrence
  int idx[5][2];
  for (int i = 0; i < 5; i++)
    idx[i][0] = idx[i][1] = 0;
  for (int i = 1; i <= n; i++) {
    int now = a[i] - 'A';
    if (idx[now][0] == 0)
      idx[now][0] = i;
    idx[now][1] = i;
  }

  // pos[i] and neg[i]: count of how many times digit i contributes positively/negatively
  vector<ll> pos(5, 0), neg(5, 0);
  ll add = 0;  // maximum gain that can be achieved by one change
  for (int i = 1; i <= n; i++) {
    int now = a[i] - 'A';
    // Only evaluate on first or last occurrence of the digit for optimization
    if (i == idx[now][1] || i == idx[now][0]) {
      ll mx = 0;
      // Try changing current digit to all other digits
      for (int j = 0; j < 5; j++) {
        ll cur = val[j];  // value of new digit
        if (now < suf[i])
          cur += val[now];  // if original was negative, add its value back
        else
          cur -= val[now];  // if original was positive, subtract its value
        
        // Adjust contributions for digits to the left of j
        if (j < now) {
          for (int k = now - 1; k >= max(suf[i], j); k--) {
            cur += 2ll * neg[k] * val[k];  // account for changes in sign
          }
        } else if (j > now) {
          for (int k = max(suf[i], now); k < j; k++) {
            cur -= 2ll * pos[k] * val[k];  // account for changes in sign
          }
        }
        mx = max(cur, mx);  // maximum gain we can get
      }
      add = max(add, mx);  // update best gain
    }
    // Update current contributions
    if (now < suf[i])
      neg[now]++;
    else
      pos[now]++;
    // Reset contributions for digits less than current
    for (int j = now - 1; j >= 0; j--) {
      neg[j] = 0;
    }
  }
  add = max(0ll, add);  // ensure we don't decrease the value
  cout << ans + add << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int _;
  cin >> _;
  while (_--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/