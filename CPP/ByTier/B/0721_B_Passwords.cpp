// Problem: CF 721 B - Passwords
// https://codeforces.com/contest/721/problem/B

/*
 * Purpose: To determine the minimum and maximum time Vanya needs to enter the correct password
 *          on a website, considering that he tries passwords in order of increasing length,
 *          and must wait 5 seconds after every k failed attempts.
 *
 * Algorithms/Techniques:
 * - Count passwords shorter and longer than the target password.
 * - Calculate best and worst case time based on position of target password
 *   among passwords of same length.
 *
 * Time Complexity: O(n^2) where n is the number of passwords.
 * Space Complexity: O(n) for storing the passwords.
 */

#include <stdio.h>
#include <cstring>
#include <iostream>

using namespace std;

int main() {
  int i, j, k, n, l;
  int boro = 0, choto = 0; // boro = count of passwords longer than target, choto = shorter
  int worst, best;
  char pass[200];
  cin >> n >> k;
  char s[n][200];
  for (i = 0; i < n; i++) {
    scanf("%s", &s[i]); // Read each password
  }
  scanf("%s", &pass); // Read the target password
  l = strlen(pass); // Length of target password
  for (i = 0; i < n; i++) {
    if (strlen(s[i]) < l)
      choto++; // Count passwords shorter than the target
    else if (strlen(s[i]) > l)
      boro++; // Count passwords longer than the target
  }
  // Best case: target is the first password among same-length ones
  best = (choto * 1) + ((choto / k) * 5) + 1;
  // Worst case: target is the last password among same-length ones
  worst = (n - boro - 1) + (((n - boro - 1) / k) * 5) + 1;
  cout << best << " " << worst;
  return 0;
}


// https://github.com/VaHiX/CodeForces/