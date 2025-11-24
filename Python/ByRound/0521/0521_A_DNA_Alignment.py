# Problem: CF 521 A - DNA Alignment
# https://codeforces.com/contest/521/problem/A

"""
Purpose: This code calculates the number of cyclic DNA strings t that achieve the maximum Vasya distance ρ(s, t)
         for a given DNA string s of length n, where the alphabet is {A, C, G, T}.
         
Algorithms/Techniques:
- Count frequency of each nucleotide in the input string s.
- Identify the maximum frequency among the four nucleotides.
- Count how many nucleotides have this maximum frequency.
- The result is (number of max freq nucleotides) ^ n mod (10^9 + 7).

Time Complexity: O(n) - We iterate through the string once to count frequencies.
Space Complexity: O(1) - We use a fixed-size array of 4 elements regardless of input size.
"""

n = int(input())
s = input()
w = [0] * 4
w[0] = s.count("A")   # Count of 'A'
w[1] = s.count("C")   # Count of 'C'
w[2] = s.count("G")   # Count of 'G'
w[3] = s.count("T")   # Count of 'T'
print((w.count(max(w)) ** n) % 1000000007)  # Raise number of max freq chars to power n, mod 1e9+7


# https://github.com/VaHiX/CodeForces/