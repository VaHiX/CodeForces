# Problem: CF 730 A - Toda 2
# https://codeforces.com/contest/730/problem/A

"""
Algorithm: Greedy approach to equalize ratings
Techniques: 
- Iteratively reduce the maximum rating(s) by 1 in each match
- Always form a party of 2-5 members to play matches
- Use greedy strategy to maximize final rating

Time Complexity: O(n * R_max) where R_max is the maximum initial rating
Space Complexity: O(n * t) where t is the number of matches played

The algorithm works by:
1. Repeatedly finding the maximum rating
2. Selecting a subset of players (2-5) to form a party
3. Reducing the ratings of party members by 1
4. Continue until all ratings are equal
"""

N = int(input())
R = [*map(int, input().split())]
ans = []
while not all(x == R[0] for x in R):  # Continue until all ratings are equal
    m = max(R)  # Find maximum rating
    i = [i for i, x in enumerate(R) if x == m]  # Get indices of all players with max rating
    if len(i) == 1:  # If only one player has max rating
        # Select that player and the player with second highest rating
        j = R.index(sorted(R)[-2])
        curr = [i[0], j]
    elif len(i) == 3:  # If exactly 3 players have max rating
        # Select all 3 players
        curr = i[:3]
    else:  # If more than 3 players have max rating
        # Select any 2 players with max rating
        curr = i[:2]
    for j in curr:  # Reduce ratings of party members
        R[j] = max(0, R[j] - 1)
    # Record match outcome as a binary string
    ans.append("".join("01"[j in curr] for j in range(len(R))))
print(R[0])  # Print final equal rating
print(len(ans))  # Print number of matches
print(*ans, sep="\n")  # Print match outcomes


# https://github.com/VaHiX/CodeForces/