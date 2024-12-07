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

  struct Input {
    uint64_t result;
    std::vector<uint64_t> numbers;
  };

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

  uint64_t concat(uint64_t lhs, uint64_t rhs)
  {
    uint64_t shift = log10(rhs);
    return lhs * exp10(shift) + rhs;
  }

  bool can_be_computed_rec(const Input& input, std::size_t index, std::size_t accum)
  {
    // std::cout << index << ' ' << accum << '\n';

    if (index == input.numbers.size()) {
      return accum == input.result;
    }

    if (accum > input.result) {
      return false;
    }

    if (can_be_computed_rec(input, index + 1, accum + input.numbers[index])) {
      return true;
    }

    if (can_be_computed_rec(input, index + 1, concat(accum, input.numbers[index]))) {
      return true;
    }

    return can_be_computed_rec(input, index + 1, accum * input.numbers[index]);
  }

  bool can_be_computed(const Input& input)
  {
    return can_be_computed_rec(input, 1, input.numbers[0]);
  }

}

int main() {
  // std::cout << concat(1, 56) << '\n';

  std::vector<Input> inputs;

  for (std::string line; std::getline(std::cin, line); ) {
    if (line.empty() || line == "\n") {
      continue;
    }

    Input input = {};

    auto parts = split_string(line, ':');
    assert(parts.size() == 2);

    std::from_chars(parts[0].begin(), parts[0].end(), input.result);

    auto numbers = split_string(parts[1], ' ');

    for (auto number : numbers) {
      uint64_t value = 0;
      std::from_chars(number.begin(), number.end(), value);
      input.numbers.push_back(value);
    }

    inputs.push_back(std::move(input));
  }

  // std::cout << inputs.size() << '\n';

  uint64_t sum = 0;

  for (auto& input : inputs) {
    if (can_be_computed(input)) {
      sum += input.result;
    }
  }

  std::cout << sum << '\n';
}
