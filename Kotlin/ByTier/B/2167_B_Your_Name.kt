// Problem: CF 2167 B - Your Name
// https://codeforces.com/contest/2167/problem/B

/*
 * Problem: Check if two strings are anagrams of each other.
 * 
 * Algorithm: 
 * - For each test case, sort the characters of both strings.
 * - Compare the sorted versions.
 * - If they are equal, then one string can be rearranged to form the other.
 * 
 * Time Complexity: O(n log n) per test case due to sorting,
 *                  where n is the length of the strings.
 * Space Complexity: O(n) for storing the character arrays and sorted results.
 */

fun main() 
{
    val see = readLine()!!.toInt() // Read number of test cases
    repeat(see)
    {
        val big = readLine()!!.toInt() // Read length of strings
        val (terrace, ping) = readLine()!!.split(" ") // Read both strings
        val puppy = terrace.toCharArray().sorted() // Sort characters of first string
        val bugg = ping.toCharArray().sorted() // Sort characters of second string
        val codee = if (puppy == bugg) "YES" else "NO" // Compare sorted strings
        println(codee) // Output result
    }
}


// https://github.com/VaHiX/CodeForces/