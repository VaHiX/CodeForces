// Problem: CF 1181 A - Chunga-Changa
// https://codeforces.com/contest/1181/problem/A

#include <cstdio>
typedef long long ll;
int main() {
  ll x, y, z;
  scanf("%lld %lld %lld", &x, &y, &z);
  ll total = (x + y) / z; // Total coconuts if all money combined
  ll give(0);
  if (x % z + y % z >= z) {
    // If remainder from both girls combined is enough for one more coconut,
    // calculate minimum chizhiks to transfer to achieve this
    give = z - (((x % z) > (y % z)) ? (x % z) : (y % z));
  }
  printf("%lld %lld\n", total, give);
  return 0;
}


// https://github.com/VaHiX/codeForces/