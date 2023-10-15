#include <iostream>
#include <algorithm>
#include <cstdio>
#include <array>
#include <bitset>
#include <set>
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
const int N = 1e5 + 5;
array <int, N> s;
bitset <N> vis;
multiset <int, greater <int> > isl;
signed main() {
	int n = read(), d = read();
	for (int i = 1; i <= n; i++) {
		s[i] = read();
		if (!s[i]) vis[i] = 1;
		s[i] += s[i - 1];
		isl.insert(s[i]);
		if (s[i] > d) {
			puts("-1");
			return 0;
		}
	}
	for (int i = 1; i <= n; i++)
		write(s[i]), putchar(32);
	puts("");
	int pos = 0, ans = 0;
	for (int i = 1; i <= n; i++) {
		isl.erase(s[i]);
		if (!vis[i] || pos + s[i] >= 0) continue;
		if (isl.size() && d - *isl.begin() < -s[i]) {
			write(*isl.begin()), puts("");
			puts("-1");
			return 0;
		}
		ans++, pos += d - *isl.begin() - pos;
	}
	write(ans), puts("");
	return 0;
}
