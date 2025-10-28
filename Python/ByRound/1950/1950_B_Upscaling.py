# Problem: CF 1950 B - Upscaling
# https://codeforces.com/contest/1950/problem/B

"""
Checkerboard Generator for 2^n x 2^n Grid

Algorithms/Techniques:
- Simulate the construction of a checkerboard pattern by alternating '#' and '.' characters.
- Use a loop to build two row patterns (ans and ans2) that are repeated in pairs.
- Each line of the output is a repeated version of these base patterns.
- Time Complexity: O(2^(2n)) - exponential in n because we generate 2^(2n) characters.
- Space Complexity: O(2^(2n)) - to store the output of size 2^(2n) x 2^(2n).

"""

for _ in range(int(input())):  # Process t test cases
    a = "##"  # Pattern for rows starting with '#'
    b = ".."  # Pattern for rows starting with '.'
    n = int(input())  # Read n for current test case
    ans = ""  # First base row pattern
    ans2 = ""  # Second base row pattern
    for i in range(n):  # Build base patterns for 2^n x 2^n grid
        if i % 2 == 0:
            ans += a  # Add '#' pattern to ans
            ans2 += b  # Add '.' pattern to ans2
        else:
            ans += b  # Add '.' pattern to ans
            ans2 += a  # Add '#' pattern to ans2
    for i in range(n):  # Output each row of the checkerboard pattern
        if i % 2 == 0:  # Even rows: print ans twice
            print(ans)
            print(ans)
        else:  # Odd rows: print ans2 twice
            print(ans2)
            print(ans2)


# https://github.com/VaHiX/CodeForces/