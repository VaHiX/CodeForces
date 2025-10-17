# Problem: CF 2124 A - Deranged Deletions
# https://codeforces.com/contest/2124/problem/A

"""
Problem: Deranged Deletions
Task: Determine if an array can be reduced by deleting elements to form a derangement.
A derangement is an array where no element appears in its sorted position.

Algorithm:
- For each test case, check if we can form a derangement by deleting some elements.
- If the array has only one element, it cannot be a derangement (as it will always match its sorted version).
- Otherwise, iterate through adjacent pairs to find a pair where a[i] > a[i+1].
  - If such a pair exists, we can delete one of the elements to create a valid derangement.
  - This works because if a[i] > a[i+1], deleting a[i] or a[i+1] will allow us to avoid
    placing an element in its original sorted position.

Time Complexity: O(n) per test case, where n is the length of array.
Space Complexity: O(1) extra space (excluding input storage).
"""

for _ in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    if n == 1:
        print("NO")
    else:
        for i in range(n - 1):
            if a[i] > a[i + 1]:
                print("YES")
                print(2)
                print(a[i], a[i + 1])
                break
        else:
            print("NO")


# https://github.com/VaHiX/codeForces/