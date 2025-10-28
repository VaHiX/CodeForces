# Problem: CF 1930 C - Lexicographically Largest
# https://codeforces.com/contest/1930/problem/C

"""
Purpose: To find the lexicographically largest array `b` that can be constructed by inserting elements 
         into a set `S` based on a specific rule and then sorting `S` in decreasing order.

Algorithm:
- For each element in the input array `a`, compute its "weighted value" as `a[i] + i + 1`.
- Sort these weighted values in descending order.
- Process the sorted values to construct a new sequence `y` such that:
  - If current value is less than the last inserted value in `y`, append it.
  - Otherwise, append `y[-1] - 1` to ensure uniqueness and decreasing order.
- Output the final sequence `y` excluding the initial dummy value.

Time Complexity: O(n log n) due to sorting.
Space Complexity: O(n) for storing intermediate arrays.
"""

for _ in range(int(input())):  # Read number of test cases
    n = int(input())  # Read length of array
    # Compute weighted values: a[i] + i + 1 for each element
    x = [i + b + 1 for i, b in enumerate(map(int, input().split()))]
    x.sort(reverse=True)  # Sort in descending order
    y = [2e9]  # Initialize result array with a large dummy value
    for a in x:  # Iterate through sorted values
        if y[-1] > a:  # If current value is smaller than last in y
            y.append(a)  # Append it directly
        else:  # Otherwise, decrease the last value by 1 to maintain strict descending order
            y.append(y[-1] - 1)
    print(" ".join(map(str, y[1:])))  # Print all but the first dummy value


# https://github.com/VaHiX/CodeForces/