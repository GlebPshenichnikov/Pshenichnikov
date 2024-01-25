#include <stdio.h>

double str2double(char str[]) {
  double ans = 0,k = 1;
  int i = 0;
  char zn;
  while (str[i] != '.' && str[i] != 'E' && str[i] != 'e' && str[i] != '\0') {
    ans = ans * 10 + str[i] - '0';
    i += 1;
  }
  if (str[i] == '.') {
    i += 1;
    while (str[i] != '\0' && str[i] != 'E' && str[i] != 'e') {
      k /= 10;
      ans = ans * 10 + str[i] - '0';
      i += 1;
    }
  }
  if (str[i] != '\0') {
      i++ ;
      
      if (str[i] == '+' || str[i] == '-'){
          zn = str[i];
          i++;
      }
      else
          zn = '+';

    int s = 0;
    while (str[i] != '\0' && str[i] != 'F' && str[i] != 'f') {
      s = s * 10 + str[i] - '0';
      i += 1;
    }
    if (zn == '+')
      for (i = 0; i < s; i++)
        k *= 10;
    else
      for (i = 0; i < s; i++)
        k /= 10;
  }
  return ans * k;
}

int main() {
  char a[255];
  while (scanf("%s", a) != EOF) {
    printf("%.10f\n", str2double(a));
  }
}
