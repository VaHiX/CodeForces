// Problem: CF 1938 H - Pho Restaurant
// https://codeforces.com/contest/1938/problem/H

/*
 * Problem: Pho Restaurant
 * Purpose: Minimize the number of contestants to move so that all contestants at each table order the same dish.
 * 
 * Algorithm:
 * 1. For each table, count the number of '0's (phở tái) and '1's (phở chín).
 * 2. For each table, we determine if it is possible to make all contestants at that table order either phở tái or phở chín.
 * 3. We compute the minimum number of moves required by considering two scenarios:
 *    - All tables are made to order phở tái (if possible).
 *    - All tables are made to order phở chín (if possible).
 * 4. If no consistent choice is possible for one of the two dishes, we calculate a minimal cost of shifting tables to satisfy the constraint.
 * 
 * Time Complexity: O(sum of string lengths) - We process each character once.
 * Space Complexity: O(n) - Where n is the number of tables, for storing counts and flags.
 */

#include <algorithm>
#include <iostream>
#include <string>

#define all(v) v.begin(), v.end()
#define compress(v) v.erase(unique(all(v)), v.end())
#define newCor(v, x) lower_bound(all(v), x) - v.begin()
#define maxx(a, b) a = max(a, b)
#define minn(a, b) a = min(a, b)
#define for0(i, n) for (int i = 0; i < n; i++)
#define for1(i, n) for (int i = 1; i <= n; i++)
#define forr(i, l, r) for (int i = l; i <= r; i++)
using namespace std;
typedef long long ll;
const int INF = (int)1e9;
int N;
int Cnt[100000][2]; // Count of '0' and '1' for each table
bool Flag[2];       // Flag[0] = can make all tables choose '0', Flag[1] = can make all tables choose '1'
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> N;
  int ans = 0;
  for0(i, N) {
    string s;
    cin >> s;
    for (char c : s)
      Cnt[i][c - '0']++; // Count 0s and 1s for table i
    if (Cnt[i][0] <= Cnt[i][1])
      Flag[0] = true;  // Table i can be made to all order '0'
    if (Cnt[i][0] >= Cnt[i][1])
      Flag[1] = true;  // Table i can be made to all order '1'
    ans += min(Cnt[i][0], Cnt[i][1]); // Minimum moves needed to make this table consistent
  }
  if (Flag[0] && Flag[1]) {
    // Both options are viable, return the minimal moves computed
    cout << ans;
    return 0;
  }
  int x = Flag[0]; // Decide which dish to aim for (0 or 1)
  bool flag = true;
  for0(i, N) {
    if (Cnt[i][!x]) // If any table has non-zero count of the dish we don't want
      flag = false;
  }
  if (flag) {
    // If all tables can be forced to the desired dish, return ans
    cout << ans;
    return 0;
  }
  int mn = INF;
  for0(i, N) minn(mn, Cnt[i][x] - Cnt[i][!x]); // Find minimum balance to shift
  cout << ans + mn; // Return final result
  return 0;
}


// https://github.com/VaHiX/CodeForces/