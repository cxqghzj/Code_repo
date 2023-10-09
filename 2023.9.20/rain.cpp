#include <iostream>
#include <algorithm>
#include <cstdio>
#include <array>
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
array <int, N> s, isl;
signed main() {
	freopen("rain.in", "r", stdin);
	freopen("rain.out", "w", stdout);
	int n = read(), res = 0;
	for (int i = 1; i <= n; i++)
		s[i] = read(), res += s[i];
	int tp0 = 0;
	for (int i = 1; i < n; i += 2)
		tp0 += s[i] * 2;
	isl[n] = res - tp0;
	for (int i = n - 1; i; i--)
		isl[i] = s[i] * 2 - isl[i + 1];
	for (int i = 1; i <= n; i++)
		write(isl[i]), putchar(32);
	puts("");
	return 0;
}
