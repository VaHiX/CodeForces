// Problem: CF 2140 A - Shift Sort
// https://codeforces.com/contest/2140/problem/A

/*
 * Problem: Shift Sort
 * Algorithm/Techniques: Greedy, Observation
 * 
 * Time Complexity: O(n) per test case
 * Space Complexity: O(1)
 *
 * Description:
 * Given a binary string, we can perform operations where we choose three indices
 * and cyclically shift their values (either left or right). The goal is to find
 * the minimum number of such operations to sort the string in non-decreasing order.
 * 
 * Key Insight:
 * Sorting a binary string means moving all 0s to the left and all 1s to the right.
 * We can observe that each operation allows us to fix up to 2 positions in one go,
 * so we compute how many 1s are present at the beginning of the string (before
 * all 0s) - those need to be moved over, which gives us a count indicating how many
 * operations are needed.
 */

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;
#define ll long long

int main() {
  int t;
  cin >> t;
  while (t--) {
    int n;                 // Read length of string
    cin >> n;
    string s;              // Read the binary string
    cin >> s;
    
    int c = count(s.begin(), s.end(), '0');  // Count total number of 0s
    
    // Count how many 1s are in the prefix of size 'c' (i.e., first c characters)
    cout << count(s.begin(), s.begin() + c, '1') << "\n";
  }
}


// https://github.com/VaHiX/codeForces/