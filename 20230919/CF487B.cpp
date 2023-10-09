#include <iostream>
#include <algorithm>
#include <cstdio>
#include <array>
#include <cmath>
#include <vector>
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
const int N = 1e5 + 5, inf = 4e18;
array <int, N> s, lg;
void init(int n) {
	for (int i = 1; i <= n; i++)
		lg[i] = log2(i);
}
namespace St1 {

array <vector <int>, N> f;
int query(int x, int y) {
	int len = lg[y - x + 1];
	return min(f[x][len], f[y - (1 << len) + 1][len]);
}
void init(int n) {
	f.fill(vector <int> (21, inf));
	for (int i = 1; i <= n; i++)
		f[i][0] = s[i];
	for (int j = 1; j < 21; j++)
		for (int i = 1; i + (1 << j - 1) <= n; i++)
			f[i][j] = min(f[i][j - 1], f[i + (1 << j - 1)][j - 1]);
}

}
namespace St2 {

array <vector <int>, N> f;
int query(int x, int y) {
	int len = lg[y - x + 1];
	return max(f[x][len], f[y - (1 << len) + 1][len]);
}
void init(int n) {
	f.fill(vector <int> (21, -inf));
	for (int i = 1; i <= n; i++)
		f[i][0] = s[i];
	for (int j = 1; j < 21; j++)
		for (int i = 1; i + (1 << j - 1) <= n; i++)
			f[i][j] = max(f[i][j - 1], f[i + (1 << j - 1)][j - 1]);
}

}
int query(int x, int y) {
	return St2::query(x, y) - St1::query(x, y);
}
array <int, N> f;
signed main() {
	int n = read(), k = read(), m = read();
	for (int i = 1; i <= n; i++)
		s[i] = read();
	init(n);
	St1::init(n), St2::init(n);
	int tp = 0;
	f.fill(inf);
	f[0] = 0;
	for (int i = m; i <= n; i++) {
		while (query(tp + 1, i) > k || (i - tp >= m && f[tp] == inf))
			tp++;
		if (i - tp >= m)
			f[i] = min(f[i], f[tp] + 1);
	}
	write(f[n] == inf ? -1 : f[n]), puts("");
	return 0;
}
