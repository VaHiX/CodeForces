// Problem: CF 1154 C - Gourmet Cat
// https://codeforces.com/contest/1154/problem/C

/*
C. Gourmet Cat
Algorithm: Greedy with cyclical pattern checking
Time Complexity: O(1) - since the cycle length is fixed (7 days), and we iterate over all possible starting days (7)
Space Complexity: O(1) - only using fixed-size arrays and variables

The problem involves determining the maximum number of consecutive days a cat can eat 
given a limited supply of 3 types of food, following a fixed weekly pattern:
- Monday, Thursday, Sunday: fish food
- Tuesday, Saturday: rabbit stew  
- Wednesday, Friday: chicken stake

Approach:
1. Precompute the weekly pattern in array 'a'
2. Use greedy method to first consume complete cycles of 7 days optimally
3. Try starting from each day of the week to find max consecutive eating days
4. For each starting day, simulate eating until no food left
5. Return total days = (complete cycles * 7) + maximum days in partial cycle
*/

#include <cstdio>
#include <vector>
int main() {
  long N = 7;
  std::vector<long> a(N);
  a[0] = a[3] = a[6] = 0;  // Monday, Thursday, Sunday -> fish food (index 0)
  a[1] = a[5] = 1;         // Tuesday, Saturday -> rabbit stew (index 1)  
  a[2] = a[4] = 2;         // Wednesday, Friday -> chicken stake (index 2)
  long b, c, d;
  scanf("%ld %ld %ld", &b, &c, &d);
  long m = (b / 3) < (c / 2) ? (b / 3) : (c / 2);  // Max complete cycles based on fish/rabbit constraint
  m = (m < d / 2) ? m : (d / 2);                   // Also limit by chicken stake
  b -= 3 * m;  // Remaining fish food after complete cycles
  c -= 2 * m;  // Remaining rabbit stew after complete cycles  
  d -= 2 * m;  // Remaining chicken stakes after complete cycles
  long mx(0);
  for (long s = 0; s < N; s++) {  // Try all possible starting days
    std::vector<long> f(3);       // Food supplies remaining for current trial
    f[0] = b;
    f[1] = c;
    f[2] = d;
    long dur(0);
    for (long p = 0; p < 2 * N; p++) {  // Simulate up to 2 weeks (since pattern repeats)
      long day = (s + p) % N;           // Determine which day of the week
      if (f[a[day]] > 0) {              // If food of required type is available
        --f[a[day]];                    // Eat one portion
        ++dur;                          // Increase duration
      } else {
        break;  // No more food of this type - can't continue
      }
    }
    mx = (mx > dur) ? mx : dur;  // Keep maximum duration found
  }
  mx += m * N;  // Add back the complete weeks eaten
  printf("%ld\n", mx);
  return 0;
}


// https://github.com/VaHiX/codeForces/