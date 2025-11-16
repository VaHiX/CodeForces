# Problem: CF 1916 D - Mathematical Problem
# https://codeforces.com/contest/1916/problem/D

"""
Code Purpose:
This code solves a mathematical problem where for a given odd number n, 
it finds n different n-digit perfect squares such that all numbers have 
the same multiset of digits. 

The solution approach:
- For n = 1, directly output "1"
- For n > 1, construct numbers by manipulating digit patterns to form 
  squares with the required digit multisets.
- Uses a specific pattern of generating numbers by:
  1. Creating numbers with certain digits and zeros
  2. Squaring them to get n-digit results
  3. Appending a special number (196 followed by zeros) to complete the set

Algorithms/Techniques:
- Mathematical digit manipulation
- Pattern-based construction of perfect squares

Time Complexity: O(n^2)
Space Complexity: O(n)
"""

def sol3(dig: int) -> int:
    if dig == 1:
        print("1")
        return
    le_len = -1

    number_arr = []
    for i in range(2):
        nbr_of_digits = (dig + 1) // 2
        if i % 2 == 0:
            f_d = "1"
            f_d2 = "3"
        else:
            f_d = "3"
            f_d2 = "1"
        for j in range(nbr_of_digits - 1):
            # Construct number based on pattern and square it
            nbr_s = str(
                (int(f_d + j * "0" + f_d2 + (nbr_of_digits - j - 2) * "0") ** 2)
            )
            le_len = len(nbr_s)

            number_arr.append(nbr_s)
    # Append a specially constructed number to complete the solution
    number_arr.append("196" + "0" * (le_len - 3))
    print(" ".join(number_arr))


def main():
    t = int(input().strip())

    for _ in range(t):
        k = int(input().strip())
        sol3(k)


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/