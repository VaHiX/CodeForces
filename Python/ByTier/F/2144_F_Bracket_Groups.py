# Problem: CF 2144 F - Bracket Groups
# https://codeforces.com/contest/2144/problem/F

from collections import deque


class AhoCorasick:
    def __init__(self, sigma=2):
        # Initialize the Aho-Corasick automaton with sigma alphabet size (2 for brackets)
        self.node = [[-1] * sigma]
        self.last = [0]
        self.sigma = sigma

    def add(self, arr, ID):
        # Add a pattern (bracket sequence) to the automaton
        v = 0
        for c in arr:
            if self.node[v][c] == -1:
                self.node[v][c] = len(self.node)
                self.node.append([-1] * self.sigma)
                self.last.append(0)
            v = self.node[v][c]
        self.last[v] |= 1 << ID

    def build(self):
        # Build failure links for the automaton
        link = [0] * len(self.node)
        que = deque()
        for i in range(self.sigma):
            if self.node[0][i] == -1:
                self.node[0][i] = 0
            else:
                link[self.node[0][i]] = 0
                que.append(self.node[0][i])

        while que:
            v = que.popleft()
            self.last[v] |= self.last[link[v]]
            for i in range(self.sigma):
                u = self.node[v][i]
                if u == -1:
                    self.node[v][i] = self.node[link[v]][i]
                else:
                    link[u] = self.node[link[v]][i]
                    que.append(u)


N, k = map(int, input().split())
AC = AhoCorasick()
stroki = []
for i in range(N):
    s = input()
    AC.add([ord(c) - ord("(") for c in s], i)
    stroki.append(s)

AC.build()
m = len(AC.node)
b = k // 2
b += 1
# dp[balance][node] = string representing a valid bracket sequence with given balance and ending at node
dp = [[None] * m for i in range(b)]
dp[0][0] = ""
for _ in range(k):
    ndp = [[None] * m for i in range(b)]
    for balance in range(b):
        for v in range(m):
            if dp[balance][v] is None:
                continue
            for i in range(2):
                to = AC.node[v][i]
                nbalance = balance + (1 if i == 0 else -1)
                if 0 <= nbalance < b and not AC.last[to]:
                    new_str = dp[balance][v] + ("(" if i == 0 else ")")
                    if ndp[nbalance][to] is None:
                        ndp[nbalance][to] = new_str
    dp = ndp

ans = False
for v in range(m):
    if dp[0][v] is not None:
        print(1)
        print(dp[0][v])
        print(N)
        print(" ".join(str(i + 1) for i in range(N)))
        ans = True
        break

if not ans:
    halfk = k // 2
    s1 = "(" * halfk + ")" * halfk
    s2 = "()" * halfk
    set1 = set()
    set2 = set()
    for i, ss in enumerate(stroki):
        if not (ss in s1):
            set1.add(i + 1)
        elif not (ss in s2):
            set2.add(i + 1)
    if (len(set1) + len(set2)) < N:
        print(-1)
    else:
        print(2)
        print(s1)
        print(len(set1))
        print(" ".join(str(i) for i in set1))
        print(s2)
        print(len(set2))
        print(" ".join(str(i) for i in set2))

### Time and Space Complexity:

# **Time Complexity:** O(N×K×2^K)  
# - Where N is the number of bracket sequences, K is the length of the regular bracket sequence.
# - The Aho-Corasick automaton construction takes O(N×K).
# - The dynamic programming part is bounded by O(K×2^K) since we process each position in the sequence and each possible balance.

# **Space Complexity:** O(K×2^K)  
# - The DP table stores up to 2^K states per position, which is acceptable given the constraints (K ≤ 50), and we also store the automaton structure which contributes to the overall space usage.

# https://github.com/VaHiX/CodeForces/