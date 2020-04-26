---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../assets/css/copy-button.css" />


# :warning: fft.cpp

<a href="../index.html">Back to top page</a>

* category: <a href="../index.html#5058f1af8388633f609cadb75a75dc9d">.</a>
* <a href="{{ site.github.repository_url }}/blob/master/fft.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-03 16:51:41+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
namespace FFT {
using dbl = double;

struct num {
  dbl x = 0, y = 0;
  num() = default;
  num(dbl _x, dbl _y) : x(_x), y(_y) {}
};

inline num operator+(num a, num b) { return num(a.x + b.x, a.y + b.y); }
inline num operator-(num a, num b) { return num(a.x - b.x, a.y - b.y); }
inline num operator*(num a, num b) {
  return num(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);
}
inline num conj(num a) { return num(a.x, -a.y); }

int base = 1;
vector<num> rts = {{0, 0}, {1, 0}};
vector<int> rev = {0, 1};

const dbl PI = asinl(1) * 2;

void ensure_base(int nbase) {
  if (nbase <= base) return;

  rev.resize(1 << nbase);
  for (int i = 0; i < (1 << nbase); i++)
    rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (nbase - 1));

  rts.resize(1 << nbase);
  while (base < nbase) {
    dbl angle = 2 * PI / (1 << (base + 1));
    for (int i = 1 << (base - 1); i < (1 << base); i++) {
      rts[i << 1] = rts[i];
      dbl angle_i = angle * (2 * i + 1 - (1 << base));
      rts[(i << 1) + 1] = num(cos(angle_i), sin(angle_i));
    }
    base++;
  }
}

void fft(vector<num>& as) {
  int n = as.size();
  assert((n & (n - 1)) == 0);

  int zeros = __builtin_ctz(n);
  ensure_base(zeros);
  int shift = base - zeros;
  for (int i = 0; i < n; i++)
    if (i < (rev[i] >> shift)) swap(as[i], as[rev[i] >> shift]);

  for (int k = 1; k < n; k <<= 1) {
    for (int i = 0; i < n; i += 2 * k) {
      for (int j = 0; j < k; j++) {
        num z = as[i + j + k] * rts[j + k];
        as[i + j + k] = as[i + j] - z;
        as[i + j] = as[i + j] + z;
      }
    }
  }
}

template <typename T>
vector<long long> multiply(vector<T>& as, vector<T>& bs) {
  int need = as.size() + bs.size() - 1;
  int nbase = 0;
  while ((1 << nbase) < need) nbase++;
  ensure_base(nbase);

  int sz = 1 << nbase;
  vector<num> fa(sz);
  for (int i = 0; i < sz; i++) {
    T x = (i < (int)as.size() ? as[i] : 0);
    T y = (i < (int)bs.size() ? bs[i] : 0);
    fa[i] = num(x, y);
  }
  fft(fa);

  num r(0, -0.25 / sz);
  for (int i = 0; i <= (sz >> 1); i++) {
    int j = (sz - i) & (sz - 1);
    num z = (fa[j] * fa[j] - conj(fa[i] * fa[i])) * r;
    if (i != j) fa[j] = (fa[i] * fa[i] - conj(fa[j] * fa[j])) * r;
    fa[i] = z;
  }
  fft(fa);

  vector<long long> res(need);
  for (int i = 0; i < need; i++) res[i] = round(fa[i].x);

  return res;
}

};  // namespace FFT

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "fft.cpp"
namespace FFT {
using dbl = double;

struct num {
  dbl x = 0, y = 0;
  num() = default;
  num(dbl _x, dbl _y) : x(_x), y(_y) {}
};

inline num operator+(num a, num b) { return num(a.x + b.x, a.y + b.y); }
inline num operator-(num a, num b) { return num(a.x - b.x, a.y - b.y); }
inline num operator*(num a, num b) {
  return num(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);
}
inline num conj(num a) { return num(a.x, -a.y); }

int base = 1;
vector<num> rts = {{0, 0}, {1, 0}};
vector<int> rev = {0, 1};

const dbl PI = asinl(1) * 2;

void ensure_base(int nbase) {
  if (nbase <= base) return;

  rev.resize(1 << nbase);
  for (int i = 0; i < (1 << nbase); i++)
    rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (nbase - 1));

  rts.resize(1 << nbase);
  while (base < nbase) {
    dbl angle = 2 * PI / (1 << (base + 1));
    for (int i = 1 << (base - 1); i < (1 << base); i++) {
      rts[i << 1] = rts[i];
      dbl angle_i = angle * (2 * i + 1 - (1 << base));
      rts[(i << 1) + 1] = num(cos(angle_i), sin(angle_i));
    }
    base++;
  }
}

void fft(vector<num>& as) {
  int n = as.size();
  assert((n & (n - 1)) == 0);

  int zeros = __builtin_ctz(n);
  ensure_base(zeros);
  int shift = base - zeros;
  for (int i = 0; i < n; i++)
    if (i < (rev[i] >> shift)) swap(as[i], as[rev[i] >> shift]);

  for (int k = 1; k < n; k <<= 1) {
    for (int i = 0; i < n; i += 2 * k) {
      for (int j = 0; j < k; j++) {
        num z = as[i + j + k] * rts[j + k];
        as[i + j + k] = as[i + j] - z;
        as[i + j] = as[i + j] + z;
      }
    }
  }
}

template <typename T>
vector<long long> multiply(vector<T>& as, vector<T>& bs) {
  int need = as.size() + bs.size() - 1;
  int nbase = 0;
  while ((1 << nbase) < need) nbase++;
  ensure_base(nbase);

  int sz = 1 << nbase;
  vector<num> fa(sz);
  for (int i = 0; i < sz; i++) {
    T x = (i < (int)as.size() ? as[i] : 0);
    T y = (i < (int)bs.size() ? bs[i] : 0);
    fa[i] = num(x, y);
  }
  fft(fa);

  num r(0, -0.25 / sz);
  for (int i = 0; i <= (sz >> 1); i++) {
    int j = (sz - i) & (sz - 1);
    num z = (fa[j] * fa[j] - conj(fa[i] * fa[i])) * r;
    if (i != j) fa[j] = (fa[i] * fa[i] - conj(fa[j] * fa[j])) * r;
    fa[i] = z;
  }
  fft(fa);

  vector<long long> res(need);
  for (int i = 0; i < need; i++) res[i] = round(fa[i].x);

  return res;
}

};  // namespace FFT

```
{% endraw %}

<a href="../index.html">Back to top page</a>

