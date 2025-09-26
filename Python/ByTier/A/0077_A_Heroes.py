# Contest 77, Problem A: Heroes
# URL: https://codeforces.com/contest/77/problem/A

from itertools import *

ind = {
    "Anka": 0,
    "Chapay": 1,
    "Cleo": 2,
    "Troll": 3,
    "Dracul": 4,
    "Snowy": 5,
    "Hexadecimal": 6,
}

gr = []
n = int(input())

for i in range(n):
    q, ch, p = input().split()
    gr.append((ind[q], ind[p]))

best_diff, best_likes = 10**18, -1

a, b, c = map(int, input().split())
for r in product([0, 1, 2], repeat=7):
    sz = [0] * 3
    for x in r:
        sz[x] += 1
    if 0 in sz:
        continue
    diff = max(a // sz[0], b // sz[1], c // sz[2]) - min(
        a // sz[0], b // sz[1], c // sz[2]
    )
    likes = 0

    for x in gr:
        if r[x[0]] == r[x[1]]:
            likes += 1
    if best_diff > diff:
        best_diff, best_likes = diff, likes
    elif best_diff == diff and best_likes < likes:
        best_likes = likes
print(best_diff, best_likes)  # 1689027214.1832247
