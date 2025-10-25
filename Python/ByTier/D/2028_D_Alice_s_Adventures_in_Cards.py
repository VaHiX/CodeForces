# Problem: CF 2028 D - Alice's Adventures in Cards
# https://codeforces.com/contest/2028/problem/D

"""
D. Alice's Adventures in Cards

Purpose:
This code determines whether Alice can trade cards from type 1 to type n using three players (Queen, King, and Jack), each with their own preference permutations. It simulates a valid sequence of trades based on the players' preferences and Alice's own preferences.

Algorithms/Techniques:
- Forward greedy simulation with precomputed reachable states
- Dynamic programming with backward pass to find minimal reachable indices
- Graph traversal using next pointers for output path reconstruction

Time Complexity: O(n) per test case
Space Complexity: O(n) per test case

Input Format:
- First line contains number of test cases t
- For each test case:
  - n (number of card types)
  - Three permutations representing preferences of Queen, King, and Jack
Output Format:
- "YES" followed by number of trades and trade details if possible,
  otherwise "NO"
"""

import sys

input = sys.stdin.readline
W = ["q", "k", "j"]


def solve():
    n = int(input())
    P = []
    for _ in range(3):
        P.append(list(map(int, input().split())))
    
    # min_to_reach[j] stores the index of the minimum card in row j that can be reached
    min_to_reach = [n - 1] * 3
    
    # nxt[i] stores the next index to jump to when starting at index i
    nxt = [-1] * n
    
    # ans[i] stores which player (0, 1, or 2) allows us to move from position i
    ans = [-1] * n
    
    # Traverse backwards from n-2 to 0
    for i in range(n - 2, -1, -1):
        for j in range(3):
            # If current card (i) is preferred more than the best known card so far for player j
            if P[j][i] > P[j][min_to_reach[j]]:
                # Record that we move using player j to reach min_to_reach[j]
                ans[i] = j
                nxt[i] = min_to_reach[j]
                
                # Update the minimum reachable card indices (for all players)
                for k in range(3):
                    if P[k][min_to_reach[k]] > P[k][i]:
                        min_to_reach[k] = i
                
                break  # Found a valid move, no need to check other players
    
    # If we cannot start from card 1 (index 0), impossible
    if ans[0] == -1:
        return "NO"
    
    res = []
    curr = 0
    while curr != n - 1:
        # Add the trade: player W[ans[curr]] gives card nxt[curr] + 1 to Alice
        res.append(f"{W[ans[curr]]} {nxt[curr] + 1}")
        # Move to next card in the path
        curr = nxt[curr]
    
    return f"YES\n{len(res)}\n" + "\n".join(res)


T = int(input())
out = [solve() for _ in range(T)]
print("\n".join(map(str, out)))


# https://github.com/VaHiX/codeForces/