# Problem: CF 1821 E - Rearrange Brackets
# https://codeforces.com/contest/1821/problem/E

"""
Algorithm/Technique:
- The problem involves finding the minimum cost of a bracket sequence after at most k operations.
- The key insight is to compute the "cost" of each matching pair of brackets.
- For a pair of brackets at positions j and i (where j < i), the cost is (i - j - 1) // 2. This represents the number of brackets between them.
- After computing all costs, we sort them in descending order to prioritize removing the most expensive pairs.
- Then we remove up to k pairs and sum the remaining costs.
- This greedy strategy works because we always want to eliminate the most costly pairs to minimize total cost.

Time Complexity: O(n log n), where n is the length of the string. Sorting costs takes O(n log n) time.
Space Complexity: O(n), for storing the stack and costs list.
"""

import sys

input = sys.stdin.readline


def solve():
    k = int(input())
    s = input().rstrip()
    left = []  # Stack to keep track of indices of '('
    costs = []  # List to store costs of each matching pair
    for i, char in enumerate(s):
        if char == "(":
            left.append(i)  # Push index of '(' to stack
        else:
            j = left.pop()  # Pop matching '(' index
            costs.append((i - j - 1) // 2)  # Compute cost of this pair

    costs.sort(reverse=True)  # Sort in descending order to prioritize high-cost pairs
    ans = sum(costs[k:])  # Sum all costs except the first k (most expensive) ones
    return ans


T = int(input())
out = [solve() for _ in range(T)]
print("\n".join(map(str, out)))


# https://github.com/VaHiX/CodeForces/