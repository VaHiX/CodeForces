// Problem: CF 2152 A - Increase or Smash
// https://codeforces.com/contest/2152/problem/A

/*
Algorithm: A. Increase or Smash
Approach:
- The problem involves transforming an array of zeros to a target array using "Increase" and "Smash" operations.
- Each "Increase" operation adds a positive integer x to all elements of the array.
- Each "Smash" operation sets some elements (possibly none or all) to zero.

Key Insight:
- To minimize operations, we want to avoid unnecessary increases or smashes.
- We can think of it as a greedy problem. 
- The minimum operations needed are related to how many distinct positive values we have in the sorted array, minus one for the base case, multiplied by 2 (since each unique value needs an Increase and potentially a Smash), plus adjustments for the first element.

Time Complexity: O(n * log(n)) due to sorting.
Space Complexity: O(n) for storing the array elements.

*/
#include <stdio.h>
#include <algorithm>
#include <iostream>

using namespace std;
int a[109]; // Array to store input elements (size up to 100)
int n, m, t; // Variables for loop control and temp storage

int main() {
  cin >> t; // Read number of test cases
  while (t--) {
    scanf("%d", &n); // Read size of array
    for (int i = 1; i <= n; i++) // Input array elements
      cin >> a[i];
    sort(a + 1, a + n + 1); // Sort the array in ascending order
    int ans = unique(a + 1, a + n + 1) - a; // Remove duplicates and calculate count of unique values
    cout << ans * 2 - 3 << '\n'; // Output result based on derived formula
  }
}


// https://github.com/VaHiX/CodeForces/