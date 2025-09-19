# Contest 2111, Problem G: Divisible Subarrays
# URL: https://codeforces.com/contest/2111/problem/G

import sys

# Optimized input function
input = sys.stdin.readline


class Solver:
    def __init__(self, p_array):
        self.p = p_array
        self.n = len(p_array)

        # LOGN needs to be ceil(log2(n))
        # If n is 0 or 1, bit_length() is 0. Handle these cases.
        if self.n <= 1:
            self.LOGN = 1  # For single element or empty array, 1 is sufficient
        else:
            self.LOGN = (
                self.n - 1
            ).bit_length()  # Equivalent to ceil(log2(n)) for n > 1

        self.nxtmn = [self.n] * self.n  # Next smaller element to the right
        self.nxtmx = [self.n] * self.n  # Next greater element to the right

        # Binary lifting tables
        # up[i][j] stores the result of applying nxtmx j times starting from i
        self.up = [[self.n] * self.LOGN for _ in range(self.n + 1)]
        # mx[i][j] stores the maximum nxtmn value encountered in the path of j nxtmx jumps from i
        self.mx = [[0] * self.LOGN for _ in range(self.n + 1)]

        self._build_sparse_table()

    def _build_sparse_table(self):
        # --- Step 1: Calculate nxtmx (next greater element to the right) ---
        # Using a monotonic stack: stores indices of elements in decreasing order
        stmx = []
        for i in range(self.n - 1, -1, -1):
            while stmx and self.p[stmx[-1]] < self.p[i]:
                stmx.pop()
            if stmx:
                self.nxtmx[i] = stmx[-1]
            # If stack is empty, no greater element to the right, so nxtmx[i] remains self.n
            stmx.append(i)

        # --- Step 2: Prepare queries for nxtmn calculation ---
        # qr[k] will store a list of original indices 'j' such that nxtmx[j] == k.
        # This groups elements by their next greater element.
        qr = [[] for _ in range(self.n + 1)]
        for i in range(self.n):
            qr[self.nxtmx[i]].append(i)

        # --- Step 3: Calculate nxtmn (next smaller element to the right, but before nxtmx) ---
        # Using a monotonic stack: stores indices of elements in increasing order (for finding smaller)
        stmn = []
        for i in range(self.n - 1, -1, -1):
            # Maintain stmn: elements `p[stmn[k]]` are in increasing order.
            # Pop elements from stack that are greater than p[i]
            while stmn and self.p[stmn[-1]] > self.p[i]:
                stmn.pop()
            stmn.append(i)  # Add current index `i` to the stack

            # Now, for all indices `j` whose `nxtmx` is the current `i`:
            # we need to find the rightmost element in `stmn` (indices < i)
            # whose value is less than `p[j]`. This effectively finds the next smaller.
            for j in qr[i]:
                l_bs, r_bs = 0, len(stmn) - 1
                found_smaller_idx = self.n  # Default to self.n (not found)

                while l_bs <= r_bs:
                    m = (l_bs + r_bs) // 2
                    # We are looking for the rightmost element `stmn[m]` such that `p[stmn[m]] < p[j]`
                    if self.p[stmn[m]] < self.p[j]:
                        found_smaller_idx = stmn[m]
                        l_bs = (
                            m + 1
                        )  # Try to find an even larger index (more to the right)
                    else:
                        r_bs = (
                            m - 1
                        )  # Current element is not smaller enough, look to the left
                self.nxtmn[j] = found_smaller_idx

        # --- Step 4: Build Binary Lifting (Sparse Table) for up and mx arrays ---
        # Base case: jump of 2^0 = 1 step
        for i in range(self.n):
            self.up[i][0] = self.nxtmx[i]
            self.mx[i][0] = self.nxtmn[i]

        # Sentinel node for index self.n (out of bounds)
        self.up[self.n][0] = self.n
        self.mx[self.n][
            0
        ] = (
            self.n
        )  # Setting to self.n ensures max(mx[..]) will not pick it up if it's the only value.
        # C++ used 0, but self.n is safer as a large sentinel value.

        # Fill up tables for larger jumps (2^j steps)
        for j in range(1, self.LOGN):
            for i in range(self.n + 1):  # Iterate up to n (including sentinel)
                intermediate_node = self.up[i][j - 1]
                self.up[i][j] = self.up[intermediate_node][j - 1]
                self.mx[i][j] = max(
                    self.mx[i][j - 1], self.mx[intermediate_node][j - 1]
                )

    def query(self, start_idx, target_r_exclusive):
        # We need to find if there's a path of 'nxtmx' jumps from `start_idx`
        # such that the path stays within `[start_idx, target_r_exclusive)`
        # AND there is at least one `nxtmn` jump along this path that reaches `target_r_exclusive` or beyond.

        v = start_idx
        # Iterate from largest jump (LOGN-1) down to smallest (0)
        for i in range(self.LOGN - 1, -1, -1):
            # Condition 1: Can we take this jump (2^i steps) without going beyond `target_r_exclusive`?
            # If up[v][i] (the node reached by 2^i nxtmx jumps from v) is ALREADY >= target_r_exclusive,
            # we cannot take this jump yet, as it would overhoot. We need to find a smaller jump.
            if self.up[v][i] >= target_r_exclusive:
                continue  # Try a smaller jump (smaller i)

            # Condition 2: If we take this jump (up[v][i]), does the *maximum nxtmn*
            # encountered *within this jump* already satisfy our condition?
            # If mx[v][i] (the max nxtmn in path) is >= target_r_exclusive, it means
            # there's an element in this segment that fulfills the nxtmn condition.
            if self.mx[v][i] >= target_r_exclusive:
                return True  # Found a valid path

            # If neither of the above, take this jump and continue searching from the new position
            v = self.up[v][i]

        # After the loop:
        # 'v' is the furthest index reachable from `start_idx` via `nxtmx` jumps
        # such that `nxtmx[v]` itself is still < `target_r_exclusive`.
        # All jumps from `v` using `up[v][i]` for `i` from LOGN-1 down to 0 resulted in either
        # overshooting `target_r_exclusive` or `mx` not being large enough.
        # This implies no such path exists. The C++ logic correctly returns false here.
        return False


