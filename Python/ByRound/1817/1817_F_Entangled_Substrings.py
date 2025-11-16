# Problem: CF 1817 F - Entangled Substrings
# https://codeforces.com/contest/1817/problem/F

"""
Suffix Automaton-based solution for counting entangled substring pairs.

Approach:
- Build a Suffix Automaton (SAM) for the given string.
- Use the SAM to identify valid entangled pairs (a,b) such that they only occur as substrings of "acb".
- Traverse the SAM's state tree to compute contributions of all valid pairs.

Time Complexity: O(n) where n is the length of the input string.
Space Complexity: O(n) for storing SAM states and auxiliary arrays.

Algorithms/Techniques:
- Suffix Automaton (SAM)
- DFS traversal on SAM's failure tree
- Dynamic Programming on SAM states
"""

import sys

sys.set_int_max_str_digits(1000000)

N = 200005


n = 0
o = [0] * N
st = [0] * N
s = [0] * N
ans = 0
vs = [0] * N
a = [""] * N


class Point:
    def __init__(self):
        self.len = 0
        self.link = 0
        self.ch = [0] * 26


class SuffixAutomaton:
    def __init__(self):
        self.nw = 1
        self.cntP = 1
        self.sz = [0] * N
        self.tg = [0] * N
        self.e = [[] for _ in range(N)]
        self.pt = [Point() for _ in range(N)]
        self.pt[1] = Point()

    def ext(self, vl):
        """Extend SAM with character vl."""
        p = self.nw
        self.nw = self.cntP + 1
        self.cntP += 1
        self.pt[self.nw].len = self.pt[p].len + 1
        self.tg[self.nw] = 1
        while p and not self.pt[p].ch[vl]:
            self.pt[p].ch[vl] = self.nw
            p = self.pt[p].link
        if not p:
            self.pt[self.nw].link = 1
            return
        p1 = self.pt[p].ch[vl]
        if self.pt[p1].len == self.pt[p].len + 1:
            self.pt[self.nw].link = p1
            return
        t = self.cntP + 1
        self.cntP += 1
        self.pt[t] = Point()
        self.pt[t].len = self.pt[p].len + 1
        self.pt[t].link = self.pt[p1].link
        self.pt[t].ch = self.pt[p1].ch[:]
        self.pt[self.nw].link = t
        self.pt[p1].link = t
        while p and self.pt[p].ch[vl] == p1:
            self.pt[p].ch[vl] = t
            p = self.pt[p].link

    def dfs(self, u):
        """Iterative DFS to compute size of each node."""
        stack = [(1, False)]
        while stack:
            u, processed = stack.pop()
            if not processed:
                stack.append((u, True))
                for v in self.e[u]:
                    stack.append((v, False))
            else:
                self.sz[u] = self.tg[u]
                for v in self.e[u]:
                    self.sz[u] += self.sz[v]

    def build(self):
        """Build fail tree and compute sizes."""
        for i in range(2, self.cntP + 1):
            self.e[self.pt[i].link].append(i)
        self.dfs(1)


SAM = SuffixAutomaton()


def wr(x):
    """Convert large integer to string iteratively."""
    if x == 0:
        return "0"
    result = ""
    while x > 0:
        result = str(x % 10) + result
        x //= 10
    return result


def slv(len_):
    """Solve for a given length."""
    global ans
    for i in range(1, st[0] + 1):
        s[i] = s[i - 1] + st[i]
    i = len_ - st[0] + 1
    t = 1
    while i <= len_ + 1 and i <= st[st[0]]:
        while t <= st[0] and st[t] < i:
            t += 1
        ans += s[i - len_ + st[0] - 1] * (st[0] - t + 1)
        i += 1


def main():
    global n, ans

    a_input = input().strip()
    n = len(a_input)
    for i in range(1, n + 1):
        a[i] = a_input[i - 1]

    for i in range(1, n + 1):
        SAM.ext(ord(a[i]) - ord("a"))
    SAM.build()

    for i in range(1, SAM.cntP + 1):
        for j in range(26):
            t = SAM.pt[i].ch[j]
            if t and SAM.sz[i] == SAM.sz[t]:
                o[i] = t
                vs[t] = 1

    for i in range(1, SAM.cntP + 1):
        if not vs[i]:
            t = 0
            st[0] = 0
            j = i
            while j:
                t = j
                st[0] += 1
                st[st[0]] = SAM.pt[j].len - SAM.pt[SAM.pt[j].link].len
                j = o[j]
            slv(SAM.pt[t].len)

    print(wr(ans))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/