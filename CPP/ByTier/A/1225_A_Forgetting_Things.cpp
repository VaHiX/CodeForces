// Problem: CF 1225 A - Forgetting Things
// https://codeforces.com/contest/1225/problem/A

/*
Purpose: This program determines if there exist positive integers a and b such that a + 1 = b,
         where the first digit of a is da and the first digit of b is db. If such a pair exists,
         it prints any valid pair; otherwise, it prints -1.

Algorithm:
- The solution handles several specific cases based on the values of da and db.
- Case 1: da = 9 and db = 1 -> special case where a = 9 and b = 10.
- Case 2: da == db -> general case where a = 10*da and b = 10*da + 1.
- Case 3: db == da + 1 -> a ends with 9, b starts with da+1.
- All other cases return -1.

Time Complexity: O(1) - Constant time operations.
Space Complexity: O(1) - Only a fixed number of variables are used.
*/

#include <cstdio>
int main() {
  int da, db;
  scanf("%d %d", &da, &db);
  if (da == 9 && db == 1) {
    puts("9 10");  // Special case: 9 + 1 = 10
  } else if (da == db) {
    printf("%d %d\n", 10 * da, 10 * da + 1);  // General case: e.g., 412 + 1 = 413
  } else if (db == da + 1) {
    printf("%d %d\n", 10 * da + 9, 10 * (da + 1));  // Case: 199 + 1 = 200
  } else {
    puts("-1");  // No valid solution exists
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/