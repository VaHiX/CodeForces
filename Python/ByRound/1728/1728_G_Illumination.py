# Problem: CF 1728 G - Illumination
# https://codeforces.com/contest/1728/problem/G

"""
Code Purpose:
This code solves the "Illumination" problem where we have a segment [0, d] with n lanterns and m points of interest.
Each lantern can have a power value between 0 and d. A lantern at position x illuminates all points y where |x - y| <= power.
We need to count the number of valid ways to assign power values such that all points are illuminated.
The approach uses inclusion-exclusion principle combined with dynamic programming and preprocessing of interval coverings.

Algorithms/Techniques:
- Inclusion-exclusion principle
- Preprocessing for left and right coverage intervals
- Segment tree or prefix/suffix sums for efficient range updates
- Modular arithmetic for large number handling

Time Complexity: O(2^m * (n + m) * log(d))
Space Complexity: O(2^m * m * log(d))
"""

input = __import__("sys").stdin.readline


MOD = 998244353


d, n, m = map(int, input().split())
lamps = list(sorted(map(int, input().split())))
points = list(sorted(map(int, input().split())))


positions = [x for x in points]
positions.append(0)
positions.append(d)
for i in range(m):
    for j in range(i + 1, m):
        mid = (points[i] + points[j]) // 2
        positions.append(mid)
        positions.append(mid + 1)
positions = list(sorted(set(positions)))
posmap = {x: i for i, x in enumerate(positions)}


i = 0
queryL = []
for p in points:
    queries = [0] * len(positions)
    while positions[i] < p:
        i += 1

    j = i
    q = 1
    for x in lamps:
        if x <= p:
            continue
        while x > positions[j]:
            queries[j] = q
            j += 1
        q = q * (x - p) % MOD

    while j < len(positions):
        queries[j] = q
        j += 1

    queryL.append(queries)


i = len(positions) - 1
queryR = []
for p in points[::-1]:
    queries = [0] * len(positions)
    while positions[i] > p:
        i -= 1

    j = i
    q = 1
    for x in lamps[::-1]:
        if x > p:
            continue
        while x < positions[j]:
            queries[j] = q
            j -= 1
        q = q * (p - x) % MOD
    while j >= 0:
        queries[j] = q
        j -= 1

    queryR.append(queries)


queryR = queryR[::-1]


querySums = [[[0] * len(positions) for _ in range(len(points))] for _ in range(2)]
current_ans = 0
for mask in range(1, 1 << m):
    keys = []
    prev_idx = -1
    popcnt = 0
    q = 1
    for i in range(m):
        if (mask >> i) & 1:
            p = points[i]
            if prev_idx == -1:
                keys.append((1, i, 0))
                q = q * queryR[i][0] % MOD
            else:
                prev_p = points[prev_idx]
                mid = (prev_p + p) // 2

                keys.append((0, prev_idx, posmap[mid]))
                q = q * queryL[prev_idx][posmap[mid]] % MOD

                keys.append((1, i, posmap[mid + 1]))
                q = q * queryR[i][posmap[mid + 1]] % MOD

            prev_idx = i
            popcnt += 1

    keys.append((0, prev_idx, len(positions) - 1))
    q = q * queryL[prev_idx][-1] % MOD
    if popcnt & 1:
        current_ans = (current_ans - q) % MOD
        for i, j, k in keys:
            querySums[i][j][k] = (querySums[i][j][k] - q) % MOD
    else:
        current_ans = (current_ans + q) % MOD
        for i, j, k in keys:
            querySums[i][j][k] = (querySums[i][j][k] + q) % MOD


for j in range(m):
    for k in range(len(positions) - 2, -1, -1):
        querySums[0][j][k] = (querySums[0][j][k] + querySums[0][j][k + 1]) % MOD
    for k in range(1, len(positions)):
        querySums[1][j][k] = (querySums[1][j][k] + querySums[1][j][k - 1]) % MOD


current_ans += pow(d + 1, n + 1, MOD)
current_ans %= MOD

_ = int(input())
for x in map(int, input().split()):
    ans = current_ans

    for i in range(len(positions)):
        if positions[i] >= x:
            pos = i
            break

    for j in range(m):
        if points[j] < x:
            total = querySums[0][j][pos]
            ans -= total
            ans += total * (x - points[j]) % MOD
            ans %= MOD

    for i in range(len(positions) - 1, -1, -1):
        if positions[i] <= x:
            pos = i
            break

    for j in range(m):
        if x <= points[j]:
            total = querySums[1][j][pos]
            ans -= total
            ans += total * (points[j] - x) % MOD
            ans %= MOD

    print(ans)


# https://github.com/VaHiX/CodeForces/