# Problem: CF 2075 B - Array Recoloring
# https://codeforces.com/contest/2075/problem/B

"""
B. Array Recoloring

Task: Given an array of integers and a number k, select exactly k elements to paint blue. 
Then iteratively paint red neighbors of blue elements until no red elements remain.
The cost is the sum of the first k selected elements plus the last painted element.
Goal: Maximize the total cost.

Algorithms/Techniques:
- Greedy approach with sorting
- For k < 2: Select the maximum element and then select the maximum remaining element
- For k >= 2: Sum of top k elements from sorted array

Time Complexity: O(n * log n) per test case due to sorting
Space Complexity: O(n) for storing the array
"""

R = lambda: map(int, input().split())
(t,) = R()
while t:
    t -= 1
    n, k = R()
    (*a,) = R()  # Read array elements into list a
    
    if k < 2:
        # For k = 1, we pick the maximum element as first and then max of remaining
        r = max(a[:: n - 1])  # Gets the first or last element (since n-1 skips middle)
        a.remove(r)  # Remove that max element from array
        r += max(a)  # Add the next maximum element to cost
    else:
        # For k >= 2, sum of top k elements after sorting gives the best initial selection
        r = sum(sorted(a)[~k:])  # ~k means -k-1, so take last k elements after sorting
    print(r)


# https://github.com/VaHiX/codeForces/