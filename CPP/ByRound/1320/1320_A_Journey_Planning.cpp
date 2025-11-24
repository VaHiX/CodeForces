// Problem: CF 1320 A - Journey Planning
// https://codeforces.com/contest/1320/problem/A

#include <cstdio>
#include <map>
typedef long long ll;
int main() {
  ll n;
  scanf("%lld", &n);
  std::map<ll, ll> m; // Map to store the maximum beauty sum for each group (b[i] - i)
  ll mx(0); // Variable to keep track of the maximum beauty sum found so far
  for (ll p = 0; p < n; p++) { // Iterate through each city
    ll b;
    scanf("%lld", &b);
    // Key insight: For a valid sequence, if c_{i+1} - c_i = b[c_{i+1}] - b[c_i],
    // then (c_{i+1} - b[c_{i+1}]) = (c_i - b[c_i])
    // This means all cities in the same group have the same value of (index - b[index])
    m[b - p] += b; // Add current city's beauty to the group it belongs to
    mx = (mx > m[b - p]) ? mx : m[b - p]; // Update maximum beauty sum if needed
  }
  printf("%lld\n", mx); // Print the maximum beauty sum found
  return 0;
}
/*
Flowerbox:
Problem: Journey Planning
Description: Tanya wants to visit cities in strictly increasing order such that for any two consecutive visited cities, the constraint c_{i+1} - c_i = b[c_{i+1}] - b[c_i] holds. This is equivalent to saying that all cities in a valid sequence belong to the same group defined by (index - b[index]).
Algorithms/Techniques: 
- Grouping based on (index - beauty) values
- Dynamic programming using a map to track maximum sum for each group
Time Complexity: O(n log n) due to map operations
Space Complexity: O(n) for storing the map and input
*/

// https://github.com/VaHiX/codeForces/