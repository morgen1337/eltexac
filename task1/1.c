#include <stdio.h>
#include <stdint.h>

void binaryprint(int x){
    int count1 = 0;
    int bit;
    for (int i = sizeof(x) * 8 - 1; i >= 0; i--){
        bit = (x >> i) & 0b01;
        printf("%d", bit);
        if (bit)
            count1++;
        if (i % 8 == 0)
            printf(" "); 
    }
}

int main(){
    int x;
    scanf("%d", &x);
    binaryprint(x);
    return 0;
}