# Problem: CF 1970 F2 - Playing Quidditch (Medium)
# https://codeforces.com/contest/1970/problem/F2

"""
Code Purpose:
This program simulates a Quidditch game between two teams (Gryffindor and Ravenclaw) on a grid-based field. 
It tracks players, balls (Quaffle and Bludger), goals, and scoring actions. It supports movement, catching, and throwing of the Quaffle, with special rules including player elimination upon collision with a Bludger, and scoring when a Quaffle is placed in an opposing team's goal.

Algorithms/Techniques:
- Grid State Simulation: The game state is represented by a dictionary mapping entity identifiers to their positions.
- Event-based Simulation: Each game step is processed sequentially, with actions affecting entities and possible events such as scoring or elimination.
- Player Elimination Detection: At each movement, the position of each entity is compared with the Bludger's position to detect collisions.
- Goal Scoring: When a Quaffle is dropped in a goal, it checks the goal type to award points to the appropriate team.

Time Complexity: O(T * N * M) where T is the number of steps, and N, M are the dimensions of the grid.
Space Complexity: O(N * M) for storing the grid and entity positions.
"""

N, M = map(int, input().split())
field = [input().split() for _ in range(N)]
assert all(len(row) == M for row in field)
# pos maps entity identifiers (like "R0", "B0") to their [row, col] positions
pos = {
    ent: [r, c]
    for r, row in enumerate(field)
    for c, ent in enumerate(row)
    if ent not in ["..", "RG", "BG"]
}
score = [0, 0]
T = int(input())
for t in range(T):
    ent, arg, *opt = input().split()
    if arg in "UDLR":
        # Move entity in direction U, D, L, R
        d = "UDLR".index(arg)
        pos[ent][d // 2] += [-1, +1][d % 2]
        # Check for any player positions that match the Bludger's position
        elim = sorted(ent for ent in pos if ent[0] != "." and pos[ent] == pos.get(".B"))
        for ent in elim:
            print(t, ent, "ELIMINATED")
            del pos[ent]
    elif arg == "T":
        # Throw the Quaffle: check if in a goal
        r, c = pos[ent]
        g = field[r][c]
        if g[1] == "G":
            d = "BR".index(g[0])
            print(t, ["RED", "BLUE"][d], "GOAL")
            score[d] += 1
    else:
        assert arg == "C"
        [opt] = opt
        if opt == ".S":
            d = "RG".index(ent[0])
            print(t, ["RED", "BLUE"][d], "CATCH GOLDEN SNITCH")
            score[d] += 10
print("FINAL SCORE:", *score)


# https://github.com/VaHiX/CodeForces/