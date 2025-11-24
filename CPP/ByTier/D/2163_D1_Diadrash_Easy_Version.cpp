// Problem: CF 2163 D1 - Diadrash (Easy Version)
// https://codeforces.com/contest/2163/problem/D1

/*
 * Problem: D1. Diadrash (Easy Version)
 * 
 * Purpose: Find the maximum MEX among all given ranges in a hidden permutation.
 * 
 * Algorithm:
 * - Use binary search on the answer (MEX value from 0 to n)
 * - For each candidate MEX value k, check if there exists a range where the MEX is exactly k
 * - To check, find the leftmost position Lk such that MEX[Lk, n] >= k and rightmost position Rk such that MEX[1, Rk] >= k
 * - If Lk <= Rk, then there exists a subarray which contains all elements from 0 to k-1, so MEX of that subarray is k
 * 
 * Time Complexity: O(n * log^2(n) * q)
 * Space Complexity: O(q)
 */

#include <iostream>
#include <utility>
#include <vector>

using namespace std;

// Function to query MEX of subarray [l, r]
int query(int l, int r) {
  cout << "? " << l << " " << r << endl;
  int x;
  cin >> x;
  return x;
}

// Find leftmost position where MEX[pos, n] >= k
int find_L(int k, int n) {
  if (k == 0)
    return 1;
  int low = 1, high = n;
  int res = 0;
  while (low <= high) {
    int mid = (low + high) / 2;
    int m = query(mid, n);
    if (m >= k) {
      res = mid;
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }
  return res;
}

// Find rightmost position where MEX[1, pos] >= k
int find_R(int k, int n) {
  if (k == 0)
    return 0;
  int low = 1, high = n;
  int res = n + 1;
  while (low <= high) {
    int mid = (low + high) / 2;
    int m = query(1, mid);
    if (m >= k) {
      res = mid;
      high = mid - 1;
    } else {
      low = mid + 1;
    }
  }
  return res;
}

// Check if there exists a range where MEX is exactly k
bool check(int k, const vector<pair<int, int>> &ranges, int n) {
  if (k == 0)
    return true;
  int Lk = find_L(k, n);
  int Rk = find_R(k, n);
  if (Lk > Rk)
    return false;
  for (auto [l, r] : ranges) {
    if (l <= Lk && r >= Rk)
      return true;
  }
  return false;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  for (int test = 0; test < t; ++test) {
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> ranges(q);
    for (int i = 0; i < q; ++i) {
      cin >> ranges[i].first >> ranges[i].second;
    }
    int low = 0, high = n;
    while (low < high) {
      int mid = (low + high + 1) / 2;
      if (check(mid, ranges, n)) {
        low = mid;
      } else {
        high = mid - 1;
      }
    }
    cout << "! " << low << endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/