#include <iostream>
#include <algorithm>
#include <cstdio>
#include <array>
#include <tuple>
#define pii pair <int, int>
#define int long long
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
const int N = 2005, inf = 1e18;
array <pii, N> isl, t;
array <int, N> prl;
bool check(int n, int x, tuple <int, int, int> m) {
	prl.fill(0);
	prl[0] = x;
	isl = t;
	isl[0].fi = -3e18, isl[0].se = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < i; j++) {
			if (isl[i].fi - isl[j].fi < get <1>(m) + get <0>(m)) break;
			if (prl[j] <= isl[i].se) isl[i].se -= prl[j], prl[i] += prl[j], prl[j] = 0;
			else prl[i] += isl[i].se, prl[j] -= isl[i].se, isl[i].se = 0;
		}
		if (isl[i].se > 0) {
			/* for (int j = 0; j < i; j++) */
				/* write(prl[j]), putchar(32); */
			/* puts(""); */
			/* write(i), puts("@"); */
			return false;
		}
	}
	return true;
}
signed main() {
	freopen("time.in", "r", stdin);
	freopen("time.out", "w", stdout);
	int n = read();
	tuple <int, int, int> m;
	get <0>(m) = read(), get <1>(m) = read(), get <2>(m) = read();
	for (int i = 1; i <= n; i++)
		isl[i].fi = read(), isl[i].se = read();
	sort(isl.begin() + 1, isl.begin() + 1 + n);
	/* for (int i = 1; i <= n; i++) */
		/* isl[i].fi -= get <0>(m) + get <1>(m) */
	t = isl;
	/* for (int i = 1; i <= n; i++) */
		/* write(isl[i].fi), putchar(32); */
	/* puts(""); */
	int l = 1, r = 1e18, ans = -1;
	/* write(check(n, 6, m)), puts(""); */
	/* write(check(n, r, m)), puts(""); */
	/* return 0; */
	while (l < r) {
		int mid = (l + r) >> 1;
		/* write(l), putchar(32); */
		/* write(r), putchar(32); */
		/* write(mid), puts(""); */
		if (check(n, mid, m)) ans = mid, r = mid - 1;
		else l = mid + 1;
	}
	write(ans), puts("");
	return 0;
}
