# Problem: CF 2064 D - Eating
# https://codeforces.com/contest/2064/problem/D

"""
D. Eating

Purpose:
This code simulates a process where a new slime with weight x is added to the end of a line of slimes,
and it eats slimes to its left based on weight comparison until no more can be eaten.
The goal is to compute how many slimes are eaten in total in each simulation.

Algorithm:
- Preprocess the initial weights using a bit manipulation approach to support efficient lookups
  during queries.
- Use a prefix array `X` to store cumulative XOR from right to left, enabling quick computation of
  weight transformations.
- For each query, simulate the eating process by traversing using bit-length comparisons to find
  which slimes can be eaten, and use precomputed structures for fast transition.

Time Complexity:
- Preprocessing: O(N * D) where D = 31 (number of bits)
- Query processing: O(Q * N) in worst case but optimized with precomputed transitions

Space Complexity:
- O(N * D + N) for `left` table and `X` array

"""

def solve():
    import sys

    data = sys.stdin.buffer.read().split()
    if not data:
        return
    it = iter(data)
    t = int(next(it))
    out_lines = []
    for _ in range(t):
        N = int(next(it))
        Q = int(next(it))
        D = 31
        W = [int(next(it)) for _ in range(N)]
        left = [[0] * (N + 1) for _ in range(D)]
        for i in range(N):
            for j in range(D):
                left[j][i + 1] = left[j][i]
            b = W[i].bit_length()
            left[b][i + 1] = i + 1
        X = [0] * (N + 1)
        for i in range(N - 1, -1, -1):
            X[i] = X[i + 1] ^ W[i]
        for i in range(N + 1):
            for j in range(D - 2, -1, -1):
                if left[j + 1][i] > left[j][i]:
                    left[j][i] = left[j + 1][i]
        res = []
        for _ in range(Q):
            x = int(next(it))
            ind = N
            while ind:
                c = (x ^ X[ind]).bit_length()
                ind = left[c][ind]
                if ind == 0:
                    break
                if W[ind - 1] <= (x ^ X[ind]):
                    ind -= 1
                else:
                    break
            res.append(str(N - ind))
        out_lines.append(" ".join(res))
    sys.stdout.write("\n".join(out_lines))


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/codeForces/