#include <cassert>
#include <iostream>
#include <string>
#include <vector>

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

  for (std::size_t i = 1; i < input.size() - 1; ++i) {
    assert(input[i].size() == sz);

    for (std::size_t j = 1; j < input[i].size() - 1; ++j) {
      if (input[i][j] != 'A') {
        continue;
      }

      if (((input[i + 1][j + 1] == 'M' && input[i - 1][j - 1] == 'S') || (input[i + 1][j + 1] == 'S' && input[i - 1][j - 1] == 'M'))
        && ((input[i + 1][j - 1] == 'M' && input[i - 1][j + 1] == 'S') || (input[i + 1][j - 1] == 'S' && input[i - 1][j + 1] == 'M'))) {
        ++count;
      }

    }
  }

  std::cout << count << '\n';

}
