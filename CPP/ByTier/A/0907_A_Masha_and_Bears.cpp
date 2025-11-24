// Problem: CF 907 A - Masha and Bears
// https://codeforces.com/contest/907/problem/A

/*
Algorithm: Greedy + Constraints Satisfaction
Approach:
1. Determine the minimum and maximum valid sizes for each car based on the constraints:
   - A character can enter a car only if their size is <= car size.
   - A character likes the car if 2 * character size >= car size.
2. For each bear (father, mother, son) and Masha:
   - Find valid ranges for car sizes.
   - Assign car sizes greedily to satisfy all conditions.
3. Check if valid car sizes exist; output result or -1.

Time Complexity: O(1) - Constant time operations.
Space Complexity: O(1) - Only using a fixed number of variables.
*/

#include <cstdio>
int main() {
  long a1, a2, a3, m;
  scanf("%ld %ld %ld %ld", &a1, &a2, &a3, &m);
  long minb1, minb2, minb3;
  long maxb1, maxb2, maxb3;
  bool possible(true);
  minb1 = a1;
  if (minb1 <= 2 * m) {
    minb1 = 2 * m + 1; // Ensure Masha can enter but not like father's car
  }
  maxb1 = 2 * a1; // Maximum size allowed for father's car (he likes it)
  minb3 = (a3 > m) ? a3 : m; // Minimum size for son's car (son or Masha enters)
  maxb3 = 2 * ((a3 < m) ? a3 : m); // Maximum size for son's car (he likes it)
  long b1, b2, b3;
  if (minb1 > maxb1) {
    possible = false; // No valid size for father's car
  } else {
    b1 = maxb1; // Assign maximum possible size to father's car
  }
  if (minb3 > maxb3) {
    possible = false; // No valid size for son's car
  } else {
    b3 = minb3; // Assign minimum possible size for son's car
  }
  minb2 = a2;
  if (minb2 <= 2 * m) {
    minb2 = 2 * m + 1; // Ensure Masha can enter but not like mother's car
  }
  minb2 = (minb2 >= b3 + 1) ? minb2 : (b3 + 1); // Ensure middle car > smallest car
  maxb2 = 2 * a2; // Maximum size allowed for mother's car (she likes it)
  maxb2 = (maxb2 <= b1 - 1) ? maxb2 : (b1 - 1); // Ensure middle car < largest car
  if (minb2 > maxb2) {
    possible = false; // No valid size for mother's car
  } else {
    b2 = minb2; // Assign minimum valid size to mother's car
  }
  if (possible) {
    printf("%ld %ld %ld\n", b1, b2, b3); // Output valid car sizes
  } else {
    puts("-1"); // No valid configuration found
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/