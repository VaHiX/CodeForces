# Problem: CF 1775 A1 - Gardener and the Capybaras (easy version)
# https://codeforces.com/contest/1775/problem/A1

"""
Purpose: 
    This code solves the problem of splitting a given binary string (consisting of 'a' and 'b') 
    into three non-empty substrings a, b, and c such that either:
    - a <= b and c <= b (b is the maximum lexicographically), or
    - a >= b and c >= b (b is the minimum lexicographically).
    
Algorithms/Techniques:
    - Brute-force triple split of the string into three parts
    - Lexicographical comparison using Python's built-in string comparison operators
    
Time Complexity: O(n^3) where n is the length of the input string.
Space Complexity: O(n) for storing the input string and intermediate substrings.
"""

def main():
    t = int(input())  # Read number of test cases
    for _ in range(t):
        p = list(input())  # Read the string as a list of characters
        n = len(p)  # Length of the string
        flag = False  # Flag to indicate if a valid split is found
        a = ""
        b = ""
        c = ""
        # Try all possible splits of the string into three non-empty parts
        for i in range(1, n):  # First split point (after a)
            a = "".join(p[:i])  # First part
            for j in range(i + 1, n):  # Second split point (after b)
                b = "".join(p[i:j])  # Second part
                c = "".join(p[j:])  # Third part
                # Check if the lexicographical condition is satisfied
                if (a <= b and c <= b) or (a >= b and c >= b):
                    flag = True
                    break  # Found a valid split, no need to continue
            if flag:
                break  # Break outer loop too
        if flag:
            print(a, b, c)  # Print the valid split
        else:
            print(":(")  # No valid split found


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/