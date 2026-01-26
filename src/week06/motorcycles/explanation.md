#include <bits/stdc++.h>
#include <CGAL/Gmpq.h>
using namespace std;

typedef std::tuple<long, long, long, int> Line;

CGAL::Gmpq compute_slope(Line& line){
  long y0 = std::get<0>(line);
  long x1 = std::get<1>(line);
  long y1 = std::get<2>(line);
  return CGAL::Gmpq(y1 - y0, x1);
}

// We assume here that the two lines intersect
bool i_stops(CGAL::Gmpq& slope_i, CGAL::Gmpq& slope_j){
  // They both go up, then j is stopped.
  if (slope_i >= 0 && slope_j > 0)
    return false;
  
  // They both go down, then i is stopped
  if (slope_i < 0 && slope_j <= 0)
    return true;
  
  // i goes down and j goes up
  if (slope_i < 0 && slope_j > 0)
    return -slope_i >= slope_j;
}

void testcase() {
  int n; 
  cin >> n;
 
  vector<Line> lines(n);
  for (int i = 0; i < n; i++) {
    long y0, x1, y1; 
    cin >> y0 >> x1 >> y1;
    lines[i] = { y0, x1, y1, i };
  }
  
  sort(lines.begin(), lines.end());
  vector<bool> sunset(n, true);
  
  for (int i = 0; i < n; i++) {
    for (int j = i-1; j >= 0; j--) {
      int index_i = get<3>(lines[i]);
      int index_j = get<3>(lines[j]);
      
      // Skip if it does not drive forever
      if (!sunset[index_j])
        continue;

      CGAL::Gmpq slope_i = compute_slope(lines[i]);
      CGAL::Gmpq slope_j = compute_slope(lines[j]);

      // They will not intersect, so we can stop searching, since we will
      // already have stopped all drivers when j was i.
      if (slope_i >= slope_j)
        break;

      if (i_stops(slope_i, slope_j)){
        sunset[index_i] = false;
        break;
      }
      else
        sunset[index_j] = false;
    }
  }
  
  for (int i = 0; i < n; i++)
    if (sunset[i])
      cout << i << ' ';
  
  cout << endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; 
  cin >> t;
  while (t--) 
    testcase();
}