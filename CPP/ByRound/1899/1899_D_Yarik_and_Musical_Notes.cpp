// Problem: CF 1899 D - Yarik and Musical Notes
// https://codeforces.com/contest/1899/problem/D

/*
Algorithm: Count pairs (i, j) where i < j and a[i] = a[j]
Techniques:
  - Sort the array to group identical elements together
  - For each group of identical elements of size k, the number of pairs is C(k,
2) = k * (k - 1) / 2
  - Time complexity: O(n log n) due to sorting
  - Space complexity: O(1) excluding input storage

The problem is essentially asking for the count of pairs (i,j) such that b_i^b_j
= b_j^b_i. Since b_i = 2^a_i and b_j = 2^a_j, this is equivalent to 2^(a_i *
a_j) = 2^(a_j * a_i). This always holds, so the condition reduces to counting
pairs of equal elements in the array.
*/
#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <string>
#include <type_traits>
#include <vector>
using namespace std;

void solve();
int main() {
  int t = 1;
  cin >> t;
  while (t--)
    solve();
}
void solve() {
  int n;
  cin >> n;
  vector<int> a;
  for (int x = 0; x < n; x++) {
    int u;
    cin >> u;
    a.emplace_back(
        max(u, 2)); // Ensure values are at least 2 as per problem statement,
                    // but seems to be a bug in original logic
  }
  sort(a.begin(), a.end());
  long long ans = 0;
  for (int x = 0; x < n;) {
    int y = x;
    for (; y < n && a[y] == a[x]; y++)
      ;
    ans += 1ll * (y - x) * (y - x - 1) /
           2; // Calculate combinations of pairs within group
    x = y;
  }
  cout << ans << endl;
}

// https://github.com/VaHiX/CodeForces/