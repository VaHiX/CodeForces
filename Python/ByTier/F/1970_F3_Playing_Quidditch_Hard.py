# Problem: CF 1970 F3 - Playing Quidditch (Hard)
# https://codeforces.com/contest/1970/problem/F3

"""
Code Purpose:
This code simulates a Quidditch game based on a given field setup and sequence of actions. 
It tracks player positions, ball movement, scoring, eliminations, and Golden Snitch catches to determine the final score.

Algorithms/Techniques:
- Simulation-based approach to model game state
- Hash map for O(1) lookup of entity positions
- Coordinate movement in grid using direction mapping
- Event-based triggers (scoring, elimination, catching Snitch)
- Sorting for consistent output order of eliminated players

Time Complexity: O(T * N * M) where T is number of steps, N and M are dimensions of grid
Space Complexity: O(N * M) for storing field and position mappings

"""

N, M = map(int, input().split())
field = [input().split() for _ in range(N)]
assert all(len(row) == M for row in field)
pos = {
    ent: [r, c]
    for r, row in enumerate(field)
    for c, ent in enumerate(row)
    if ent not in ["..", "RG", "BG"]  # Exclude empty cells and goals
}
score = [0, 0]  # [Red score, Blue score]
T = int(input())
for t in range(T):
    ent, arg, *opt = input().split()
    if arg in "UDLR":
        # Process movement action
        d = "UDLR".index(arg)
        pos[ent][d // 2] += [-1, +1][d % 2]  # Move in direction
        # Check if any player is on Bludger's position and get eliminated
        elim = sorted(ent for ent in pos if ent[0] != "." and pos[ent] == pos.get(".B"))
        for ent in elim:
            print(t, ent, "ELIMINATED")
            del pos[ent]  # Remove eliminated player
    elif arg == "T":
        # Process throwing the Quaffle
        r, c = pos[ent]
        g = field[r][c]
        if g[1] == "G":
            # Check if thrown into a goal
            d = "BR".index(g[0])  # Determine which team scored
            print(t, ["RED", "BLUE"][d], "GOAL")
            score[d] += 1
    else:
        # arg == "C" - Catching action
        assert arg == "C"
        [opt] = opt
        if opt == ".S":
            # Catching the Golden Snitch
            d = "RB".index(ent[0])  # Determine which team caught Snitch
            print(t, ["RED", "BLUE"][d], "CATCH GOLDEN SNITCH")
            score[d] += 10  # Award bonus points
print("FINAL SCORE:", *score)


# https://github.com/VaHiX/CodeForces/