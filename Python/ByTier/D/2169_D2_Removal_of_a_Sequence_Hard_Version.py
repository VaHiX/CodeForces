# Problem: CF 2169 D2 - Removal of a Sequence (Hard Version)
# https://codeforces.com/contest/2169/problem/D2

from sys import stdin

input_int = lambda: int(stdin.readline())
input_ints = lambda: list(map(int, stdin.readline().split()))


def f(x, y, k):
    # If y equals 1, every element is removed in the first step, return -1
    if y == 1:
        return -1
    
    # Track how many operations we have performed
    used = 0
    while used < x:
        # Calculate how many elements are skipped for each step
        d = (k - 1) // (y - 1)
        # If d is 0, it means k is small enough that no elements were removed
        if d == 0:
            return k
        # Compute the limit of the current k value after operations
        k_limit = (d + 1) * (y - 1)
        # Estimate number of times to apply next operation
        times = (k_limit - k) // d
        # Ensure we do not exceed the remaining operations allowed
        times = min(times, x - used)
        # Ensure at least one operation is applied
        times = max(times, 1)
        # Update number of operations used
        used += times
        # Update k value for the next iteration
        k += d * times
        # If k exceeds 10^12, it's out of range, return -1
        if k > 10**12:
            return -1
    return k


t = input_int()
for _ in range(t):
    x, y, k = input_ints()
    print(f(x, y, k))

### Algorithm and Complexity Analysis

# **Purpose**:  
# This code solves a problem where a sequence of numbers from 1 to $10^{12}$ is modified by removing elements at specific intervals $y$, $2y$, $3y$, ..., up to $x$ steps. After all operations, it returns the $k$-th element in the resulting sequence, or $-1$ if the sequence is shorter than $k$.  

# **Algorithms/Techniques**:
# - **Reverse Simulation**: Instead of simulating the removal of elements forward, the code works backward to infer the final position of the element.
# - **Binary Search or Mathematical Estimation**: Efficiently calculates how many elements are skipped and how many operations can be applied before $k$ exceeds the limits.

# **Time Complexity**:  
# - **$O(x)$** per test case, as the loop runs at most $x$ times and each step processes elements in constant time. Since $x$ can be up to $10^{12}$, the algorithm must be very efficient.

# **Space Complexity**:  
# - **$O(1)$**, only using a constant amount of extra memory.

# **Note**:  
# While theoretical worst-case complexity is $O(x)$, due to large input size, performance optimization is critical for correctness in competitive programming settings. The function `f` avoids full simulation and uses mathematical estimation to reduce computations.

# https://github.com/VaHiX/CodeForces/