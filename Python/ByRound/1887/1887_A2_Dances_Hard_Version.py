# Problem: CF 1887 A2 - Dances (Hard Version)
# https://codeforces.com/contest/1887/problem/A2

"""
Algorithm: 
- The problem requires us to find the minimum operations to ensure a[i] < b[i] for all valid i.
- For a fixed array a and b, we want to pair elements of a with b such that a[i] < b[i] and minimize operations.
- We sort both arrays first.
- We use greedy approach to match elements from a to b such that a[i] < b[i].
- We compute how many elements of a need to be matched.
- We also calculate the maximum b element to determine where to switch calculation for different values of m.

Time Complexity: O(n log n) due to sorting.
Space Complexity: O(n) to store the dp array and other auxiliary data.
"""

def solve(nums1, nums2):
    nums1.sort()  # Sort first array
    nums2.sort()  # Sort second array
    n1 = len(nums1)
    n2 = len(nums2)
    dp1 = [0 for i in range(n2)]  # dp1[i] = 1 if we can match nums1[pos1] with nums2[i]
    pos1 = 0  # Pointer for nums1
    for i in range(n2):
        if pos1 < n1 and nums2[i] > nums1[pos1]:
            dp1[i] = 1
            pos1 += 1  # Move to next element in nums1
    remain = n2 - pos1  # Number of unmatched elements in nums2
    lastMax = nums2[n2 - 1]  # Get max element in nums2 to help determine switch point for m
    for i in range(n2 - 1, -1, -1):
        if dp1[i] == 0:
            lastMax = nums2[i]
            break
    return remain, lastMax


T = int(input())
final = []
for t in range(T):
    t1 = input().split(" ")
    _, m = t1[0], int(t1[1])
    a = input().split(" ")
    a = [int(e) for e in a]
    b = input().split(" ")
    b = [int(e) for e in b]
    sum = 0
    maxb = max(b)
    currSum = sum
    currSum, lastMax = solve(a, b)
    if lastMax > m:
        sum = (currSum - 1) * m  # Calculate sum when lastMax > m
        print(f"{sum}")
    else:
        sum = (currSum - 1) * (lastMax - 1) + (currSum) * (m - lastMax + 1)
        print(f"{sum}")


# https://github.com/VaHiX/CodeForces/