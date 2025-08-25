# Contest 2082, Problem E: Quaternary Matrix
# URL: https://codeforces.com/contest/2082/problem/E


def solve():
    import sys

    data = sys.stdin.read().split()
    if not data:
        return
    t = int(data[0])
    pos = 1
    out_lines = []
    for _ in range(t):
        n = int(data[pos])
        pos += 1
        m = int(data[pos])
        pos += 1
        a = [[0] * m for _ in range(n)]
        rx = [0] * n
        cx = [0] * m
        rv = [[] for _ in range(4)]
        cv = [[] for _ in range(4)]
        for i in range(n):
            s = data[pos]
            pos += 1
            for j, ch in enumerate(s):
                a[i][j] = int(ch)
                rx[i] ^= a[i][j]
                cx[j] ^= a[i][j]
        for i in range(n):
            if rx[i]:
                rv[rx[i]].append(i)
        for j in range(m):
            if cx[j]:
                cv[cx[j]].append(j)
        ans = 0
        rV = []
        cV = []
        for x in range(1, 4):
            while rv[x] and cv[x]:
                ans += 1
                i_idx = rv[x].pop()
                j_idx = cv[x].pop()
                a[i_idx][j_idx] ^= x
            if rv[x]:
                rV.append(x)
            if cv[x]:
                cV.append(x)
        if rV and cV:
            if len(cV) == 2:
                i_val = rV[0]
                j_val = cV[0]
                k_val = cV[1]
                while rv[i_val] and cv[j_val] and cv[k_val]:
                    ans += 2
                    i_idx = rv[i_val].pop()
                    j_idx = cv[j_val].pop()
                    k_idx = cv[k_val].pop()
                    a[i_idx][j_idx] ^= j_val
                    a[i_idx][k_idx] ^= k_val
            elif len(rV) == 2:
                i_val = cV[0]
                j_val = rV[0]
                k_val = rV[1]
                while cv[i_val] and rv[j_val] and rv[k_val]:
                    ans += 2
                    j_idx = rv[j_val].pop()
                    k_idx = rv[k_val].pop()
                    i_idx = cv[i_val].pop()
                    a[j_idx][i_idx] ^= j_val
                    a[k_idx][i_idx] ^= k_val
        i_val = -1
        j_val = -1
        for x in range(1, 4):
            if rv[x]:
                i_val = x
            if cv[x]:
                j_val = x
        if i_val != -1 and j_val != -1:
            while rv[i_val] and cv[j_val]:
                i1 = rv[i_val].pop()
                i2 = rv[i_val].pop()
                j1 = cv[j_val].pop()
                j2 = cv[j_val].pop()
                ans += 3
                a[i2][j1] ^= i_val
                a[i1][j2] ^= j_val
                a[i1][j1] ^= i_val ^ j_val
        for x in range(1, 4):
            for i in rv[x]:
                ans += 1
                a[i][0] ^= x
            for j in cv[x]:
                ans += 1
                a[0][j] ^= x
        out_lines.append(str(ans))
        for i in range(n):
            out_lines.append("".join(str(x) for x in a[i]))
    sys.stdout.write("\n".join(out_lines))


if __name__ == "__main__":
    solve()
