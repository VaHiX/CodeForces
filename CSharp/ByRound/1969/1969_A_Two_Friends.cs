// Problem: CF 1969 A - Two Friends
// https://codeforces.com/contest/1969/problem/A

using System;
public class TwoFriends {
  /*
   * Problem: Minimum invitations to ensure at least 2 friends attend a party.
   * 
   * Approach:
   * - Each friend i has a best friend p[i].
   * - A friend attends only if both they and their best friend receive invitations.
   * - We want to find the minimum number of invitations such that at least 2 friends attend.
   * 
   * Key insight:
   * - If there exists a pair (i, j) such that p[i] = j and p[j] = i (mutual best friends),
   *   then inviting both i and j will make both attend. Thus, 2 invitations is enough.
   * - Otherwise, we might need to invite at least 3 friends:
   *   - If we have a chain like i -> j -> k, inviting all three ensures at least 2 attend.
   *   - The minimum number of invitations needed in the worst case (no mutual best friends) is 3.
   * 
   * Algorithm:
   * 1. Parse input to get the array p where p[i] is the best friend of friend i.
   * 2. Check if there exists any mutual best friend pair (i.e., p[p[i]] == i).
   * 3. If yes, answer is 2. Else, answer is 3.
   * 
   * Time Complexity: O(n) per test case, where n is the number of friends.
   * Space Complexity: O(n) for storing the array p.
   */
  
  public static void Main() {
    short t = short.Parse(Console.ReadLine());
    for (short i = 0; i < t; i++) {
      byte n = byte.Parse(Console.ReadLine());
      string[] parts = Console.ReadLine().Split();
      byte[] p = new byte[n];
      for (byte j = 0; j < n; j++)
        p[j] = Convert.ToByte(byte.Parse(parts[j]) - 1); // Convert to 0-based indexing
      bool mutualFriend = false;
      for (byte j = 0; j < n && !mutualFriend; j++)
        mutualFriend = (p[p[j]] == j); // Check if j and p[j] are mutual best friends
      byte ans = Convert.ToByte(mutualFriend ? 2 : 3);
      Console.WriteLine(ans);
    }
  }
}

// https://github.com/VaHiX/CodeForces/