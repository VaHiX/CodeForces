// Problem: CF 1471 B - Strange List
// https://codeforces.com/contest/1471/problem/B

/*
B. Strange List
Algorithms/Techniques: Simulation with queue-like behavior using vector
Time Complexity: O(n * log_x(max(a_i))) where n is the initial array size and max(a_i) is the maximum element in the array
Space Complexity: O(n * log_x(max(a_i))) for storing the expanded array elements

The robot processes each element of the array:
- If the current element q is divisible by x, it adds x copies of q/x to the end of the array.
- If not divisible, the robot shuts down.
We simulate this process to compute the final sum of all elements in the array.

Input: 
- t test cases
- For each case: n (size of array), x (divisor)
- Array a of size n

Output:
- Sum of all elements after processing
*/

#include <cstdio>
#include <vector>
#include <utility>

typedef long long ll;
int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, x;
    scanf("%lld %lld", &n, &x);
    std::vector<std::pair<ll, ll>> a(n); // pair: {value, count}
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &a[p].first); // read value
      a[p].second = 1; // initial count is 1
    }
    ll idx(0), res(0);
    bool add(true);
    while (idx < a.size()) {
      ll q = a[idx].first;     // current element value
      ll y = a[idx].second;    // how many copies of this value exist
      res += q * y;            // add contribution to sum
      if (q % x) {             // if not divisible by x
        add = false;           // stop adding new elements
      }
      if (add) {
        a.push_back(std::make_pair(q / x, x * y)); // add x copies of q/x
      }
      ++idx;
    }
    printf("%lld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/