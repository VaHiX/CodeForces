// Problem: CF 987 B - High School: Become Human
// https://codeforces.com/contest/987/problem/B

#include <cmath>
#include <iostream>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n")
#define nl printf("\n");
#define N 50700
#define sf(n) scanf("%d", &n)
#define sff(n, m) scanf("%d%d", &n, &m)
#define sfl(n) scanf("%I64d", &n)
#define sffl(n, m) scanf("%I64d%I64d", &n, &m)
#define pf(n) printf("%d ", n)
#define pfl(n) printf("%I64d ", n)
#define pfs(s) printf("%s", s)
#define pb push_back
using namespace std;
int main() {
  int i, j, k;
  int n, m;
  ll x, y;
  cin >> x >> y;
  if (x == y) {
    cout << "=";
    return 0;
  }
  double a, b;
  a = y * log(x);         // Compute y * log(x) to avoid overflow
  b = x * log(y);         // Compute x * log(y) to avoid overflow
  if (a == b)
    cout << "=";
  else if (a > b)
    cout << ">";
  else
    cout << "<";
  return 0;
}


// https://github.com/VaHiX/CodeForces/