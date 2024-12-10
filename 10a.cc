#include <cassert>
#include <iostream>
#include <set>
#include <string>
#include <tuple>
#include <vector>

int main() {

  std::vector<std::string> map;

  for (std::string line; std::getline(std::cin, line); ) {
    if (line.empty() || line == "\n") {
      continue;
    }

    map.push_back(std::move(line));
  }

  const int isize = int(map.size());
  const int jsize = int(map.front().size());

  std::size_t sum = 0;

  for (int i = 0; i < isize; ++i) {
    for (int j = 0; j < jsize; ++j) {
      if (map[i][j] != '0') {
        continue;
      }

      char current = '0';
      std::set<std::tuple<int, int>> step;
      step.emplace(i, j);

      while (current != '9') {
        ++current;
        std::set<std::tuple<int, int>> next_step;

        std::cout << current << " - > ";
        for (auto [ icurr, jcurr ] : step) {
          std::cout << icurr << ',' << jcurr << ' ';
        }
        std::cout << '\n';

        for (auto [ icurr, jcurr ] : step) {
          if (icurr > 0) {
            if (map[icurr - 1][jcurr] == current) {
              next_step.emplace(icurr - 1, jcurr);
            }
          }

          if (icurr < isize - 1) {
            if (map[icurr + 1][jcurr] == current) {
              next_step.emplace(icurr + 1, jcurr);
            }
          }

          if (jcurr > 0) {
            if (map[icurr][jcurr - 1] == current) {
              next_step.emplace(icurr, jcurr - 1);
            }
          }

          if (jcurr < jsize - 1) {
            if (map[icurr][jcurr + 1] == current) {
              next_step.emplace(icurr, jcurr + 1);
            }
          }
        }

        step = std::move(next_step);
      }

      sum += step.size();
    }
  }

  std::cout << sum << '\n';
}
