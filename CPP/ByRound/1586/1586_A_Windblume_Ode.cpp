// Problem: CF 1586 A - Windblume Ode
// https://codeforces.com/contest/1586/problem/A

/*
 * Problem: Windblume Ode
 * 
 * Purpose: Find the largest subset of an array such that the sum of elements in the subset is a composite number.
 * 
 * Algorithms/Techniques:
 * - Use a helper function `isPrime` to determine if a number is prime.
 * - If the total sum of the array is composite, the entire array can be selected.
 * - If the total sum is prime, we need to remove the smallest odd number (to make the sum composite).
 * 
 * Time Complexity: O(n * sqrt(S)) where S is the sum of the array elements, due to prime checking.
 * Space Complexity: O(1) excluding input storage.
 */

#include <stdio.h>
#include <iosfwd>

using namespace std;
int T, n, sum, a[110], flag;

// Function to check if a number is prime
int isPrime(int x) {
  for (int i = 2; i * i <= x; i++)
    if (x % i == 0)
      return 0; // Not prime
  return 1; // Prime
}

int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    sum = 0;
    for (int i = 1; i <= n; i++)
      scanf("%d", &a[i]), sum += a[i]; // Read input and compute total sum
    
    flag = isPrime(sum); // Check if total sum is prime
    printf("%d\n", n - flag); // If prime, we remove one element; otherwise, we take all
    
    for (int i = 1; i <= n; i++) {
      // If sum is prime and current element is odd, skip it to make sum composite
      if (flag && a[i] % 2 == 1)
        flag = 0; // Mark that we've skipped one odd element
      else
        printf("%d ", i); // Print index of element to include
    }
    printf("\n");
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/