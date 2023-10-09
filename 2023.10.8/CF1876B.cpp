#include <iostream>
#include <algorithm>
#include <cstdio>
#include <array>
#include <set>
#define int long long
#define pii pair <int, int>
using namespace std;
#ifdef ONLINE_JUDGE

/* #define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1+) */
/* char buf[1 << 23], *p1 = buf, *p2 = buf, ubuf[1 << 23], *u = ubuf; */

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
const int N = 1e5 + 5;
array <pii, N> s;
multiset <int> isl;
void solve() {
	isl.clear();
	int n = read(), p = read();
	for (int i = 1; i <= n; i++)
		s[i].se = read();
	for (int i = 1; i <= n; i++)
		s[i].fi = read();
	sort(s.begin() + 1, s.begin() + 1 + n);
	int ans = 0, cnt = 0;
	for (int i = 1; i <= n; i++) {
		if (!isl.size()) ans += p;
		else if (*isl.begin() < p) ans += *isl.begin(), isl.erase(isl.begin());
		else ans += p;
		int tp = s[i].se;
		while (cnt <= n && tp--)
			isl.insert(s[i].fi), cnt++;
		/* for (auto j : isl) { */
			/* write(j), putchar(32); */
		/* } */
		/* puts(""); */
	}
	write(ans), puts("");
}
signed main() {
	int T = read();
	while (T--) solve();
	return 0;
}
