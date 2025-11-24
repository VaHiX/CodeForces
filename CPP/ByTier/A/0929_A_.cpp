// Problem: CF 929 A - Прокат велосипедов
// https://codeforces.com/contest/929/problem/A

#include <iostream>

using namespace std;
/*
 * Code purpose: 
 *   Determines the minimum number of bicycles needed for Arkadiy to travel 
 *   from the first to the last bike rental point, given that each bike 
 *   can only be used for a limited distance k.
 * 
 * Algorithm:
 *   Greedily traverse the rental points. At each step:
 *   - If the distance to the next point exceeds k, output -1 (impossible).
 *   - If the distance from the last rental point used exceeds k,
 *     increment the count of bicycles used and update the last rental point.
 * 
 * Time Complexity: O(n), where n is the number of rental points.
 * Space Complexity: O(1), only using a constant amount of extra space.
 */
int main() {
  int n, k;
  cin >> n >> k;
  int a;
  cin >> a;
  int pra = a;  // Track the last rental point used
  int kol = 1;  // Count of bicycles used (starts with 1 because we use the first one)
  for (int i = 1; i < n; i++) {
    int as;
    cin >> as;
    if (as - a > k) {  // If the distance to next point is greater than k
      cout << -1 << endl;
      return 0;
    }
    if (as - pra > k) {  // If distance from previously used point is greater than k
      kol++;             // Need a new bicycle
      pra = a;           // Update last rental point used to current point
    }
    a = as;  // Move to next point
  }
  cout << kol << endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/