#include <bits/stdc++.h>
struct Matrix {
	int n,m;//n行 m列,最大100*100
	double a[100][100];
	Matrix () {
	}
	Matrix (int _n,int _m) {
		n = _n;
		m = _m;
	}
	Matrix T() {//求转置矩阵
		Matrix ret = Matrix(m,n);
		for (int i=0;i<n;i++)
			for (int j=0;j<m;j++) ret.a[j][i] = a[i][j];
		return ret;
	}
	Matrix operator + (const Matrix &b) {//矩阵加法，需保证b.n==a.n 且 a.m == b.m
		Matrix tmp = Matrix(n,m);
		for (int i=0;i<n;i++) for (int j=0;j<m;j++) tmp.a[i][j] = a[i][j] + b.a[i][j];
		return tmp;
	}
	Matrix operator - (const Matrix &b) {//矩阵减法，需保证b.n==a.n 且 a.m == b.m
		Matrix tmp = Matrix(n,m);
		for (int i=0;i<n;i++) for (int j=0;j<m;j++) tmp.a[i][j] = a[i][j] - b.a[i][j];
		return tmp;
	}
	Matrix operator * (const Matrix &b) {//矩阵乘法，需保证m == b.n
		Matrix tmp = Matrix(n,b.m);
		for (int i=0;i<n;i++)
			for (int j=0;j<b.m;j++) 
				for (int k=0;k<m;k++) tmp.a[i][j] += a[i][k] * b.a[k][j];
		return tmp;
	}
	double val() {//求行列式的值，需保证n==m
		if (n != m) return 0;
		if (n <= 0) return 0;
		if (n == 1) return a[0][0];
		double ans = 0;
		for (int i=0;i<m;i++) {//按第一行展开
			Matrix sub = Matrix(n-1,m-1);
			int _x = 0;
			for (int x=0;x<n;x++) {
				if (x == 0) continue;
				int _y = 0;
				for (int y=0;y<m;y++) {
					if (y == i) continue;
					sub.a[_x][_y] = a[x][y];
					_y ++;
				}
				_x ++;
			}
			ans += (double)pow(-1,1+1+i) * a[0][i] * sub.val();
		}
		return ans;
	}
	Matrix I() {//矩阵求逆，需确保n == m
		Matrix tmp = Matrix(n,m);
		double v = val();
		for (int i=0;i<n;i++)
			for (int j=0;j<m;j++) {
				Matrix sub = Matrix(n-1,m-1);
				int _x = 0;
				for (int x=0;x<n;x++) {
					if (x == i) continue;
					int _y = 0;
					for (int y=0;y<m;y++) {
						if (y == j) continue;
						sub.a[_x][_y] = a[x][y];
						_y ++;
					}
					_x ++;
				}
				tmp.a[i][j] = (double)pow(-1,i+1+j+1) * sub.val() / v;
			}
		return tmp.T();
	}
	void input() {
		scanf("%d%d",&n,&m);
		for (int i=0;i<n;i++) for (int j=0;j<m;j++) scanf("%lf",&a[i][j]);
	}
	void print() {
		for (int i=0;i<n;i++) {
			printf("|");
			for (int j=0;j<n;j++) printf("\t%lf",a[i][j]);
			printf("\t|\n");
		}
	}
};
void help() {
	printf("Usage:\n\t1. 先输入一个操作类型：\n\t\t包含以下几类：\n\t\t1. T:矩阵转置\n\t\t2. A:矩阵加法\n\t\t3. S:矩阵减法\n\t\t4. M:矩阵乘法\n\t\t5. V:行列式求值\n\t\t6. D:矩阵除法\n\t2. 然后输入矩阵\n\t\t按照以下格式：\n\t\tn m\n\t\ta11\ta12\t...\ta1m\n\t\t...\t...\t...\t...\n\t\tan1\tan2\t...\tanm\n\t3. 若操作为A、D、M\n\t\t则再输入一个矩阵，与上面格式相同\n\n\t测试样例：\n\tM\n\n\t2 2\n\n\t1 2\n\t3 4\n\n\t2 2\n\n\t5 6\n\t7 8\n\n");
}
int main() {
	char o;
	scanf(" %c",&o);
	Matrix a,b;
	switch (o) {
		case 'V':
			a.input();
			if (a.n != a.m) perror("你输入的不是一个行列式\n");
			else printf("%lf\n",a.val());
			break;
		case 'T':
			a.input();
			a = a.T();
			a.print();
			break;
		case 'A':
			a.input();
			b.input();
			if (a.n != b.n || a.m != b.m) perror("两个矩阵行数和列数都要相等\n");
			else {
				a = a + b;
				a.print();
			}
			break;
		case 'S':
			a.input();
			b.input();
			if (a.n != b.n || a.m != b.m) perror("两个矩阵行数和列数都要相等\n");
			else {
				a = a - b;
				a.print();
			}
			break;
		case 'M':
			a.input();
			b.input();
			if (a.m != b.n) perror("第一个矩阵的列数必须等于第二个矩阵的行数\n");
			else {
				a = a * b;
				a.print();
			}
			break;
		case 'D':
			a.input();
			b.input();
			if (b.n != b.m) perror("矩阵求逆需要行数和列数相等\n");
			else {
				b = b.I();
				if (a.m != b.n) perror("第一个矩阵的列数必须等于第二个矩阵的行数\n");
				else {
					a = a * b;
					a.print();
				}
			}
			break;
		default:
			help();
			break;
	}
	return 0;
}