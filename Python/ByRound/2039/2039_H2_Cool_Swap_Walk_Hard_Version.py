# Problem: CF 2039 H2 - Cool Swap Walk (Hard Version)
# https://codeforces.com/contest/2039/problem/H2

"""
Algorithm: Cool Swap Walk (Hard Version)
Purpose: Sort an array using at most n+4 cool swap walks by traversing an n×n grid from (1,1) to (n,n).
Each walk corresponds to a path of right (R) and down (D) moves.

Key Techniques:
- Grid traversal with path encoding
- Permutation-based sorting simulation using swaps
- Modular arithmetic for cyclic indexing
- Preprocessing to determine target order

Time Complexity: O(n^2) per test case due to nested loops
Space Complexity: O(n) for storing operations and auxiliary arrays

The approach constructs a series of paths to simulate sorting:
1. Normalize input indices to 0-based
2. Map original array indices to their sorted positions
3. Generate paths through a grid to swap elements when needed
4. Each path is designed to partially sort the array
"""
def II():
    return int(input())

def LII():
    return list(map(int, input().split()))

def f(nums):
    n = len(nums)
    if n == 2:
        # Base case: for n=2, only one path needed if not sorted
        if nums[0] < nums[1]:
            return []
        else:
            return ["DR"]
    else:
        # Normalize elements to range [0, n-1] to simplify indexing
        nums = [(i + 4) % n for i in nums]
        ops = []

        # For each of the n+4 paths, simulate the process
        for i in range(n + 4):
            op = []
            # Process pairs of adjacent elements (odd indices in path)
            for j in range(1, n - 1, 2):
                j1 = (i + j) % n
                j2 = (i + j + 1) % n
                # If the pair is out of order, perform a swap and record path step
                if j1 < j2 and nums[j1] > nums[j2]:
                    nums[j1], nums[j2] = nums[j2], nums[j1]
                    op.append("RRDD")
                else:
                    op.append("RDRD")
            # Handle the final element for even n (to complete grid path)
            if n % 2 == 0:
                op.append("RD")
            ops.append("".join(op))

        return ops


t = II()  # Read number of test cases
outs = []

for _ in range(t):
    n = II()  # Read array size
    nums = LII()  # Read array elements

    # Determine how to sort indices of the array
    st_range = sorted(range(n), key=lambda x: nums[x])
    tmp = [0] * n  # Map from sorted position to original index
    for i in range(n):
        tmp[st_range[i]] = i

    ans = f(tmp)  # Compute the required paths
    outs.append(str(len(ans)))  # First output number of operations
    if len(ans):  # If operations exist
        outs.append("\n".join(ans))  # Output each path

# Print all results
print("\n".join(outs))


# https://github.com/VaHiX/CodeForces/