# Problem: CF 1907 F - Shift and Reverse
# https://codeforces.com/contest/1907/problem/F

"""
Problem: F. Shift and Reverse
Algorithm/Technique: Simulation and analysis of array properties
Time Complexity: O(n) per test case
Space Complexity: O(n) due to copying array for analysis

The problem involves sorting an array using two operations:
1. Shift: move last element to front
2. Reverse: reverse the entire array

Approach:
1. Check if the array is already sorted (0 inversions)
2. For arrays with at most 1 inversion (either ascending or descending), 
   calculate minimum operations needed:
   - For ascending inversions, consider shift operations from that point
   - For descending inversions, consider reverse operations
3. If more than 1 inversion exists, it's impossible to sort using given operations

Key insight:
- We extend the array by appending the first element to detect wraparound shifts
- We count inversions to determine if solution is possible
- Minimum operations are computed based on where inversions occur
"""

INF = 10**18


def solve():
    n = int(input())
    a = list(map(int, input().split()))
    b = a[::] + [a[0]]  # Extend array to detect wraparound
    cnt_not_sort = 0    # Count of descending inversions
    cnt_not_rev = 0     # Count of ascending inversions
    i_not_sort = -1     # Position of last descending inversion
    i_not_rev = -1      # Position of last ascending inversion
    for i in range(1, len(b)):
        if b[i] < b[i - 1]:         # Descending inversion found
            cnt_not_sort += 1
            i_not_sort = i
        if b[i] > b[i - 1]:         # Ascending inversion found
            cnt_not_rev += 1
            i_not_rev = i
    # If more than one inversion of either type, impossible to sort
    if min(cnt_not_rev, cnt_not_sort) > 1:
        print(-1)
        return
    ans_sort = INF  # Minimum operations for shift-based solution
    ans_rev = INF   # Minimum operations for reverse-based solution
    if cnt_not_sort == 0:  # Already sorted
        print(0)
        return
    if cnt_not_rev == 0:   # All elements are same or sorted increasing
        print(1)
        return
    if cnt_not_sort == 1:  # One descending inversion
        # Option 1: Shift to put inversion at end, then reverse
        # Option 2: Shift to put inversion at beginning, then reverse twice
        ans_sort = min(n - i_not_sort, 2 + i_not_sort)
    if cnt_not_rev == 1:   # One ascending inversion
        # Option 1: Reverse from position i_not_rev onwards
        # Option 2: Shift to move inv. to front, then reverse
        ans_rev = min(n - i_not_rev, i_not_rev)
        ans_rev += 1  # Add one reverse
    ans = min(ans_sort, ans_rev)
    if ans == INF:
        print(-1)
        return
    print(ans)


def main():
    t = int(input())
    for _ in range(t):
        solve()


main()


# https://github.com/VaHiX/CodeForces/