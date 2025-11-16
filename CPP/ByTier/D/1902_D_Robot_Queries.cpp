// Problem: CF 1902 D - Robot Queries
// https://codeforces.com/contest/1902/problem/D

/*
Algorithm: Preprocessing + Binary Search
Time Complexity: O(n log n + q log n)
Space Complexity: O(n)

The solution preprocesses all positions the robot visits during the original
command sequence. For each query, it uses binary search to check if there's a
valid position that matches the requirements. When the substring [l,r] is
reversed, the final position is calculated using the formula: final_x = end_x +
start_x - target_x final_y = end_y + start_y - target_y This transformation
allows checking if the target position can be reached with the reversed
substring.
*/
#include <algorithm>
#include <iostream>
#include <map>
#include <stdio.h>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

using namespace std;

#define Setprecision 10
#define between '\n'
#define __int128 long long
template <typename T> struct is_char {
  static constexpr bool value =
      (std::is_same<T, char>::value || std::is_same<T, signed char>::value ||
       std::is_same<T, unsigned char>::value);
};
template <typename T> struct is_integral_ex {
  static constexpr bool value =
      (std::is_integral<T>::value || std::is_same<T, __int128>::value) &&
      !is_char<T>::value;
};
template <typename T> struct is_floating_point_ex {
  static constexpr bool value =
      std::is_floating_point<T>::value || std::is_same<T, __float128>::value;
};

pair<int, int> v[200001];
int main() {
  int n, q;
  cin >> n >> q;
  map<pair<int, int>, vector<int>> mp;
  mp[{0, 0}].emplace_back(0);
  int x = 0, y = 0;
  for (int _ = 1; _ <= n; _++) {
    char ch;
    cin >> ch;
    if (ch == 'U')
      y++;
    if (ch == 'D')
      y--;
    if (ch == 'L')
      x--;
    if (ch == 'R')
      x++;
    mp[{x, y}].emplace_back(_);
    v[_] = {x, y};
  }
  while (q--) {
    int x, y, l, r;
    cin >> x >> y >> l >> r;
    if (mp.count({x, y})) {
      if (mp[{x, y}].back() >= r) {
        cout << "YES" << endl;
        continue;
      }
      if (mp[{x, y}][0] < l) {
        cout << "YES" << endl;
        continue;
      }
    }
    x = v[r].first + v[l - 1].first - x;
    y = v[r].second + v[l - 1].second - y;
    if (mp.count({x, y})) {
      auto it = lower_bound(mp[{x, y}].begin(), mp[{x, y}].end(), l);
      if (it != mp[{x, y}].end() && *it <= r) {
        cout << "YES" << endl;
        continue;
      }
    }
    cout << "NO" << endl;
  }
}

// https://github.com/VaHiX/CodeForces/