#include <iostream>
#include <algorithm>
#include <cstdio>
#include <array>
#include <set>
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

namespace fake_algorithm {

array <pii, N> isl;
void main(int n, int m) {
	for (int i = n + 1; i <= n + m; i++)
		isl[i - n] = s[i];
	sort(isl.begin() + 1, isl.begin() + 1 + m, greater <pii>());
	int v = read();
	sort(s.begin() + 1, s.begin() + 1 + n, greater <pii>());
	for (int i = 1; i <= v && i <= n; i++)
		s[i].fi += s[i - 1].fi;
	int ans = 0, sum = 0;
	for (int i = 0; i <= m; i++) {
		sum += isl[i].se;
		if (v - 2 * i < 0) break;
		ans = max(ans, sum + s[min(v - 2 * i, n)].fi);
	}
	write(ans), puts("");
	return;
}

}

namespace Subtask2 {


void main(int n, int m) {
	sort(s.begin() + 1, s.begin() + 1 + n + m);
	int v = read(), ans = 0;
	for (int i = 1; i <= v && i <= n + m; i++)
		ans += s[i].fi;
	write(ans), puts("");
}

}

namespace Subtask3 {


}

signed main() {
	freopen("king.in", "r", stdin);
	freopen("king.out", "w", stdout);
	int n = read(), m = read();
	for (int i = 1; i <= n; i++)
		s[i].fi = read();
	bool flg2 = false;
	for (int i = 1; i <= m; i++) {
		s[i + n].fi = read(), s[i + n].se = read();
		/* if (s[i + n].fi) flg1 = 1; */
		if (s[i + n].se) flg2 = 1;
	}
	if (!flg2) Subtask2::main(n, m);
	else fake_algorithm::main(n, m);
	return 0;
}
