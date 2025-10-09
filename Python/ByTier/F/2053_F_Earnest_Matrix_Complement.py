# Problem: CF 2053 F - Earnest Matrix Complement
# https://codeforces.com/contest/2053/problem/F

"""
F. Earnest Matrix Complement
Algorithm: Dynamic Programming with State Compression + Greedy Heuristics
Time Complexity: O(n * m * k)
Space Complexity: O(m * k)

This problem involves maximizing the "beauty" of a matrix A of size n x m, 
where each element is in [1,k], and some positions are -1 (unfilled). 

The beauty is calculated as sum over all pairs of adjacent rows of:
  sum_{u=1}^k c_{u,i} * c_{u,i+1}
Where c_{u,i} is the count of value u in row i.

We use dynamic programming optimized with state tracking to compute 
the maximum possible beauty by considering how to fill the -1 cells,
and maintaining counts per row and value.

The key idea:
- Use two arrays (vep, veq) to represent previous and current rows
- Track frequency counts of values in each row (cntp, cntq)
- Use dynamic programming to compute best scores for each element value
- Keep track of global maximum using greedy selection heuristics

Implementation details:
- Process rows sequentially
- For each new row, update counts and calculate contributions
- Maintain state via dp array tracking best score per element
"""

import sys


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

        for i in range(m):
            val = int(input[ptr])
            ptr += 1
            old = veq[i]
            cntq[get(old)] -= 1
            veq[i] = val
            cntq[get(val)] += 1
        cntQ = cntq[0]
        vep, veq = veq, vep
        cntp, cntq = cntq, cntp
        cntP, cntQ = cntQ, cntP
        for row in range(2, n + 1):
            for i in range(m):
                val = int(input[ptr])
                ptr += 1
                old = veq[i]
                cntq[get(old)] -= 1
                veq[i] = val
                cntq[get(val)] += 1
            cntQ = cntq[0]
            max_dp = max(a, v + b)
            for elem in vep:
                if elem != -1:
                    current = max(a, dp[elem] + b) + cntP * cntq[elem]
                    if current > max_dp:
                        max_dp = current
            for elem in veq:
                if elem != -1:
                    current = max(a, dp[elem] + b) + cntP * cntq[elem]
                    if current > max_dp:
                        max_dp = current
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
            vep, veq = veq, vep
            cntp, cntq = cntq, cntp
            cntP, cntQ = cntQ, cntP
        res = max(a, v + b) + ext
        print(res)


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/codeForces/