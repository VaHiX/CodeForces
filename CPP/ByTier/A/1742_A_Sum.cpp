// Problem: CF 1742 A - Sum
// https://codeforces.com/contest/1742/problem/A

/*
Problem: Determine if one of three integers is the sum of the other two.

Algorithm/Techniques: 
- Simple comparison check
- For each test case, verify if any one number equals the sum of the other two

Time Complexity: O(t), where t is the number of test cases
Space Complexity: O(1)

Input:
- First line: number of test cases t
- Each test case: three integers a, b, c (0 ≤ a,b,c ≤ 20)

Output:
- "YES" if one number is sum of others, "NO" otherwise
*/

#include <stdio.h>
int t, a, b, c;
int main() {
  for (scanf("%d", &t); t; --t) // Read number of test cases and loop through them
    scanf("%d%d%d", &a, &b, &c), // Read three integers for current test case
        puts(a + b == c || a + c == b || b + c == a ? "YES" : "NO"); // Check if any number is sum of others and print result
}


// https://github.com/VaHiX/codeForces/