# Contest 2045, Problem A: Scrambled Scrabble
# URL: https://codeforces.com/contest/2045/problem/A


def solve():
    s = input()
    n, g, y, f = 0, 0, 0, [0, 0]
    for i in s:
        if i == "N":
            n += 1
        if i == "G":
            g += 1
        if i == "Y":
            y += 1
        elif i in ["A", "E", "I", "O", "U"]:
            f[1] += 1
        else:
            f[0] += 1
    # print(f"n: {n}, g: {g}, y: {y}, f: {f}")
    for _ in range(y):
        if f[0] >= 2 * f[1] + 2:
            f[1] += 1
        else:
            f[0] += 1
    t = min(f[0] // 2, f[1])
    out = t * 3 + max(0, min(n, g, f[0] - t * 2, t * 2))
    print(out)


solve()
