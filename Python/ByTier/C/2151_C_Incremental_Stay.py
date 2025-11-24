# Problem: CF 2151 C - Incremental Stay
# https://codeforces.com/contest/2151/problem/C

# Incremental Stay
# Purpose: For each k from 1 to n, compute the maximum possible total stay time of visitors,
#          given that at most k people can be in the museum simultaneously.
# Algorithm: Greedy approach with prefix sum and alternating signs for optimal pairing.
# Time Complexity: O(n) per test case, as we process array once and compute results incrementally.
# Space Complexity: O(1), using only a few variables for computation.

for _ in range(int(input())):  # Loop through each test case
    n = int(input())          # Read number of entries/exists (n)
    l = list(map(int, input().split()))  # Read activity times
    
    a = 0                     # Initialize variable for cumulative stay time
    b = 0                     # Initialize another variable for tracking

    # Compute initial value of 'a' using alternating sign sum on activity times
    for i in range(2 * n):
        a += (-1) ** (i + 1) * l[i]
    
    print(a, end=" ")         # Print result for k=1
    
    # Iterate from k=2 to k=n and compute incremental results
    for i in range(0, n - 1):
        # Update 'a' by adding difference of adjacent elements and negating
        a += l[i] - l[~i]     # ~i is bitwise NOT; equivalent to -(i+1) so l[~i] = l[-(i+1)]
        a = -a                # Negate 'a'
        
        # Update 'b' with the contribution of current pair
        b += l[~i] - l[i]
        
        # Print combined value for current k
        print(int(b + a), end=" ")
    
    print()                   # New line after printing all k values



# https://github.com/VaHiX/CodeForces/