# Problem: CF 1998 B - Minimize Equal Sum Subarrays
# https://codeforces.com/contest/1998/problem/B

"""
Algorithm: Minimize Equal Sum Subarrays
Approach: 
- For each test case, we are given a permutation p of length n.
- We need to construct a permutation q such that the number of equal sum subarrays is minimized.
- Key insight:
    - If we reverse the array (i.e., q[i] = p[n-1-i]), then we can minimize the number of identical subarray sums.
    - This is because reversing disrupts many of the possible subarray sum matches between p and q.
- Time Complexity: O(n) per test case, as we only perform a single reversal operation.
- Space Complexity: O(n) for storing the input and output arrays.
"""

for i in range(int(input())):  # Read number of test cases
    n = int(input())           # Read length of permutation
    a = input().split()        # Read the permutation p
    # Reverse the array to form q such that q[i] = p[n-1-i]
    print(" ".join(a[1:n]), a[0])


# https://github.com/VaHiX/CodeForces/