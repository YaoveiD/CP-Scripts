/*
*  author: yaoveil
*  date:   2021-06-22 23:13:08
*/

#include <bits/stdc++.h>

using namespace std;

//basic Dsu
class Dsu {
public:
  vector<int> p;
  int n;

  Dsu(int _n) : n(_n) {
    p.resize(n);
    iota(p.begin(), p.end(), 0);
  }

  inline int get(int x) {
    return (x == p[x] ? x : (p[x] = get(p[x])));
  }

  inline bool unite(int x, int y) {
    x = get(x);
    y = get(y);
    if (x != y) {
      p[x] = y;
      return true;
    }
    return false;
  }

  inline bool same(int x, int y) {
    return get(x) == get(y);
  }
};

//unite by size ? but we can get the size of each component
class Dsu {
public:
  vector<int> p;
  vector<int> sz;
  int n, components;

  Dsu(int _n) : n(_n), components(_n) {
    p.resize(n);
    sz.resize(n);
    iota(p.begin(), p.end(), 0);
    fill(sz.begin(), sz.end(), 1);
  }

  inline int get(int x) {
    return (x == p[x] ? x : (p[x] = get(p[x])));
  }

  inline bool unite(int x, int y) {
    x = get(x);
    y = get(y);
    if (x != y) {
      components -= 1;
      p[x] = y;
      sz[y] += sz[x];
      return true;
    }
    return false;
  }

  inline int size(int x) {
    x = get(x);
    return sz[x];
  }

  inline bool same(int x, int y) {
    return get(x) == get(y);
  }

  inline int get_components() const {
    return components;
  }
};

//weighted
class Dsu {
public:
  int n;
  vector<int> p;
  vector<int> weight;

  Dsu(int _n) : n(_n) {
    p.resize(n);
    weight.resize(n);
    iota(p.begin(), p.end(), 0);
  }

  inline int get(int x) {
    if (x != p[x]) {
      int t = p[x];
      p[x] = get(p[x]);
      weight[x] += weight[t];
    }
    return p[x];
  }

  inline bool unite(int x, int y, int w = 0) {
    int px = get(x);
    int py = get(y);
    if (px != py) {
      p[px] = py;
      weight[px] = -weight[x] + weight[y] + w;
      return true;
    }
    // here should be some constraints
    return false;
  }
};