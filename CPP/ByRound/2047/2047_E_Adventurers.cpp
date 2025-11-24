// Problem: CF 2047 E - Adventurers
// https://codeforces.com/contest/2047/problem/E

/*
Algorithm: 2D coordinate compression + Fenwick Tree (Binary Indexed Tree) + Binary Search
Time Complexity: O(n^2 * log n) per test case
Space Complexity: O(n) 

The solution uses coordinate compression for the y-coordinates and a Fenwick tree to efficiently 
count points in different quadrants. It performs a binary search on possible dividing points 
to maximize the minimum number of cities assigned to any merchant.
*/

#include <algorithm>
#include <iostream>
#include <utility>

using namespace std;
using node = pair<int, int>;
const int maxn = 2e5 + 5;
int t, n, ma, sum, b[maxn], mp[maxn], s[maxn][2];
node a[maxn], ans;

// Update Fenwick Tree: add 1 to position x in dimension f
void A(int f, int x, int c) {
  for (; x <= n; x += x & -x) {
    s[x][f] += c;
  }
}

// Query Fenwick Tree: sum from 1 to x in dimension f
int Q(int f, int x) {
  int c = 0;
  for (; x >= 1; x -= x & -x) {
    c += s[x][f];
  }
  return c;
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  for (cin >> t; t--;) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> a[i].first >> a[i].second;
    }
    fill(s[1], s[n + 1], 0);
    ma = sum = 0, b[1] = 1;
    
    // Sort points by y-coordinate
    sort(a + 1, a + n + 1, [](node x, node y) { return x.second < y.second; });
    
    // Coordinate compression for y-coordinates
    for (int i = 2; i <= n; i++) {
      b[i] = b[i - 1] + (a[i].second != a[i - 1].second);
    }
    
    // Assign compressed y-coordinate to original points and update Fenwick tree
    for (int i = 1; i <= n; i++) {
      mp[b[i]] = a[i].second, a[i].second = b[i];
      A(0, a[i].second, 1);
    }
    
    // Sort by x-coordinate
    sort(a + 1, a + n + 1);
    
    // Process points from right to left (highest x to lowest)
    for (int i = n; i > 1; i--) {
      A(1, a[i].second, 1), A(0, a[i].second, -1);
      
      // Only consider x-coordinate changes
      if (a[i].first != a[i - 1].first) {
        // Binary search on y-coordinate to find optimal splitting point
        for (int l = 1, r = n + 1; l < r;) {
          int mid = (l + r) / 2;
          
          // Count cities in each quadrant
          int b1 = Q(1, mid - 1) - Q(1, 0);  // Quadrant 1: x >= x0, y >= y0
          int b2 = Q(0, mid - 1) - Q(0, 0);  // Quadrant 2: x < x0, y >= y0
          int b3 = n - i + 1 - b1;           // Quadrant 3: x >= x0, y < y0
          int b4 = i - 1 - b2;               // Quadrant 4: x < x0, y < y0
          
          // Update maximum minimum count
          if (min({b1, b2, b3, b4}) > ma) {
            ma = min({b1, b2, b3, b4}), ans = {a[i].first, mp[mid]};
          }
          
          // Binary search adjustment
          (min(b1, b2) < min(b3, b4) ? l = mid + 1 : r = mid);
        }
      }
    }
    
    cout << ma << '\n';
    cout << ans.first << ' ' << ans.second << '\n';
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/