// Problem: CF 448 A - Rewards
// https://codeforces.com/contest/448/problem/A

/*
Purpose: Determine if all cups and medals can be placed on n shelves following specific rules:
         - Each shelf can hold only cups or only medals
         - No shelf can hold more than 5 cups
         - No shelf can hold more than 10 medals

Algorithm: 
- Calculate minimum shelves needed for cups: (total_cups / 5) + (1 if remainder > 0)
- Calculate minimum shelves needed for medals: (total_medals / 10) + (1 if remainder > 0)
- Check if total shelves needed <= n

Time Complexity: O(1) - only basic arithmetic operations
Space Complexity: O(1) - only a fixed number of variables used
*/

#include <cstdio>
int main() {
  int a1, a2, a3;
  scanf("%d %d %d\n", &a1, &a2, &a3);
  int b1, b2, b3;
  scanf("%d %d %d\n", &b1, &b2, &b3);
  int n;
  scanf("%d\n", &n);
  // Calculate minimum shelves needed for cups (5 per shelf max)
  int a = ((a1 + a2 + a3) / 5) + ((a1 + a2 + a3) % 5 > 0);
  // Calculate minimum shelves needed for medals (10 per shelf max)
  int b = ((b1 + b2 + b3) / 10) + ((b1 + b2 + b3) % 10 > 0);
  // Check if total required shelves <= available shelves
  puts((a + b) <= n ? "YES" : "NO");
  return 0;
}


// https://github.com/VaHiX/CodeForces/