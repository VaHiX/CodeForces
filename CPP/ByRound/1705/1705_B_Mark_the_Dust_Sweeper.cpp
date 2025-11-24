// Problem: CF 1705 B - Mark the Dust Sweeper
// https://codeforces.com/contest/1705/problem/B

/*
B. Mark the Dust Sweeper
Algorithm: Greedy approach to move dust from left to right.
Time Complexity: O(n) per test case
Space Complexity: O(1)

The problem involves moving all dust from the first n-1 rooms to the nth room,
using a specific operation that transfers 1 unit of dust from a room i to room j 
where all rooms between i and j have strictly positive dust levels.

Key idea:
We simulate the process from left to right. For each room, if it contains dust,
we move all of it to the next room using operations such that we always keep
the intermediate rooms positive (this is ensured by our greedy approach).

The algorithm:
- We maintain a running sum (`res`) representing how much dust has been moved so far.
- As we process each room from left to right, if it has dust (x > 0), we add x to res.
- If the current room has no dust but there is some accumulated dust in `res`, 
  we add one operation (to move dust to the next room).

This greedy approach mimics the correct strategy of collecting and moving dust
as efficiently as possible from left to right.
*/

#include <cstdio>
typedef long long ll;
int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    ll x(0), res(0);
    for (ll p = 1; p < n; p++) {
      scanf("%lld", &x);
      res += x ? x : (res > 0); // Add dust if present or increment operation count if needed
    }
    scanf("%lld", &x);
    printf("%lld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/