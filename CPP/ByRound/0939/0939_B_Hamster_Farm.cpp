// Problem: CF 939 B - Hamster Farm
// https://codeforces.com/contest/939/problem/B

/*
Code Purpose:
This program determines the optimal type and number of boxes to buy for transporting hamsters.
Each box must be completely filled, and Dima can only buy boxes of one type to get a discount.
The goal is to maximize the number of hamsters transported.

Algorithms/Techniques:
- Greedy approach: For each box type, calculate how many hamsters can be transported
  by dividing total hamsters by box capacity and multiplying back by capacity.
- Keep track of the maximum number of hamsters that can be transported and
  the corresponding box type.

Time Complexity: O(K), where K is the number of box types.
Space Complexity: O(1), only using a constant amount of extra space.
*/

#include <cstdio>
typedef long long ll;
int main() {
  ll n, k;
  scanf("%lld %lld", &n, &k);
  ll mx(0), cnt(0), w(1);  // mx: max hamsters transported, cnt: number of boxes, w: box type
  for (long p = 1; p <= k; p++) {  // iterate through each box type
    ll x;
    scanf("%lld", &x);
    ll num = x * (n / x);  // calculate how many hamsters can be transported with this box type
    if (num > mx) {  // if this is better than previous best
      mx = num;
      cnt = (n / x);  // number of boxes needed
      w = p;  // store the box type
    }
  }
  printf("%lld %lld\n", w, cnt);  // output the best box type and count
  return 0;
}


// https://github.com/VaHiX/CodeForces/