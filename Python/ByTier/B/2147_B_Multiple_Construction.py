# Problem: CF 2147 B - Multiple Construction
# https://codeforces.com/contest/2147/problem/B

# B. Multiple Construction
# Algorithms/Techniques: Direct construction using reverse and forward sequences
# Time Complexity: O(n) per test case, O(∑n) overall
# Space Complexity: O(n) per test case, O(∑n) overall

for _ in range(int(input())):  # Read number of test cases
    n = int(input())  # Read current test case value
    # Construct the array by:
    # 1. Reversing numbers from (n-1) down to 1
    # 2. Adding n
    # 3. Adding numbers from 1 to n
    print(
        " ".join(
            list(map(str, list(range(n - 1, 0, -1)) + [n] + list(range(1, n + 1))))
        )
    )


# https://github.com/VaHiX/CodeForces/