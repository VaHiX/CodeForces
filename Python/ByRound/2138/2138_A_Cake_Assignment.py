# Contest 2138, Problem A: Cake Assignment
# URL: https://codeforces.com/contest/2138/problem/A

import sys


# deepseek
def resolver(k, x):
    T = 1 << (k + 1)
    inicial = 1 << k
    pasos = []
    actual = x
    while actual != inicial:
        if 2 * actual <= T:
            actual *= 2
            pasos.append(1)
        else:
            actual = 2 * actual - T
            pasos.append(2)
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
