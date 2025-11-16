// Problem: CF 991 A - If at first you don't succeed...
// https://codeforces.com/contest/991/problem/A

/*
Purpose: Determine the number of students who did not pass the exam based on
         celebration data from two restaurants. This uses set theory to calculate
         how many students are accounted for and whether the numbers are consistent.

Algorithm/Techniques:
- Use inclusion-exclusion principle to calculate the total number of students
  who visited at least one restaurant.
- Check for consistency between the given data and the total number of students.
- Handle edge cases where the data is contradictory.

Time Complexity: O(1) - constant time operations.
Space Complexity: O(1) - only a few variables are used.
*/

#include <cstdio>
int main() {
  long a, b, c, n;
  scanf("%ld %ld %ld %ld", &a, &b, &c, &n);
  long ans(0);
  
  // Check if the data is contradictory:
  // 1. C students visited both, so C must be <= A and B
  // 2. C students cannot be greater than the sum of students visiting each restaurant
  if (c > a || c > b || c > a + b) {
    ans = -1;
  } 
  // Check if the number of students who celebrated is greater than total students
  // Total students celebrating = (A - C) + (B - C) + C = A + B - C
  // At least one student must stay home (Vasya), so total students >= 1 + A + B - C
  else if (1 + a + b - c > n) {
    ans = -1;
  } 
  // Calculate the number of students who did not pass (including Vasya)
  else {
    ans = n - (a + b - c);
  }
  
  printf("%ld\n", ans);
  return 0;
}


// https://github.com/VaHiX/CodeForces/