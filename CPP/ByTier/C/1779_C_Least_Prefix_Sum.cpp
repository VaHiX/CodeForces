// Problem: CF 1779 C - Least Prefix Sum
// https://codeforces.com/contest/1779/problem/C

/*
Purpose: To find the minimum number of operations to make the prefix sum at index m the smallest among all prefix sums.
Approach:
- We process the array from index m onwards, maintaining a min-heap of negative elements.
- For every element that makes the current prefix sum negative, we flip the smallest negative element (if exists) to reduce the prefix sum.
- Then we process elements from m-2 down to 1, maintaining a max-heap of positive elements.
- For every element that makes the current prefix sum positive, we flip the largest positive element (if exists) to reduce the prefix sum.
Time Complexity: O(n log n) due to heap operations.
Space Complexity: O(n) for storing the array and heaps.
*/
#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;
#define f(length) for (ll i = 0; i < (length); i++)
#define f1(length) for (ll i = 1; i <= (length); i++)
#define AsFastAsIraqi                                                          \
  ios_base::sync_with_stdio(0);                                                \
  cin.tie(0);                                                                  \
  cout.tie(0);
#define AbuAli                                                                 \
  ios_base::sync_with_stdio(false);                                            \
  cin.tie(nullptr);                                                            \
  cout.tie(nullptr);
#define dd double
#define ll long long
#define counter cout << count << "\n";
#define YES cout << "YES" << "\n";
#define NO cout << "NO" << endl;
#define endl "\n"
#define vi vector<long long>
#define bb break;
#define all(a) a.begin(), a.end()
#define inv(a) a.rbegin(), a.rend()
#define mod 1000000007
void solve() {
  ll number, mubb;
  cin >> number >> mubb;
  int ary[number];
  f(number) { cin >> ary[i]; }
  ll suii = 0, count = 0;
  priority_queue<int, vector<int>, greater<int>> somet; // min-heap for negative elements
  for (int i = mubb; i < number; i++) {
    if (ary[i] < 0) {
      somet.push(ary[i]);
    }
    count += ary[i];
    while (count < 0) { // if prefix sum becomes negative, flip the smallest negative element
      ll SmallX = somet.top();
      somet.pop();
      SmallX = -1 * SmallX;
      count += (2 * SmallX);
      suii++;
    }
  }
  if (ary[mubb - 1] <= 0) {
    count = ary[mubb - 1];
  } else if (mubb != 1) {
    count = -1 * ary[mubb - 1];
    suii++;
  }
  priority_queue<int> somet23; // max-heap for positive elements
  for (int i = mubb - 2; i >= 1; i--) {
    if (ary[i] > 0) {
      somet23.push(ary[i]);
    }
    count += ary[i];
    while (count > 0) { // if prefix sum becomes positive, flip the largest positive element
      ll anotherX = somet23.top();
      somet23.pop();
      anotherX = -1 * anotherX;
      count += (2 * anotherX);
      suii++;
    }
  }
  cout << suii << endl;
}
int main() {
  AbuAli AsFastAsIraqi ll t = 1;
  cin >> t;
  while (t--) {
    solve();
  }
}


// https://github.com/VaHiX/CodeForces/