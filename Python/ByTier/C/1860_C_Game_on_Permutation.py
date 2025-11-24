# Problem: CF 1860 C - Game on Permutation
# https://codeforces.com/contest/1860/problem/C

"""
Algorithm: Game on Permutation
Techniques: Greedy, Array Traversal

Time Complexity: O(n) per test case
Space Complexity: O(1)

The problem is about determining the number of "lucky" elements in a permutation,
where an element is lucky if Alice can guarantee a win by placing the chip on it
initially, regardless of Bob's moves.

The key insight is to traverse the array from left to right and keep track of:
1. `bound` - the upper limit for valid moves
2. `mi` - the minimum value seen so far to the left
3. `ans` - the number of lucky elements

For each element:
- If it's greater than `bound`, skip it (cannot move here)
- If it's less than `mi`, update `mi` (potential new minimum)
- Otherwise, it's a lucky element, increment `ans` and update `bound`

This greedy approach works because it simulates the optimal play where Alice
chooses the best possible starting positions to ensure victory.
"""

import sys

input = sys.stdin.readline


def readList():
    return list(map(int, input().split()))


def readInt():
    return int(input())


def readInts():
    return map(int, input().split())


def readStr():
    return input().strip()


def solve():
    n, arr = readInt(), readList()
    bound, mi, ans = n + 1, arr[0], 0
    for i in range(1, n):
        if arr[i] > bound:
            continue
        if arr[i] < mi:
            mi = arr[i]
        else:
            ans += 1
            bound = arr[i]
    return ans


for _ in range(int(input())):
    print(solve())


# https://github.com/VaHiX/CodeForces/