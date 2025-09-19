# Contest 1866, Problem I: Imagination Castle
# URL: https://codeforces.com/contest/1866/problem/I

# Optimize the obvious O(NM) dp (0 means player moving will lose).
# We don't need to store the answer to all O(NM) states.
# As we iterate from bottom to top row, we just have to store the columns where an answer of 0 exists.
#   Motivated by the fact that our dp is just dp[i][j] = 1 if can transition to dp[i2][j2] = 0 else 0
# We obviously have at least O(K) updates (at special tile, answer is 0).
# However, we only have at most 1 extra update per row:
# first column j where no answer of 0 exists and no special tiles to right
#   By definition, all j2 > j have answer 1
#   Since answer = 0 for j, answer = 1 for j2 < j

import sys

input = sys.stdin.buffer.readline

n, m, k = map(int, input().split())
special = [[] for _ in range(n)]
for _ in range(k):
    x, y = map(int, input().split())
    x -= 1
    y -= 1
    special[x].append(y)

j = m - 1
has0 = [0] * m

for i in range(n - 1, 0, -1):
    while j >= 0 and has0[j]:
        j -= 1

    mxjt = -1
    for jt in special[i]:
        has0[jt] = 1
        mxjt = max(jt, mxjt)
    if j >= 0 and j > mxjt:
        has0[j] = 1

if special[0] or has0[0]:
    print("Chaneka")
else:
    while j >= 0 and has0[j]:
        j -= 1

    print("Chaneka" if j else "Bhinneka")
