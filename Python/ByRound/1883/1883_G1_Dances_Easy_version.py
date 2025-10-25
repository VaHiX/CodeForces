# Problem: CF 1883 G1 - Dances (Easy version)
# https://codeforces.com/contest/1883/problem/G1

"""
Purpose: Solve the problem of finding the minimum number of operations to make array a[i] < b[i] for all valid i,
         where arrays can be reordered before operations. This version handles m=1 as specified in the easy version.

Algorithms/Techniques:
- Greedy approach with two pointers
- Sorting arrays to facilitate greedy matching
- Two pointers technique to count mismatches efficiently

Time Complexity: O(n log n) due to sorting; the while loop is O(n), so total is O(n log n)
Space Complexity: O(1) excluding input storage, as we use only a few variables for pointers and counters

"""

def solve():
    n, m = map(int, input().split())
    a = list(map(int, input().split()))
    a.append(1)  # Inserting the value of a[1] which is fixed as 1 in this problem's context
    b = list(map(int, input().split()))
    a.sort()  # Sort array a to apply greedy matching
    b.sort()  # Sort array b to apply greedy matching
    ans = 0
    idxa = 0  # Pointer for sorted array a
    idxb = 0  # Pointer for sorted array b
    while idxb < n:
        if b[idxb] > a[idxa]:  # If current element of b is greater than a, we can match them
            idxb += 1
            idxa += 1
        else:  # If b[idxb] <= a[idxa], we need to remove one element from a (operation)
            idxb += 1
            ans += 1
    print(ans)


t = int(input())
for i in range(0, t):
    solve()


# https://github.com/VaHiX/CodeForces/