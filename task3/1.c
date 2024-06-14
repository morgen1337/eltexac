#include <stdio.h>

void change3bit(int *numb){
    char *bytes = (char*)numb;
    int new_value;
    scanf("%d", &new_value);
    if (new_value < 0 || new_value > 255) {
        printf("Неверное значение. Должно быть в диапазоне 0-255.\n");
    } else {
        bytes[2] = (char)new_value;
    }
}

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
}

int main(){
    int numb;
    scanf("%d", &numb);
    binaryprint(numb);
    printf("\n");
    change3bit(&numb);
    binaryprint(numb);
    return 0;
}