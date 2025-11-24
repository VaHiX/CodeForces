# Problem: CF 2062 B - Clockwork
# https://codeforces.com/contest/2062/problem/B

# B. Clockwork
# Purpose: Determine if it's possible to move between clocks and reset their times infinitely without any clock reaching 0.
# Algorithm: For each possible starting position, compute a minimum time needed to move and reset, then check if the minimum time is enough to sustain movement.
# Time complexity: O(n) per test case
# Space complexity: O(1)

for s in [*open(0)][2::2]:
    a = s.split()
    print(
        "NYOE S"[all(i * 2 < int(x) > len(a) + ~i << 1 for i, x in enumerate(a)) :: 2]
    )


# https://github.com/VaHiX/codeForces/