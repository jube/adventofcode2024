#include <cassert>
#include <cstdint>
#include <charconv>
#include <iostream>
#include <string>
#include <vector>

namespace {

  std::vector<std::string_view> split_string(std::string_view string, char delimiter)
  {
    const std::size_t size = string.size();
    std::size_t i = 0;
    std::vector<std::string_view> result;

    while (i < size) {
      while (i < size && string[i] == delimiter) {
        ++i;
      }

      if (i == size) {
        break;
      }

      const char* start = string.data() + i;
      size_t length = 0;

      while (i < size && string[i] != delimiter) {
        ++i;
        ++length;
      }

      result.emplace_back(start, length);
    }

    return result;
  }

  uint64_t log10(uint64_t value)
  {
    if (value == 0) {
      return 1;
    }

    uint64_t res = 0;

    while (value > 0)
    {
      ++res;
      value /= 10;
    }

    return res;
  }

  uint64_t exp10(uint64_t value)
  {
    uint64_t res = 1;

    for (uint64_t i = 0; i < value; ++i)
    {
      res *= 10;
    }

    return res;
  }

}

int main() {

  std::vector<uint64_t> input;

  for (std::string line; std::getline(std::cin, line); ) {
    if (line.empty() || line == "\n") {
      continue;
    }

    auto parts = split_string(line, ' ');

    for (auto part : parts) {
      uint64_t x;
      std::from_chars(part.begin(), part.end(), x);
      input.push_back(x);
    }

    break;
  }

  for (int i = 0; i < 25; ++i) {
    std::vector<uint64_t> next;

    for (auto x : input) {
      if (x == 0) {
        next.push_back(1);
      } else {
        auto size = log10(x);

        if (size % 2 == 0) {
          const uint64_t base = exp10(size / 2);

          uint64_t hi = x / base;
          uint64_t lo = x % base;

          next.push_back(hi);
          next.push_back(lo);
        } else {
          next.push_back(x * 2024);
        }
      }
    }

    input = std::move(next);

    // for (auto x : input) {
    //   std::cout << x << ' ';
    // }
    // std::cout << '\n';
  }

  std::cout << input.size() << '\n';
}
