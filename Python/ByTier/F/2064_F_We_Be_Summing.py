# Problem: CF 2064 F - We Be Summing
# https://codeforces.com/contest/2064/problem/F

"""
F. We Be Summing

Purpose:
This code counts the number of "epic" subarrays in a given array. A subarray is epic if there exists an index i such that the sum of the minimum element of the prefix (from 1 to i) and the maximum element of the suffix (from i+1 to end) equals k.

Algorithms/Techniques:
- Monotonic stack technique to efficiently calculate contributions of min/max elements
- Two passes using stacks to process left-to-right and right-to-left
- Preprocessing with contribution tracking for both minimum and maximum

Time Complexity: O(n) per test case, where n is the length of the array.
Space Complexity: O(n) for storing auxiliary arrays and stack.

"""

from sys import stdin

input = lambda: stdin.readline().rstrip()


def solve():
    n, k = map(int, input().split())
    a = list(map(int, input().split()))
    put = [[] for _ in range(n)]  # Stores pairs of (value, count) for putting into stack
    delete = [[] for _ in range(n)]  # Stores pairs of (value, count) for deleting from stack
    cmn = [0] * (2 * n)  # Count of min contributions per value
    cmx = [0] * (2 * n)  # Count of max contributions per value
    st = [n]  # Stack to maintain indices; initialized with n to avoid boundary check

    # Right-to-left pass to populate put and delete arrays
    for i in range(n - 1, -1, -1):
        while len(st) > 1 and a[st[-1]] < a[i]:
            # Remove elements from stack that are smaller than current element
            put[i].append((k - a[st[-1]], st[-2] - st[-1]))  # Add contribution of removed element
            st.pop()
        delete[i].append((k - a[i], st[-1] - i))  # Add contribution of current element
        st.append(i)

    # Update cmx for the remaining elements in stack
    for i in range(len(st) - 1):
        cmx[k - a[st[i + 1]]] += st[i] - st[i + 1]

    st = [-1]  # Reuse stack initialized with -1 for left-to-right pass
    ans = 0  # Result counter

    # Left-to-right processing
    for i in range(n):
        while len(st) > 1 and a[st[-1]] > a[i]:
            # Remove elements from stack that are larger than current element
            v = a[st[-1]]
            cmn[v] -= st[-1] - st[-2]  # Update contribution of removed element
            st.pop()
        
        # Process delete operations for current index
        for x, y in delete[i]:
            cmx[x] -= y
        
        # Process put operations for current index
        for x, y in put[i]:
            cmx[x] += y
            ans += y * cmn[x]  # Add contribution to answer using previous min counts

        cmn[a[i]] += i - st[-1]  # Update contribution of current element as min
        st.append(i)
        ans += (st[-1] - st[-2]) * cmx[a[i]]  # Add contribution to answer based on max counts

    return ans


for _ in range(int(input())):
    print(solve())


# https://github.com/VaHiX/codeForces/