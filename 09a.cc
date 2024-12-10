#include <cassert>
#include <cstdint>
#include <algorithm>
#include <charconv>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

int main() {

  std::string input;

  for (std::string line; std::getline(std::cin, line); ) {
    if (line.empty() || line == "\n") {
      continue;
    }

    input = line;
  }

  std::cout << input.size() << '\n';
  bool file = true;

  int id = 0;
  std::vector<int> memory;

  for (auto c : input) {
    if (file) {
      memory.insert(memory.end(), c - '0', id);
      ++id;
    } else {
      if (c > '0') {
        memory.insert(memory.end(), c - '0', -1);
      }
    }

    file = !file;
  }

  std::cout << memory.size() << '\n';

  std::size_t i = 0;
  std::size_t j = memory.size() - 1;

  for (;;) {
    while (memory[i] != -1) {
      ++i;
    }

    while (memory[j] == -1) {
      --j;
    }

    if (i > j) {
      break;
    }

    std::swap(memory[i], memory[j]);
  }

  for (auto x : memory) {
    if (x == -1) {
      std::cout << '.';
    } else {
      std::cout << x;
    }
  }
  std::cout << '\n';

  uint64_t checksum = 0;

  for (uint64_t block = 0; block < memory.size(); ++block) {
    if (memory[block] != -1) {
      checksum += block * memory[block];
    }
  }

  std::cout << checksum << '\n';
}

