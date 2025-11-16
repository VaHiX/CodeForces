// Problem: CF 1519 A - Red and Blue Beans
// https://codeforces.com/contest/1519/problem/A

/*
A. Red and Blue Beans
Algorithms/Techniques: Mathematical analysis and inequality checking

Time Complexity: O(t), where t is the number of test cases
Space Complexity: O(1)

The problem asks whether we can distribute r red and b blue beans into packets such that:
1. Each packet has at least one red and one blue bean.
2. The absolute difference between red and blue beans in each packet is at most d.

Key insight:
- If we distribute all beans optimally, the maximum difference occurs when we pack as few beans as possible per packet.
- Let diff = r - b (assuming r >= b without loss of generality).
- For a valid distribution, it must be possible to split r and b into packets where each has difference <= d.
- The key check is whether:
  * d * b >= diff: The total extra red beans can be distributed among blue beans with allowed difference
  * d * r >= -diff: The total extra blue beans can be distributed among red beans with allowed difference
*/

#include <cstdio>
typedef long long ll;
int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll r, b, d;
    scanf("%lld %lld %lld", &r, &b, &d);
    ll diff = r - b; // difference between red and blue beans
    bool res = (d * b >= diff) && (d * r >= -diff); // check if distribution is possible
    puts(res ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/