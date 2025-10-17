# Problem: CF 1970 F1 - Playing Quidditch (Easy)
# https://codeforces.com/contest/1970/problem/F1

"""
Quidditch Game Scoring System

Algorithms/Techniques:
- Grid simulation with hash maps for tracking entities
- State machine for ball handling (free/carrying)
- Movement and action processing in order
- Goal detection upon ball placement

Time Complexity: O(N * M + T * K) where N and M are grid dimensions, T is number of steps, K is average moves per step (constant in practice)
Space Complexity: O(N * M + P) where P is number of players, for storing grid state and player positions

The code simulates a Quidditch match between two teams (Red and Blue), tracking player movements,
ball carrying, and scoring events. Players can move, catch the Quaffle, and throw it. When a player
throws the Quaffle into the opposing team's goal, that team scores a point. The Quaffle respawns
at the center of the field after each goal. The output lists the time and team of each goal
followed by the final score.
"""

def main():
    import sys

    data = sys.stdin.read().splitlines()
    if not data:
        return
    n, m = map(int, data[0].split())
    red_goals = set()
    blue_goals = set()
    players = {}
    quaffle = {"state": "free", "position": None}
    mid_pos = ((n - 1) // 2, (m - 1) // 2)
    index = 1
    for i in range(n):
        line = data[index].split()
        index += 1
        for j in range(m):
            cell = line[j]
            if cell == "RG":
                red_goals.add((i, j))
            elif cell == "BG":
                blue_goals.add((i, j))
            elif cell == ".Q":
                quaffle["position"] = (i, j)
            elif cell != "..":
                players[cell] = (i, j)
    T = int(data[index])
    index += 1
    moves = {"U": (-1, 0), "D": (1, 0), "L": (0, -1), "R": (0, 1)}
    red_score = 0
    blue_score = 0
    for step_index in range(T):
        line = data[index]
        index += 1
        parts = line.split()
        entity_str = parts[0]
        action = parts[1]
        ball_str = parts[2] if len(parts) >= 3 else None
        if entity_str in players:
            r0, c0 = players[entity_str]
            if action in moves:
                dr, dc = moves[action]
                new_r = r0 + dr
                new_c = c0 + dc
                players[entity_str] = (new_r, new_c)
            elif action == "C":
                if ball_str == ".Q":
                    if quaffle["state"] == "free":
                        if quaffle["position"] == (r0, c0):
                            quaffle["state"] = entity_str
            elif action == "T":
                if quaffle["state"] == entity_str:
                    quaffle["state"] = "free"
                    quaffle["position"] = (r0, c0)
        elif entity_str == ".Q":
            if quaffle["state"] == "free":
                if action in moves:
                    dr, dc = moves[action]
                    rq, cq = quaffle["position"]
                    new_r = rq + dr
                    new_c = cq + dc
                    quaffle["position"] = (new_r, new_c)
        if quaffle["state"] == "free":
            q_pos = quaffle["position"]
            if q_pos in red_goals:
                blue_score += 1
                print(f"{step_index} BLUE GOAL")
                quaffle["position"] = mid_pos
            elif q_pos in blue_goals:
                red_score += 1
                print(f"{step_index} RED GOAL")
                quaffle["position"] = mid_pos
    print(f"FINAL SCORE: {red_score} {blue_score}")


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/