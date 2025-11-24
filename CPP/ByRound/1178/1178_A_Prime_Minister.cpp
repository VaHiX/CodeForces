// Problem: CF 1178 A - Prime Minister
// https://codeforces.com/contest/1178/problem/A

/*
Code Purpose:
This program determines whether Alice (party 1) can form a coalition to become the prime minister, 
satisfying two conditions:
1. The coalition must have more than half the total seats (strict majority).
2. Alice's party must have at least twice as many seats as any other party in the coalition.

Algorithm/Techniques:
- Greedy approach: Try including parties one by one starting from party 2, 
  checking if the coalition still satisfies both conditions.
- Time Complexity: O(n), where n is the number of parties.
- Space Complexity: O(1), only using a fixed-size array and a few variables.

*/

#include <cstdio>

using namespace std;

int a[101], n, s, i, p, j, S;

int main() {
  // Read input and process parties
  for (; scanf("%d", i ? a + i : &n) > 0; ++i)
    i ? i ^ 1 ?: p = a[i], i == 1 | 2 * a[i] <= p ? S += a[i],
                 a[++*a] = i : s += a[i] : 0;
  
  // Check if coalition formed with Alice's party satisfies majority condition
  if (S > s)
    // Print the indices of parties included in coalition
    for (; j <= *a; ++j)
      printf("%d ", a[j]);
  else
    // No valid coalition found
    puts("0");
}


// https://github.com/VaHiX/CodeForces/