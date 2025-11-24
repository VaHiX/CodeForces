# Problem: CF 1887 A1 - Dances (Easy version)
# https://codeforces.com/contest/1887/problem/A1

"""
Algorithm: Greedy Approach
- We want to pair elements from array 'a' and 'b' such that a[i] < b[i] for all valid i.
- Since we can reorder both arrays, we sort 'a' in ascending order and 'b' in descending order.
- Then use two pointers (i for a from end, j for b from start) to greedily match elements:
    - If a[i] >= b[j], we must perform an operation (remove a[i]), increment k.
    - Otherwise, we successfully pair a[i] with b[j], increment both i and j.
- Time Complexity: O(n log n) due to sorting
- Space Complexity: O(1) excluding input storage
"""

def solve():
    l = [int(x) for x in input().split()]
    n = l[0]
    l[1]  # m is always 1, so we ignore this
    a = [int(x) for x in input().split()]
    b = [int(x) for x in input().split()]
    
    # Construct c[i] by setting c[i][0] = i and copying rest from a
    a = [1] + a  # In the example, i = 1, so we prepend 1 to a
    a.sort()     # Sort a in ascending order
    b.sort()     # Sort b in ascending order
    b = b[::-1]  # Reverse b to get descending order
    
    i = n - 1    # Pointer to the end of sorted array a
    j = 0        # Pointer to the start of sorted array b
    k = 0        # Counter for operations
    
    # Greedily pair elements
    while not (i < 0 or j >= n):
        if a[i] >= b[j]:
            # Cannot pair a[i] with b[j], need to remove a[i]
            i -= 1
            k += 1
        else:
            # Successfully paired a[i] with b[j]
            i -= 1
            j += 1
    
    return k


t = int(input())
for _ in range(t):
    print(solve())


# https://github.com/VaHiX/CodeForces/