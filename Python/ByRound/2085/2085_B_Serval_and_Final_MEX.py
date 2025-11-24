# Problem: CF 2085 B - Serval and Final MEX
# https://codeforces.com/contest/2085/problem/B

"""
Problem: Serval and Final MEX

Purpose:
This code solves a problem where we are given an array of non-negative integers and must perform operations to reduce it to a single element, such that the final element is 0. Each operation involves selecting a subarray [l, r] and replacing it with the mex (minimum excluded) of that subarray.

Algorithms/Techniques:
- Greedy strategy based on finding zeros in specific parts of array
- Using prefix and suffix zero checks to determine how to operate efficiently

Time Complexity:
O(n) per test case, since we process each element a constant number of times.

Space Complexity:
O(n) for storing the input array and output operations.
"""

for tt in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    
    # Check if 0 is present in first two elements
    c1 = 0 in a[:2]
    # Check if 0 is present in remaining elements (from index 2 onwards)
    c2 = 0 in a[2:]
    
    # Print number of operations needed
    print(1 + c1 + c2)
    
    # Generate operations:
    # If there's a zero in first two elements, operate on positions 1 and 2
    # If there's no zero in first two but there is one in rest, operate on last two elements
    # Final operation always covers entire array to get mex = 0
    
    # Create string output:
    # c2 * "3 n" - if we have zeros in later part (operation to reduce suffix)
    # c1 * "1 2" - if we have zeros in prefix (operation to reduce prefix)
    # Final step: reduce entire array
    print(c2 * f"3 {n} \n" + c1 * f"1 2 \n" + f"1 {(n-c1)-c2*(n-3)}")


# https://github.com/VaHiX/codeForces/