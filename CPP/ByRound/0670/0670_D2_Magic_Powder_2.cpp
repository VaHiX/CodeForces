// Problem: CF 670 D2 - Magic Powder - 2
// https://codeforces.com/contest/670/problem/D2

/*
Algorithm: Binary Search on Answer
Purpose: To find the maximum number of cookies that can be baked using available ingredients and magic powder.
Approach:
- Use binary search on the number of cookies (answer).
- For each candidate number of cookies, calculate the total additional ingredients needed (using magic powder).
- If total required magic powder is within limit k, try higher number; otherwise, try lower.
- The search space is from 0 to 2e9 + 5 (safe upper bound).

Time Complexity: O(n * log(2e9)) where n is the number of ingredients
Space Complexity: O(1) - only using a few variables and arrays of fixed size
*/

#include <stdio.h>
#include <iostream>

using namespace std;
int a[100001]; // Required amount of each ingredient per cookie
int b[100001]; // Available amount of each ingredient

int main() {
  int n, k;
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]);
  for (int i = 1; i <= n; i++)
    scanf("%d", &b[i]);
  
  // Binary search on the number of cookies
  long long l = 0, r = 2e9 + 5, m, t;
  while (l < r) {
    m = (l + r) >> 1; // Midpoint calculation (equivalent to (l + r) / 2)
    long long temp = 0; // Total magic powder needed for 'm' cookies
    
    // Calculate how much more of each ingredient is needed
    for (int i = 1; i <= n; i++) {
      t = a[i] * m - b[i]; // How many grams needed for 'm' cookies minus what's available
      temp += 0 > t ? 0 : t; // Add only if positive, i.e., if more is needed
      if (temp > k) // Early termination if already exceeded the limit
        break;
    }
    
    // Adjust binary search bounds
    if (temp > k)
      r = m; // Too many cookies, reduce upper bound
    else
      l = m + 1; // Enough magic powder, increase lower bound
  }
  
  cout << l - 1 << endl; // Return maximum possible number of cookies
  return 0;
}


// https://github.com/VaHiX/CodeForces/