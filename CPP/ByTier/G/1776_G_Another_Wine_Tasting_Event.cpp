// Problem: CF 1776 G - Another Wine Tasting Event
// https://codeforces.com/contest/1776/problem/G

/*
Code Purpose:
This code solves the problem of finding the maximum number of white wines (W) that can be tasted 
by a critic in a valid interval assignment. It uses a sliding window technique to compute the 
maximum number of white wines in any contiguous subarray of length n, which represents the minimum 
required interval size for each critic.

Algorithm:
Sliding window technique
- First compute the count of white wines in the first window of size n.
- Then slide the window one position at a time, updating the count by adding the new element 
  and removing the old element from the count.
- Keep track of the maximum count encountered.

Time Complexity: O(2*n - 1) = O(n)
Space Complexity: O(1)

*/
#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>

using namespace std;
#define sz(x) (int)x.size()
#define all(v) v.begin(), v.end()
#define pb push_back
#define pp pop_back
#define f first
#define s second
typedef long long ll;
typedef long double ld;
ld pi = acos(-1);
ld eps = 1e-9;
ll mod = 1e9 + 7;
void fast() {
  cin.sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
}
void sam07a() {
  int n;
  string s;
  cin >> n >> s;
  int ans = 0, cnt = 0;
  // Count white wines in the first window of size n
  for (int i = 0; i < n; i++) {
    if (s[i] == 'W')
      cnt++;
  }
  ans = max(ans, cnt);
  int l = 0;
  // Slide the window over the rest of the string
  for (int i = n; i < sz(s); i++) {
    if (s[i] == 'W')
      cnt++;  // Add new element to window
    if (s[l] == 'W')
      cnt--;  // Remove old element from window
    l++;
    ans = max(ans, cnt);  // Update maximum white wine count
  }
  cout << ans << "\n";
}
int main() {
  fast();
  int ts = 1;
  for (int tt = 1; tt <= ts; tt++) {
    sam07a();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/