#pragma once

struct Node {
  Node *left, *right;
  ll v;

  Node() : left(nullptr), right(nullptr), v(0) {}
};

// Dynamic Segment Tree
class SegmentTree {
  Node *root;
  int n, n0;

  ll fold(int a, int b, Node *n, int l, int r) {
    if(a <= l && r <= b) {
      return n->v;
    }
    if(r <= a || b <= l) {
      return 0;
    }

    ll lv = n->left ? fold(a, b, n->left, l, (l + r) >> 1) : 0;
    ll rv = n->right ? fold(a, b, n->right, (l + r) >> 1, r) : 0;
    return lv + rv;
  }

public:
  SegmentTree(int n) : n(n) {
    n0 = 1;
    while(n0 < n) n0 <<= 1;
    root = new Node();
  }
  ~SegmentTree() {
    delete root; root = nullptr;
  }

  void update(int k, ll x) {
    Node *n = root;
    int l = 0, r = n0;
    n->v = (n->v + x);
    while(r-l > 1) {
      int m = (l + r) >> 1;
      if(k < m) {
        if(!n->left) n->left = new Node();
        n = n->left;

        r = m;
      } else {
        if(!n->right) n->right = new Node();
        n = n->right;

        l = m;
      }
      n->v = n->v + x;
    }
  }

  ll fold(int a, int b) {
    return fold(a, b, root, 0, n0);
  }
};
