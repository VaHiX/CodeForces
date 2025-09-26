# Problem: CF 2111 G - Divisible Subarrays
# https://codeforces.com/contest/2111/problem/G

"""
G. Divisible Subarrays
Purpose: Determine if a subarray of a permutation is divisible.
         A subarray is divisible if it can be split at some index such that:
         - Left part is all <= x and right part is all > x, or
         - Left part is all > x and right part is all <= x for some x.
Algorithms/Techniques:
    - Sparse Table for Range Maximum/Minimum queries
    - Preprocessing to find next greater/smaller elements using stack techniques
Time Complexity: O(n * log n + q * log n)
Space Complexity: O(n * log n)
"""

import sys

input = sys.stdin.readline


class Solver:
    def __init__(self, p_array):
        self.p = p_array
        self.n = len(p_array)
        if self.n <= 1:
            self.LOGN = 1
        else:
            self.LOGN = (self.n - 1).bit_length()
        self.nxtmn = [self.n] * self.n  # Next smaller element index for each position
        self.nxtmx = [self.n] * self.n  # Next greater element index for each position
        self.up = [[self.n] * self.LOGN for _ in range(self.n + 1)]  # Sparse table for next greater elements
        self.mx = [[0] * self.LOGN for _ in range(self.n + 1)]      # Sparse table for maximum smaller element indices
        self._build_sparse_table()

    def _build_sparse_table(self):
        stmx = []
        # Find next greater element for each index using stack
        for i in range(self.n - 1, -1, -1):
            while stmx and self.p[stmx[-1]] < self.p[i]:
                stmx.pop()
            if stmx:
                self.nxtmx[i] = stmx[-1]
            stmx.append(i)
        
        # Prepare queries for next smaller elements
        qr = [[] for _ in range(self.n + 1)]
        for i in range(self.n):
            qr[self.nxtmx[i]].append(i)
        
        stmn = []
        # Find the next smaller element (with respect to current elements) using stack
        for i in range(self.n - 1, -1, -1):
            while stmn and self.p[stmn[-1]] > self.p[i]:
                stmn.pop()
            stmn.append(i)
            for j in qr[i]:
                l_bs, r_bs = 0, len(stmn) - 1
                found_smaller_idx = self.n
                # Binary search on stack to find the smallest element that is smaller than p[j]
                while l_bs <= r_bs:
                    m = (l_bs + r_bs) // 2
                    if self.p[stmn[m]] < self.p[j]:
                        found_smaller_idx = stmn[m]
                        l_bs = m + 1
                    else:
                        r_bs = m - 1
                self.nxtmn[j] = found_smaller_idx
        
        # Initialize the first level of sparse tables for up and mx
        for i in range(self.n):
            self.up[i][0] = self.nxtmx[i]
            self.mx[i][0] = self.nxtmn[i]
        self.up[self.n][0] = self.n
        self.mx[self.n][0] = self.n
        
        # Build sparse table by doubling the jump length
        for j in range(1, self.LOGN):
            for i in range(self.n + 1):
                intermediate_node = self.up[i][j - 1]
                self.up[i][j] = self.up[intermediate_node][j - 1]
                self.mx[i][j] = max(
                    self.mx[i][j - 1], self.mx[intermediate_node][j - 1]
                )

    def query(self, start_idx, target_r_exclusive):
        v = start_idx
        # Jump using sparse table to see if there exists any valid split
        for i in range(self.LOGN - 1, -1, -1):
            if self.up[v][i] >= target_r_exclusive:
                continue
            if self.mx[v][i] >= target_r_exclusive:
                return True
            v = self.up[v][i]
        return False


def main():
    n = int(input())
    p_input = list(map(int, input().split()))
    p0_values = [x - 1 for x in p_input] # Convert to 0-indexed
    p1_values = p0_values[::-1]          # Reverse array for second solver
    solver_p0 = Solver(p0_values)
    solver_p1 = Solver(p1_values)
    m = int(input())
    output_buffer = []
    for i in range(m):
        l_orig, r_orig = map(int, input().split())
        l_0_indexed = l_orig - 1
        r_0_indexed = r_orig - 1
        ans_p0 = solver_p0.query(l_0_indexed, r_0_indexed + 1)
        # Reverse the indices for second checker to simulate original array
        ans_p1 = solver_p1.query(n - 1 - r_0_indexed, n - 1 - l_0_indexed + 1)
        if ans_p0 or ans_p1:
            output_buffer.append("YES")
        else:
            output_buffer.append("NO")
        # Flush after every 10 queries
        if (i + 1) % 10 == 0:
            sys.stdout.write("\n".join(output_buffer) + "\n")
            sys.stdout.flush()
            output_buffer = []
    if output_buffer:
        sys.stdout.write("\n".join(output_buffer) + "\n")
        sys.stdout.flush()


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/codeForces/