// Problem: CF 1189 B - Number Circle
// https://codeforces.com/contest/1189/problem/B

/*
Purpose: 
  To determine if a given array of numbers can be arranged in a circle such that 
  each number is strictly less than the sum of its two neighboring numbers.
  
Algorithm:
  - Sort the array in ascending order.
  - Check if the largest number is greater than or equal to the sum of the two 
    next largest numbers. If so, no valid arrangement exists.
  - Otherwise, rearrange the last two elements to ensure the condition is met for 
    the smallest elements. The key insight is that sorting ensures we only need 
    to check the largest element against the two preceding ones.

Time Complexity: O(n log n) due to sorting.
Space Complexity: O(n) for storing the array.
*/

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  sort(a.begin(), a.end());  // Sort the array to facilitate checking
  if (a[n - 1] >= a[n - 2] + a[n - 3]) {
    // If the largest element is greater than or equal to sum of two previous,
    // it's impossible to make a valid circle
    puts("NO");
  } else {
    // Swap the last two elements to ensure valid arrangement at the end
    long temp = a[n - 2];
    a[n - 2] = a[n - 1];
    a[n - 1] = temp;
    puts("YES");
    for (long p = 0; p < n; p++) {
      printf("%ld ", a[p]);
    }
    puts("");
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/