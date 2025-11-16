// Problem: CF 732 A - Buy a Shovel
// https://codeforces.com/contest/732/problem/A

/*
 * Problem: Buy a Shovel
 * 
 * Purpose: Find the minimum number of shovels Polycarp can buy such that the total cost 
 *          can be paid exactly using 10-burle coins and at most one r-burle coin.
 * 
 * Algorithm: 
 *   - Iterate through possible numbers of shovels (from 1 upwards).
 *   - For each number i, calculate the total cost: k * i.
 *   - Check if the cost modulo 10 is either 0 or equal to r.
 *     - If so, it means we can pay the exact amount with 10-burle coins and possibly one r-burle coin.
 *   - Return the first such i.
 * 
 * Time Complexity: O(10) = O(1) since in worst case we need at most 10 iterations before finding the answer.
 * Space Complexity: O(1) - only using a constant amount of extra space.
 */

#include <iostream>

typedef long long int ll;
#define pair <ll, ll> pii
using namespace std;

int main() {
  ll i, j, k;
  ll n, r;
  cin >> k >> r; // Read the price of one shovel and the denomination of the unique coin
  
  for (i = 1;; i++) { // Loop through possible number of shovels starting from 1
    if ((k * i) % 10 == r || (k * i) % 10 == 0) { // Check if total cost can be paid exactly
      cout << i << endl; // Output the minimum number of shovels
      break;
    }
  }
  
  return 0;
}


// https://github.com/VaHiX/CodeForces/