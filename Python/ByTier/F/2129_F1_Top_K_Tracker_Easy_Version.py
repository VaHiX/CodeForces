# Contest 2129, Problem F1: Top-K Tracker (Easy Version)
# URL: https://codeforces.com/contest/2129/problem/F1

groups = [[] for _ in range(30)]
free = 0
appear = {}


def add(g):
    global free
    for e in g:
        groups[e].append(free)
    appear[tuple(sorted(g))] = free
    free += 1


add([])
for i in range(30):
    add([i])
for a in range(30):
    for b in range(a):
        add([a, b])

for i in range(10):
    for x in range(27):
        add([0, 1 + x, 1 + (x + i + 1) % 27])
for i in range(27):
    add([28, 29, 1 + i])
for i in range(2):
    for x in range(27):
        add([1 + x, 1 + (x + 1) % 27, 1 + (x + 3 + i) % 27])
for x in range(29):
    add([1 + x, 1 + (x + 2) % 29, 1 + (x + 10) % 29])

for _ in range(int(input())):
    n = int(input())
    seen = [[] for _ in range(n)]
    for i in range(30):
        q = [e + 1 for e in groups[i] if e < n]
        if not q:
            continue
        print(4 if i == 0 else 2, len(q), *q)
        for e in [int(t) for t in input().split()]:
            seen[e - 1].append(i)

    line = [0] * n
    for i in range(n):
        t = tuple(seen[i])
        line[i] = appear[t] + 1
    print("!", *line)
