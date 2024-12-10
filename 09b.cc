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

  for (;;) {
    --id;

    if (id < 0) {
      break;
    }

    auto iterator_start = std::find(memory.begin(), memory.end(), id);
    auto iterator_end = iterator_start;

    while (iterator_end != memory.end() && *iterator_end == id) {
      ++iterator_end;
    }

    auto size = iterator_end - iterator_start;
    const std::vector<int> free_block(size, -1);

    auto iterator_free = std::search(memory.begin(), memory.end(), free_block.begin(), free_block.end());

    if (iterator_free == memory.end() || iterator_free > iterator_start) {
      continue;
    }

    std::swap_ranges(iterator_start, iterator_end, iterator_free);
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

