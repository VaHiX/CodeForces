// Problem: CF 1214 B - Badges
// https://codeforces.com/contest/1214/problem/B

/*
B. Badges
Purpose: Determine the minimum number of badge decks to ensure coverage for any combination of boys and girls among n participants.

Algorithm:
- The problem involves selecting the minimal number of decks from n+1 possible decks,
  where each deck i contains i blue badges and (n-i) red badges.
- For a valid selection, every possible distribution of b boys and g girls among n participants must be covered by at least one selected deck.
- This is modeled as interval coverage: for any valid split (x boys, n-x girls) with x ranging from max(0, n-g) to min(n, b),
  we must select enough decks such that their ranges cover all necessary combinations.
- The approach uses the concept of overlapping intervals:
  - Find minimum needed blue count (mnb) and maximum blue count (mxb) for valid selections.
  - Then the number of decks needed is (mxb - mnb + 1).

Time Complexity: O(1)
Space Complexity: O(1)

Input
The first line contains an integer b (1 <= b <= 300), the number of boys. 
The second line contains an integer g (1 <= g <= 300), the number of girls. 
The third line contains an integer n (1 <= n <= b + g), the number of the board games tournament participants.
Output
Output the only integer, the minimum number of badge decks that Vasya could take.
*/

#include <cstdio>
int main() {
  long b, g, n;
  scanf("%ld %ld %ld", &b, &g, &n);
  long mnb(0), mxb(b); // mnb: minimum required blue badges; mxb: maximum required blue badges
  if (g < n) {         // Adjust lower bound if not enough girls to fill all spots
    mnb = n - g;
  }
  if (n < b) {         // Adjust upper bound if not enough boys to fill all spots
    mxb = n;
  }
  printf("%ld\n", mxb - mnb + 1); // Number of decks needed
  return 0;
}


// https://github.com/VaHiX/codeForces/