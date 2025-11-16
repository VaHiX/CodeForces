// Problem: CF 714 B - Filya and Homework
// https://codeforces.com/contest/714/problem/B

/*
 * Problem: Filya and Homework
 * Purpose: Determine if it's possible to make all elements of an array equal 
 *          by adding/subtracting a fixed value x to/from some elements.
 * 
 * Algorithm:
 * - Use a set to store unique values from the array.
 * - If there are 0, 1, or 2 unique values, it's always possible to make all equal.
 * - If there are 3 unique values, check if they form an arithmetic sequence.
 *   That is, the middle value should be the average of the smallest and largest.
 * - If there are 4 or more unique values, it's impossible.
 * 
 * Time Complexity: O(n log n) due to insertion into the set.
 * Space Complexity: O(n) for storing unique elements in the set.
 */

#include <cstdio>
#include <set>
int main() {
  long n;
  scanf("%ld\n", &n);
  std::set<long> s;  // Set to store unique elements
  while (n--) {
    long a;
    scanf("%ld", &a);
    s.insert(a);  // Insert element into set
  }
  if (s.size() <= 2) {  // If 0, 1, or 2 unique values, possible
    puts("YES");
    return 0;
  }
  if (s.size() >= 4) {  // If 4 or more unique values, impossible
    puts("NO");
    return 0;
  }
  // If exactly 3 unique values, check if they form an arithmetic sequence
  long a = *s.begin();  // First smallest element
  long b = *(++s.begin());  // Second smallest element
  long c = *(++(++s.begin()));  // Third smallest element
  puts(2 * b == a + c ? "YES" : "NO");  // Check arithmetic progression condition
  return 0;
}


// https://github.com/VaHiX/CodeForces/