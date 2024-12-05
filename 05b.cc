#include <cassert>
#include <algorithm>
#include <charconv>
#include <iostream>
#include <map>
#include <set>
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

}

int main() {

  std::map<unsigned, std::set<unsigned>> orders;

  for (std::string line; std::getline(std::cin, line); ) {
    if (line.empty() || line == "\n") {
      break;
    }

    auto parts = split_string(line, '|');
    assert(parts.size() == 2);

    unsigned first, second;

    std::from_chars(parts[0].begin(), parts[0].end(), first);
    std::from_chars(parts[1].begin(), parts[1].end(), second);

    orders[first].insert(second);
  }

  std::vector<std::vector<unsigned>> sequences;

  for (std::string line; std::getline(std::cin, line); ) {
    if (line.empty() || line == "\n") {
      break;
    }

    auto parts = split_string(line, ',');

    std::vector<unsigned> sequence;

    for (auto part : parts) {
      unsigned number;
      std::from_chars(part.begin(), part.end(), number);
      sequence.push_back(number);
    }

    sequences.push_back(std::move(sequence));
  }

  // std::cout << orders.size() << ' ' << sequences.size() << '\n';

  unsigned total = 0;

  for (const auto& sequence : sequences) {
    bool good = true;

    for (std::size_t i = 0; i < sequence.size(); ++i) {
      if (i > 0) {
        for (std::size_t j = 0; j < i - 1; ++j) {
          if (auto iterator = orders.find(sequence[i]); iterator != orders.end()) {
            auto& next = iterator->second;

            if (next.find(sequence[j]) != next.end()) {
              good = false;
            }
          }
        }
      }

      if (i + 1 < sequence.size()) {
        for (std::size_t j = i + 1; j < sequence.size(); ++j) {
          if (auto iterator = orders.find(sequence[j]); iterator != orders.end()) {
            auto& next = iterator->second;

            if (next.find(sequence[i]) != next.end()) {
              good = false;
            }
          }
        }
      }
    }

    if (!good) {
      auto copy = sequence;

      std::sort(copy.begin(), copy.end(), [&orders](unsigned lhs, unsigned rhs) {
        if (auto iterator = orders.find(lhs); iterator != orders.end()) {
          auto& next = iterator->second;

          if (next.find(rhs) != next.end()) {
            return true;
          }
        }

        return false;
      });

      total += copy[copy.size() / 2];
    }
  }

  std::cout << total << '\n';

}
