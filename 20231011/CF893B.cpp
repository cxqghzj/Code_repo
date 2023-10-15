#include <iostream>
#include <algorithm>
#include <cstdio>
#include <array>
#include <vector>
#include <map>
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
vector <int> isl;
map <int, int> vis;
signed main() {
	for (int i = 1; i <= 20; i++)
		vis[(long long)(1 << (i - 1)) * (long long)((1 << i) - 1)] = 1;
	int n = read();
	isl.push_back(1);
	isl.push_back(n);
	for (int i = 2; i * i <= n; i++) {
		if (n % i) continue;
		isl.push_back(i);
		isl.push_back(n / i);
	}
	sort(isl.begin(), isl.end(), greater <int>());
	for (auto x : isl) {
		/* write(x), puts(""); */
		if (vis[x]) {
			write(x), puts("");
			return 0;
		}
	}
	return 0;
}
