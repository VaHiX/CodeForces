# Problem: CF 1984 D - ''a'' String Problem
# https://codeforces.com/contest/1984/problem/D

"""
Algorithm/Techniques: Z-function, prefix analysis, and iterative enumeration.
Time Complexity: O(n^2) in the worst case, but typically much better due to early termination and z-function optimizations.
Space Complexity: O(n) for storing the Z-array and auxiliary arrays.

This solution counts how many valid strings t (not equal to "a") can be used to partition a given string s,
such that each partition is either "a" or t, and at least one partition is t.
"""

def z_function(s: str) -> list[int]:
    n = len(s)
    z = [0] * n
    l, r = 0, 0
    for i in range(1, n):
        if i < r:
            z[i] = min(r - i, z[i - l])
        while i + z[i] < n and s[z[i]] == s[i + z[i]]:
            z[i] += 1
        if i + z[i] > r:
            l, r = i, i + z[i]
    return z


def solve():
    import sys

    input = sys.stdin.read
    data = input().split()
    t = int(data[0])
    idx = 1
    for _ in range(t):
        s = data[idx]
        idx += 1
        n = len(s)
        # nona[i] stores the index of the next non-'a' character from position i
        nona = [n] * n
        for i in range(n - 1, -1, -1):
            if s[i] != "a":
                nona[i] = i
            elif i + 1 < n:
                nona[i] = nona[i + 1]
        # If all characters in s are 'a', answer is n - 1
        if nona[0] == n:
            print(n - 1)
            continue
        # Find the first non-'a' character
        i1 = nona[0]
        # Extract substring starting from first non-'a'
        s2 = s[i1:]
        # Compute Z-function for this substring
        z = z_function(s2)
        ans = 0
        # Try all possible lengths of t (from 1 to len(s2))
        for length in range(1, n - i1 + 1):
            cur = i1 + length
            mn = i1
            works = True
            # Check if a valid partition exists with this length
            while cur < n:
                if nona[cur] == n:
                    break
                bt = nona[cur] - cur
                mn = min(mn, bt)
                cur += bt
                # Use z-function to verify match
                if z[cur - i1] < length:
                    works = False
                    break
                cur += length
            if works:
                ans += mn + 1
        print(ans)


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/CodeForces/