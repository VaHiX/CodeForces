# Problem: CF 1610 G - AmShZ Wins a Bet
# https://codeforces.com/contest/1610/problem/G

"""
Algorithm: Binary Lifting + Stack-based Approach for Bracket Sequence Reconstruction
Time Complexity: O(n log n) where n is the length of the string
Space Complexity: O(n log n) for storing the binary lifting tables P and H

This solution reconstructs the lexicographically smallest possible bracket sequence 
that could result in the given sequence after performing the allowed operations.

The key idea is to process the string from right to left and use a stack to maintain 
indices of unmatched opening brackets. Binary lifting is used to compare prefixes 
efficiently to determine the lexicographically smallest configuration.

The algorithm uses:
1. A stack to track unmatched brackets
2. Binary lifting tables P and H for efficient prefix comparison
3. A method to determine when to replace a bracket in the sequence
"""

import sys

raw_input = sys.stdin.readline


def binary_lifting(P, H, u, v):
    # Compare prefixes using binary lifting to determine lexicographical order
    for i in reversed(range(len(P[u]))):
        if i < min(len(H[u]), len(H[v])) and H[u][i] == H[v][i]:
            u, v = P[u][i], P[v][i]
    return (not H[u] and H[v]) or (H[u] and H[v] and H[u][0] < H[v][0])


def update_infos(s, nxt, i, P, H):
    # Update the binary lifting tables P and H for the current index
    P[i].append(nxt[i + 1])
    H[i].append(int(s[i] == ")"))
    j, base = 0, 2
    while j < len(P[i]) and j < len(P[P[i][j]]):
        P[i].append(P[P[i][j]][j])
        H[i].append((H[i][j] * base + H[P[i][j]][j]) % MOD)
        j += 1
        base = (base * base) % MOD


def solution():
    s = input().strip()
    stk, nxt = [len(s)], list(range(len(s) + 1))
    # Initialize P and H for binary lifting
    P, H = [[[] for _ in range(len(s) + 1)] for _ in range(2)]
    for i in reversed(range(len(s))):
        update_infos(s, nxt, i, P, H)
        if s[i] == ")":
            # Push index of closing bracket
            stk.append(i)
            continue
        # Pop matching closing bracket
        stk.pop()
        if not stk:
            # No more unmatched brackets, start new stack
            stk.append(i)
        elif binary_lifting(P, H, i, stk[-1]):
            # Current bracket should be replaced to get lexicographically smaller string
            stk[-1] = i
        else:
            # Update next position for replacement
            nxt[i] = stk[-1]
    
    # Reconstruct final string after applying operations
    result = []
    i = 0
    while i < len(s):
        result.append(s[i])
        i = nxt[i + 1]
    return "".join(result)


MOD = 10**9 + 7
print("%s" % solution())


# https://github.com/VaHiX/CodeForces/