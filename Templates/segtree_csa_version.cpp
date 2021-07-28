#include <bits/stdc++.h>

#define ls (i << 1)
#define rs (i << 1 | 1)

using namespace std;

int a[200005];

struct node{
    int l;
    int r;
    int val;
}tree[800010];

void push_up(int i) {
    tree[i].val = __gcd(tree[ls].val, tree[rs].val);
}

void build(int i, int l, int r) {
    tree[i].l = l;
    tree[i].r = r;
    int mid = (l + r) >> 1;
    if (l == r) {
        tree[i].val = a[l];
        return;
    }
    build(ls, l, mid);
    build(rs, mid + 1, r);
    push_up(i);
}

int query(int i, int l, int r) {
    if (tree[i].l > r || tree[i].r < l) {
        return 0;
    }
    if (tree[i].l >= l && tree[i].r <= r) {
        return tree[i].val;
    }
    return __gcd(query(ls, l, r), query(rs, l, r)); 
}
