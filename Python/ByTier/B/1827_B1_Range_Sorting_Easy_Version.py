# Problem: CF 1827 B1 - Range Sorting (Easy Version)
# https://codeforces.com/contest/1827/problem/B1

"""
Purpose: 
This code computes the sum of "beauty" over all subarrays of the given array.
The "beauty" of a subarray is defined as the minimum number of range-sort operations needed to sort it.
Each operation sorts a contiguous subarray in time equal to its length.

Algorithms/Techniques:
- Sliding window with stack-like logic
- For each starting index i, we build a "sorted prefix" of the subarray starting at i.
- When a new element is added to the prefix:
  - If it's greater than the last element, it can be appended directly.
  - Otherwise, we use a "stack" simulation to remove elements that violate the sorted order.
- We maintain a count of operations needed for each subarray and accumulate the total.

Time Complexity: O(n^2) in worst case due to nested loops.
Space Complexity: O(n) for the temporary list 'a' used in the inner loop.
"""

for _ in range(int(input())):
    n = int(input())
    arr = list(map(int, input().split()))
    ans = 0
    for i in range(n):
        a = [arr[i]]  # Start building the sorted prefix with first element
        for j in range(i + 1, n):
            if arr[j] > a[-1]:  # If current element is greater than last in prefix
                a.append(arr[j])
            else:
                # Pop elements greater than current element
                p = a[-1]
                a.pop()
                while a and arr[j] < a[-1]:
                    a.pop()
                a.append(p)
            # Add the number of operations needed for the current subarray [i, j]
            # Operations = length - number of elements in sorted prefix
            ans += j - i + 1 - len(a)
    print(ans)


# https://github.com/VaHiX/CodeForces/