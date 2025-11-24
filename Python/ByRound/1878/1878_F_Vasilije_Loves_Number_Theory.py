# Problem: CF 1878 F - Vasilije Loves Number Theory
# https://codeforces.com/contest/1878/problem/F

"""
Purpose: This code solves the problem "F. Vasilije Loves Number Theory" which involves determining 
         whether there exists a positive integer 'a' such that gcd(a,n)=1 and d(n*a)=n, where d(n) 
         is the number of positive divisors of n.

Algorithms/Techniques:
- Sieve of Eratosthenes for generating prime numbers up to a limit
- Prime factorization of numbers to compute the number of divisors
- Mathematical analysis to determine if a solution exists based on the prime factorization
- Efficient preprocessing and query handling

Time Complexity:
- Preprocessing primes: O(n log log n) where n is the limit (1005)
- Prime factorization per number: O(sqrt(m)) where m is the number being factorized
- Query processing: O(k) where k is the number of distinct prime factors of n
- Overall per test case: O(n log log n + q * sqrt(max_n))

Space Complexity:
- Space for primes list: O(n) where n is the limit
- Space for prime factorization map: O(log(max_n)) for storing prime factors
- Overall space complexity: O(n + log(max_n))

"""

class Solution:
    def __init__(self):
        self.limit = 1005
        self.prime_number = self.seive_prime()  # Generate primes up to limit
        self.prime_fact = {}  # Map to store prime factorization of current n

    def seive_prime(self, *args, **kwargs):
        """
        Generate all prime numbers up to 'self.limit' using Sieve of Eratosthenes.
        This is used to quickly get prime factors of any number.
        """
        check_number = {}
        prime_number = [2]
        for i in range(3, self.limit, 2):
            if check_number.get(i, False):
                continue
            j = i * i
            while j < self.limit:
                check_number[j] = True
                j += i * 2
        for i in range(3, self.limit, 2):
            if not check_number.get(i, False):
                prime_number.append(i)
        return prime_number

    def get_prime_factrization(self, number):
        """
        Returns the prime factorization of 'number'.
        For example, if number=12, returns {2: 2, 3: 1} because 12 = 2^2 * 3^1
        """
        prime_fact = {}
        for prime in self.prime_number:
            if prime * prime > number:
                break
            if number % prime == 0:
                cnt = 0
                while number % prime == 0:
                    number //= prime
                    cnt += 1
                prime_fact[prime] = cnt
        if number > 1:
            prime_fact[number] = 1
        return prime_fact

    def prime_factrization(self, number):
        """
        Adds the prime factors of 'number' to 'self.prime_fact' (cumulative addition).
        """
        prime_fact = self.get_prime_factrization(number)
        for key, value in prime_fact.items():
            self.prime_fact[key] = self.prime_fact.get(key, 0) + value

    def is_divisor_or_not(self):
        """
        Check if there exists a positive integer 'a' such that gcd(a,n)=1 and d(n*a)=n.
        This is based on mathematical reasoning that uses the structure of the prime factorization.
        """
        nod = self.get_number_of_divisor()  # Get divisor count of current n
        prime_fact = self.get_prime_factrization(nod)  # Factorize this count
        for key, value in prime_fact.items():
            # If current prime power in divisor count is greater than in n, it's impossible
            if self.prime_fact.get(key, 0) < value:
                return False
        return True

    def get_number_of_divisor(self):
        """
        Calculates and returns the number of divisors of current n using stored prime factors.
        Formula: If n = p1^a1 * p2^a2 * ... * pk^ak, then d(n) = (a1+1)*(a2+1)*...*(ak+1)
        """
        nod = 1
        for value in self.prime_fact.values():
            nod *= value + 1
        return nod

    def get_input(self):
        """
        Read and parse input line into integers.
        """
        number_input = input()
        number_strings = number_input.split()
        return tuple(int(num) for num in number_strings)

    def solution(self):
        """
        Main solution function that processes test cases and queries.
        """
        test = int(input())
        while test > 0:
            n, q = self.get_input()
            self.prime_fact = {}  # Reset prime factors
            self.prime_factrization(n)  # Initialize with prime factors of n
            for i in range(q):
                query_input = self.get_input()
                if len(query_input) > 1:  # Query type 1: multiply n by x
                    self.prime_factrization(query_input[1])  # Add x's prime factors to n
                    self.get_number_of_divisor()  # Recalculate divisor count
                    print(f"{'YES' if self.is_divisor_or_not() else 'NO'}")
                else:  # Query type 2: reset n to original value
                    self.prime_fact = {}
                    self.prime_factrization(n)  # Reset prime factors to original
            test -= 1
            print()


if __name__ == "__main__":
    sol = Solution()
    sol.solution()


# https://github.com/VaHiX/CodeForces/