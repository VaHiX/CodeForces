# Problem: CF 1717 C - Madoka and Formal Statement
# https://codeforces.com/contest/1717/problem/C

"""
Algorithm: Check if array 'a' can be transformed into array 'b' using allowed operations.
Techniques: 
- Single pass through the array with modular indexing for circular comparison
- Key condition: For each element, either it's already equal or can be increased under constraints

Time Complexity: O(n) - single pass through the array
Space Complexity: O(1) - only using a few variables, no extra space needed
"""

for i in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))
    boo = 1
    for i in range(n):
        # If current element in 'a' is greater than in 'b', transformation is impossible
        if a[i] > b[i]:
            boo = 0
            break
        # If 'a' element is less than 'b' element, check if it's allowed to increase
        # Check if the next element in 'b' is too small to allow increasing
        elif a[i] < b[i] and b[i] > b[(i + 1) % n] + 1:
            boo = 0
            break
    print("YES" if boo else "NO")


# https://github.com/VaHiX/CodeForces/