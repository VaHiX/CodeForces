// Problem: CF 462 C - Appleman and Toastman
// https://codeforces.com/contest/462/problem/C

/*
Purpose: This code solves the problem of maximizing the score in the game between Appleman and Toastman, 
where numbers are split and summed in a way that maximizes total score.

Algorithms/Techniques: 
- Greedy approach: Sort the array and process elements from smallest to largest.
- For each element, we calculate how many times it contributes to the score based on its position in the sorting order.
- The formula `min(n, i + 1) * w[i]` computes the contribution of element w[i] to the final score.

Time Complexity: O(n log n) due to sorting, where n is the number of elements.
Space Complexity: O(n) for storing the array of numbers.

*/

#include <algorithm>
#include <stdio.h>
using namespace std;
long long S, w[301000]; // S accumulates the total score; w stores the input numbers
int main() {
  int i, n;
  scanf("%d", &n);
  for (i = 1; i <= n; i++) {
    scanf("%d", &w[i]); // Read the numbers into array w
  }
  sort(w + 1, w + n + 1); // Sort the array in ascending order
  for (i = 1; i <= n; i++) {
    S += min(n, i + 1) * w[i]; // Accumulate the contribution of each number to the score
  }
  printf("%lld\n", S); // Print the maximum possible score
}


// https://github.com/VaHiX/CodeForces/