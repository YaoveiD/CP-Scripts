/*
* author:  yaoveil
* created: 2021-08-24 16:40:24
* seems like useless
*/

#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <vector>
 
using namespace std;

#define ALL(V) V.begin(), V.end()
#define RALL(V) V.rbegin(), V.rend()

template<typename T>
struct Point {
  T x, y;
  int idx;

  Point(T _x = 0, T _y = 0, int _idx = -1)
    : x(_x), y(_y), idx(_idx) {}

  inline void read(int _idx = -1) {
    cin >> x >> y;
    idx = _idx;
  }

  bool operator<(const Point& rhs) const {
    if (x != rhs.x)
      return x < rhs.x;
    if (y != rhs.y)
      return y < rhs.y;
    return idx < rhs.idx;
  }

  inline T mht_dist(const Point& p) {
    return abs(x - p.x) + abs(y - p.y);
  }

  inline double dist(const Point& p) {
    return sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y));
  }
};

template<typename T>
struct Point {
  T x, y, z;
  int idx;

  Point(T _x = 0, T _y = 0, T _z = 0, int _idx = -1)
    : x(_x), y(_y), z(_z), idx(_idx) {}

  inline void read(int _idx = -1) {
    cin >> x >> y >> z;
    idx = _idx;
  }

  bool operator<(const Point& rhs) const {
    if (x != rhs.x)
      return x < rhs.x;
    if (y != rhs.y)
      return y < rhs.y;
    if (z != rhs.z)
      return z < rhs.z;
    return idx < rhs.idx;
  }

  inline T mht_dist(const Point& p) {
    return abs(x - p.x) + abs(y - p.y) + abs(z - p.z);
  }

  inline double dist(const Point& p) {
    return sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y) +
      (z - p.z) * (z - p.z));
  }
};

// make sure to initialize all global vars
// uncomment cin >> tt? 
void solve() {

}
 
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
 
  int tt = 1;
  // cin >> tt;
  while (tt--) {
    solve();
  }
 
  return 0;
}
