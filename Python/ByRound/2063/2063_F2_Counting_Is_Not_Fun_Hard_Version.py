# Problem: CF 2063 F2 - Counting Is Not Fun (Hard Version)
# https://codeforces.com/contest/2063/problem/F2

# F2. Counting Is Not Fun (Hard Version)
# Purpose: Compute the number of valid balanced bracket sequences compatible with a series of clues,
#          where each clue specifies a good pair (l, r) indicating that s[l]='(' and s[r]=')'
#          are part of the same "good pair" in the sequence construction.
#
# Algorithms:
#   - Precompute Catalan numbers and their modular inverses for fast computation
#   - Use Union-Find with path compression for tracking connectivity changes
#   - Use dynamic enumeration technique involving modular arithmetic to efficiently update
#     the number of valid sequences after each clue.
#
# Time Complexity: O(n log n) per test case due to Union-Find and inverse computation
# Space Complexity: O(n) for storing precomputed values and structures

import os
import sys
from io import BytesIO, IOBase


def make_nCr_mod(max_n=2 * 10**5, mod=10**9 + 7):
    max_n = min(max_n, mod - 1)
    fact, inv_fact = [0] * (max_n + 1), [0] * (max_n + 1)
    fact[0] = 1
    for i in range(max_n):
        fact[i + 1] = fact[i] * (i + 1) % mod
    inv_fact[-1] = pow(fact[-1], mod - 2, mod)
    for i in reversed(range(max_n)):
        inv_fact[i] = inv_fact[i + 1] * (i + 1) % mod

    def nCr_mod(n, r):
        res = 1
        while n or r:
            a, b = n % mod, r % mod
            if a < b:
                return 0
            res = res * fact[a] % mod * inv_fact[b] % mod * inv_fact[a - b] % mod
            n //= mod
            r //= mod
        return res

    return nCr_mod


def main():
    MOD = 998244353
    MAX_N = 3 * 10**5 + 1
    inv = [0] * (2 * MAX_N)
    inv[1] = 1
    for i in range(2, len(inv)):
        # Compute modular inverse using extended Euclidean algorithm or Fermat's little theorem
        inv[i] = (MOD // i) * -inv[MOD % i] % MOD
    catalan = [1] * MAX_N
    # Catalan number computation with multiplication and modular arithmetic:
    # C(n) = (2*(2n-1)/(n+1)) * C(n-1)
    for i in range(1, len(catalan)):
        catalan[i] = (4 * i - 2) * catalan[i - 1] % MOD * inv[i + 1] % MOD
    catalan_inv = [1] * MAX_N
    # Precompute inverse of Catalan numbers for efficient updates during processing
    for i in range(1, len(catalan)):
        catalan_inv[i] = (
            inv[2] * inv[2 * i - 1] % MOD * catalan_inv[i - 1] % MOD * (i + 1) % MOD
        )
    t = int(input())
    for _ in range(t):
        n = int(input())
        point = list(range(1, 2 * n + 3))
        parent = [0]
        parent_idx = [0] * (2 * n + 2)
        size = [0] * (2 * n + 2)
        # Initialize boundary points to form circular structure
        point[0], point[2 * n + 1] = 2 * n + 2, 2 * n + 1
        size[0] = 2 * n
        ans = catalan[n]
        sol = [ans]
        for _ in range(n):
            l, r = map(int, input().split())
            # Update connection between nodes based on clue
            point[l], point[r] = r + 1, r
            p = parent[parent_idx[l]]
            out_ptr, ins_ptr = p + 1, l + 1
            out_size = ins_size = 0
            # Traverse the paths to compute sizes of segments
            while point[out_ptr] != out_ptr and point[ins_ptr] != ins_ptr:
                out_size += point[out_ptr] == out_ptr + 1
                ins_size += point[ins_ptr] == ins_ptr + 1
                out_ptr, ins_ptr = point[out_ptr], point[ins_ptr]
            # Adjust tree structure based on whether pointers reached root nodes
            if point[out_ptr] == out_ptr:
                upd_ptr = p + 1
                parent.append(p)
                parent[parent_idx[l]] = l
                ins_size = size[p] - 2 - out_size
            else:
                upd_ptr = l + 1
                parent.append(l)
                out_size = size[p] - 2 - ins_size
            # Update answer with inverse catalan values based on current segments
            ans = (ans * catalan_inv[size[p] // 2]) % MOD
            size[p], size[l] = out_size, ins_size
            ans = (ans * catalan[size[p] // 2]) % MOD * catalan[size[l] // 2] % MOD
            # Update parent index for all affected nodes in path
            while point[upd_ptr] != upd_ptr:
                parent_idx[upd_ptr] = len(parent) - 1
                upd_ptr = point[upd_ptr]
            sol.append(ans)
        print(*sol)


BUFSIZE = 8192


class FastIO(IOBase):
    newlines = 0

    def __init__(self, file):
        self._file = file
        self._fd = file.fileno()
        self.buffer = BytesIO()
        self.writable = "x" in file.mode or "r" not in file.mode
        self.write = self.buffer.write if self.writable else None

    def read(self):
        while True:
            b = os.read(self._fd, max( os.fstat(self._fd).st_size, BUFSIZE ))
            if not b: break
            ptr = self.buffer.tell()
            self.buffer.seek(0,2)
            self.buffer.write(b)
            self.buffer.seek(ptr)
        return self.buffer.read()

    def readline(self):
        while self.buffer.tell() == 0:
            b = os.read(self._fd, max( os.fstat(self._fd).st_size, BUFSIZE ))
            if not b: break
            ptr = self.buffer.tell()
            self.buffer.seek(0,2)
            self.buffer.write(b)
            self.buffer.seek(ptr)
        return self.buffer.readline()

    def flush(self):
        if self.writable:
            os.write(self._fd, self.buffer.getvalue())
            self.buffer.truncate(0)
            self.buffer.seek(0)

    def write(self, b):
        self.flush()
        os.write(self._fd, b)


class IOWrapper(IOBase):
    def __init__(self, file):
        self.buffer = FastIO(file)
        self.flush = self.buffer.flush
        self.writable = self.buffer.writable
        self.write = lambda x: self.buffer.write(x.encode('utf-8'))

def input():
    return sys.stdin.readline().rstrip()

if __name__ == "__main__":
    main()


# https://github.com/VaHiX/codeForces/