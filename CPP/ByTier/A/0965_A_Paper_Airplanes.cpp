// Problem: CF 965 A - Paper Airplanes
// https://codeforces.com/contest/965/problem/A

/*
Algorithm: 
  - Calculate the number of sheets required per person: if n airplanes need to be made,
    and each sheet makes s airplanes, then sheets needed per person = ceil(n / s).
  - Multiply by k (number of people) to get total sheets needed.
  - Then calculate how many packs are needed: if total sheets are divided by p (sheets per pack),
    we need ceil(total_sheets / p) packs.

Time Complexity: O(1)
Space Complexity: O(1)
*/

#include <cstdio>
#include <iostream>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n")
#define nl printf("\n");
#define N 5000
#define inf 1000000
#define pp pair<int, int>
#define sf(n) scanf("%d", &n)
#define sff(n, m) scanf("%d%d", &n, &m)
#define sfl(n) scanf("%I64d", &n)
#define sffl(n, m) scanf("%I64d%I64d", &n, &m)
#define pf(n) printf("%d ", n)
#define pfl(n) printf("%I64d ", n)
#define pfs(s) printf("%s\n", s)
#define pb push_back
using namespace std;
int main() {
  int i, j, k;
  int n, m;
  int s, p;
  sff(k, n);  // Read k (people) and n (airplanes per person)
  sff(s, p);  // Read s (airplanes per sheet) and p (sheets per pack)
  if (n % s == 0)
    n = n / s;  // If n is divisible by s, no extra sheet needed
  else
    n = n / s + 1;  // Otherwise, round up to get required sheets per person
  n = k * n;  // Total sheets needed for all people
  if (n % p == 0)
    m = n / p;  // If total sheets divide evenly by pack size
  else
    m = n / p + 1;  // Otherwise, round up to get number of packs
  pf(m);  // Print the minimum number of packs needed
  return 0;
}


// https://github.com/VaHiX/CodeForces/