def main():
    # Use global input/output for faster access and consistency
    # sys.stdin.readline is generally faster than input()
    # sys.stdout.write is generally faster than print() for multiple outputs
    # and avoiding string concatenation for every print.

    n = int(input())
    p_input = list(map(int, input().split()))
    p0_values = [x - 1 for x in p_input]  # Adjust to 0-indexed values for problem logic

    # The problem implies we also need to check the "reversed" array logic,
    # which corresponds to finding a partition where min(Left) > max(Right).
    # This is handled by applying the same logic to the reversed array.
    p1_values = p0_values[::-1]  # Reversed array for the second condition

    solver_p0 = Solver(p0_values)
    solver_p1 = Solver(p1_values)

    m = int(input())

    output_buffer = []  # Store results to print in batches

    for i in range(m):
        l_orig, r_orig = map(int, input().split())
        l_0_indexed = l_orig - 1  # Convert to 0-indexed
        r_0_indexed = r_orig - 1  # Convert to 0-indexed

        # Condition 1 check: For the original array p0_values
        # We query if there's a partition in [l_0_indexed, r_0_indexed]
        # such that max(Left) < min(Right).
        # This is what p0_solver.query(l, r+1) aims to find.
        # The target_r_exclusive is r+1 because the 'nxtmx' chain
        # should stay within [l, r], and we need an 'nxtmn' value
        # that reaches 'r' or beyond.
        ans_p0 = solver_p0.query(l_0_indexed, r_0_indexed + 1)

        # Condition 2 check: For the reversed array p1_values
        # This corresponds to min(Left) > max(Right) in the original problem.
        # We need to map the original [l_orig, r_orig] range to the reversed array's indices.
        # If original range is [l, r], in reversed array (length n),
        # this corresponds to indices [n - 1 - r, n - 1 - l].
        # So, the query for solver_p1 uses:
        # start_idx_p1 = n - 1 - r_0_indexed
        # target_r_exclusive_p1 = (n - 1 - l_0_indexed) + 1
        ans_p1 = solver_p1.query(n - 1 - r_0_indexed, n - 1 - l_0_indexed + 1)

        if ans_p0 or ans_p1:
            output_buffer.append("YES")
        else:
            output_buffer.append("NO")

        # Flush output periodically if problem has strict interactive output requirements
        # or to debug where it stops. Otherwise, batching is generally faster.
        # The C++ code had `if (i % 10 == 0) cout.flush();`. Let's match that.
        if (i + 1) % 10 == 0:
            sys.stdout.write("\n".join(output_buffer) + "\n")
            sys.stdout.flush()
            output_buffer = []  # Clear buffer after flushing

    # Print any remaining results after the loop
    if output_buffer:
        sys.stdout.write("\n".join(output_buffer) + "\n")
        # No need for flush if it's the end of program, but good practice
        sys.stdout.flush()


if __name__ == "__main__":
    main()
