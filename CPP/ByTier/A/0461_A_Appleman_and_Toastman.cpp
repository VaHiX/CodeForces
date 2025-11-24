// Problem: CF 461 A - Appleman and Toastman
// https://codeforces.com/contest/461/problem/A

/*
Purpose: This code solves the problem of maximizing the score in a game between Appleman and Toastman, where groups of numbers are split and summed to accumulate points. 
The key idea is to recognize that the total score depends on how the numbers are weighted based on how many times they are summed during the splitting process.

Algorithm:
- The optimal strategy is to sort the array and then compute a weighted sum where each element contributes based on how many times it's included in sums during the splitting process.
- Each element M[i] is added to the sum a number of times equal to (i + 2), as it gets summed in all splits where it is part of a group of size greater than 1, plus initial sum of the full group.
- Finally, subtract the largest element once since it's counted one extra time due to the structure of the algorithm.

Time Complexity: O(n log n) due to sorting
Space Complexity: O(n) for storing the array
*/

#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
long long int n, p, r, f, s = 0, M[300002], c;
int main() {
  cin >> n;
  for (p = 0; p < n; p++)
    scanf("%lld", &M[p]);  // Read input numbers into array M
  sort(M, M + n);  // Sort the array to optimize the weighting
  for (p = 0; p < n; p++)
    c += M[p] * (p + 2);  // Accumulate weighted sum
  printf("%lld\n", c - M[n - 1]);  // Subtract last element to adjust for overcounting
}


// https://github.com/VaHiX/CodeForces/