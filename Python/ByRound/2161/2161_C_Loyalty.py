# Problem: CF 2161 C - Loyalty
# https://codeforces.com/contest/2161/problem/C

"""
Algorithm: Greedy approach to maximize bonus points
Approach:
1. Sort items in ascending order to process smaller items first
2. Use two pointers (i, j) to decide which item to buy next:
   - If buying the largest remaining item (a[j]) increases loyalty level, buy it
   - Otherwise, buy the smallest remaining item (a[i]) to minimize cost of loyalty increase
3. This ensures we get maximum bonus points by prioritizing items that cause loyalty increases

Time Complexity: O(n log n) due to sorting
Space Complexity: O(n) for storing the input and output
"""

import sys

input = lambda: sys.stdin.readline().rstrip()

ii = lambda: int(input())
mii = lambda: map(int, input().split())
lii = lambda: list(mii())
answers = []
for _ in range(int(input())):
    n, x = mii()
    a = lii()

    i, j = 0, n - 1
    a.sort()
    lit = []
    ans, s = 0, 0
    while i <= j:
        # Check if buying the largest remaining item increases loyalty level
        if (s + a[j]) // x > s // x:
            s += a[j]
            ans += a[j]
            lit.append(a[j])
            j -= 1
        else:
            # Buy the smallest item to minimize cost of next loyalty increase
            s += a[i]
            lit.append(a[i])
            i += 1
    ans = str(ans) + "\n" + " ".join(map(str, lit))
    ans = str(ans)
    answers.append(ans)
print("\n".join(answers))


# https://github.com/VaHiX/CodeForces/