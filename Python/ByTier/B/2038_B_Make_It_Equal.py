# Problem: CF 2038 B - Make It Equal
# https://codeforces.com/contest/2038/problem/B

"""
B. Make It Equal

Purpose:
This code solves the problem of making all elements of an array equal using a specific operation:
- Choose an index i, decrease a[i] by 2 and increase a[(i % n) + 1] by 1.
The goal is to find the minimum number of such operations needed.

Algorithm:
- The core idea is to simulate the process and track how many operations (units of 2) are distributed
  from each element to its neighbor. 
- For a solution to exist, the sum of all elements must be divisible by n (since we're moving
  values around in cycles and all have to end up being equal).
- We track how much each element contributes to the operations (by "giving" half of its value,
  since every 2 units from one position gives 1 unit to the next).

Time Complexity: O(n) per test case, where n is the length of the array.
Space Complexity: O(n) for storing arrays of size n.

Techniques:
- Modular arithmetic to handle circular array traversal.
- Simulation of operation with tracking of "give" counts.
"""

def main():
    t = int(input())
    for _ in range(t):
        n = int(input())
        l = list(map(int, input().split()))
        verif = True
        i = 0
        op = 0
        ops = [0] * n  # Track how many units each index gives
        while verif:
            u = l[i] // 2  # Amount to give (half of current element)
            l[i] = l[i] % 2  # Remaining value after giving away half
            l[(i + 1) % n] += u  # Give units to the next element (module n for rotation)
            ops[i] += u  # Count how many operations index i contributed
            op += u  # Total operations count
            if i == n - 1:
                verif = False
                for i in range(len(l)):
                    if l[i] > 1:
                        verif = True  # If any element is still > 1, continue
            i += 1
            i = i % n  # Circular increment

        exist = False
        for i in range(len(l)):
            if l[i] != l[0]:
                exist = True
        if exist:
            print(-1)
        else:
            c = min(ops)
            print(op - c * n)

main()


# https://github.com/VaHiX/codeForces/