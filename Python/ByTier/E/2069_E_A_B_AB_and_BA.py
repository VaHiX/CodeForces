# Contest 2069, Problem E: A, B, AB and BA
# URL: https://codeforces.com/contest/2069/problem/E


def solve():
    import sys, sys

    data = sys.stdin.read().split()
    if not data:
        return
    t = int(data[0])
    idx = 1
    res = []
    for _ in range(t):
        s = data[idx]
        idx += 1
        a = int(data[idx])
        b = int(data[idx + 1])
        ab = int(data[idx + 2])
        ba = int(data[idx + 3])
        idx += 4

        sa = s.count("A")
        sb = s.count("B")
        n = len(s)

        extras = 0
        aval = []
        bval = []
        i = 0
        while i < n:
            j = i
            while j + 1 < n and s[j + 1] != s[j]:
                j += 1
            # Обрабатываем сегмент [i, j]
            if (i % 2) == (j % 2):
                extras += (j - i) // 2
            elif s[i] == "A":
                aval.append((j - i + 1) // 2)
            else:
                bval.append((j - i + 1) // 2)
            i = j + 1

        aval.sort()
        bval.sort()
        for x in aval:
            if ab >= x:
                ab -= x
                sa -= x
                sb -= x
            else:
                extras += x - 1
        for x in bval:
            if ba >= x:
                ba -= x
                sa -= x
                sb -= x
            else:
                extras += x - 1
        while extras > 0:
            if ab > 0:
                ab -= 1
            elif ba > 0:
                ba -= 1
            else:
                break
            extras -= 1
            sa -= 1
            sb -= 1

        res.append("YES" if (sa <= a and sb <= b) else "NO")
    sys.stdout.write("\n".join(res))


if __name__ == "__main__":
    solve()
