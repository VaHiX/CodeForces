# Problem: CF 1860 B - Fancy Coins
# https://codeforces.com/contest/1860/problem/B

"""
Algorithm: Greedy with Coin Selection
Purpose: To find the minimum number of fancy coins needed to pay exactly m burles,
         using two types of coins (1 burle and k burles), with limited regular coins.
         Fancy coins are preferred to be used minimally.

Approach:
1. First, greedily use as many regular k-burle coins as possible to minimize fancy coins.
2. Then, fill the remaining amount with regular 1-burle coins.
3. If there aren't enough regular 1-burle coins, make up the difference using fancy coins.
4. Finally, adjust by using fancy k-burle coins to reduce the number of fancy 1-burle coins used.

Time Complexity: O(1) - Only constant time operations are performed per test case.
Space Complexity: O(t) - Space used to store answers for t test cases.
"""

import sys

input = sys.stdin.readline
print = sys.stdout.write
t = int(input())
ans = [0] * t
for i in range(t):
    m, k, a1, ak = map(int, input().split())
    # Calculate how many k-burle coins are needed to make up m
    cnt_ak = m // k
    # Calculate the remaining amount after using k-burle coins
    cnt_a1 = m % k
    # Use regular 1-burle coins to cover the remainder, but not more than available
    use_a1 = min(a1, cnt_a1)
    a1 -= use_a1
    cnt_a1 -= use_a1
    # Use regular k-burle coins to reduce fancy coin usage, but not more than available
    cnt_ak -= min(ak, cnt_ak)
    # Adjust remaining 1-burle coins to cover any shortage with fancy k-burle coins
    cnt_ak -= min(a1 // k, cnt_ak)
    ans[i] = str(cnt_a1 + cnt_ak)
print("\n".join(ans))


# https://github.com/VaHiX/CodeForces/