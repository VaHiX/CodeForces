# Problem: CF 2040 C - Ordered Permutations
# https://codeforces.com/contest/2040/problem/C

"""
C. Ordered Permutations

Purpose:
This code finds the k-th lexicographically smallest permutation of length n that maximizes the sum S(p), 
where S(p) = sum over all subarrays of min values in those subarrays.

Key Observations:
- To maximize S(p), we should place the largest elements towards the front.
- The optimal structure is to split elements into two parts: a prefix with larger values and a suffix 
  such that the total sum is maximized.
- A greedy approach using bit manipulation helps construct the desired permutation efficiently.

Algorithms/Techniques:
Bit manipulation, greedy construction, lexicographical ordering, binary representation

Time Complexity: O(n)
Space Complexity: O(n)

Input Format:
- t: number of test cases
- For each case: n (length of permutation), k (index of desired permutation)

Output Format:
- If k exceeds the count of valid permutations, output -1.
- Otherwise, output the k-th lexicographically smallest valid permutation.

"""

import sys

input = sys.stdin.readline
t = int(input())
for _ in range(t):
    n, k = map(int, input().split())
    if n < 50:
        if 2 ** (n - 1) < k:
            print(-1)
            continue
    k -= 1  # Convert to 0-based indexing
    last = []  # Stores indices in the second part (suffix)
    front = []  # Stores indices in the first part (prefix)
    
    for i in range(n - 1):
        if (k >> (n - i - 2)) & 1:  # Check bit at position (n-i-2)
            last.append(i + 1)      # Add to suffix if bit is set
        else:
            front.append(i + 1)     # Add to prefix if bit is not set
    
    front.append(n)             # Append the last element to the prefix
    last.reverse()              # Reverse suffix for correct order
    front += last               # Concatenate prefix and reversed suffix
    
    print(*front)


# https://github.com/VaHiX/codeForces/