#include <stdio.h>




void MyFunc(int &ii)
{
    int k = 1;
    int kk = 1;
    printf("3: %p\n", &k);
    printf("3: %ld\n", (&k-&ii) * sizeof(int));

    printf("3: %p\n", &kk);
    printf("3: %ld\n", (&kk-&ii) * sizeof(int));
}

int main(){
    int ii = 0;

    printf("0: %p\n", &ii);

    int i = 1;
    printf("1: %p\n", &i);
    printf("1: %ld\n", (&i-&ii) * sizeof(int));

    int j = 1;
    printf("2: %p\n", &j);
    printf("2: %ld\n", (&j-&ii) * sizeof(int));

    MyFunc(ii);

    int l = 1;
    printf("4: %p\n", &l);
    printf("4: %ld\n", (&l-&ii) * sizeof(int));

    return 0;
}