# Problem: CF 2171 H - Shiori Miyagi and Maximum Array Score
# https://codeforces.com/contest/2171/problem/H

"""
Algorithm: Dynamic Programming with Optimization
Time Complexity: O(n * sqrt(m) * log(m) + n * m * log(m))
Space Complexity: O(m * log(m))

This solution uses a dynamic programming approach to find the maximum score
for an array of length n with elements bounded by m. For each position i in the
array, we calculate the maximum value of v(i, a_i) across all valid arrays.

The algorithm maintains a set of (value, score) pairs where value is a possible
array element and score is the maximum accumulated score so far for that element.
At each step, we try to extend the valid sequences by choosing the next element
in the array according to the constraints.
"""

import sys

input_data = sys.stdin.read().split()
it = iter(input_data)


class CodeWithRanjan:
    @staticmethod
    def Ranjan():
        t = int(next(it))
        o = []
        for _ in range(t):
            o.append(str(CodeWithRanjan.Ranju()))
        print("\n".join(o))

    @staticmethod
    def Rancho(n, m):
        # Calculate square root of m to optimize initial iterations
        s = int(m**0.5)
        if s > n:
            s = n
        # Initialize with (value, score) where value = 1 and score = 0
        st = [(1, 0)]
        # Iterate through bases from 2 to sqrt(m)
        for i in range(2, s + 1):
            nm = {}
            p = i
            k = 1
            # Generate all powers of i up to m
            while p <= m:
                # Update possible next values by multiplying with current power
                for v, sc in st:
                    nv = (v // p + 1) * p
                    if nv > m:
                        continue
                    ns = sc + k
                    # Keep only the maximum score for each value
                    if nv not in nm or ns > nm[nv]:
                        nm[nv] = ns
                # Break if next power would exceed m
                if p > m // i:
                    break
                p *= i
                k += 1
            # Handle case where we increment value instead of multiplying
            for v, sc in st:
                nv = v + 1
                if nv <= m:
                    if nv not in nm or sc > nm[nv]:
                        nm[nv] = sc
            # Sort by value and filter out dominated states
            tmp = sorted(nm.items())
            cur = []
            mx = -1
            for v, sc in tmp:
                if sc > mx:
                    cur.append((v, sc))
                    mx = sc
            st = cur
        # Handle remaining positions
        for j in range(s + 1, n + 1):
            # Limit of current value
            lim = m - (n - j)
            raw = []
            for v, sc in st:
                if v > lim:
                    continue
                nx = (v // j + 1) * j
                if nx <= lim:
                    raw.append((nx, sc + 1))
                else:
                    raw.append((v + 1, sc))
            if not raw:
                st = []
                break
            # Sort and filter out dominated states
            raw.sort()
            cur = []
            mx = -1
            for v, sc in raw:
                if sc > mx:
                    cur.append((v, sc))
                    mx = sc
            st = cur
        # Find the maximum score among valid states
        ans = 0
        for v, sc in st:
            if v <= m:
                if sc > ans:
                    ans = sc
        return ans

    @staticmethod
    def Ranju():
        n = int(next(it))
        m = int(next(it))
        return CodeWithRanjan.Rancho(n, m)


if __name__ == "__main__":
    CodeWithRanjan.Ranjan()


# https://github.com/VaHiX/CodeForces/