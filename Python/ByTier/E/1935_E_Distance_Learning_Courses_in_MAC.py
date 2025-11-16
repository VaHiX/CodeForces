# Problem: CF 1935 E - Distance Learning Courses in MAC
# https://codeforces.com/contest/1935/problem/E

"""
Algorithm: Segment Tree with BIT manipulation
Time Complexity: O(n * log(n) + q * log(n) * 30)
Space Complexity: O(n * 30 + n)

This solution processes distance learning courses where each course i has a range [x_i, y_i] 
of possible grades. For each student j, who can take courses from l_j to r_j, we must 
compute the maximum possible bitwise OR of grades they can achieve.

The approach:
1. Build a segment tree of base values derived from range [x_i, y_i].
2. For each query [l_j, r_j], get the OR of base values in that range.
3. Use preprocessed bit counts to check how many times a bit appears in [l_j, r_j].
4. For each bit position:
   - If it appears more than once, we can make it 1 in the result.
   - If it appears exactly once, we can still make it 1 if the range allows.
5. This gives us the maximum possible OR value.

The segment tree is used to compute range OR queries efficiently.
The bit counting pre-processing allows us to quickly compute how many times a bit appears
in any range.
"""

from sys import stdin


class SegTree:
    def __init__(self, vals, val=0):
        assert len(vals) > 0
        self.n = 1 << (len(vals) - 1).bit_length()  # Compute next power of 2
        self.vals = [0] * (self.n)
        self.vals.extend(vals)  # Copy values
        self.vals.extend([0] * (2 * self.n - len(self.vals)))
        vals = self.vals
        # Build the segment tree by combining children with OR operation
        for v in reversed(range(1, self.n)):
            vals[v] = vals[v << 1] | vals[v << 1 | 1]

    def range_or(self, l, r):
        n = self.n
        vals = self.vals
        res = 0
        l += n  # Convert to leaf indices
        r += n
        # Traverse the tree to compute OR of range [l, r)
        while l < r:
            if r & 1:  # If right index is odd
                res |= vals[r - 1]
            if l & 1:  # If left index is odd
                res |= vals[l]
                l += 1
            r >>= 1  # Move to parent
            l >>= 1
        return res


def solve():
    n = int(stdin.readline())
    # Preprocessing: bit_counts[d][i] counts how many times bit d appears in prefixes up to i
    bit_counts = [[0] * (n + 1) for deg in range(30)]
    base_vals = [0] * n  # Base values for segment tree
    
    for i in range(n):
        x, y = map(int, stdin.readline().split())
        if x == y:
            # If range has only one value, use it directly
            base_vals[i] = x
        else:
            # Extract the highest bit that differs between x and y
            deg = (x ^ y).bit_length()
            # Compute the largest value in [x, y] that has only the higher bits set
            base_vals[i] = (x >> deg) << deg
            # Mark positions that can set bit d in [x, y]
            for d in range(deg):
                if y & (1 << d) != 0:
                    bit_counts[d][i + 1] = 1  # Mark that bit d can be set
    
    # Build prefix sums for each bit position
    for d in range(30):
        arr = bit_counts[d]
        for i in range(1, n + 1):
            arr[i] += arr[i - 1]
    
    # Create segment tree for base values
    or_tree = SegTree(base_vals)

    q = int(stdin.readline())
    result = []
    for i in range(q):
        l, r = (int(w) - 1 for w in stdin.readline().split())  # Convert to 0-indexed
        res = or_tree.range_or(l, r + 1)  # Get OR of range
        
        # Enhance the result using bit counts
        for d in reversed(range(30)):
            # Count how many 1s are in bit d for range [l, r]
            n_ones = ((res >> d) & 1) + bit_counts[d][r + 1] - bit_counts[d][l]
            if n_ones > 1:  # Two or more 1s in bit d, so we can make it 1
                res |= (1 << d + 1) - 1
                break
            if n_ones == 1:  # Exactly one 1, we can potentially make it 1
                res |= 1 << d
        result.append(res)
    print(*result)


n_tests = int(stdin.readline())
for test_id in range(n_tests):
    solve()


# https://github.com/VaHiX/CodeForces/