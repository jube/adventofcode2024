#include <cassert>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

constexpr std::tuple<int, int> Directions[] = { { 1, 0 }, { 1, -1 }, { 0, -1 }, { -1, -1 }, { -1, 0 }, { -1, 1 }, { 0, 1 }, { 1, 1 } };

int main() {

  std::vector<std::string> input;

  for (std::string line; std::getline(std::cin, line); ) {
    if (line.empty() || line == "\n") {
      continue;
    }

    input.push_back(std::move(line));
  }

  int count = 0;

  assert(!input.empty());

  [[maybe_unused]] const std::size_t sz = input.front().size();

  for (std::size_t i = 0; i < input.size(); ++i) {
    assert(input[i].size() == sz);

    for (std::size_t j = 0; j < input[i].size(); ++j) {
      if (input[i][j] != 'X') {
        continue;
      }

      for (auto [ di, dj ] : Directions ) {
        if (int(i) + 3 * di < 0) {
          continue;
        }

        if (int(i) + 3 * di >= int(input.size())) {
          continue;
        }

        if (int(j) + 3 * dj < 0) {
          continue;
        }

        if (int(j) + 3 * dj >= int(input[i].size())) {
          continue;
        }

        // std::cout << int(i) + 3 * di << ',' << int(j) + 3 * dj << '\n';

        if (input[int(i) + 1 * di][int(j) + 1 * dj] == 'M'
         && input[int(i) + 2 * di][int(j) + 2 * dj] == 'A'
         && input[int(i) + 3 * di][int(j) + 3 * dj] == 'S') {
          ++count;
        }
      }
    }
  }

  std::cout << count << '\n';

}
