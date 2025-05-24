#include <stdio.h>

int main(void)
{
int n = 0;
int power = 1;
printf("%12s%12s%12s\n", "n ", "2**n ", "2**n");
printf("%12s%12s%12s\n", "decimal", "decimal", "hex ");
while (n <= 16) {
printf("%12d%12d%12x\n", n, power, power);
power = power + power;
n++;
}
return 0;
}