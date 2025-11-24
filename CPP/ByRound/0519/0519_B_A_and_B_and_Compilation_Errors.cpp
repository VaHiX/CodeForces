// Problem: CF 519 B - A and B and Compilation Errors
// https://codeforces.com/contest/519/problem/B

/*
 * Problem: B. A and B and Compilation Errors
 * Purpose: Determine which two compilation errors were fixed by calculating the difference in sums
 *          between consecutive compilations.
 *
 * Algorithm:
 * - Read the initial list of errors and compute their sum (sum).
 * - Read the second list of errors (after one correction) and compute their sum (sum2).
 * - Read the third list of errors (after second correction) and compute their sum (sum3).
 * - The first error fixed is the difference between sum and sum2.
 * - The second error fixed is the difference between sum2 and sum3.
 *
 * Time Complexity: O(n), where n is the number of errors in the first compilation.
 * Space Complexity: O(1), only a few variables are used regardless of input size.
 */

#include <bits/std_abs.h>  // Note: This is likely a typo and should be <bits/stdc++.h> or similar
#include <iostream>

using namespace std;

int main() {
  long long int i, j, k;
  long long int n, x;
  long long int sum = 0, sum2 = 0, sum3 = 0;  // Variables to store sums of errors at each stage
  cin >> n;
  for (i = 0; i < n; i++) {
    cin >> x;
    sum += x;  // Accumulate sum of all errors in first compilation
  }
  for (i = 0; i < n - 1; i++) {
    cin >> x;
    sum2 += x;  // Accumulate sum of errors in second compilation
  }
  for (i = 0; i < n - 2; i++) {
    cin >> x;
    sum3 += x;  // Accumulate sum of errors in third compilation
  }
  cout << abs(sum - sum2) << endl << abs(sum2 - sum3);  // Output the two corrected errors
  return 0;
}


// https://github.com/VaHiX/CodeForces/