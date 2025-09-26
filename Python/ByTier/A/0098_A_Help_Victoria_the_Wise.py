# Contest 98, Problem A: Help Victoria the Wise
# URL: https://codeforces.com/contest/98/problem/A

import sys

input = sys.stdin.readline

from collections import Counter

s = input()[:-1]
a = Counter(s)
a = tuple(sorted([a[i] for i in a]))
d = {
    (6,): 1,
    (1, 5): 1,
    (2, 4): 2,
    (1, 1, 4): 2,
    (3, 3): 2,
    (1, 2, 3): 3,
    (1, 1, 1, 3): 5,
    (2, 2, 2): 6,
    (1, 1, 2, 2): 8,
    (1, 1, 1, 1, 2): 15,
    (1, 1, 1, 1, 1, 1): 30,
}
print(d[a])
