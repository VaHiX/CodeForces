# Problem: CF 2022 D1 - Asesino (Easy Version)
# https://codeforces.com/contest/2022/problem/D1

"""
Algorithm: Asesino (Easy Version)
Purpose: Find the impostor among n players using at most n+69 questions.
Approach:
- We use a strategy based on identifying pairs of players that are not consistent with each other.
- For each pair (i, i+1), we ask two questions: i thinks i+1 is a knight, and i+1 thinks i is a knight.
- If the responses differ, then one of them must be the impostor (since impostors always lie).
- We then confirm by checking consistency with a third player (either 1 or n depending on the position).
- This approach leverages the fact that impostors will give contradictory answers when questioned about others.

Time Complexity: O(n) - Since we process at most n/2 pairs and perform a constant number of questions per pair.
Space Complexity: O(1) - Only using a few variables for the computation.
"""

import sys

input = lambda: sys.stdin.readline().rstrip()


def ask(i, j):
    # Ask player i if player j is a knight
    print(f"? {i} {j}", flush=True)
    reply = int(input())
    if reply == -1:
        exit()
    return reply


def answer(i):
    # Output the index of the impostor
    print(f"! {i}", flush=True)


def solve_case():
    n = int(input())
    # Iterate through pairs of players
    for i in range(1, n, 2):
        a = ask(i, i + 1)  # i thinks i+1 is a knight
        b = ask(i + 1, i)  # i+1 thinks i is a knight
        # If the responses differ, one of them is the impostor
        if a != b:
            # Determine which player to use for further confirmation
            j = n if i == 1 else 1
            a = ask(i, j)  # Check i thinks j is a knight
            b = ask(j, i)  # Check j thinks i is a knight
            # If the responses still differ, then i is the impostor
            if a != b:
                answer(i)
            else:
                # Otherwise, i+1 must be the impostor
                answer(i + 1)
            return
    # If all pairs were consistent, the last player must be the impostor
    answer(n)


for _ in range(int(input())):
    solve_case()


# https://github.com/VaHiX/CodeForces/