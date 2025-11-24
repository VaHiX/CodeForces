// Problem: CF 523 D - Statistics of Recompressing Videos
// https://codeforces.com/contest/523/problem/D

/*
Purpose: This program simulates the recompression of videos on k servers, where each server processes videos in a first-come-first-served manner. 
         For each video, we determine the time when its recompression finishes.

Algorithms/Techniques: 
- Use a multiset to maintain the earliest available time on each server.
- For each video, select the server that becomes available earliest.
- Update the server's availability time after processing the current video.

Time Complexity: O(n * log k), where n is the number of videos and k is the number of servers.
Space Complexity: O(k), as we store at most k server availability times in the multiset.

*/

#include <cstdio>
#include <set>
typedef long long ll;
int main() {
  ll n, k;
  scanf("%lld %lld", &n, &k);
  std::multiset<ll> ms; // Multiset to store the finish times of servers
  for (ll p = 0; p < k; p++) {
    ms.insert(0); // Initialize all servers to be available at time 0
  }
  while (n--) {
    ll t, dur;
    scanf("%lld %lld", &t, &dur);
    std::multiset<ll>::iterator it = ms.begin(); // Get the earliest available server
    ll s = *it;
    ms.erase(it); // Remove that server from the set
    ll f = ((s > t) ? s : t) + dur; // Compute finish time: max(server_available_time, video_upload_time) + duration
    ms.insert(f); // Add the updated finish time back to the set
    printf("%lld\n", f);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/