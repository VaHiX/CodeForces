# Problem: CF 2037 B - Intercepted Inputs
# https://codeforces.com/contest/2037/problem/B

"""
Algorithm: Find grid dimensions n and m such that n * m equals the number of integers in the input stream,
           and both n and m are present in the input stream. This is done by trying all divisors of the total
           count of integers (k), checking if both the divisor and its corresponding cofactor are present in
           the input set.

Time Complexity: O(sqrt(k)) per test case, because we iterate up to sqrt(k) to find divisors.
Space Complexity: O(k) for storing the input integers in a set.
"""

for s in [*open(0)][2::2]:  # Read input lines starting from index 2, skipping the first line of each test case
    n = len(a := s.split()) - 2  # Get number of integers, subtract 2 to exclude n and m from the count
    s = {*a}  # Convert list of integers to a set for fast lookup
    i = 1  # Start checking from 1 to find a divisor
    while n % i or {str(i), str(n // i)} - s:  # Loop until a valid divisor pair is found
        i += 1  # Increment to check next potential divisor
    print(i, n // i)  # Print the valid n and m


# https://github.com/VaHiX/CodeForces/