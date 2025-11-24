# Problem: CF 2093 G - Shorten the Array
# https://codeforces.com/contest/2093/problem/G

"""
G. Shorten the Array

Problem Description:
Given an array of integers and a value k, find the shortest subarray whose beauty (maximum XOR of any two elements) is at least k.
If no such subarray exists, return -1.

Approach:
Use a trie data structure to efficiently compute maximum XOR values.
We iterate from right to left, insert elements into a trie, and for each element,
we try to find the maximum XOR value with existing elements in the trie.
We track the minimum length of subarrays that satisfy the condition f(b) >= k.

Time Complexity: O(30 * n) per test case, where 30 is the number of bits in integer representation.
Space Complexity: O(30 * n) for the trie structure in worst case.

Algorithms/Techniques:
- Trie (prefix tree) for efficient maximum XOR search
- Bit manipulation
"""

import sys

def input():
    return sys.stdin.readline().strip()

def getints():
    return map(int, sys.stdin.readline().strip().split())

out = []
for _ in range(int(input())):
    n, k = getints()
    a = list(getints())
    if k == 0:
        out.append("1")
        continue
    inf = 10**9
    ans = inf
    # x: trie structure (30 * n + 2 entries) - stores [left_child, right_child, next_index]
    x = [-1, -1, inf] * (30 * n + 2)
    nex = 3  # next available index in the trie array
    for i in range(n - 2, -1, -1):  # iterate from right to left
        u = 0  # current node pointer in trie
        p = 1 << 29  # bit mask (most significant bit)
        # Traverse and build the trie for a[i+1]
        for j in range(30):
            t = 1 if (a[i + 1] & p) else 0  # extract current bit
            if x[u + t] == -1:  # if child doesn't exist, create new node
                x[u + t] = nex
                nex += 3  # increment next index pointer
            u = x[u + t]  # move to the child
            x[u + 2] = i + 1  # store index in leaf node
            p >>= 1  # shift to next bit
        
        u = 0  # reset pointer for querying
        t = 1 << 29  # bit mask (most significant bit)
        # Try to find maximum XOR with current element 'a[i]'
        for j in range(30):
            if u == -1:  # no valid path
                break
            if k & t:  # if the j-th bit of k is 1, prefer opposite bit for max XOR
                u = x[u + int(a[i] & t == 0)]  # go to opposite branch if possible
            else:  # if the j-th bit of k is 0, prefer same bit
                p = 0 if a[i] & t else 1  # determine which branch we are on
                if x[u + p] != -1:  # if path exists
                    temp = 1 + x[x[u + p] + 2] - i  # compute length of subarray
                    if temp < ans:
                        ans = temp
                u = x[u + (1 - p)]  # go to the same-bit branch
            t >>= 1  # move to next bit
        
        # After traversal, check if a path led to valid node
        if u != -1:
            temp = 1 + x[u + 2] - i
            if temp < ans:
                ans = temp
        if ans == 2:  # early termination if minimal possible length found
            break
    
    out.append(str(ans if ans != inf else -1))
print("\n".join(out))


# https://github.com/VaHiX/codeForces/