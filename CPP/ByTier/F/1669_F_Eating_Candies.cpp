// Problem: CF 1669 F - Eating Candies
// https://codeforces.com/contest/1669/problem/F

/*
F. Eating Candies
Algorithm: Two Pointers
Time Complexity: O(n) per test case
Space Complexity: O(n) due to vector storage

Alice eats candies from the left in a row, Bob eats candies from the right in a row.
Goal: Maximize total candies eaten such that Alice's total weight = Bob's total weight.
Approach:
- Use two pointers (left and right) to simulate eating from both ends
- Keep track of weights eaten by each person (wa and wb)
- Increment counters (cnta, cntb) as candies are eaten
- When weights become equal, update the answer with the total candies eaten so far
- Continue until all candies are considered or one side runs out

Sample Input:
4
3
10 20 10
6
2 1 4 2 4 1
5
1 2 4 8 16
9
7 3 20 5 15 1 11 8 10

Sample Output:
2
6
0
7
*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> w(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &w[p]);
    }
    long left(-1), right(n), cnta(0), cntb(0), wa(0), wb(0), ans(0);
    while (cnta + cntb < n) { // Continue while not all candies eaten
      if (wa <= wb) { // If Alice's weight is less than or equal to Bob's
        ++left; // Move Alice's pointer to the right (eat next candy)
        ++cnta; // Increment Alice's candy count
        wa += w[left]; // Add candy weight to Alice's total
      } else { // If Bob's weight is less than Alice's
        --right; // Move Bob's pointer to the left (eat previous candy)
        ++cntb; // Increment Bob's candy count
        wb += w[right]; // Add candy weight to Bob's total
      }
      if (wa == wb) { // If both have equal weights
        ans = cnta + cntb; // Update maximum candies eaten
      }
    }
    printf("%ld\n", ans);
  }
}


// https://github.com/VaHiX/codeForces/