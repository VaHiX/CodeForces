# Problem: CF 1946 D - Birthday Gift
# https://codeforces.com/contest/1946/problem/D

"""
Algorithm: Dynamic Programming with Bitmasking
Time Complexity: O(31 * n) per test case, where n is the length of array
Space Complexity: O(n) for prefix XOR array and O(31) for targets list

This solution uses prefix XOR to represent subarray XORs, then checks all valid
bitmasks that can be used to partition the array. For each valid bitmask,
we count how many prefix XOR values fall under the constraint and take the maximum.
"""

import sys

input = sys.stdin.buffer.readline


def find_targets(X):
    # Convert X to binary string and pad to 31 bits
    b = bin(X)[2:].zfill(31)
    targets = [X]
    entry = 0
    # Iterate through each bit position
    for i in range(31):
        if b[i] == "1":
            # Add a new target based on current bit
            targets.append(entry + 2 ** (30 - i) - 1)
        # Update entry for next iteration
        entry = entry + int(b[i]) * 2 ** (30 - i)
    return targets


def process(A, X):
    """
    Compute prefix XORs and determine maximum number of segments
    that satisfy the given constraint on OR of XOR values.
    
    Let S[i] be prefix XOR up to index i-1.
    We want to partition [0, n) into k segments such that:
    (S[l1] ^ S[r1]) | (S[l2] ^ S[r2]) | ... | (S[lk] ^ S[rk]) <= X
    
    Which is equivalent to:
    (S[0] ^ S[l1]) | (S[l1] ^ S[l2]) | ... | (S[lk] ^ S[n]) <= X
    """
    # Build prefix XOR array
    S = [0]
    for x in A:
        S.append(x ^ S[-1])
    
    # If entire array XOR exceeds X, impossible to partition
    if S[-1] > X:
        print("-1")
        return
    
    # Generate all possible target values for valid bitmasks
    targets = find_targets(X)
    max_count = 0
    
    # For each valid target bitmask, count how many prefix XORs can be used
    for target in targets:
        if target | S[-1] == target:
            entry = []
            # Collect all prefix XORs that satisfy the constraint
            for x in S:
                if x | target == target:
                    entry.append(x)
            # Verify that the OR of all collected values doesn't exceed target
            check1 = entry[0]
            for x in entry:
                check1 = check1 | x
            assert check1 <= target
            # Update maximum number of segments
            max_count = max(max_count, len(entry))
    
    # Output number of segments (k), which is one less than count of nodes
    print(max_count - 1)
    return


t = int(input())
for i in range(t):
    n, X = [int(x) for x in input().split()]
    A = [int(x) for x in input().split()]
    process(A, X)


# https://github.com/VaHiX/CodeForces/