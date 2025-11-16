# Problem: CF 2138 A - Cake Assignment
# https://codeforces.com/contest/2138/problem/A

import sys


def resolver(k, x):
    # T = 2^(k+1) is the total number of cakes
    T = 1 << (k + 1)
    # inicial = 2^k is the initial number of cakes each person has
    inicial = 1 << k
    pasos = []
    actual = x
    # While current number of cakes Chocola has is not equal to the target
    while actual != inicial:
        # If doubling the current cakes doesn't exceed total, double (operation 1)
        if 2 * actual <= T:
            actual *= 2
            pasos.append(1)
        else:
            # Otherwise, subtract total from doubled value (operation 2)
            actual = 2 * actual - T
            pasos.append(2)
    # Reverse the steps to get the correct order for execution
    pasos.reverse()
    return pasos


def main():
    data = sys.stdin.read().split()
    t = int(data[0])
    index = 1
    resultados = []
    for _ in range(t):
        k = int(data[index])
        x = int(data[index + 1])
        index += 2
        pasos = resolver(k, x)
        resultados.append(str(len(pasos)))
        if pasos:
            resultados.append(" ".join(map(str, pasos)))
        else:
            resultados.append("")
    print("\n".join(resultados))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/codeForces/