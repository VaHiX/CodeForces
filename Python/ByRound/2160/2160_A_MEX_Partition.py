# Problem: CF 2160 A - MEX Partition
# https://codeforces.com/contest/2160/problem/A

"""
A. MEX Partition
Algorithms/Techniques: Greedy, Set operations, MEX calculation

Time Complexity: O(n^2) in worst case due to checking for MEX in a set,
                 where n is the number of elements in the input array.
Space Complexity: O(n) for storing the set of present elements.

The problem asks to find the minimum score over all valid partitions of a multiset A,
where each partition's multisets must have the same MEX value. The key insight is:
- If we can form a valid partition where each subset has mex = k, then we can try k from 0 upward.
- For any k, if there are at least k distinct elements in A such that we can "split" them into k groups,
  then it's a valid partition with score k.
- The answer is the smallest k for which such a split is possible.

We compute MEX of the full array, and use greedy approach to determine the minimal possible score.
"""
t = int(input())
for i in range(t):
    n = int(input())
    A = list(map(int, input().split()))
    present = set(A)  # Store all unique elements for fast lookup
    mex = 0
    while mex in present:  # Keep incrementing mex until we find one not in the set
        mex += 1
    print(mex)


# https://github.com/VaHiX/CodeForces/