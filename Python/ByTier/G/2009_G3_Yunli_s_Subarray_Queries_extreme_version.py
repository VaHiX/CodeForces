# Problem: CF 2009 G3 - Yunli's Subarray Queries (extreme version)
# https://codeforces.com/contest/2009/problem/G3

"""
Algorithm: G3. Yunli's Subarray Queries (extreme version)

This problem involves computing the sum of minimum operations needed to form a consecutive subarray of length at least k for all subarrays within a range [l, r].

Approach:
1. Preprocess array 'a' to transform it using `a[i] = a[i] - i`. This allows us to identify consecutive elements easily.
2. Use a sliding window technique with a frequency map to compute `f(b)` for each subarray efficiently.
3. Build a segment tree with range minimum queries to answer range min queries quickly.
4. Use prefix/suffix sums and segment tree to calculate the final result of each query in O(log n) time.

Time Complexity: O(n log n + q log n)
Space Complexity: O(n)

The solution uses a combination of:
- Hash map for frequency counting
- Segment trees for range minimum queries
- Prefix/suffix sums for efficient range calculations

"""

import sys


def main():
    data = sys.stdin.read().split()
    it = iter(data)
    T = int(next(it))
    out_lines = []
    for _ in range(T):
        n0 = int(next(it))
        k = int(next(it))
        q = int(next(it))
        a = [0] * (n0 + 2)
        for i in range(1, n0 + 1):
            a[i] = int(next(it)) - i  # Transform element to check for consecutive values
        c = {}
        fc = {}
        maxf = 0
        b = [0] * (n0 + 2)
        for i in range(n0, 0, -1):
            old = c.get(a[i], 0)
            if old > 0:
                fc[old] = fc.get(old, 0) - 1  # Decrease frequency of old count
            new = old + 1
            c[a[i]] = new
            fc[new] = fc.get(new, 0) + 1  # Increase frequency of new count
            if new > maxf:
                maxf = new
            if i + k <= n0:
                v = a[i + k]
                old_r = c.get(v, 0)
                fc[old_r] -= 1
                new_r = old_r - 1
                if new_r > 0:
                    c[v] = new_r
                    fc[new_r] = fc.get(new_r, 0) + 1
                else:
                    del c[v]
                if fc.get(maxf, 0) == 0:
                    maxf -= 1
            b[i] = k - maxf  # Compute f(b) value for subarray starting at i
        n = n0 - (k - 1)  # Effective length for our operations
        fl = [0] * (n + 2)
        fr = [0] * (n + 2)
        sl = [0] * (n + 2)
        sr = [0] * (n + 2)
        st = [[0] * (n.bit_length() + 1) for _ in range(n + 2)]
        stack = []
        for i in range(1, n + 1):
            while stack and b[stack[-1]] > b[i]:
                stack.pop()
            prev = stack[-1] if stack else 0
            fl[i] = fl[prev] + b[i] * (i - prev)
            stack.append(i)
        stack.clear()
        b[n + 1] = 0
        for i in range(n, 0, -1):
            while stack and b[stack[-1]] > b[i]:
                stack.pop()
            nxt = stack[-1] if stack else n + 1
            fr[i] = fr[nxt] + b[i] * (nxt - i)
            stack.append(i)
        for i in range(1, n + 1):
            sl[i] = sl[i - 1] + fl[i]
        for i in range(n, 0, -1):
            sr[i] = sr[i + 1] + fr[i]
        for i in range(1, n + 1):
            st[i][0] = i
        max_log = n.bit_length()
        for j in range(1, max_log + 1):
            span = 1 << (j - 1)
            for i in range(1, n - (1 << j) + 2):
                x = st[i][j - 1]
                y = st[i + span][j - 1]
                st[i][j] = x if b[x] <= b[y] else y
        for _ in range(q):
            l = int(next(it))
            r = int(next(it))
            r -= k - 1
            length = r - l + 1
            j = length.bit_length() - 1
            x1 = st[l][j]
            x2 = st[r - (1 << j) + 1][j]
            x = x1 if b[x1] <= b[x2] else x2
            A = sl[r] - sl[x] - fl[x] * (r - x)
            B = sr[l] - sr[x] - fr[x] * (x - l)
            C = b[x] * (x - l + 1) * (r - x + 1)
            out_lines.append(str(A + B + C))
    sys.stdout.write("\n".join(out_lines))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/