# Problem: CF 1499 C - Minimum Grid Path
# https://codeforces.com/contest/1499/problem/C

"""
Minimum Grid Path

This problem involves finding the minimum cost path from (0,0) to (n,n) on a grid,
where movement is restricted to horizontal and vertical segments alternating.
Each segment has a cost associated with it, and the cost of a path is the sum of
(length * cost) for each segment.

Algorithm:
- Dynamic Programming approach is used.
- We precompute minimum costs for paths of even and odd lengths.
- For each possible number of segments k (from 2 to n), we compute the minimal cost
  of a path using exactly k segments, considering:
    - Alternating pattern of horizontal and vertical moves
    - Minimizing the sum of costs across all segments

Time Complexity: O(n^2) - For each k (up to n), we do constant time work.
Space Complexity: O(n) - For storing M and csum arrays of size n.

"""

for _ in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    # M[i] stores the minimum cost of the last two elements in an alternating pattern up to index i
    M = [a[0], a[1]]
    # csum[i] stores cumulative sum of costs up to index i (with alternating pattern considered)
    csum = [a[0], a[1]]
    
    # Fill up the dp arrays
    for i in range(2, n):
        M.append(min(a[i], M[-2]))  # Keep track of the minimal cost so far
        csum.append(a[i] + csum[-2])  # Cumulative sum with alternating pattern

    ans = 10**18  # Initialize answer with a large number
    
    # Try all possible numbers of segments from 2 to n
    for k in range(2, n + 1):
        # Calculate the number of odd and even positions in the path of k segments
        e = k - 1 - (k % 2 == 0)  # Even position count
        o = k - 1 - (k % 2)       # Odd position count
        
        # Compute the cost of a path with k segments
        # Use alternating costs for even and odd segments
        subans = csum[e] + (n - (k - k // 2)) * M[e]  # Even part
        subans += csum[o] + (n - k // 2) * M[o]       # Odd part
        ans = min(ans, subans)  # Update the answer
        
    print(ans)


# https://github.com/VaHiX/CodeForces/