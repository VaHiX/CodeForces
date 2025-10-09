// Problem: CF 2149 A - Be Positive
// https://codeforces.com/contest/2149/problem/A

#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;
#define ll long long int

/*
Algorithm: A. Be Positive
Purpose: To find the minimum number of operations to make the product of array elements strictly positive.
Techniques:
- Count frequency of elements (-1, 0, 1) using a map.
- If count of -1 is odd, we need at least one more 1 or 0 to be turned into 1 to balance the sign.
- If count of -1 is even, we only need to account for zeros.

Time Complexity: O(n) per test case, where n is the size of array.
Space Complexity: O(1), since the map stores at most 3 keys (-1, 0, 1).
*/

int main() {
  ll tc;
  cin >> tc;
  while (tc--) {
    ll n;
    cin >> n;
    vector<ll> v(n);
    map<ll, ll> mp; // Count frequency of each element
    for (int i = 0; i < n; i++) {
      cin >> v[i];
      mp[v[i]]++; // Store frequency
    }
    if (mp[-1] % 2 != 0) // If odd number of -1s
      cout << 2 + mp[0] << endl; // Need 2 operations to make one -1 -> 1, plus ops for zeros
    else
      cout << mp[0] << endl; // Even count of -1s, just need to cover zeros
  }
}

// https://github.com/VaHiX/CodeForces/