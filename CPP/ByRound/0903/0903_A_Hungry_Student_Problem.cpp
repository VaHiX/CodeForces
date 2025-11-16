// Problem: CF 903 A - Hungry Student Problem
// https://codeforces.com/contest/903/problem/A

/*
 * Problem: Hungry Student
 * Purpose: Determine if a given number of chicken chunks can be bought using
 *          combinations of small (3 chunks) and large (7 chunks) portions.
 * 
 * Algorithm:
 * - For each test case x:
 *   - If x is divisible by 3 or 7, output "YES"
 *   - Otherwise, test all possible numbers of small portions (up to 40)
 *     to see if remaining chunks are divisible by 7
 * 
 * Time Complexity: O(n * 40) = O(n), where n is number of test cases
 * Space Complexity: O(1)
 */

#include <cstdio>
#include <iostream>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n");
#define nl printf("\n");
#define N 200010
#define inf 1000000000
#define pp pair<string, int>
using namespace std;

int main() {
  int i, j, k;
  int n, m, t;
  int x, y;
  
  // Read number of test cases
  scanf("%d", &n);
  
  // Process each test case
  for (i = 0; i < n; i++) {
    scanf("%d", &m);
    
    // If m is divisible by 3 or 7, it's possible to form it with only one type of portion
    if (m % 3 == 0 || m % 7 == 0)
      printf("YES\n");
    else {
      bool f = 0; // flag to indicate if solution is found
      
      // Try up to 40 small portions (since 3 * 40 = 120, which is more than max x=100)
      for (j = 0; j < 40; j++) {
        x = m - 3 * j; // remaining chunks after taking j small portions
        
        // Check if remaining chunks are divisible by 7
        if (x > 0 && x % 7 == 0) {
          printf("YES\n");
          f = 1;
          break;
        }
      }
      
      // If no valid combination found
      if (!f)
        printf("NO\n");
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/