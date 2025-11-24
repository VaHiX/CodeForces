// Problem: CF 1393 B - Applejack and Storages
// https://codeforces.com/contest/1393/problem/B

/*
B. Applejack and Storages
time limit per test
2 seconds
memory limit per test
256 megabytes
input
standard input
output
standard output

This year in Equestria was a year of plenty, so Applejack has decided to build some new apple storages. According to the advice of the farm designers, she chose to build two storages with non-zero area: one in the shape of a square and another one in the shape of a rectangle (which possibly can be a square as well).
Applejack will build the storages using planks, she is going to spend exactly one plank on each side of the storage. She can get planks from her friend's company. Initially, the company storehouse has n planks, Applejack knows their lengths. The company keeps working so it receives orders and orders the planks itself. Applejack's friend can provide her with information about each operation. For convenience, he will give her information according to the following format:

+ x: the storehouse received a plank with length x 
- x: one plank with length x was removed from the storehouse (it is guaranteed that the storehouse had some planks with length x). 
Applejack is still unsure about when she is going to order the planks so she wants to know if she can order the planks to build rectangular and square storages out of them after every event at the storehouse. Applejack is busy collecting apples and she has completely no time to do the calculations so she asked you for help!
We remind you that all four sides of a square are equal, and a rectangle has two pairs of equal sides.

Algorithm:
The problem is to determine if we can form one square (4 equal sides) and one rectangle (2 pairs of equal sides) from available planks after each operation.
We maintain counts of plank lengths in a map, and track how many 2s, 4s, 6s, and 8s we have:
- two: number of lengths that appear 2 times
- four: number of lengths that appear 4 times  
- six: number of lengths that appear 6 times
- eight: number of lengths that appear 8 times

When adding/removing planks, we update counts and adjust these counters accordingly.

Time Complexity: O(n log n + q log n)
Space Complexity: O(n)

*/
#include <cstdio>
#include <map>
int main() {
  long n;
  scanf("%ld\n", &n);
  std::map<long, long> cnt;
  long two(0), four(0), six(0), eight(0); // counters for frequencies 2,4,6,8
  for (long p = 0; p < n; p++) {
    long x;
    scanf("%ld ", &x);
    ++cnt[x]; // increment count of plank length x
    if (cnt[x] == 8) { // if x now appears 8 times
      ++eight;
      --six;
    } else if (cnt[x] == 6) { // if x now appears 6 times
      ++six;
      --four;
    } else if (cnt[x] == 4) { // if x now appears 4 times
      ++four;
      --two;
    } else if (cnt[x] == 2) { // if x now appears 2 times
      ++two;
    }
  }
  long q;
  scanf("\n%ld\n", &q);
  while (q--) {
    char w;
    long x;
    scanf("%c %ld\n", &w, &x); // read operation and value
    if (w == '+') {
      ++cnt[x]; // add one plank of length x
      if (cnt[x] == 8) { // x went from 7 to 8
        ++eight;
        --six;
      } else if (cnt[x] == 6) { // x went from 5 to 6
        ++six;
        --four;
      } else if (cnt[x] == 4) { // x went from 3 to 4
        ++four;
        --two;
      } else if (cnt[x] == 2) { // x went from 1 to 2
        ++two;
      }
    } else if (w == '-') {
      --cnt[x]; // remove one plank of length x
      if (cnt[x] == 7) { // x went from 8 to 7
        --eight;
        ++six;
      } else if (cnt[x] == 5) { // x went from 6 to 5
        --six;
        ++four;
      } else if (cnt[x] == 3) { // x went from 4 to 3
        --four;
        ++two;
      } else if (cnt[x] == 1) { // x went from 2 to 1
        --two;
      }
    }
    // check if we can form a square and rectangle:
    // - square needs 4 equal sides (at least 4 planks of same length)
    // - rectangle needs two pairs of equal sides (at least 2 pairs with same lengths)
    // We use counters for frequencies to efficiently test conditions
    puts((eight > 0 || (six > 0 && (four > 0 || two > 0)) ||
          (four > 0 && two > 1) || (four > 1) || (six > 1))
             ? "YES"
             : "NO");
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/