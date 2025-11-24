// Problem: CF 1199 B - Water Lily
// https://codeforces.com/contest/1199/problem/B

#include <iomanip>
#include <iostream>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n")
#define nl printf("\n")
#define N 200100
#define inf 1e18
#define mod 998244353
#define sf(n) scanf("%d", &n)
#define sff(n, m) scanf("%d%d", &n, &m)
#define sfl(n) scanf("%I64d", &n)
#define sffl(n, m) scanf("%I64d%I64d", &n, &m)
#define pf(n) printf("%d", n)
#define pff(n, m) printf("%d %d", n, m)
#define pffl(n, m) printf("%I64d %I64d", n, m)
#define pfl(n) printf("%I64d", n)
#define pfs(s) printf("%s", s)
#define pb push_back
#define pp pair<int, int>
using namespace std;

int main() {
  int i, j, k;
  int n, m;
  double H, L;
  cin >> H >> L;
  // Calculate the depth of the lake using the Pythagorean theorem.
  // The flower's stem forms a right triangle with the water surface.
  // Let d be the depth of the lake, then:
  // (L^2) = (H + d)^2 - d^2
  // Solving for d gives: d = (L^2 - H^2) / (2 * H)
  cout << fixed << setprecision(10) << ((L * L - H * H) / (2 * H));
  return 0;
}


// https://github.com/VaHiX/CodeForces/