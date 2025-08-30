# Contest 2053, Problem F: Earnest Matrix Complement
# URL: https://codeforces.com/contest/2053/problem/F

import sys
from sys import stdin


def main():
    input = sys.stdin.read().split()
    ptr = 0
    t = int(input[ptr])
    ptr += 1
    for _ in range(t):
        n = int(input[ptr])
        m = int(input[ptr + 1])
        k = int(input[ptr + 2])
        ptr += 3

        # Initialize variables
        cntP = 0
        cntQ = 0
        vep = [0] * m
        veq = [0] * m
        cntp = [0] * (k + 2)
        cntq = [0] * (k + 2)
        vis = [0] * (k + 2)
        dp = [0] * (k + 2)
        a = 0
        b = 0
        v = 0
        ext = 0

        cntp[0] = m
        cntq[0] = m

        def get(x):
            return x if x != -1 else 0

        # Read initial queue (row 1)
        for i in range(m):
            val = int(input[ptr])
            ptr += 1
            old = veq[i]
            cntq[get(old)] -= 1
            veq[i] = val
            cntq[get(val)] += 1
        cntQ = cntq[0]

        # Swap to make previous row
        vep, veq = veq, vep
        cntp, cntq = cntq, cntp
        cntP, cntQ = cntQ, cntP

        for row in range(2, n + 1):
            # Read current row
            for i in range(m):
                val = int(input[ptr])
                ptr += 1
                old = veq[i]
                cntq[get(old)] -= 1
                veq[i] = val
                cntq[get(val)] += 1
            cntQ = cntq[0]

            max_dp = max(a, v + b)

            # Check previous row elements
            for elem in vep:
                if elem != -1:
                    current = max(a, dp[elem] + b) + cntP * cntq[elem]
                    if current > max_dp:
                        max_dp = current

            # Check current row elements
            for elem in veq:
                if elem != -1:
                    current = max(a, dp[elem] + b) + cntP * cntq[elem]
                    if current > max_dp:
                        max_dp = current

            # Update DP for previous row elements
            for elem in vep:
                if elem != -1 and vis[elem] != row:
                    vis[elem] = row
                    ext += cntp[elem] * cntq[elem]
                    new_val = (
                        max(a, dp[elem] + b) + cntP * cntq[elem] + cntQ * cntp[elem] - b
                    )
                    if new_val > dp[elem]:
                        dp[elem] = new_val
                    candidate = max_dp + cntp[elem] * cntQ - b - cntP * cntQ
                    if candidate > dp[elem]:
                        dp[elem] = candidate
                    if dp[elem] > v:
                        v = dp[elem]

            # Update DP for current row elements
            for elem in veq:
                if elem != -1 and vis[elem] != row:
                    vis[elem] = row
                    new_val = (
                        max(a, dp[elem] + b) + cntP * cntq[elem] + cntQ * cntp[elem] - b
                    )
                    if new_val > dp[elem]:
                        dp[elem] = new_val
                    candidate = max_dp + cntp[elem] * cntQ - b - cntP * cntQ
                    if candidate > dp[elem]:
                        dp[elem] = candidate
                    if dp[elem] > v:
                        v = dp[elem]

            a = max(max_dp, a + cntP * cntQ)
            b += cntP * cntQ

            # Swap current and previous
            vep, veq = veq, vep
            cntp, cntq = cntq, cntp
            cntP, cntQ = cntQ, cntP

        res = max(a, v + b) + ext
        print(res)


if __name__ == "__main__":
    main()
