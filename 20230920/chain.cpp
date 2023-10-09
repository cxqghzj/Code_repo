#include <iostream>
#include <algorithm>
#include <cstdio>
#include <array>
#include <cmath>
#include <vector>
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
namespace subtask1 {

vector <pii> isl;
int solve(int n, int m) {
	isl.clear();
	for (int i = 1; i <= n; i++) {
		if ((s[i].fi | m) > m) continue;
		isl.push_back(s[i]);
	}
	int ans = 0;
	for (auto x : isl)
		ans += x.se;
	return ans;

}
void main(int n, int m) {
	int ans = 0;
	for (int i = 0; i <= log2(m); i++) {
		if (!(m & (1 << i))) continue;
		int res = m;
		res >>= (i + 1);
		res <<= (i + 1);
		res += (1 << i) - 1;
		ans = max(solve(n, res), ans);
	}
	write(ans), puts("");
}

}
namespace subtask2 {

vector <pii> isl;
vector <int> f, g;
int solve(int n, int m) {
	int ans = 0;
	/* write(m), puts(""); */
	isl.clear();
	f.clear();
	f.resize(2005, 0);
	g = f;
	for (int i = 1; i <= n; i++) {
		if ((s[i].fi | m) > m) continue;
		isl.push_back(s[i]);
	}

	f[0] = 1;
	for (auto x : isl) {
		for (int j = 0; j <= 2000; j++) {
			if ((j ^ x.se) > 2000) continue;
			g[j] |= f[j ^ x.se];
		}
		f = g;
	}
	for (int i = 0; i <= 2000; i++)
		if (f[i]) ans = max(ans, i);
	return ans;
}
void main(int n, int m) {
	int ans = 0;
	for (int i = 0; i <= log2(m); i++) {
		if (!(m & (1 << i))) continue;
		int res = m;
		res >>= (i + 1);
		res <<= (i + 1);
		res += (1 << i) - 1;
		ans = max(solve(n, res), ans);
	}
	write(ans), puts("");
}

}
signed main() {
	/* freopen("chain.in", "r", stdin); */
	/* freopen("chain.out", "w", stdout); */
	int n = read(), m = read(), type = read();
	for (int i = 1; i <= n; i++)
		s[i].fi = read(), s[i].se = read();
	if (!type) subtask1::main(n, m);
	else subtask2::main(n, m);
	return 0;
}
