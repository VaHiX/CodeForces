// Problem: CF 727 C - Guess the Array
// https://codeforces.com/contest/727/problem/C

/*
 * Problem: Guess the Array
 * Algorithm: Interactive array reconstruction using pairwise sums
 * 
 * Approach:
 * 1. First, query sums of elements with index 1 and each other index (2 to n).
 *    Store these sums in array 'arr'.
 * 2. Then, query sum of elements at indices 2 and 3 to get a reference value.
 * 3. Calculate the value of element at index 1 using the formula derived from
 *    the system of equations:
 *    arr[2] = a[1] + a[2]
 *    arr[3] = a[1] + a[3]
 *    x = (arr[2] - x + arr[3]) / 2
 * 4. Reconstruct the rest of the array by subtracting the value of a[1] from each arr[i].
 * 
 * Time Complexity: O(n) - We make at most n queries and perform constant time operations for each.
 * Space Complexity: O(n) - We store the sums in an array of size n.
 */

#include <stdio.h>
#include <iosfwd>

using namespace std;
int main() {
  int n;
  int arr[10000]; // Array to store the sums of (1, i) for i = 2 to n
  scanf("%d", &n);
  
  // Query sums of element 1 with all other elements
  for (int i = 2; i <= n; i++) {
    printf("? 1 %d \n", i); // Ask for sum of elements at index 1 and i
    fflush(stdout);        // Flush output buffer
    scanf("%d", &arr[i]);  // Read the sum
  }
  
  int x;
  printf("? 2 3 \n"); // Ask for sum of elements at index 2 and 3
  fflush(stdout);
  scanf("%d", &x);    // Read the sum
  
  // Calculate the value of element at index 1
  // From equations:
  // arr[2] = a[1] + a[2] => a[2] = arr[2] - a[1]
  // arr[3] = a[1] + a[3] => a[3] = arr[3] - a[1]
  // x = a[2] + a[3]
  // x = (arr[2] - a[1]) + (arr[3] - a[1])
  // x = arr[2] + arr[3] - 2*a[1]
  // a[1] = (arr[2] + arr[3] - x) / 2
  x = (arr[2] - x + arr[3]) / 2;
  
  // Output the reconstructed array
  printf("! %d ", x); // Print the first element
  for (int i = 2; i <= n; i++) {
    printf("%d ", arr[i] - x); // Print all other elements
  }
  printf("\n");
}


// https://github.com/VaHiX/CodeForces/