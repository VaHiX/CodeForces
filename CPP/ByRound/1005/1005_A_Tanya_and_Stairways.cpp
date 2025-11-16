// Problem: CF 1005 A - Tanya and Stairways
// https://codeforces.com/contest/1005/problem/A

#include <iostream>

using namespace std;
int n, x, p, i, s, a[1790];
int main() {
  // Read the number of pronounced numbers
  for (cin >> n, p = 1; i < n; i++)
    // Read each number and check if it's 1
    cin >> x, s += x == 1, a[s] = x;
  // Output the number of stairways (s) and the number of steps in each stairway
  for (cout << s << endl, i = 1; i <= s; i++)
    cout << a[i] << " ";
}
// Algorithm: The code counts how many times "1" appears in the sequence, which indicates the start of a new stairway.
//           Then it stores the maximum step number for each stairway and outputs them.
// Time Complexity: O(n), where n is the number of elements in the input sequence.
// Space Complexity: O(n), for storing the array a and other variables.

// https://github.com/VaHiX/CodeForces/