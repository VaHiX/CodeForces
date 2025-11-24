# Problem: CF 1779 E - Anya's Simultaneous Exhibition
# https://codeforces.com/contest/1779/problem/E

"""
Algorithm/Technique:
This solution uses a greedy approach combined with binary search logic to identify candidate masters.
The key idea is to sort players by their simulated wins and then greedily determine which players can potentially win a tournament by checking if they beat a subset of previously considered candidates.

Steps:
1. First, we query each player against all others to determine how many games they win. This gives us initial ranking.
2. We sort the players by number of wins in descending order.
3. Then, we use a greedy method to determine a subset of players who could potentially win a tournament.
   - For each player in the sorted list, we test if they can beat the current candidate set.
   - If they can beat at least one player in the set, we include them in the final set.
4. Finally, we output the indices of players who can be candidate masters.

Time Complexity: O(n^2) in the worst case due to multiple queries, each potentially involving up to n players.
Space Complexity: O(n) for storing intermediate results and player data.
"""

def query(guy, ppl):
    # Prepare the binary string for the query
    v = [0] * n
    for t in ppl:
        v[t] = 1
    v[guy] = 0  # A player cannot play against themselves
    print("?", guy + 1, "".join(str(r) for r in v), flush=True)
    return int(input())


def ans(ppl):
    # Output the result as a binary string indicating candidate masters
    v = [0] * n
    for t in ppl:
        v[t] = 1
    print("!", "".join(str(r) for r in v), flush=True)


n = int(input())
# Query each player against all others to get win counts and player indices
a = [(query(i, list(range(n))), i) for i in range(n)]
# Sort by number of wins in descending order
a.sort(key=lambda x: -x[0])

cut = 1  # Initial cut-off point for candidate set
# Greedily expand the candidate set
for i in range(1, n):
    # Test current player against the set of possible candidates so far
    test = [a[j][1] for j in range(cut)]
    if query(a[i][1], test) > 0:
        # If the current player can beat someone in the candidate set, include them
        cut = i + 1

# Output the final list of candidate masters
ans([a[j][1] for j in range(cut)])


# https://github.com/VaHiX/CodeForces/