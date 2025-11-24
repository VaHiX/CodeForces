// Problem: CF 458 A - Golden System
// https://codeforces.com/contest/458/problem/A

/*
 * Golden System Comparison
 * 
 * This code compares two numbers represented in the "golden system", a base system 
 * where each digit's value is determined by the golden ratio (φ ≈ 1.618),
 * and q^2 = q + 1 holds. The numbers are given in binary form (strings of 0s and 1s),
 * and we need to determine their relative decimal values. 
 *
 * Approach:
 * The algorithm attempts to simulate the golden system arithmetic directly, 
 * using a method similar to "carrying" in base systems, but adapted to the golden 
 * ratio rules. It aligns the two numbers by padding with leading zeros, and then 
 * applies transformations based on the property that 1*φ^k = φ^(k-1) + φ^(k-2). 
 *
 * Time Complexity: O(n), where n is the maximum length of the two strings.
 * Space Complexity: O(n), for storing the aligned digits of both numbers.
 */

#include <stdio.h>
#include <string.h>
#include <algorithm>

#define mxn 100005
using namespace std;
int a[mxn], b[mxn]; // Arrays to store padded binary digits of the two numbers
char s1[mxn], s2[mxn]; // Input strings for the two numbers

int main() {
  scanf("%s %s", s1, s2);
  int n1 = strlen(s1), n2 = strlen(s2);
  int n = max(n1, n2); // Determine the maximum length for alignment

  // Align strings by padding with leading zeros
  for (int i = 0; i < n1; i++)
    a[n - n1 + i] = s1[i] - '0'; // Convert and store first number
  for (int i = 0; i < n2; i++)
    b[n - n2 + i] = s2[i] - '0'; // Convert and store second number

  int flag = 0; // Flag to indicate comparison result

  // Process the digits according to golden ratio rules
  for (int i = 0; i < n && !flag; i++) {
    int mn = min(a[i], b[i]); // Find common value to subtract
    a[i] -= mn; // Subtract common value from both
    b[i] -= mn;
    
    // Apply golden ratio transformation: a[i] = a[i] * φ --> a[i+1] += a[i], a[i+2] += a[i]
    a[i + 1] += a[i];
    a[i + 2] += a[i];
    b[i + 1] += b[i];
    b[i + 2] += b[i];

    // Overflow check: if any digit goes beyond the expected limit, set flag
    if (a[i] > n)
      flag = 1;
    else if (b[i] > n)
      flag = 2;
  }

  // Final comparison after normalization
  if (!flag) {
    if (a[n] > b[n])
      flag = 1;
    else if (a[n] < b[n])
      flag = 2;
    else {
      if (a[n + 1] > b[n + 1])
        flag = 1;
      else if (a[n + 1] < b[n + 1])
        flag = 2;
    }
  }

  // Output the result based on flag value
  if (flag == 1)
    puts(">");
  else if (flag == 2)
    puts("<");
  else
    puts("=");

  return 0;
}


// https://github.com/VaHiX/CodeForces/