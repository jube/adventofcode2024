#include <cassert>
#include <charconv>
#include <iostream>
#include <string>

constexpr bool is_digit(char c) {
  return '0' <= c && c <= '9';
}

int main() {

  int total = 0;

  for (std::string line; std::getline(std::cin, line); ) {
    if (line.empty() || line == "\n") {
      continue;
    }

    std::size_t pos = 0;

    for (;;) {
      std::size_t found = line.find("mul(", pos);

      if (found == std::string::npos) {
        break;
      }


      found += 4;
      std::size_t first_begin = found;

      while (found < line.size() && is_digit(line[found])) {
        ++found;
      }

      if (found == line.size()) {
        break;
      }

      std::size_t first_end = found;

      if (line[found] == ',') {
        ++found;
      } else {
        pos = found;
        continue;
      }

      std::size_t second_begin = found;

      while (found < line.size() && is_digit(line[found])) {
        ++found;
      }

      if (found == line.size()) {
        break;
      }

      std::size_t second_end = found;

      if (line[found] == ')') {
        ++found;
      } else {
        pos = found;
        continue;
      }

      std::cout << line.substr(first_begin - 4, second_end - first_begin + 5) << ' ';

      int first;
      std::from_chars(&line[first_begin], &line[first_end], first);
      int second;
      std::from_chars(&line[second_begin], &line[second_end], second);

      std::cout << first << ' ' << second << '\n';

      total += first * second;

      pos = found;
    }

  }

  std::cout << total << '\n';
}
