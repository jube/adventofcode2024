#include <cassert>
#include <charconv>
#include <iostream>
#include <string>

constexpr bool is_digit(char c) {
  return '0' <= c && c <= '9';
}

int main() {

  int total = 0;
  bool enabled = true;

  for (std::string line; std::getline(std::cin, line); ) {
    if (line.empty() || line == "\n") {
      continue;
    }

    std::size_t pos = 0;

    for (;;) {
      if (!enabled) {
        std::size_t found_do = line.find("do()", pos);

        if (found_do == std::string::npos) {
          break;
        }

        enabled = true;
        pos = found_do + 4;
      }

      std::size_t found_dont = line.find("don't()", pos);
      std::size_t found_mul = line.find("mul(", pos);

      if (found_dont < found_mul) {
        enabled = false;
        pos = found_dont + 7;
        continue;
      }

      if (found_mul == std::string::npos) {
        break;
      }

      found_mul += 4;
      std::size_t first_begin = found_mul;

      while (found_mul < line.size() && is_digit(line[found_mul])) {
        ++found_mul;
      }

      if (found_mul == line.size()) {
        break;
      }

      std::size_t first_end = found_mul;

      if (line[found_mul] == ',') {
        ++found_mul;
      } else {
        pos = found_mul;
        continue;
      }

      std::size_t second_begin = found_mul;

      while (found_mul < line.size() && is_digit(line[found_mul])) {
        ++found_mul;
      }

      if (found_mul == line.size()) {
        break;
      }

      std::size_t second_end = found_mul;

      if (line[found_mul] == ')') {
        ++found_mul;
      } else {
        pos = found_mul;
        continue;
      }

      std::cout << line.substr(first_begin - 4, second_end - first_begin + 5) << ' ';

      int first;
      std::from_chars(&line[first_begin], &line[first_end], first);
      int second;
      std::from_chars(&line[second_begin], &line[second_end], second);

      std::cout << first << ' ' << second << '\n';

      total += first * second;

      pos = found_mul;
    }

  }

  std::cout << total << '\n';
}
