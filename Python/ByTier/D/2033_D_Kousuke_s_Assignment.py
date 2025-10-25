# Problem: CF 2033 D - Kousuke's Assignment
# https://codeforces.com/contest/2033/problem/D

"""
D. Kousuke's Assignment

Task: Given an array of integers, find the maximum number of non-overlapping segments
such that each segment sums to zero.

Algorithm:
- Use prefix sums and a set to track previously seen prefix sums.
- When a prefix sum is encountered again, it indicates a subarray with sum 0.
- Reset the tracking set and counter when such a segment is found to ensure non-overlapping.
- This greedy approach ensures maximum number of segments.

Time Complexity: O(n) per test case, where n is the length of the array.
Space Complexity: O(n) for storing prefix sums in the set.

Input:
- t: number of test cases
- For each test case:
  - n: length of array
  - a: array of integers

Output:
- Maximum number of non-overlapping beautiful segments (sum = 0).
"""

for _ in range(int(input())):  # Process each test case
    n = int(input())  # Read the size of the array
    a = list(map(int, input().split()))  # Read the array elements
    
    s = 0  # Running prefix sum
    st = {0}  # Set to store seen prefix sums, initialized with 0
    c = 0  # Count of beautiful segments found
    
    for x in a:  # Iterate through each element
        s += x  # Update the running prefix sum
        if s in st:  # If current prefix sum was seen before
            c += 1  # Increment segment count
            st = {0}  # Reset set to start fresh (non-overlapping constraint)
            s = 0   # Reset prefix sum
        st.add(s)  # Add current prefix sum to set
    
    print(c)  # Output the number of beautiful segments


# https://github.com/VaHiX/codeForces/