// Problem: CF 1468 N - Waste Sorting
// https://codeforces.com/contest/1468/problem/N

/*
N. Waste Sorting
time limit per test
2 seconds
memory limit per test
512 megabytes
input
standard input
output
standard output

The progress is not standing still in Berland. Recently all garbage containers in Bertown, the capital of Berland, were replaced by differentiated recycling bins, each accepting some category of waste. While this will definitely improve the ecological situation, for some citizens it's difficult to get used to the habit of sorting waste.
Monocarp is one of those citizens who tries to get used to waste sorting. Today he has to take out the trash from his house. There are three containers near the Monocarp's house, the first one accepts paper waste, the second one accepts plastic waste, and the third one — all other types of waste. It is possible to fit $$$c_1$$$ items into the first container, $$$c_2$$$ items into the second container and $$$c_3$$$ items into the third container.
Monocarp has a lot of items to throw into containers. Some are made of paper, so Monocarp has to put them into the first container (he has $$$a_1$$$ such items), some are made of plastic, so he has to put them into the second container (he has $$$a_2$$$ such items), and some are neither paper nor plastic — so Monocarp has to put them into the third container (he has $$$a_3$$$ such items).
Unfortunately, there are also two categories of items that Monocarp is unsure of: he has $$$a_4$$$ items which are partially made of paper, so he will put each of these items either into the first container or into the third container. Similarly, he has $$$a_5$$$ items partially made of plastic, so he has to put each of them either into the second container or into the third container. Obviously, this choice is made separately for each item — for example, Monocarp can throw several partially-plastic items into the second container, and all other partially-plastic items — into the third one.
Now Monocarp wonders: is it possible to put each item into some container so that the first container will hold no more than $$$c_1$$$ items, the second one — no more than $$$c_2$$$ items, and the third one — no more than $$$c_3$$$ items?

Algorithm:
Greedy approach:
1. Place all fixed items (a1, a2, a3) into their respective containers.
2. For partially-paper items (a4), allocate to container 1 or 3 optimally.
3. Similarly for partially-plastic items (a5), allocate to container 2 or 3 optimally.
4. Check if remaining capacity allows assignment.

Time Complexity: O(1) per test case
Space Complexity: O(1)

*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long cd, ce, cf; // capacities of containers 1, 2, 3
    scanf("%ld %ld %ld", &cd, &ce, &cf);
    long ad, ae, af, ag, ah; // a1, a2, a3, a4, a5
    scanf("%ld %ld %ld %ld %ld", &ad, &ae, &af, &ag, &ah);
    bool possible(true); // flag to track if solution is possible
    
    // Place fixed items first
    if (ad > cd || ae > ce || af > cf) {
      possible = false;
    }
    cd -= ad; // remaining capacity of container 1
    ce -= ae; // remaining capacity of container 2
    cf -= af; // remaining capacity of container 3
    
    // Allocate partially-paper items (ag)
    long bd = (cd < ag) ? cd : ag; // allocate as much as possible to container 1
    cd -= bd;
    ag -= bd;
    if (cf < ag) { // remaining partially-paper items cannot fit in container 3
      possible = false;
    }
    cf -= ag; // update remaining capacity of container 3
    
    // Allocate partially-plastic items (ah)
    long be = (ce < ah) ? ce : ah; // allocate as much as possible to container 2
    ce -= be;
    ah -= be;
    if (cf < ah) { // remaining partially-plastic items cannot fit in container 3
      possible = false;
    }
    cf -= ah; // update remaining capacity of container 3
    
    puts(possible ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/