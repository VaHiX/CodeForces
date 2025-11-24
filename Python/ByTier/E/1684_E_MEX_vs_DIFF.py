# Problem: CF 1684 E - MEX vs DIFF
# https://codeforces.com/contest/1684/problem/E

"""
Purpose: 
    This code solves the problem of minimizing the cost of an array defined as DIFF(a) - MEX(a),
    where DIFF is the number of distinct elements and MEX is the smallest non-negative integer
    not present in the array. We are allowed to perform at most k operations to change array elements.

Algorithms/Techniques:
    - Use a set to track distinct elements and Counter to count frequencies.
    - Compute MEX by finding the smallest non-negative integer not in the set.
    - Simulate increasing MEX by up to k operations, considering how many elements
      must be changed to achieve a higher MEX.
    - Greedily reduce the cost by merging small frequency elements into larger ones
      to cover the operations needed to increase MEX.

Time Complexity: O(n log n)
    - Building set and counter: O(n)
    - Finding initial MEX: O(n)
    - Simulating k increases in MEX: O(k)
    - Sorting the elements with frequency > current MEX: O(n log n)
    - Greedy selection of low-frequency elements: O(n)
Space Complexity: O(n)
    - Storing set, counter, and list of frequencies
"""

from collections import Counter

t = int(input())
for q in range(t):
    n, k = map(int, input().split())
    arr = list(map(int, input().split()))
    found = set(arr)  # Set to store all distinct elements
    c = Counter(arr)  # Counter to store frequencies of each element
    mex = 0
    # Find the initial MEX (smallest non-negative integer not in the array)
    while mex in found:
        mex += 1
    
    # Simulate increasing the MEX by up to k operations
    for i in range(k):
        mex += 1
        # Adjust mex by skipping over elements that are already in found
        while mex in found:
            mex += 1
    
    # Collect elements whose value is greater than current mex
    a = []
    for el in found:
        if el > mex:
            a.append(c[el])
    
    a.sort()  # Sort frequencies in ascending order
    
    # Greedily reduce cost by using operations to merge small groups
    ans = len(a)
    for el in a:
        if el <= k:
            k -= el
            ans -= 1
    
    print(ans)


# https://github.com/VaHiX/CodeForces/