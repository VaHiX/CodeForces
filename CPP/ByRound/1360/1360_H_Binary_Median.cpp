// Problem: CF 1360 H - Binary Median
// https://codeforces.com/contest/1360/problem/H

/*
H. Binary Median
Algorithms/Techniques: Binary search on answer, sorting, bit manipulation

Time Complexity: O(n * m + n * log(n)) per test case, where n is the number of strings and m is the length of each string.
Space Complexity: O(n * m) per test case for storing the binary strings.

The problem asks to find the median of all remaining binary strings after removing n given strings from the set of all 2^m binary strings of length m.
We use a technique where we sort the removed strings and then do a binary search or direct computation to determine the median.
*/

#include <algorithm>
#include <bitset>
#include <iostream>
#include <string>

typedef long long ll;
using namespace std;

void solve() {
  int n, m;
  cin >> n >> m;
  ll a[n];
  string s;
  
  // Calculate initial estimate of median using formula
  ll ans = ((1LL << m) - n - 1) / 2;  // This calculates the middle index in sorted list of remaining strings
  
  for (int i = 0; i < n; i++) {
    cin >> s;
    a[i] = bitset<64>(s).to_ullong();  // Convert binary string to unsigned long long integer
  }
  
  sort(a, a + n);  // Sort the removed strings
  
  for (auto i : a)
    ans += (i <= ans);  // Adjust median by counting how many removed strings are <= current ans
  
  cout << bitset<64>(ans).to_string().substr(64 - m) << endl;  // Convert back to binary string and print
}

int main() {
  int t;
  cin >> t;
  while (t--)
    solve();
}


// https://github.com/VaHiX/codeForces/