# Problem: CF 1707 B - Difference Array
# https://codeforces.com/contest/1707/problem/B

"""
Algorithm: Difference Array Simulation
Approach:
- Start with the given array 'a' of size n
- Repeatedly compute differences between adjacent elements
- Sort the differences and replace the array with the sorted differences
- Decrease the size of the array by 1 each time
- Continue until only one element remains

Time Complexity: O(n^2 * log(n)) in worst case due to repeated sorting
Space Complexity: O(n) for storing the intermediate arrays during operations

The process involves:
1. For each step, compute all adjacent differences
2. Sort the differences
3. Filter out zeros (which are accumulated in cnt)
4. Repeat until array size is 1
"""

T = int(input())
MAX = int(1e5) * 5 + 1
while T:
    T -= 1
    n = int(input())
    a = [int(x) for x in input().split()]
    cnt = 0
    while len(a) > 1:
        nxt = []
        if cnt > 0:
            cnt -= 1
            nxt.append(a[0])  # Carry forward the first element if there are accumulated zeros
        for j in range(len(a) - 1):
            x = a[j + 1] - a[j]
            if x == 0:
                cnt += 1  # Count zeros, they will be handled in next iteration
            else:
                nxt.append(x)  # Add non-zero difference
        nxt.sort()  # Sort the new array of differences

        a = nxt.copy()  # Update the current array
    print(a[0] if a else 0)  # Output final result


# https://github.com/VaHiX/CodeForces/