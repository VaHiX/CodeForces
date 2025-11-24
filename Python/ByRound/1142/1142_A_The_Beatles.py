# Problem: CF 1142 A - The Beatles
# https://codeforces.com/contest/1142/problem/A

import math


def main():
    n, k = map(int, input().split())  # Read n (number of restaurants) and k (distance between restaurants)
    a, b = map(int, input().split())  # Read a (distance to nearest restaurant from start), b (from first stop)
    v = n * k  # Total number of cities on the circle
    c, d = n * k, 0  # Initialize min and max stops counter
    for i in range(n):  # For each possible starting restaurant position
        x = i * k + a - b  # Compute one candidate for l based on distance difference
        res = v // math.gcd(v, x)  # Calculate number of stops needed using GCD
        if res < c:  # Update minimum stops if necessary
            c = res
        if res > d:  # Update maximum stops if necessary
            d = res
        x = i * k + a + b  # Compute another candidate for l based on distance sum
        res = v // math.gcd(v, x)  # Calculate number of stops needed using GCD
        if res < c:  # Update minimum stops if necessary
            c = res
        if res > d:  # Update maximum stops if necessary
            d = res
    print(c, d)  # Output the min and max number of stops


main()


# https://github.com/VaHiX/codeForces/