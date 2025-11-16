# Problem: CF 1285 B - Just Eat It!
# https://codeforces.com/contest/1285/problem/B

"""
B. Just Eat It!
Algorithm: Prefix Sum with Suffix Sum
Time Complexity: O(n) per test case
Space Complexity: O(1)

The problem requires determining if Yasser's total tastiness (sum of all cupcakes) 
is strictly greater than the maximum possible sum Adel can achieve by choosing 
any contiguous segment [l, r] where l != 1 and r != n.

Key Insight:
- Yasser always takes all cupcakes, so his total is the sum of array.
- Adel chooses a segment that does not include all elements (not [1,n]).
- We compute prefix sums from left and suffix sums from right.
- If any prefix or suffix sum is non-positive, then there exists a valid segment 
  with sum >= Yasser's total, making the answer "NO".

Approach:
- For each test case, compute prefix and suffix sums.
- Track if any prefix or suffix sum becomes non-positive.
- If such a sum is found, output "NO"; otherwise, "YES".
"""

from sys import stdin

input = lambda: stdin.readline().strip()
for _ in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    s1, s2 = 0, 0
    for i in range(n):
        s1 += a[i]           # prefix sum from left
        s2 += a[-i - 1]      # suffix sum from right
        if s1 <= 0 or s2 <= 0:  # if any prefix or suffix sum is non-positive
            print("NO")
            break
    else:
        print("YES")


# https://github.com/VaHiX/codeForces/