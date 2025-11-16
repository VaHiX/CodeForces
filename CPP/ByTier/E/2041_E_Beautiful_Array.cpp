// Problem: CF 2041 E - Beautiful Array
// https://codeforces.com/contest/2041/problem/E

/*
 * Problem: Beautiful Array
 * Purpose: Construct an array with given mean 'a' and median 'b'.
 * Algorithm: 
 *   - Use a simple 3-element array construction:
 *     - First two elements are set to 'b' (median).
 *     - Third element is calculated as (3*a - 2*b) to ensure the mean is 'a'.
 *     - This works because (b + b + (3*a - 2*b))/3 = (2*b + 3*a - 2*b)/3 = 3*a/3 = a.
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 */
#include <iostream>
using namespace std;

int main() {
  int a, b;
  cin >> a >> b;
  // Output array of size 3 with elements b, b, and (3*a - 2*b)
  cout << 3 << endl << b << " " << b << " " << 3 * a - 2 * b;
  return 0;
}


// https://github.com/VaHiX/CodeForces/