// Problem: CF 1351 B - Square?
// https://codeforces.com/contest/1351/problem/B

/*
Problem: Square?
Purpose: Determine if two rectangles obtained by cutting a square can be reassembled to form the original square.
Algorithms/Techniques: 
    - Brute force checking of all possible ways to arrange two rectangles to form a square
    - For each test case, check 4 conditions that would imply the original shape was a square:
        1. First rectangle's width equals second rectangle's width and their heights sum to first width
        2. First rectangle's width equals second rectangle's height and their heights sum to first width
        3. First rectangle's height equals second rectangle's width and their widths sum to first height
        4. First rectangle's height equals second rectangle's height and their widths sum to first height
      
Time Complexity: O(1) per test case (constant number of comparisons)
Space Complexity: O(1) (only using a constant amount of extra space)

Input format:
    - t test cases
    - For each test case:
        - Two integers a1, b1 (dimensions of first rectangle)
        - Two integers a2, b2 (dimensions of second rectangle)
Output format:
    - "YES" if rectangles can form a square, otherwise "NO"
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b;              // dimensions of first rectangle
    scanf("%ld %ld", &a, &b);
    long c, d;              // dimensions of second rectangle
    scanf("%ld %ld", &c, &d);
    
    // Check all possible arrangements to see if they could form a square
    if ((a == c) && (b + d == a)) {  // first rect width = second rect width, heights sum to width
      puts("Yes");
    } else if ((a == d) && (b + c == a)) {  // first rect width = second rect height, heights sum to width
      puts("Yes");
    } else if ((b == c) && (a + d == b)) {  // first rect height = second rect width, widths sum to height
      puts("Yes");
    } else if ((b == d) && (a + c == b)) {  // first rect height = second rect height, widths sum to height
      puts("Yes");
    } else {
      puts("No");
    }
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/