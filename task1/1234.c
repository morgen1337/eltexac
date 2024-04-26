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
            printf("  "); 
    }
    printf("\nNumber of 1 - %d\n", count1);
}

void change3bit(int* x){
    int bits = sizeof(int) * 8;
    uint8_t byte3;
    if (bits < 24)
        return;
    scanf("%hhd", &byte3);
    *x = (*x & 0xff0f) | (byte3 << 8);
}

int main(){
    int x;
    scanf("%d", &x);
    binaryprint(x);
    if (x >= 0){
    change3bit(&x);
    binaryprint(x);
    }
    return 0;
}