# Problem: CF 2092 F - Andryusha and CCB
# https://codeforces.com/contest/2092/problem/F

"""
F. Andryusha and CCB
Time Complexity: O(n^2) in worst case, but with optimizations it's closer to O(n * sqrt(n))
Space Complexity: O(n)

This solution computes for each prefix of the binary string, how many values of k 
are possible such that we can split the prefix into exactly k parts with equal beauty.

The beauty of a string is defined as the number of adjacent differing characters.
For a valid split:
1. The total beauty must be divisible by k
2. Each part will have the same beauty value
3. We need to partition the string such that each part's beauty is maintained

We use segment tree concepts and prefix sum techniques to efficiently compute 
these values across all prefixes.
"""

import sys


def solve():
    data = sys.stdin.read().split()
    t = int(data[0])
    idx = 1
    out_lines = []
    for _ in range(t):
        n = int(data[idx])
        idx += 1
        s = data[idx]
        idx += 1
        a = []  # Store lengths of consecutive segments of same character
        curr = 1
        for i in range(1, n):  # Traverse the string to group consecutive same characters
            if s[i] == s[i - 1]:
                curr += 1
            else:
                a.append(curr)
                curr = 1
        a.append(curr)
        sz = len(a)
        left = [0] * sz
        right = [0] * sz
        if sz > 0:
            # left[i] and right[i] define range of indices in the final array that corresponds to segment i
            left[0] = 0
            right[0] = a[0] - 1
            for i in range(1, sz):
                left[i] = right[i - 1] + 1
                right[i] = left[i] + a[i] - 1

        ans = [0] * n
        ans_local = ans
        left_local = left
        right_local = right
        
        # First pass: assign initial values based on linear increase per segment
        for i in range(sz):
            li = left_local[i]
            ri = right_local[i]
            const = 1 - i
            for j in range(li, ri + 1):
                ans_local[j] += j + const

        # Second phase: handle dependencies using difference array technique
        if sz > 1:
            a_local = a
            add = [0] * sz
            add_local = add
            for m in range(1, sz):  # Loop through possible gap sizes (m)
                l = m
                r = m
                while l < sz:
                    add_local[l] += 1
                    nr = r + 1
                    if nr < sz:
                        add_local[nr] -= 1
                    if a_local[l] == 1:  # If segment length is 1, move by m+1 steps
                        l += m + 1
                    else:  # Otherwise move by m steps
                        l += m
                    r += m + 1
            
            # Compute prefix sum to apply the updates
            pref = 0
            for i in range(sz):
                pref += add_local[i]
                if pref != 0:
                    li = left_local[i]
                    ri = right_local[i]
                    val = pref
                    for j in range(li, ri + 1):
                        ans_local[j] += val

        out_lines.append(" ".join(str(ans_local[i]) for i in range(n)))
    sys.stdout.write("\n".join(out_lines))


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/codeForces/