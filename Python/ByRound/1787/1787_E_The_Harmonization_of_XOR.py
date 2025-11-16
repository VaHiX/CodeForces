# Problem: CF 1787 E - The Harmonization of XOR
# https://codeforces.com/contest/1787/problem/E

from sys import stdin, stdout

t = int(stdin.readline())

for _ in range(t):
    n, k, x = [int(z) for z in stdin.readline().split()]

    checker = 0
    for i in range(1, n + 1):
        checker = checker ^ i

    need = x * (k % 2)

    if checker != need:
        stdout.write("NO\n")

    else:
        temp_x = x
        l = -1
        while temp_x > 0:
            temp_x = temp_x // 2
            l += 1

        count = 0
        alpha = 0
        answer = []
        left = [1] * (n + 1)
        left[0] = 0
        if k == 1:
            alive = False
        else:
            alive = True

        while alive:
            factor = (1 << (l + 1)) * alpha

            for i in range((1 << l)):
                temp1 = x ^ i ^ factor
                temp2 = i ^ factor

                if temp2 > n:
                    alive = False
                    break

                if temp1 <= n:
                    answer.append((temp1, temp2))
                    count += 1
                    left[temp1] = 0
                    left[temp2] = 0
                    if count == k - 1:
                        alive = False
                        break

            alpha += 1

        if count == k - 1:
            stdout.write("YES\n")
            for temp1, temp2 in answer:
                if temp2 == 0:
                    stdout.write("1 {}\n".format(temp1))
                else:
                    stdout.write("2 {} {}\n".format(temp1, temp2))

            stdout.write("{} ".format(sum(left)))
            for i in range(1, n + 1):
                if left[i]:
                    stdout.write("{} ".format(i))
            stdout.write("\n")

        else:
            stdout.write("NO\n")


# https://github.com/VaHiX/CodeForces/