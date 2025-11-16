// Problem: CF 2121 B - Above the Clouds
// https://codeforces.com/contest/2121/problem/B

/*
B. Above the Clouds

Problem Description:
Given a string s of length n, determine if there exist three non-empty strings a, b, and c such that:
1. a + b + c = s (concatenation equals s)
2. b is a substring of a + c (the concatenation of a and c)

Algorithm:
- For each test case:
  - Count frequency of each character in the string.
  - Check if there exists a position i in the middle of the string (1 <= i <= n-2) 
    such that the character at this position appears at least twice in the string.
  - If such a character exists, then we can construct valid a, b, c strings:
    For example, use the first occurrence as part of 'a', last occurrence as part of 'c',
    and place the char in between as 'b' which is a substring of a + c.

Time Complexity: O(n) per test case, where n is the length of string s.
Space Complexity: O(1), since we use fixed size array of 26 for character frequencies.

Techniques:
- Frequency counting
- Greedy approach based on character repetition
*/

fun main() {
    val t = readLine()!!.toInt()
    repeat(t) {
        val n = readLine()!!.toInt()
        val s = readLine()!!
        val freq = IntArray(26)
        for (c in s) freq[c - 'a']++ // Count frequency of each character
        var ok = false
        for (i in 1 until n - 1) {
            if (freq[s[i] - 'a'] >= 2) { // If current character appears more than once
                ok = true
                break
            }
        }
        println(if (ok) "Yes" else "No")
    }
}


// https://github.com/VaHiX/CodeForces/