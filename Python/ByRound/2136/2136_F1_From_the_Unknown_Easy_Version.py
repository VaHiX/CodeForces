# Contest 2136, Problem F1: From the Unknown (Easy Version)
# URL: https://codeforces.com/contest/2136/problem/F1

import sys
t = int(input())

def calcL(W, article):
    article = article.split()

    x = 1
    y = 0
    for i in range (2, len(article)):
        word_length = int(article[i])
        if y + word_length <= W:
            y += word_length
        elif word_length > W:
            return 0
        else:
            x += 1
            y = word_length

    return x

for _ in range (t):
    input_W = _

    article_1 = ["111"] * 12500
    output_str = f"? {len(article_1)} {' '.join(article_1)}"
    print(output_str)
    sys.stdout.flush()
    L1 = int(input())
    #L1 = calcL(input_W, output_str)

    if L1 == 0:
        max_W = 110
        min_W = 1

        article_2 = ["1"] * 12500
        output_str = f"? {len(article_2)} {' '.join(article_2)}"
        print(output_str)
        sys.stdout.flush()
        L2 = int(input())
        #L2 = calcL(input_W, output_str)

        W = 12500 // L2
        if W * L2 < 12500:
            W += 1

    else:
        min_word = 12500 // L1
        if min_word * L1 < 12500:
            min_word += 1

        max_word = 12500 // (L1-1)
        if max_word * (L1-1) > 12500:
            max_word -= 1

        min_W = 111 * min_word
        max_W = 111 * max_word + (111-1)
        article_2 = [f"{min_W} {i}" for i in range (1, max_W - min_W + 1)]
        output_str = f"? {len(article_2) * 2} {' '.join(article_2)}"
        print(output_str)
        sys.stdout.flush()
        L2 = int(input())
        #L2 = calcL(input_W, output_str)

        reduced_lines = 2 * (max_W - min_W) - L2
        W = min_W + reduced_lines

    #print(f"! {input_W} {W} {W == input_W}")
    #if W != input_W:
    #    break
    print(f"! {W}")