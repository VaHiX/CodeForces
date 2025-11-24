// Problem: CF 1080 A - Petya and Origami
// https://codeforces.com/contest/1080/problem/A

#include <cstdio>
typedef long long ll;
/*
A. Petya and Origami

Purpose:
This program calculates the minimum number of notebooks Petya needs to buy to make origami invitations for his friends.
Each invitation requires 2 red sheets, 5 green sheets, and 8 blue sheets.
Each notebook contains exactly k sheets of one color.

Algorithms/Techniques:
- Mathematical calculation using ceiling division to determine minimum notebooks needed
- For each color, we compute how many notebooks are required by dividing total sheets needed by sheets per notebook and taking ceiling

Time Complexity: O(1) - Constant time arithmetic operations
Space Complexity: O(1) - Only using a constant amount of extra space

Input:
n (number of friends), k (sheets per notebook)

Output:
Minimum number of notebooks required
*/
int main() {
  ll n, k;
  scanf("%lld %lld", &n, &k);
  ll total(0);
  // Calculate red notebooks needed: (2*n) ceiling divided by k
  total += (2 * n + k - 1) / k;
  // Calculate green notebooks needed: (5*n) ceiling divided by k
  total += (5 * n + k - 1) / k;
  // Calculate blue notebooks needed: (8*n) ceiling divided by k
  total += (8 * n + k - 1) / k;
  printf("%lld\n", total);
  return 0;
}

// https://github.com/VaHiX/codeForces/