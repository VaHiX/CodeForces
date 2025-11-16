# Problem: CF 2162 C - Beautiful XOR
# https://codeforces.com/contest/2162/problem/C

"""
Purpose: 
This code solves the problem of transforming an integer 'a' to 'b' using XOR operations with integers x such that 0 <= x <= a.
The approach leverages properties of XOR and bit manipulation to determine the minimum number of operations needed.

Algorithms/Techniques:
- Bit manipulation using XOR operation
- Checking conditions on bit patterns to determine if transformation is possible
- Greedy approach based on bit comparison and masking

Time Complexity: O(1) - The operations performed are constant time, involving only bit manipulation and comparisons.
Space Complexity: O(1) - Only a constant amount of extra space is used.

"""

def solve():
    t = int(input())
    for _ in range(t):
        a, b = map(int, input().split())
        if a == b:
            print(0)
        elif (a ^ b) < a:
            # Direct transformation possible with one operation
            print(1)
            print(a ^ b)
        else:
            # Try to find a valid two-step transformation
            c = a | b  # Create a mask that includes all bits of a and b
            if (a ^ c) <= a and (c ^ b) <= c:
                # If both intermediate values are valid (within range), use two operations
                print(2)
                print(a ^ c, c ^ b)
            else:
                # Transformation not possible within constraints
                print(-1)


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/CodeForces/