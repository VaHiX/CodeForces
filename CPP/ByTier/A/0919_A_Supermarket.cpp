// Problem: CF 919 A - Supermarket
// https://codeforces.com/contest/919/problem/A

/*
 * Code Purpose: This program finds the minimum cost to buy exactly m kilos of apples
 *               from n available supermarkets. Each supermarket offers apples at a rate
 *               of 'a' yuan for 'b' kilos. The goal is to determine the cheapest price
 *               per kilo among all supermarkets and then multiply by the required amount m.
 *
 * Algorithms/Techniques: Greedy approach - we find the minimum price per kilo across all
 *                        supermarkets, then multiply by total needed kilos.
 *
 * Time Complexity: O(n), where n is the number of supermarkets. We iterate through each
 *                  supermarket once to find the minimum price per kilo.
 *
 * Space Complexity: O(1), as we only use a constant amount of extra space (variables mn, c, q).
 */

#include <cstdio>
int main() {
  long n, m;
  scanf("%ld %ld", &n, &m);  // Read number of supermarkets and required kilos
  double mn(10001); // Initialize minimum price per kilo to a large value
  while (n--) {
    double c, q;
    scanf("%lf %lf", &c, &q); // Read cost 'c' for 'q' kilos
    mn = (mn < (c / q)) ? mn : (c / q); // Update minimum price per kilo
  }
  printf("%.8lf\n", mn * m); // Output total cost for m kilos
  return 0;
}


// https://github.com/VaHiX/CodeForces/