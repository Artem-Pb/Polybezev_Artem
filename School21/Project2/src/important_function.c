#include <stdio.h>
#include <math.h> 

double calculate_function(double x);

int main() {
   double x;
   while (scanf("%lf", &x) != 1) {
       printf("n/a\n");
       return 1;
   }
   double result = calculate_function(x);

   if (isnan(result)) {
       printf("n/a\n ");
   } else {
       printf("%.1lf", result);
   }
   return 0;
}

double calculate_function(double x) {
    if (x == 0) {
        return NAN;
    }

    double part1= 7e-3 * pow(x, 4);
    double cube_root = (x < 0) ? -pow(-x, 1.0/3) : pow(x, 1.0/3);
    double numerator =  (22.8 * cube_root - 1e3) * x + 3;
    double denominator = (x * x) / 2;
    double part2 = numerator / denominator;
    double exponent = 2 / x;
    double part3 = x * pow(10 + x, exponent);

    return part1 + part2 - part3 - 1.01;
}
