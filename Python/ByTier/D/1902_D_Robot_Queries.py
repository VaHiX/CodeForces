# Problem: CF 1902 D - Robot Queries
# https://codeforces.com/contest/1902/problem/D

"""
Algorithm/Techniques:
- Precompute prefix positions of the robot after executing each command in the sequence.
- For each query, determine if the robot reaches the target point (x, y) with the reversed substring from l to r.
- Use binary search (bisect) to efficiently check if a position is reached at a certain step or in a range.
- Key insight: if the path from l to r is reversed, the robot's position at any moment depends on:
  - The original starting prefix (before l),
  - The reversed path from l to r,
  - The suffix after r.

Time Complexity: O(n + q * log(n))
Space Complexity: O(n)

The algorithm precomputes all positions the robot reaches (O(n)), then answers queries in O(log(n)) per query.
"""

def main():
    import bisect
    import sys

    input = sys.stdin.readline
    n, q = map(int, input().split())
    s = input().strip()
    P = [(0, 0)]  # Prefix positions list: P[i] = position after i-th command
    moves = {"U": (0, 1), "D": (0, -1), "L": (-1, 0), "R": (1, 0)}
    for ch in s:
        dx, dy = moves[ch]
        last = P[-1]
        P.append((last[0] + dx, last[1] + dy))
    
    # Map each position to a list of indices where it appears in P
    pos_dict = {}
    for i, pos in enumerate(P):
        pos_dict.setdefault(pos, []).append(i)
    
    out_lines = []
    for _ in range(q):
        x, y, l, r = map(int, input().split())
        T = (x, y)  # Target position
        ans = False
        
        # Check if T is reachable at or before l or after r.
        if T in pos_dict:
            lst = pos_dict[T]
            if bisect.bisect_left(lst, l) > 0:  # Check if T is reached before l
                ans = True
            elif bisect.bisect_left(lst, r) < len(lst):  # Check if T is reached after r
                ans = True

        # If not found, we need to check if T is reachable as a result of reverse(l, r).
        # The new start position is P[l-1], end position is P[r].
        # To get to target T, the relative move from P[l-1] to T must be equal to reverse(l,r) path.
        # That means we check if P[r] + P[l-1] - T was visited within range [l, r].
        if not ans:
            Y = (P[r][0] + P[l - 1][0] - T[0], P[r][1] + P[l - 1][1] - T[1])
            if Y in pos_dict:
                lst = pos_dict[Y]
                idx = bisect.bisect_left(lst, l - 1)
                # Ensure the position Y was visited in [l, r].
                if idx < len(lst) and lst[idx] <= r:
                    ans = True
        
        out_lines.append("YES" if ans else "NO")
    
    sys.stdout.write("\n".join(out_lines))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/