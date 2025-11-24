# Problem: CF 1859 A - United We Stand
# https://codeforces.com/contest/1859/problem/A

"""
Code Purpose:
This code solves the problem of partitioning an array into two non-empty subarrays such that no element in one subarray is a divisor of any element in the other subarray. 
The approach is based on sorting the array and then checking if all elements are equal (which makes a solution impossible). 
If not, it partitions the array into two parts: the first part contains all elements equal to the smallest element, and the second part contains the rest.

Algorithms/Techniques:
- Sorting
- Greedy partitioning based on the smallest element
- Simple iteration and counting

Time Complexity: O(n log n) due to sorting, where n is the length of the input array.
Space Complexity: O(n) for storing the input array and the sorted version.
"""

t = int(input())

for _ in range(t):
    n = int(input())
    nums = sorted(list(map(int, input().split())))  # Sort the array to simplify partitioning

    if nums[0] == nums[-1]:  # If all elements are the same, no valid partition exists
        print(-1)
        continue

    lb = nums.count(nums[0])  # Count how many times the smallest element appears

    print(lb, n - lb)  # Print lengths of the two partitions
    print(" ".join(list(map(str, nums[:lb]))))  # Print elements of first partition
    print(" ".join(list(map(str, nums[lb:]))))  # Print elements of second partition


# https://github.com/VaHiX/CodeForces/