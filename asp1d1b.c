#include <stdio.h>
#include <stdbool.h>

int m, n, b;

void stvaranje(int c[], int r[], int v[]) {
    int k;
    int p=0;
    c[0]=1;
    while (p<b){
        for (int i=0;i<n;i++) {
            c[i+1]=c[i];
            for (int j=0;j<m;j++){
                scanf("%d", &k);
                if (k!=0) {
                    c[i+1]++;
                    r[p]=j+1;
                    v[p]=k;
                    p++;
                }
            }
        }
    }
}

int element (int c[], int r[], int v[], int x, int y) {
    for (int i=c[x-1];i<c[x];i++) {
        if (r[i-1]==y) {
            return v[i-1];
        }
    }
    return 0;
}

void ispis (int c[], int r[], int v[]) {
    for (int i=1; i<=m; i++) {
        for (int j=1; j<=n; j++) {
            printf("%d ", element(c, r, v, j, i));
        }
        printf("\n");
    }
}

void sabiranje (int c[], int r[], int v[]) {
    int m1, n1, b1;
    printf("unesite drugu matricu:\n");
    scanf("%d %d %d", &m1, &n1, &b1);
    if (m!=m1 || n!=n1 || b1<1) {
        printf("lose unete dimenzije\n");
        return;
    }
    int c1 [n+1];
    int r1 [b+b1];
    int v1 [b+b1];
    int k;
    int p=0;
    c1[0]=1;
    while (p<b1){
        for (int i=1;i<=n;i++) {
            c1[i]=c1[i-1];
            for (int j=1;j<=m;j++){
                scanf("%d", &k);
                int t=element(c, r, v, i, j);
                if (k+t!=0) {
                    c1[i]++;
                    r1[p]=j;
                    v1[p]=k+t;
                    p++;
                }
            }
        }
    }
    ispis(c1, r1, v1);
}

int main() {
    int k;
    bool t=false;
    printf("unesite matricu:\n");
    while (true) {
        scanf("%d %d %d", &m, &n, &b);
        if (m<1 || n<1 || b<1) {
            printf("lose unete dimenzije\n");
        }
        else
            break;
    }
    int c [n+1];
    int r [b];
    int v [b];
    stvaranje(c, r, v);
    t=true;
    printf("1 provera vrednosti odredjenog elementa\n2 ispis matrice\n"
           "3 sabiranje unete matrice sa drugom \n4 izlaz\n");
    while (true) {
        printf("izaberite stavku iz menija:\n");
        scanf("%d", &k);
        if (t) {
            switch (k) {
                case 1:
                    printf("unesite koordinate elementa\n");
                    int x, y;
                    while (true) {
                        scanf("%d %d", &x, &y);
                        if (x<1 || y<1 || x>n || y>m)
                            printf("lose unete koordinate\n");
                        else
                            break;
                    }
                    printf("%d\n",element(c, r, v, x, y));
                    break;
                case 2:
                    ispis(c, r, v);
                    break;
                case 3:
                    sabiranje(c, r, v);
                    break;
                case 4:
                    return 0;
            }
        }
    }
}