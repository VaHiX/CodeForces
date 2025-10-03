# Problem: CF 2066 D2 - Club of Young Aircraft Builders (hard version)
# https://codeforces.com/contest/2066/problem/D2

"""
D2. Club of Young Aircraft Builders (hard version)

This problem involves counting the number of valid ways to fill in missing airplane launch data,
where each launch is attributed to a specific floor of a building. The constraints are:
- There are n floors, c minimum required airplanes, and m total launched airplanes.
- For each launch at floor i, all residents from floor 1 to i can see it.
- At most one person per floor can launch an airplane before seeing c total airplanes.
- The final arrangement must ensure that every floor sees c or more airplanes by the end.

Approach:
- Dynamic Programming (DP) with state [floor][seen_airplanes]
- Precompute combination numbers C(n, k) for binomial coefficients
- Process each test case using DP over the sequence of launches
- For each step, compute valid transitions where the number of airplanes launched
  up to a given floor meets the constraint that no floor can launch more than c before 
  seeing at least c airplanes from lower floors.

Time Complexity: O(n^3 * m) in worst case per test case due to nested loops.
Space Complexity: O(n^2 + m) for combination table and DP arrays.

Algorithms/Techniques:
- Dynamic Programming
- Precomputed Binomial Coefficients
"""

def solve():
    import sys

    input_data = sys.stdin.read().split()
    if not input_data:
        return
    mod = 10**9 + 7
    # Precompute binomial coefficients C(n, k)
    c = [[0] * 101 for _ in range(101)]
    c[0][0] = 1
    for i in range(1, 101):
        c[i][0] = 1
        for j in range(1, i + 1):
            c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % mod
    ptr = 0
    t = int(input_data[ptr])
    ptr += 1
    out_lines = []
    for _ in range(t):
        n = int(input_data[ptr])
        ptr += 1
        C_val = int(input_data[ptr])
        ptr += 1
        m_val = int(input_data[ptr])
        ptr += 1
        a = [0] * (m_val + 1)
        cnt = [[0] * (m_val + 1) for _ in range(n + 1)]
        # Count occurrences of each floor up to position j
        for i in range(1, m_val + 1):
            a[i] = int(input_data[ptr])
            ptr += 1
            for j in range(0, n + 1):
                cnt[j][i] = cnt[j][i - 1]
            cnt[a[i]][i] += 1
        f = [[0] * (m_val + 1) for _ in range(n + 1)]
        f[0][0] = 1
        # DP transition
        for i in range(0, n):
            for j in range(0, m_val + 1):
                if f[i][j] == 0:
                    continue
                r = j + C_val
                if r > m_val:
                    r = m_val
                fix = cnt[i + 1][r]
                whi = r - j
                # Check if valid transition based on floor constraints
                if cnt[i + 1][r] != cnt[i + 1][m_val]:
                    continue
                for k in range(i + 2, n + 1):
                    whi -= cnt[k][r]
                # Compute combinations for filling gaps
                for t_val in range(fix, whi + 1):
                    if t_val > C_val:
                        break
                    if i != n - 1 or t_val == C_val:
                        f[i + 1][j + t_val] = (
                            f[i + 1][j + t_val] + f[i][j] * c[whi - fix][t_val - fix]
                        ) % mod
        out_lines.append(str(f[n][m_val] % mod))
    sys.stdout.write("\n".join(out_lines))


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/codeForces/