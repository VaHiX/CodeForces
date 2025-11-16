# Problem: CF 1741 F - Multi-Colored Segments
# https://codeforces.com/contest/1741/problem/F

"""
Algorithm: Multi-Colored Segments
Approach:
- For each segment, we need to find the minimum distance to any segment of a different color
- We use coordinate compression and a sweep line technique to efficiently find nearest segments of different colors
- We sort segments by left coordinate and process them in order
- For each segment, we maintain the farthest segment seen so far for each color to quickly find distances
- Time Complexity: O(n log n) due to sorting and linear processing
- Space Complexity: O(n) for storing segments and auxiliary arrays

The key idea is to process segments in order of their left coordinate and maintain information about the "farthest" segment seen so far for each color, allowing us to quickly compute distances to segments of different colors.
"""

def code(a, b, i):
    # Encodes segment info into a single number for sorting
    return a * 10**16 + b * 10**6 + i


def decode(x):
    # Decodes the encoded number back to segment info
    a = x // 10**16
    x = x % 10**16
    c = x % 10**6
    b = x // 10**6
    return a, b, c


def compare(i, j):
    # Calculates distance between two segments
    l, r, q = a[i]
    x, y, q = a[j]
    if y < l:
        return l - y
    if r < x:
        return x - r
    return 0


inf = 10**10
for _ in range(int(input())):
    n = int(input())
    a, p = [], []
    for i in range(n):
        l, r, c = [int(e) for e in input().split()]
        p += [code(l, r, i)]
        a += [(l, r, c)]
    p.sort()
    save = [[] for i in range(n + 1)]
    ma, xma = [-1, -1], [-1, -1]
    last = -1
    ans = [inf] * n
    for el in p:
        l, r, i = decode(el)
        c = a[i][-1]
        # Check distance to the farthest segment of different color
        if xma[0] not in [c, -1]:
            q = compare(ma[0], i)
            ans[i], ans[ma[0]] = min(ans[i], q), min(ans[ma[0]], q)
        if xma[1] not in [c, -1]:
            q = compare(i, ma[1])
            ans[i] = min(ans[i], q)
            ans[ma[1]] = min(ans[ma[1]], q)
        # Update the farthest segments of each color
        if ma[0] == -1:
            ma[0], xma[0] = i, c
        elif xma[0] == c:
            if r > a[ma[0]][1]:
                ma[0] = i
        elif r > a[ma[0]][1]:
            ma, xma = ma[::-1], xma[::-1]
            ma[0], xma[0] = i, c
        elif ma[1] == -1 or r > a[ma[1]][1]:
            ma[1], xma[1] = i, c
        # Check against saved segments of the same color
        if last not in [-1, c]:
            for ind in save[last]:
                q = compare(i, ind)
                ans[i] = min(ans[i], q)
                ans[ind] = min(ans[ind], q)
            save[last] = []
        save[c] += [i]
        last = c
    print("    ", *ans)


# https://github.com/VaHiX/CodeForces/