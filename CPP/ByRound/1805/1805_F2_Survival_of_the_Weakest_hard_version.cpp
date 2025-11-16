// Problem: CF 1805 F2 - Survival of the Weakest (hard version)
// https://codeforces.com/contest/1805/problem/F2

/*
Purpose: This code solves the "Survival of the Weakest (hard version)" problem. 
         It repeatedly applies a function F to an array of integers, where F transforms 
         the array by computing all pairwise sums and keeping the smallest n-1 of them.
         The process continues until a single element remains, which is then returned modulo 10^9 + 7.

Algorithm:
- The function F computes all pairwise sums of elements in the array, sorts them, and keeps the n-1 smallest.
- The process is applied iteratively, updating the array until a single element remains.
- Special optimizations are used to avoid redundant computation and improve performance.

Time Complexity: O(n^2 * log(n)) where n is the size of the initial array.
Space Complexity: O(n^2) due to intermediate arrays storing pairwise sums.
*/

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
const int M = 1000000007;
long long ans = 0;
int real_len = 0;

// Fast exponentiation function to compute (a^x) % M
long long binpow(long long a, int x) {
  long long ans0 = 1;
  while (x) {
    if (x % 2) {
      ans0 *= a;
      ans0 %= M;
    }
    a *= a;
    a %= M;
    x /= 2;
  }
  return ans0;
}

// Process the current array b, add contribution of minimum element to ans and subtract it from all elements
void chill(vector<int> &b) {
  int mn = b[0];
  ans += (int)((long long)mn * binpow(2, real_len - 1) % M);
  if (ans >= M)
    ans -= M;
  for (auto &x : b)
    x -= mn;
}

// Function F that transforms the array b according to the problem definition
void F(vector<int> &b, int sub = 0) {
  --real_len;
  vector<int> cnd;
  // Generate all pairwise sums
  for (int i = 0; i < b.size(); i++) {
    for (int j = i + 1; j < b.size(); j++) {
      if (i * j >= b.size())
        break;
      cnd.push_back(b[i] + b[j]);
    }
  }
  sort(cnd.begin(), cnd.end());
  vector<int> b2((int)b.size() - sub);
  for (int i = 0; i < (int)b.size() - sub; i++)
    b2[i] = cnd[i];
  chill(b2);
  b = b2;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++)
    cin >> a[i];
  sort(a.begin(), a.end());
  int L = 64;
  vector<int> b(min(n, L));
  for (int i = 0; i < min(n, L); i++)
    b[i] = a[i];
  real_len = n;
  chill(b);
  while (b.size() < real_len) {
    if (b[1] + b[2] > b.back()) {
      F(b, 1);
      F(b, 1);
    } else
      F(b);
  }
  while (real_len > 1)
    F(b, 1);
  ans += b[0];
  ans %= M;
  cout << ans << '\n';
}


// https://github.com/VaHiX/CodeForces/