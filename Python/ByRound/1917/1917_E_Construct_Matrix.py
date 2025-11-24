# Problem: CF 1917 E - Construct Matrix
# https://codeforces.com/contest/1917/problem/E

"""
Construct Matrix

Algorithm:
This problem requires constructing an n×n matrix with only 0s and 1s such that:
1. The total sum of the matrix is exactly k
2. Each row has the same XOR value
3. Each column has the same XOR value

The approach is based on the observation that if all rows and columns have the same XOR,
then the overall XOR of the matrix must be 0 (since rows XOR = cols XOR = overall XOR).

Key insights:
- If k is odd, it's impossible since the sum of a matrix with 0s and 1s must be even (each row/column XOR is 0 or 1)
- If k is a multiple of 4, we can construct by placing 1s in pairs and keeping the pattern consistent
- Special cases for n=2 and specific ranges need handling

Time Complexity: O(n^2) per test case - we construct and output the matrix
Space Complexity: O(n^2) - to store the matrix
"""

for _ in range(int(input())):

    n, k = map(int, input().split())

    if k % 2 == 1:
        print("No")
    elif k % 4 == 0:
        print("Yes")
        ost = n
        for i in range(k // (n * 2)):
            ost -= 2
            print("1 " * (n - 1) + "1")
            print("1 " * (n - 1) + "1")
        if k % (n * 2) > 0:
            ost -= 2
            print(
                "1 " * ((k % (n * 2)) // 2) + "0 " * (n - (k % (n * 2)) // 2 - 1) + "0"
            )
            print(
                "1 " * ((k % (n * 2)) // 2) + "0 " * (n - (k % (n * 2)) // 2 - 1) + "0"
            )
        for i in range(ost):
            print("0 " * (n - 1) + "0")
    elif n == 2:
        print("Yes")
        print(1, 0)
        print(0, 1)
    elif k == 2 or k == n**2 - 2:
        print("No")
    elif k <= n**2 - 10:
        ans = [[0] * n for i in range(n)]
        ans[0][0] = 1
        ans[1][0] = 1
        ans[0][1] = 1
        ans[2][1] = 1
        ans[1][2] = 1
        ans[2][2] = 1
        ost = (k - 6) // 4
        for i in range(4, n, 2):
            if ost > 0:
                ans[0][i] = 1
                ans[0][i + 1] = 1
                ans[1][i] = 1
                ans[1][i + 1] = 1
                ost -= 1
        for i in range(4, n, 2):
            if ost > 0:
                ans[2][i] = 1
                ans[2][i + 1] = 1
                ans[3][i] = 1
                ans[3][i + 1] = 1
                ost -= 1
        for j in range(4, n, 2):
            for i in range(0, n, 2):
                if ost > 0:
                    ans[j][i] = 1
                    ans[j][i + 1] = 1
                    ans[j + 1][i] = 1
                    ans[j + 1][i + 1] = 1
                    ost -= 1
        print("Yes")
        for x in ans:
            print(" ".join(map(str, x)))
    else:
        ans = [[1] * n for i in range(n)]
        ans[0][0] = 0
        ans[1][0] = 0
        ans[0][1] = 0
        ans[2][1] = 0
        ans[1][2] = 0
        ans[2][2] = 0
        print("Yes")
        for x in ans:
            print(" ".join(map(str, x)))


# https://github.com/VaHiX/CodeForces/