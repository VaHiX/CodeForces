# Contest 2092, Problem F: Andryusha and CCB
# URL: https://codeforces.com/contest/2092/problem/F

#!/usr/bin/env python3
# -*- coding: utf-8 -*-

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

        # Compress the binary string into runs of equal characters.
        a = []
        curr = 1
        for i in range(1, n):
            if s[i] == s[i - 1]:
                curr += 1
            else:
                a.append(curr)
                curr = 1
        a.append(curr)

        sz = len(a)

        # Build left and right arrays mapping block indices to positions in the original string.
        left = [0] * sz
        right = [0] * sz
        if sz > 0:
            left[0] = 0
            right[0] = a[0] - 1
            for i in range(1, sz):
                left[i] = right[i - 1] + 1
                right[i] = left[i] + a[i] - 1

        ans = [0] * n
        ans_local = ans
        left_local = left
        right_local = right

        # Baseline contributions for k = 1 and k >= B + 1.
        for i in range(sz):
            li = left_local[i]
            ri = right_local[i]
            const = 1 - i  # used to compute j - i + 1 as j + const
            # Update ans[j] for each character position j in this block.
            for j in range(li, ri + 1):
                ans_local[j] += j + const

        # For beauty values m >= 1, compute additional contributions.
        if sz > 1:
            a_local = a
            add = [0] * sz
            add_local = add
            # Iterate over beauty m from 1 to sz-1.
            for m in range(1, sz):
                l = m
                r = m
                # k starts implicitly from 1, but k itself isn't needed here.
                while l < sz:
                    add_local[l] += 1
                    nr = r + 1
                    if nr < sz:
                        add_local[nr] -= 1
                    # Next block index for l depends on the type of block.
                    # If block length == 1 (type-1), we skip an extra block.
                    if a_local[l] == 1:
                        l += m + 1
                    else:
                        l += m
                    # For r, we always move by m+1.
                    r += m + 1

            # Propagate the accumulated add-array into ans.
            pref = 0
            for i in range(sz):
                pref += add_local[i]
                if pref != 0:
                    li = left_local[i]
                    ri = right_local[i]
                    val = pref
                    for j in range(li, ri + 1):
                        ans_local[j] += val

        # Prepare the output for this test case.
        out_lines.append(" ".join(str(ans_local[i]) for i in range(n)))

    sys.stdout.write("\n".join(out_lines))


if __name__ == "__main__":
    solve()
