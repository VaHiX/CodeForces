# Problem: CF 1956 A - Nene's Game
# https://codeforces.com/contest/1956/problem/A

"""
Algorithm: Simulation of a game where players are removed based on a sequence of indices.

Approach:
- For each initial number of players `n`, simulate the game by repeatedly removing players at positions specified by the sequence `a`.
- In each round, check if the required positions exist in the current lineup. If yes, remove the corresponding players.
- Continue until no more players can be removed in a round.
- Return the count of remaining players (winners).

Time Complexity: O(q * n^2) in worst case due to simulation and list operations.
Space Complexity: O(k + q) for storing the sequence and query answers.

Techniques:
- Simulation with list manipulation
- Iterative removal based on index positions
"""

def i():
    input()  # Read and discard the line (not used)
    n = min(map(int, input().split())) - 1  # Get the value of n from first query
    s = [str(min(n, x)) for x in map(int, input().split())]  # Process sequence elements
    return " ".join(s)  # Return processed results as space-separated string


t = int(input())  # Number of test cases
a = []
for _ in range(t):
    a.append(i())  # Process each test case
print("\n".join(a))  # Output all results


# https://github.com/VaHiX/CodeForces/