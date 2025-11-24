# Problem: CF 2126 G2 - Big Wins!  (hard version)
# https://codeforces.com/contest/2126/problem/G2

"""
G2. Big Wins! (hard version)

This problem asks to find a contiguous subarray such that the difference between its median and minimum element is maximized.

Approach:
- For each element a[i], we consider it as a potential median in some subarray.
- We use two Disjoint Set Union (DSU) structures to maintain segments of elements.
  - fl: For leftward expansion from index i
  - fr: For rightward expansion from index i
- We preprocess the array to compute prefix sums for counting occurrences of each element.
- We reverse the order of processing and for each element, we merge adjacent segments in DSUs.
- For each merged segment, we track the minimum value and update the maximum difference.

Time Complexity: O(n * α(n)) where α is the inverse Ackermann function (n is the length of array).
Space Complexity: O(n) for storing the DSU structures, counters, and other auxiliary arrays.

Algorithm: 
- Preprocessing to compute prefix counts and positions.
- Two-pass DSU-based merge process to find optimal subarrays.
"""

import sys


def solve():
    data = sys.stdin.buffer.read().split()
    it = iter(data)
    t = int(next(it))
    out = []

    class DSU:
        def __init__(self, n):
            self.f = list(range(n))
            self.siz = [1] * n

        def find(self, x):
            while x != self.f[x]:
                self.f[x] = self.f[self.f[x]]
                x = self.f[x]
            return x

        def merge(self, x, y):
            x = self.find(x)
            y = self.find(y)
            if x == y:
                return False
            self.siz[x] += self.siz[y]
            self.f[y] = x
            return True

        def same(self, x, y):
            return self.find(x) == self.find(y)

        def size(self, x):
            return self.siz[self.find(x)]

    for _ in range(t):
        n = int(next(it))
        a = [int(next(it)) - 1 for _ in range(n)]
        fl = DSU(n + 1)
        fr = DSU(n + 1)
        cnt = [0] * n
        for ai in a:
            cnt[ai] += 1
        for i in range(1, n):
            cnt[i] += cnt[i - 1]
        p = [0] * n
        for i in range(n):
            cnt[a[i]] -= 1
            p[cnt[a[i]]] = i
        ans = 0
        min_val = n
        p.reverse()
        for i in p:
            for _ in range(2):  # Run the merge operation twice (once for each direction)
                x = fl.find(i + 1)
                if x:  # If x is not zero, update leftward segment
                    fl.merge(x - 1, x)
                    min_val = min(min_val, a[x - 1])
                x = fr.find(i)
                if x < n:  # If x is less than n, update rightward segment
                    fr.merge(x + 1, x)
                    min_val = min(min_val, a[x])
            ans = max(ans, a[i] - min_val)  # Calculate and track max difference
        out.append(str(ans))
    sys.stdout.write("\n".join(out))


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/CodeForces/