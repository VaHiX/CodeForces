# Contest 2064, Problem D: Eating
# URL: https://codeforces.com/contest/2064/problem/D


def solve():
    import sys, sys

    data = sys.stdin.buffer.read().split()
    if not data:
        return
    it = iter(data)
    t = int(next(it))
    out_lines = []
    for _ in range(t):
        N = int(next(it))
        Q = int(next(it))
        D = 31
        W = [int(next(it)) for _ in range(N)]
        left = [[0] * (N + 1) for _ in range(D)]
        for i in range(N):
            for j in range(D):
                left[j][i + 1] = left[j][i]
            b = W[i].bit_length()
            left[b][i + 1] = i + 1
        X = [0] * (N + 1)
        for i in range(N - 1, -1, -1):
            X[i] = X[i + 1] ^ W[i]
        for i in range(N + 1):
            for j in range(D - 2, -1, -1):
                if left[j + 1][i] > left[j][i]:
                    left[j][i] = left[j + 1][i]
        res = []
        for _ in range(Q):
            x = int(next(it))
            ind = N
            while ind:
                c = (x ^ X[ind]).bit_length()
                ind = left[c][ind]
                if ind == 0:
                    break
                if W[ind - 1] <= (x ^ X[ind]):
                    ind -= 1
                else:
                    break
            res.append(str(N - ind))
        out_lines.append(" ".join(res))
    sys.stdout.write("\n".join(out_lines))


if __name__ == "__main__":
    solve()
