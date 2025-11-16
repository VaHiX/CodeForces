// Problem: CF 2162 D - Beautiful Permutation
// https://codeforces.com/contest/2162/problem/D

/*
Purpose: This code solves the problem of finding the range [l, r] that was modified in a permutation.
The key idea is to use binary search on the range and compare sums from the original and modified arrays.
Algorithm:
- The difference between the sum of the entire modified array and the sum of the original array gives the length of the modified range.
- Binary search is used to find the exact start of the modified range.
- By querying prefix sums, we can determine how much of the range has been shifted.

Time Complexity: O(n log n) due to binary search and multiple queries.
Space Complexity: O(1) as we only use a constant amount of extra space.
*/

#include <iostream>
#include <utility>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef long double LD;
typedef pair<LL, LL> PII;

void solve() {
  int n;
  cin >> n;
  // Calculate the sum of original permutation (1+2+...+n)
  int sum = n * (n + 1) / 2;
  
  // Query the sum of the entire modified array
  cout << "2 1 " << n << endl;
  int ans;
  cin >> ans;
  
  // The difference gives the length of the modified range (since each element in the range increases by 1)
  int len = ans - sum;
  
  // Binary search for the position of the modified range
  int l = 1;
  int r = n;
  while (l < r) {
    int mid = (l + r) / 2;
    int ans1, ans2;
    
    // Query the sum of the prefix [1, mid] from the original array
    cout << "1 1 " << mid << endl;
    cin >> ans1;
    
    // Query the sum of the prefix [1, mid] from the modified array
    cout << "2 1 " << mid << endl;
    cin >> ans2;
    
    // If the difference is equal to the expected length, we found a potential start
    if (ans2 - ans1 == len)
      r = mid;
    else
      l = mid + 1;
  }
  
  // Output the range [l - len + 1, l] which corresponds to [l, r] that was modified
  cout << "! " << l - len + 1 << ' ' << l << endl;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int t = 1;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/