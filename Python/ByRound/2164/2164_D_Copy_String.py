# Problem: CF 2164 D - Copy String
# https://codeforces.com/contest/2164/problem/D

"""
Algorithm: String Transformation with Limited Operations
Approach:
    - The key idea is to determine the minimum number of operations required to transform string `s` to `t`.
    - Each operation allows us to construct a new string `s'` where each character can either be:
        - The same as the corresponding character in `s`, or
        - The character from the previous position in `s` (to propagate forward).
    - We are constrained by a maximum number of operations `kmax`.

Complexity:
    - Time Complexity: O(n * kmax), where n is the length of the string and kmax is the maximum allowed operations.
    - Space Complexity: O(n * kmax), to store the intermediate transformation steps and the strings.

Techniques Used:
    - Greedy approach to determine positions of characters in `t` relative to `s`.
    - Preprocessing the positions to compute minimum operations needed.
    - Simulating the transformation steps to build the result.

The solution identifies the minimal number of steps by:
1. Finding how far each character in `t` can be reached from `s`.
2. Ensuring that we do not exceed `kmax`.
3. Performing actual simulations only when needed.
"""

import sys

input = sys.stdin.readline


def solver():
    t = int(input().strip())
    out_lines = []
    for _ in range(t):
        n, kmax = map(int, input().split())
        st = input().strip()
        tt = input().strip()

        if st == tt:
            out_lines.append(str(0))
            continue

        # v[i] will store the position in s where the character t[i] is found
        v = [-1] * n
        ma = 0
        p1 = n - 1
        ok = True
        for i in range(n - 1, -1, -1):
            if p1 > i:
                p1 = i
            # Find the last position in s where character tt[i] appears
            while p1 >= 0 and st[p1] != tt[i]:
                p1 -= 1
            if p1 < 0:
                ok = False
                break
            v[i] = p1
            if i - p1 > ma:
                ma = i - p1

        if not ok or ma > kmax:
            out_lines.append("-1")
            continue

        if ma == 0:
            out_lines.append("0")
            continue

        # last keeps track of current index mapping
        last = list(range(n))
        tans = []
        for _ in range(ma):
            temp = last[:]
            temp[0] = last[0]
            for j in range(1, n):
                if last[j] != v[j]:
                    temp[j] = last[j - 1]
                else:
                    temp[j] = last[j]
            tans.append(temp)
            last = temp

        out_lines.append(str(ma))
        for idx_map in tans:
            out_lines.append("".join(st[pos] for pos in idx_map))

    sys.stdout.write("\n".join(filter(None, out_lines)))


if __name__ == "__main__":
    solver()


# https://github.com/VaHiX/CodeForces/