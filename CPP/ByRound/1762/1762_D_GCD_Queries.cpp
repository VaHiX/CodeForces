// Problem: CF 1762 D - GCD Queries 
// https://codeforces.com/contest/1762/problem/D

/*
 * Problem: GCD Queries
 * Algorithm: Greedy approach to find index of 0 in permutation
 * 
 * Approach:
 * - We know that in the permutation p, there is exactly one element that is 0.
 * - The key insight is to use GCD queries to efficiently narrow down where that 0 is.
 * - We maintain two indices, lasa and lasb, initially 1 and 2.
 * - For each subsequent index i from 3 to n:
 *   - Query gcd(p_lasa, p_lasb) and gcd(p_lasa, p_i)
 *   - If the results are equal, it implies p_i = 0 (since gcd(a,b) = gcd(a,c) means b and c share same factors as a)
 *   - Else if gcd(p_lasa, p_lasb) < gcd(p_lasa, p_i), then p_lasb must be 0 because we have a larger GCD when comparing with a new element
 *   - Else, update lasa to i (because p_lasa is likely 0 or has a factor that makes the GCD smaller)
 * - Finally we output the two indices as our guess for where 0 is.
 *
 * Time Complexity: O(n) - we make at most 2*n queries (2 per step from iteration 3 to n)
 * Space Complexity: O(1) - only store constant extra variables
 */
#include <iostream>
using namespace std;

int main() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    int lasa = 1, lasb = 2; // Initialize two indices to compare against
    for (int i = 3; i <= n; i++) {
      cout << "? " << lasa << " " << lasb << endl;
      int x, y;
      cin >> x;  // gcd(p_lasa, p_lasb)
      cout << "? " << lasa << " " << i << endl;
      cin >> y;  // gcd(p_lasa, p_i)
      
      // If gcd(p_lasa, p_lasb) == gcd(p_lasa, p_i), then p_i must be 0
      // because p_lasb and p_i share same factors with p_lasa
      if (x == y)
        lasa = i;
      // If gcd(p_lasa, p_lasb) < gcd(p_lasa, p_i), then p_lasb must be 0
      else if (x < y)
        lasb = i;
      // If gcd(p_lasa, p_lasb) > gcd(p_lasa, p_i), then p_lasa must be 0
      // But we do nothing, since we're checking whether we already found a 0 in lasa
      else
        ;
    }
    cout << "! " << lasa << " " << lasb << endl;
    int fc;
    cin >> fc;  // Read the response from jury
  }
}


// https://github.com/VaHiX/CodeForces/