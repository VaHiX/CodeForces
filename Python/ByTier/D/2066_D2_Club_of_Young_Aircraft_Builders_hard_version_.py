# Contest 2066, Problem D2: Club of Young Aircraft Builders (hard version)
# URL: https://codeforces.com/contest/2066/problem/D2


def solve():
    import sys

    input_data = sys.stdin.read().split()
    if not input_data:
        return
    mod = 10**9 + 7

    # Precompute binomial coefficients c[i][j] for 0 <= i,j <= 100.
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
        # Read n, C (input variable C), and m.
        n = int(input_data[ptr])
        ptr += 1
        C_val = int(input_data[ptr])
        ptr += 1
        m_val = int(input_data[ptr])
        ptr += 1

        # Allocate array a of length m_val+1 (1-indexed).
        a = [0] * (m_val + 1)
        # Allocate cnt: dimensions (n+1) x (m_val+1)
        cnt = [[0] * (m_val + 1) for _ in range(n + 1)]
        # Read a[1..m_val] and update cnt.
        for i in range(1, m_val + 1):
            a[i] = int(input_data[ptr])
            ptr += 1
            # For each j from 0 to n, copy cnt[j][i] = cnt[j][i-1]
            for j in range(0, n + 1):
                cnt[j][i] = cnt[j][i - 1]
            # Increment the count for value a[i].
            cnt[a[i]][i] += 1

        # Create DP table f with dimensions (n+1) x (m_val+1) and initialize to zero.
        f = [[0] * (m_val + 1) for _ in range(n + 1)]
        f[0][0] = 1

        # DP recurrence:
        # For i=0 to n-1, for j=0 to m_val such that f[i][j] != 0:
        #    let r = min(m_val, j + C_val)
        #    let fix = cnt[i+1][r] and whi = r - j.
        #    if cnt[i+1][r] != cnt[i+1][m_val], skip this state.
        #    For k=i+2 to n, subtract cnt[k][r] from whi.
        #    Then for t from fix to min(whi, C_val) (if i != n-1, require t == C_val):
        #         update f[i+1][j+t] += f[i][j] * c[whi-fix][t-fix] (mod mod)
        for i in range(0, n):
            for j in range(0, m_val + 1):
                if f[i][j] == 0:
                    continue
                r = j + C_val
                if r > m_val:
                    r = m_val
                fix = cnt[i + 1][r]
                whi = r - j
                if cnt[i + 1][r] != cnt[i + 1][m_val]:
                    continue
                for k in range(i + 2, n + 1):
                    whi -= cnt[k][r]
                # Now iterate t from fix to whi (and t must be <= C_val)
                for t_val in range(fix, whi + 1):
                    if t_val > C_val:
                        break
                    if i != n - 1 or t_val == C_val:
                        # Add f[i][j] * c[whi-fix][t_val-fix] to f[i+1][j+t_val]
                        f[i + 1][j + t_val] = (
                            f[i + 1][j + t_val] + f[i][j] * c[whi - fix][t_val - fix]
                        ) % mod

        out_lines.append(str(f[n][m_val] % mod))
    sys.stdout.write("\n".join(out_lines))


if __name__ == "__main__":
    solve()
