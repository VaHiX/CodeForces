// Problem: CF 1480 B - The Great Hero
// https://codeforces.com/contest/1480/problem/B

/*
B. The Great Hero

Algorithm:
The problem requires determining whether a hero with attack power A and health B can defeat all n monsters,
where each monster has attack power a_i and health b_i. 

Key insight:
- The order of fighting doesn't matter in terms of total damage taken by the hero.
- For each monster, we compute how many hits the hero needs to kill it (b_i + A - 1) / A.
- Then simulate the process where for each monster, the hero takes a_i * number_of_hits damage.
- We also track the maximum attack power of any monster seen so far which affects the final result.

Time Complexity: O(n)
Space Complexity: O(n)

*/
#include <cstdio>
#include <vector>
typedef long long ll;
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    ll A, B, n;
    scanf("%lld %lld %lld", &A, &B, &n);
    std::vector<ll> a(n);
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &a[p]);
    }
    std::vector<ll> b(n);
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &b[p]);
    }
    ll mxd(0); // maximum attack power of any monster
    for (ll p = 0; p < n; p++) {
      ll r = (b[p] + A - 1) / A; // number of hits needed to kill monster p
      B -= r * a[p]; // subtract total damage from hero's health
      mxd = (mxd > a[p] ? mxd : a[p]); // track maximum monster attack power
    }
    puts(B + mxd > 0 ? "YES" : "NO"); // if hero survives with at least 1 HP, or dies but max is covered in final blow, then YES
  }
}


// https://github.com/VaHiX/codeForces/