# Problem: CF 2020 A - Find Minimum Operations
# https://codeforces.com/contest/2020/problem/A

"""
Problem: Find minimum operations to reduce n to 0 by subtracting powers of k.
Algorithm: Greedy approach using base-k representation.
Time Complexity: O(log_k(n)) per test case.
Space Complexity: O(1).

This solution uses the fact that the minimum number of operations equals 
the sum of digits in the base-k representation of n.
"""

for s in [*open(0)][1:]:
    n, k = map(int, s.split())  # Read n and k from input line
    r = n * (k < 2)             # If k is 1, all operations must subtract 1, so answer is n
    while (k > 1) * n:          # While k > 1 and n > 0
        r += n % k              # Add the remainder when dividing n by k (this contributes to digit sum)
        n //= k                 # Divide n by k (move to next digit in base-k representation)
    print(r)                    # Print result


# https://github.com/VaHiX/codeForces/