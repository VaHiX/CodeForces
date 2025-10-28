# Problem: CF 1994 B - Fun Game
# https://codeforces.com/contest/1994/problem/B

"""
Algorithm: 
The key insight is to understand that the allowed operation allows us to xor a segment of the sequence s with a prefix of s. 
This means that we can effectively shift the pattern and apply xor operations. 

The approach is based on:
1. Finding the first occurrence of '1' in both sequences s and t.
2. If s has no '1's, then t must also have no '1's to be convertible.
3. If s has a '1' at position p, then t must have a '1' at a position >= p to be convertible.

Time Complexity: O(n) where n is the length of the sequences. We scan each sequence at most once per test case.
Space Complexity: O(1) as we are only using a constant amount of extra space.
"""

import sys


def solve() -> None:
    data = sys.stdin.read().split()
    it = iter(data)
    q = int(next(it))
    out_lines = []
    for _ in range(q):
        n = int(next(it))
        s = next(it).strip()
        t = next(it).strip()
        p = s.find("1")  # Find first '1' in s
        if p == -1:
            p = n  # If no '1' found, set to n
        qpos = t.find("1")  # Find first '1' in t
        if qpos == -1:
            qpos = n  # If no '1' found, set to n
        if p == n:
            # If s has no '1's, then t must also have no '1's
            ans = qpos == n
        else:
            # If s has a '1' at position p, then t must have a '1' at position >= p
            ans = qpos >= p
        out_lines.append("YES" if ans else "NO")
    sys.stdout.write("\n".join(out_lines))


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/CodeForces/