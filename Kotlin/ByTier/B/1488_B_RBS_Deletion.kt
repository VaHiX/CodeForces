// Problem: CF 1488 B - RBS Deletion
// https://codeforces.com/contest/1488/problem/B

/*
B. RBS Deletion
Algorithm: Greedy + Prefix Balance Tracking
Time Complexity: O(n) per test case, where n is the length of the string s.
Space Complexity: O(1), only using a few variables for counting and tracking.

Approach:
- For each test case:
  - We can perform prefix deletions (operation type 1) and substring deletions (operation type 2).
  - The key insight is that a substring deletion of an RBS can be reduced to:
    - Removing balanced parts from the string.
  - To maximize operations:
    - We first consider how many prefixes we can delete (each prefix contributes 1 operation).
    - Then we consider how many substrings we can remove, with at most k operations allowed.
  - Counting the maximum number of matching brackets from left to right gives us an upper bound on prefix deletions.
    - Every time we find a balanced prefix (equal open and close parentheses), that means we have a valid RBS
      which can be deleted as one operation.
  - The maximum number of operations is the sum of possible prefix deletions plus up to k substring deletions.

*/

import java.io.BufferedReader
import java.io.InputStreamReader
import java.util.StringTokenizer

fun main() {
    val br = BufferedReader(InputStreamReader(System.`in`))
    var st = StringTokenizer(br.readLine())
    val t = st.nextToken().toInt()
    
    repeat(t) {
        st = StringTokenizer(br.readLine())
        val n = st.nextToken().toLong()
        var ans = n / 2 // Maximum prefix operations if all balanced
        var ans2 = st.nextToken().toLong() // This appears to be k, the limit on type 2 operations // line 21
        
        val s = br.readLine()
        var open = 0L
        var close = 0L
        for (ch in s) {
            if (ch == '(') open++ else close++
            if (open == close) { // Found a balanced prefix
                ans2++ // Increment count of valid operations; this counts both prefix and substring if applicable
            }
        }
        println(minOf(ans, ans2))
    }
}


// https://github.com/VaHiX/codeForces/