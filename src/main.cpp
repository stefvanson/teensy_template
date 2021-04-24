#include <stdio.h>
#include <Arduino.h>

#include "module1/module1.hpp"

int main(int argc, char *argv[]) {
  int res = module1_function(0);
  printf("Result = %i\n", res);
  return res;
}
