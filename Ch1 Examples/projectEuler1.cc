#include <iostream>

int main() {
  // Running sum
  int sum = 0;

  // Loop
  for (int i = 0; i < 1000; i++) {
    if (i % 3 == 0) {
      sum += i;
    } else if (i % 5 == 0) {
      sum += i;
    }
  }

  // After all is done, print the result.
  std::cout << "Final Sum: " << sum << std::endl;
}