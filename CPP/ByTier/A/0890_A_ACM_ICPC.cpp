// Problem: CF 890 A - ACM ICPC
// https://codeforces.com/contest/890/problem/A

/*
 * Problem: ACM ICPC - Determine if 6 participants can be split into two teams of 3 such that both teams have equal total scores.
 * 
 * Algorithm: Brute-force enumeration of all possible ways to choose 3 participants out of 6 for the first team,
 * and check if the remaining 3 form a team with the same total score.
 * 
 * Time Complexity: O(C(6,3)) = O(20) = O(1) since we're choosing 3 from 6 elements which is a constant.
 * Space Complexity: O(1) as we only use a fixed-size array of 6 integers and a few variables.
 * 
 * Techniques:
 * - Enumeration of combinations using nested loops (i, j, k)
 * - Early termination on finding a valid split
 * - Comparison of team scores using sum of scores
 */

#include <stdlib.h>
#include <iostream>

using namespace std;

int main() {
  int i, j, k, a[10], sum = 0, s;
  
  // Read input scores and calculate total sum
  for (i = 1; i <= 6; i++) {
    cin >> a[i];
    sum += a[i];  // Accumulate total score
  }
  
  // Try all combinations of 3 participants for the first team
  for (i = 1; i <= 4; i++)     // First participant index
    for (j = i + 1; j <= 5; j++) // Second participant index
      for (k = j + 1; k <= 6; k++) { // Third participant index
        s = a[i] + a[j] + a[k];  // Compute score of current team
        if (s == sum - s) {      // Check if remaining participants form equal score team
          cout << "YES";
          exit(0);               // Exit early upon finding a valid split
        }
      }
  
  cout << "NO";  // No valid split found
}


// https://github.com/VaHiX/CodeForces/