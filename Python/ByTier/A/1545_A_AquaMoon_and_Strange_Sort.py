# Problem: CF 1545 A - AquaMoon and Strange Sort
# https://codeforces.com/contest/1545/problem/A

"""
AquaMoon and Strange Sort

Algorithm/Techniques: Sorting, parity check

Time Complexity: O(n log n) due to sorting operations
Space Complexity: O(n) for storing the array and its sorted version

This problem checks if we can sort an array by swapping adjacent elements such that 
the final arrangement is non-decreasing and all elements end up facing right.
The key insight is that we can only swap adjacent elements, so we're essentially checking 
if it's possible to sort the array using adjacent swaps. Since we can perform any number of 
adjacent swaps, the array can always be sorted using bubble sort or similar methods.

However, in this specific case, since we are told that direction is flipped on each swap,
the parity of swaps affects directions. For the final state to have all friends facing right, 
an even number of flips must occur for each element.
This solution uses an observation: if both odd and even indexed elements (when considering 0-based indexing) 
are sorted in their respective positions when comparing with original array, then sorting is possible.
"""

t = int(input())
for _ in range(t):
    n = int(input())
    a = list(map(int, input().split()))
    b = sorted(a)
    ans = "NO"
    # Check if elements at even indices (0, 2, 4, ...) are the same when sorted
    if sorted(a[::2]) == b[::2]:
        ans = "YES"
    print(ans)


# https://github.com/VaHiX/codeForces/