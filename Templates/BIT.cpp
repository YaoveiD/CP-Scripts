/*
*  author: yaoveil
*  date:   2021-06-22 23:18:30
*/

//indexed from 1
class BIT {
private:
  int n;
  vector<int> tree;

public:
  BIT(int _n): n(_n), tree(_n + 1) {}

  static constexpr int lowbit(int x) {
    return x & (-x);
  }

  //d -> delta
  void update(int x, int d) {
    while (x <= n) {
        tree[x] += d;
        x += lowbit(x);
    }
  }

  //[0, x]
  int query(int x) const {
    int ans = 0;
    while (x) {
        ans += tree[x];
        x -= lowbit(x);
    }
    return ans;
  }

  //(l, r]
  int range_sum(int r, int l) {
    return query(r) - query(l);
  }
};