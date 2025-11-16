// Problem: CF 1965 B - Missing Subsequence Sum
// https://codeforces.com/contest/1965/problem/B

/*
Algorithm/Technique: Constructive Greedy Approach
Purpose: To find a sequence of at most 25 non-negative integers such that:
- There is no subsequence with sum equal to k.
- For every value v from 1 to n (excluding k), there exists a subsequence with sum equal to v.

Time Complexity: O(log n) per test case, due to bit manipulation and loop over powers of 2.
Space Complexity: O(1) extra space excluding output storage, as the maximum size of the vector is bounded by 25.
*/

#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;
int T, n, k;
int main() {
  scanf("%d", &T);
  while (T--) {
    vector<int> v; // Vector to store the constructed sequence
    scanf("%d%d", &n, &k);
    
    int x = k - 1; // We want to represent all numbers from 1 to k-1 using bits
    
    // Fill the vector with powers of 2 up to x, subtracting them from x
    for (int i = 0; 1 << i <= x; i++)
      x -= 1 << i, v.push_back(1 << i);
    
    // If x is still greater than 0, it means we have leftover bits to represent
    if (x)
      v.push_back(x);
      
    // Add k+2 to ensure no subsequence sums to k (since we won't be able to form k now)
    v.push_back(k + 2);
    
    // Add powers of 2 starting from k+1 up to n to cover all values up to n
    for (int i = k + 1; i <= n; i *= 2)
      v.push_back(i);
      
    printf("%d\n", v.size()); // Print length of the sequence
    for (int x : v)
      printf("%d ", x); // Print each element
    puts(""); // Newline after printing the sequence
  }
}


// https://github.com/VaHiX/CodeForces/