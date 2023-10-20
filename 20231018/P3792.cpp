#include <iostream>
#include <algorithm>
#include <cstdio>
#include <array>
#include <random>
#define pii pair <int, int>
using namespace std;
#ifdef ONLINE_JUDGE

#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
char buf[1 << 23], *p1 = buf, *p2 = buf, ubuf[1 << 23], *u = ubuf;

#endif
int read() {
	int p = 0, flg = 1;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-') flg = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		p = p * 10 + c - '0';
		c = getchar();
	}
	return p * flg;
}
void write(int x) {
	if (x < 0) {
		x = -x;
		putchar('-');
	}
	if (x > 9) {
		write(x / 10);
	}
	putchar(x % 10 + '0');
}
const int N = 5e5 + 5, M = 2.5e7 + 5, inf = 0x7f7f7f7f;
array <int, M> prl;
mt19937 rnd('N' + 'y' + 'a' + 'r' + 'u' + 'k' + 'o');

namespace Bit {

array <int, N> edge;

int lowbit(int x) {
	return x & -x;
}
void modify(int x, int y, int n) {
	while (x <= n) {
		edge[x] ^= y;
		x += lowbit(x);
	}
	return;
}
int query(int x) {
	int ans = 0;
	while (x) {
		ans ^= edge[x];
		x -= lowbit(x);
	}
	return ans;
}


}

#define fi first
#define se second
namespace Sgt {

array <pii, N * 4> edge;
pii update(pii x, pii y) {
	pii ans = make_pair(0, inf);
	ans.fi = max(x.fi, y.fi);
	ans.se = min(x.se, y.se);
	return ans;
}
void pushup(int x, int l, int r) {
	edge[x] = update(edge[x * 2], edge[x * 2 + 1]);
}
void modify(int x, int l, int r, int k, int y) {
	if (k > r || k < l) return;
	if (l == r) {
		edge[x].fi = edge[x].se = y;
		return;
	}
	int mid = (l + r) >> 1;
	if (k <= mid) modify(x * 2, l, mid, k, y);
	else modify(x * 2 + 1, mid + 1, r, k, y);
	pushup(x, l, r);
}
pii query(int x, int l, int r, int L, int R) {
	if (L > r || R < l) return make_pair(0, inf);
	if (L <= l && R >= r) return edge[x];
	int mid = (l + r) >> 1;
	pii ans = make_pair(0, inf);
	if (L <= mid) ans = update(ans, query(x * 2, l, mid, L, R));
	if (R > mid) ans = update(ans, query(x * 2 + 1, mid + 1, r, L, R));
	return ans;
}


}

array <int, N> s;

int main() {
	int n = read(), m = read();
	for (int i = 1; i <= 2.5e7; i++)
		prl[i] = prl[i - 1] ^ rnd();

	Sgt::edge.fill(make_pair(0, inf));

	for (int i = 1; i <= n; i++) {
		s[i] = read();
		Bit::modify(i, prl[s[i]] ^ prl[s[i] - 1], n);
		/* cerr << i << endl; */
		Sgt::modify(1, 1, n, i, s[i]);
	}

	while (m--) {
		int op = read(), x = read(), y = read();
		if (op == 1) {
			Bit::modify(x, prl[s[x]] ^ prl[s[x] - 1], n); s[x] = y;
			Bit::modify(x, prl[s[x]] ^ prl[s[x] - 1], n);
		}
		else {
			pii u = Sgt::query(1, 1, n, x, y);
			i (u.fi - u.se + 1 == y - x + 1
			&& (prl[u.fi] ^ prl[u.se - 1]) == (Bit::query(y) ^ Bit::query(x - 1)))
				puts("damushen");
			else
				puts("yuanxing");
		}
	}
	return 0;
}
