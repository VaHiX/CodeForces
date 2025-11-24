# Problem: CF 1490 A - Dense Array
# https://codeforces.com/contest/1490/problem/A

"""
Purpose: 
    Determine the minimum number of elements to insert into an array to make it "dense".
    An array is dense if for every pair of adjacent elements, the larger is at most twice the smaller.
    
    Algorithm:
        - For each adjacent pair of elements, check if they violate the dense condition.
        - If the ratio of max to min exceeds 2, we need to insert elements in between.
        - We keep doubling the smaller element until it satisfies the condition,
          incrementing the count of insertions for each step.

    Time Complexity: O(n * log(max_value)) where n is the size of the array.
                      In the worst case, we might keep doubling a small value up to the maximum value in the array.
    Space Complexity: O(1) - only using a few variables for computation, no extra space proportional to input.
"""

for i in range(int(input())):  # Process each test case
    n = int(input())           # Read the length of the array
    a = list(map(int, input().split()))  # Read the array elements
    ans = 0                    # Initialize the count of elements to insert
    
    for j in range(1, n):      # Iterate through adjacent pairs
        x, y = max(a[j], a[j - 1]), min(a[j], a[j - 1])  # Get max and min of pair
        
        # While the ratio exceeds 2, keep inserting elements
        while x / y > 2:
            y *= 2             # Double the smaller number
            ans += 1           # Increment the insertion count
    
    print(ans)                 # Print the total number of insertions needed


# https://github.com/VaHiX/CodeForces/