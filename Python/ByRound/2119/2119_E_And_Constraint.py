# Problem: CF 2119 E - And Constraint
# https://codeforces.com/contest/2119/problem/E

"""
E. And Constraint

Purpose:
This code solves a problem where we are given two sequences: 'a' of length n-1 and 'b' of length n.
The goal is to find the minimum number of increment operations on elements of b such that for every i,
b[i] & b[i+1] == a[i], where & is bitwise AND. If impossible, return -1.

Algorithms/Techniques:
- Bit manipulation and dynamic programming with state compression
- For each bit position, it's checked whether the constraints can be satisfied.
- A backtracking-like logic is used in `opt` function to compute possible values for a given value and constraint.
- Dynamic Programming over states of possible values in b for current and next positions.

Time Complexity:
O(n * 30 * (2^30)) in worst case due to bit manipulation and state transitions, but bounded by constraints.

Space Complexity:
O(2^30) for storing intermediate results in DP, but practically much less due to pruning.

"""

baku = []
inf = 1 << 61

for _ in range(int(input())):
    n = int(input())
    a = [int(t) for t in input().split()]
    b = [int(t) for t in input().split()]
    
    # Precompute required bits that must be set to satisfy constraints
    need = [0] * n
    for i in range(n - 1):
        need[i] |= a[i]
        need[i + 1] |= a[i]

    # Check if it's logically possible to satisfy conditions
    if any(need[i] & need[i + 1] != a[i] for i in range(n - 1)):
        baku.append(-1)
        continue

    def opt(e, p):
        """
        Given an element 'e' and its required bits 'p', compute all valid extensions
        such that the final value is consistent with allowed bit patterns.
        """
        x = e
        for z in range(29, -1, -1):
            if p & (1 << z) and not e & (1 << z):
                mask = (1 << z + 1) - 1
                x = (e ^ (e & mask)) | p # Set all bits up to z+1 according to 'p' 
                break
        line = [x]
        if x == p:
            return line
        m = x & (-x) # Get lowest set bit
        while m < (1 << 31):
            if not p & m: # If we can unset bit at position m in the pattern
                if not x & m: # Only if it's already unset in x
                    x ^= m
                    line.append(x)
                x ^= m
            m <<= 1
        return line

    # Compute all valid extensions for each element of b under constraint from 'need'
    nums = [opt(e, p) for e, p in zip(b, need)]
    
    # Dynamic Programming on possible states of values from first to last
    v = [e - b[0] for e in nums[0]]  # Cost to achieve each valid start value
    
    for i in range(n - 1):
        nl = nums[i]
        nr = nums[i + 1]
        w = [inf] * len(nr)
        
        for x, bx in enumerate(nl):
            for y, by in enumerate(nr):
                if bx & by != a[i]:
                    continue  # Skip impossible combinations
                w[y] = min(w[y], v[x] + by - b[i + 1])  # Update DP with new cost
                
        v = w  # Move to next state

    baku.append(min(v))

print(*baku)


# https://github.com/VaHiX/codeForces/