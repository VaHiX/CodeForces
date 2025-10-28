# Problem: CF 1923 B - Monsters Attack!
# https://codeforces.com/contest/1923/problem/B

"""
Algorithm: Greedy + Prefix Sum
Time Complexity: O(n) per test case, where n is the number of monsters.
Space Complexity: O(n) for the prefix sum array.

The approach uses a greedy strategy where we process monsters from the farthest
from the player (in absolute value of position) to the closest. For each position,
we calculate how many bullets are needed to kill monsters at that distance.
We maintain a running count (`lft`) of available bullets and ensure it never goes negative,
which would mean we can't kill all monsters in time before they reach the player.
"""

import sys


def main():
    input = sys.stdin.read
    data = input().split()
    index = 0
    t = int(data[index])
    index += 1
    results = []
    for _ in range(t):
        n = int(data[index])
        k = int(data[index + 1])
        index += 2
        a = list(map(int, data[index : index + n]))
        index += n
        x = list(map(int, data[index : index + n]))
        index += n
        # Create a prefix sum array to count total health at each distance
        s = [0] * (n + 1)
        for i in range(n):
            s[abs(x[i])] += a[i]
        ok = True
        lft = 0
        # Traverse from farthest to closest distance
        for i in range(1, n + 1):
            lft += k - s[i]  # Update available bullets
            ok &= lft >= 0   # Check if we have enough bullets
        results.append("YES" if ok else "NO")
    print("\n".join(results))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/