# Contest 6, Problem D: Lizards and Basements 2
# URL: https://codeforces.com/contest/6/problem/D


def calc(arr, a, b):
    last = {
        (arr[0], 0): 0
    }  # {(healh left of the previous archer, hit on the previous archer): total hits}
    lastq = {(arr[0], 0): [0]}  # hits on every archer
    for x in arr[1:-2]:
        cur = {}
        curq = {}
        for i, j in last:  # -1//n = -1
            hit1 = i // b + 1  # deal with health left of the previous archer
            left = max(-1, x - b * j - a * hit1)
            for hit2 in range(
                left // a + 2
            ):  # additional hit avialble for the current archer
                key = (max(-1, left - a * hit2), hit1 + hit2)
                if last[(i, j)] + hit1 + hit2 < cur.get(key, float("inf")):
                    cur[key] = last[(i, j)] + hit1 + hit2
                    curq[key] = lastq[(i, j)] + [hit1 + hit2]
        last = cur
        lastq = curq
    mi = float("inf")
    for i, j in last:
        cur = max(i // b + 1, max(-1, arr[-2] - j * b) // a + 1, arr[-1] // b + 1)
        if cur + last[(i, j)] < mi:
            mi = cur + last[(i, j)]
            q = lastq[(i, j)] + [cur]
    s = []
    for i, c in enumerate(q):
        s.extend([str(i + 1)] * c)
    print(mi)
    print(" ".join(s))


n, a, b = [int(x) for x in input().split(" ")]
arr = [int(x) for x in input().split(" ")]
calc(arr, a, b)
