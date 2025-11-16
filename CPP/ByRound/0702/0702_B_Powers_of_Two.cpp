// Problem: CF 702 B - Powers of Two
// https://codeforces.com/contest/702/problem/B

/*
Algorithm: Powers of Two
Techniques:
  - Precompute all possible powers of 2 up to 2 * 10^9
  - Use a hash map to count occurrences of each number
  - For each number, check how many numbers can sum up to a power of 2
  - Avoid double counting by adjusting for duplicate elements

Time Complexity: O(n * log(10^9)) where n is the number of elements
Space Complexity: O(n + log(10^9)) for the map and precomputed powers

*/
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>
#include <vector>

typedef long long int ll;
using namespace std;

int main() {
  ll i, j, k;
  ll n, m;
  ll x, y, z;
  vector<ll> p2; // Store all powers of 2 up to 2 * 10^9
  n = 2;
  while (n <= (2 * 1000000000)) {
    p2.push_back(n);
    n *= 2;
  }
  cin >> n;
  m = 0;
  map<ll, ll> mp; // Map to store frequency of each number
  ll *a = new ll[n];
  for (i = 0; i < n; i++) {
    cin >> a[i];
    m = max(m, a[i]);
    mp[a[i]]++; // Count frequency of each number
  }
  ll cnt = 0;
  for (i = 0; i < n; i++) {
    k = a[i];
    for (j = 0; j < p2.size(); j++) {
      x = p2[j] - k; // Find required complement to form a power of 2
      if (mp[x]) {   // If complement exists
        if (x == k)
          cnt +=
              (mp[x] -
               1); // If complement is same, subtract 1 to avoid counting self
        else
          cnt += mp[x]; // Add frequency of complement
      }
    }
  }
  cout << cnt / 2 << endl; // Divide by 2 to avoid double counting pairs
  return 0;
}

// https://github.com/VaHiX/CodeForces/