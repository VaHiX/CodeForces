# Problem: CF 2082 A - Binary Matrix
# https://codeforces.com/contest/2082/problem/A

"""
Problem: Minimum changes to make a binary matrix "good"
A good binary matrix has all row XORs and column XORs equal to 0.

Algorithm:
- For each test case, analyze the matrix to determine how many elements must be changed.
- Use bit manipulation for efficient XOR operations.
- The solution leverages two key insights:
  1. If we fix the first n-1 rows and first m-1 columns, the last row/column is uniquely determined by the XOR constraints.
  2. We compute cumulative XORs and counts to find how many mismatches exist with valid configurations.

Time Complexity: O(n*m) for each test case, since we process at most all elements once.
Space Complexity: O(1), only using a few variables for computation.
"""

print(
    "\n".join(
        map(
            str,
            (
                max(
                    [
                        rc := (rc := rc if i else 0)  # Initialize or reuse row cumulative XOR
                        + ((x := int(input(), 2)).bit_count() & 1)  # Add parity of input row
                        + (cc := (cc := cc if i else 0) ^ x)  # Update column cumulative XOR with current row
                        - cc  # Subtract previous column XOR to compute difference
                        for i in range(list(map(int, input().split()))[0])  # Iterate over rows
                    ][-1],  # Take last computed value
                    cc.bit_count(),  # Compare with final column XOR's bit count
                )
                for _ in range(int(input()))  # Repeat for number of test cases
            ),
        )
    )
)


# https://github.com/VaHiX/codeForces/