# Contest 2093, Problem D: Skibidi Table
# URL: https://codeforces.com/contest/2093/problem/D


def __Main__():
    T = int(input())

    outs = []
    for _ in range(T):
        n = int(input())
        for _ in range(int(input())):
            f = list(input().split())
            if f[0] == "->":
                x, y = int(f[1]) - 1, int(f[2]) - 1
                d = 0
                for i in range(n):
                    nx, ny = x >> i & 1, y >> i & 1
                    nd = (nx * 2) ^ (ny * 3)
                    d |= nd << (2 * i)
                outs.append(str(d + 1))
            else:
                d = int(f[1]) - 1
                x, y = 0, 0
                for i in range(n):
                    nd = d >> (2 * i) & 3
                    nx, ny = (nd & 1) ^ (nd >> 1), nd & 1
                    x |= nx << i
                    y |= ny << i
                outs.append(f"{x + 1} {y + 1}")
    print("\n".join(map(str, outs)))


if __name__ == "__main__":
    __Main__()
