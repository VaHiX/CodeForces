# Problem: CF 2094 H - La Vaca Saturno Saturnita
# https://codeforces.com/contest/2094/problem/H

"""
H. La Vaca Saturno Saturnita
Algorithm: Efficient computation of function f(k, a, l, r) using precomputed factors and reverse iteration.
Approach:
    - Precompute all prime factors for numbers up to 1e5.
    - Process queries in reverse order to efficiently track next occurrence of each factor.
    - For each query, simulate the process of reducing k by dividing with elements from a[l] to a[r].
    - Track transitions using precomputed factor positions.

Time Complexity: O(N * log(N) + Q * log(max(a[i]))) where N is max array length and Q is number of queries
Space Complexity: O(N + Q) for storing factors, next_pos array, and queries per index

"""

import sys

input = sys.stdin.readline

N = int(1e5) + 10
next_pos = [N] * N  # Tracks next occurrence of each value in array
factors = [[] for _ in range(N)]  # Precomputed list of factors for each number up to N
for i in range(2, N):
    for j in range(i, N, i):
        factors[j].append(i)  # Build list of prime factors for all numbers up to N


def solve_testcase():
    n, nq = map(int, input().split())
    a = list(map(int, input().split()))
    q = [[] for _ in range(n)]  # Store queries per starting index
    
    # Read all queries and group them by their starting index
    for i in range(nq):
        k, l, r = map(int, input().split())
        l -= 1  # Convert to 0-based indexing
        r -= 1
        q[l].append((r, k, i))
    
    ans = [0] * nq  # Store answers for each query

    # Process array from right to left
    for i in range(n - 1, -1, -1):
        next_pos[a[i]] = i  # Update next occurrence of value a[i]
        
        # Process all queries that start at this index
        for r, k, idx in q[i]:
            l = i  # Current left boundary
            
            # Simulate the process of reducing k and calculating contribution
            while True:
                p = N  # Next position of any factor of k
                
                # Find minimum next position among all prime factors of k
                for v in factors[k]:
                    p = min(p, next_pos[v])
                
                # If no such position exists within range (r), add final contribution
                if p > r:
                    ans[idx] += (r - l + 1) * k
                    break
                
                # Add contribution of current segment before transition
                ans[idx] += (p - l) * k
                
                # Remove all occurrences of factor a[p] from k
                while k % a[p] == 0:
                    k //= a[p]
                
                l = p  # Move left pointer to transition point
    
    # Output answers for each query
    for x in ans:
        print(x)

    # Reset next_pos array for next test case
    for i in a:
        next_pos[i] = N


T = int(input())
for _ in range(T):
    solve_testcase()


# https://github.com/VaHiX/codeForces/