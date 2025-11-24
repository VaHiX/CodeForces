# Problem: CF 2065 C1 - Skibidus and Fanum Tax (easy version)
# https://codeforces.com/contest/2065/problem/C1

"""
Algorithm: Greedy approach
- For each element in array `a`, we have two choices:
    1. Keep the original value `a[i]`
    2. Replace it with `b[0] - a[i]`
- We process elements from left to right, always trying to choose the smaller of the two options that maintains non-decreasing order.
- At each step, we check if either of the two values is >= last selected value.
    - If so, we update `last` to that value.
    - If neither works, sorting is impossible.

Time Complexity: O(n) per test case
Space Complexity: O(1) additional space (excluding input storage)
"""

def main():
    t = int(input())
    for _ in range(t):
        n, m = map(int, input().split())
        a = list(map(int, input().split()))
        b = list(map(int, input().split()))
        B = b[0]  # Only one element in b, so use b[0]
        last = -(10**18)  # Initialize to a very small number
        possible = True
        for x in a:
            op1 = x  # Option 1: keep original value
            op2 = B - x  # Option 2: replace with b[0] - x
            low = op1 if op1 < op2 else op2  # Smaller of the two options
            high = op1 if op1 >= op2 else op2  # Larger of the two options
            if low >= last:
                last = low  # Choose smaller value if it maintains order
            elif high >= last:
                last = high  # Choose larger value if it maintains order
            else:
                possible = False  # Neither option maintains non-decreasing order
                break
        print("YES" if possible else "NO")


main()


# https://github.com/VaHiX/CodeForces/