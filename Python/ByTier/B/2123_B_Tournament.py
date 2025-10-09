# Problem: CF 2123 B - Tournament
# https://codeforces.com/contest/2123/problem/B

"""
B. Tournament

Purpose:
This code determines whether a specific player j can survive to be among the last k players in a tournament,
where players are eliminated based on strength comparisons. The key idea is to check if the strongest player 
among the last k players (in terms of index) can possibly remain in the final k players.

Algorithms/Techniques:
- Greedy approach with key insight: A player j can be among the last k players if either:
  1. Player j has the maximum strength in the array, or
  2. k > 1, which allows for more flexible tournament outcomes.

Time Complexity: O(n) per test case, where n is the number of players.
Space Complexity: O(n) due to the input list storage.

Input Format:
- t: number of test cases
- For each test case:
    - n, j, k: array size, player index (1-based), and number of final players
    - Array a of n integers representing player strengths

Output Format:
- "YES" if player j can be among the last k players, "NO" otherwise
"""

for _ in range(int(input())):  # Process each test case
    n, j, k = map(int, input().split())  # Read n, j, k
    lst = list(map(int, input().split()))  # Read the array of player strengths
    
    # Check if player j can be among the last k players:
    # Case 1: If player j has maximum strength, they can always win and stay.
    # Case 2: If k > 1, it's possible to rearrange tournament such that player j stays in final k players.
    if (lst[j - 1] == max(lst)) or k > 1:
        print("YES")
    else:
        print("NO")


# https://github.com/VaHiX/codeForces/