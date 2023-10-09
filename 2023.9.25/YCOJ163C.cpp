#include <iostream>
#include <algorithm>
#include <cstdio>
#include <array>
#include <cmath>
#define int long long
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
#define fi first
#define se second
const int N = 2e5 + 5;


array <pii, N> s;


namespace Bas {

array <int, N> prl;

void insert(int x) {
	for (int i = 63; ~i; i--) {
		if (~x & (1ll << i)) continue;
		if (!prl[i]) {
			prl[i] = x;
			return;
		}
		else x ^= prl[i];
	}
}
int query() {
	int ans = 0;
	for (int i = 63; ~i; i--)
		ans = max(ans ^ prl[i], ans);

	return ans;
}
}

int solve1(int n, int m) {
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		if ((s[i].fi | m) > m) continue;
		ans += s[i].se;
	}
	return ans;
}
int solve2(int n, int m) {
	for (int i = 1; i <= n; i++) {
		if ((s[i].fi | m) > m) continue;
		Bas::insert(s[i].se);
	}
	return Bas::query();
}
int lowbit(int x) {
	return x & -x;
}
signed main() {
	/* freopen("chain10.in", "r", stdin); */
	int n = read(), m = read(), k = read();
	for (int i = 1; i <= n; i++)
		s[i].fi = read(), s[i].se = read();
	int ans = 0, res = 0;
	while (m) {
		ans = max(k == 0 ? solve1(n, m + res) : solve2(n, m + res), ans);
		res = lowbit(m) - 1;
		write(m), putchar(32);
		write(lowbit(m)), puts("");
		m -= lowbit(m);
	}
	write(ans), puts("");
	return 0;
}
