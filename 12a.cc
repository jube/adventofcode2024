#include <cassert>
#include <iostream>
#include <queue>
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

  int isize = int(map.size());
  int jsize = int(map.front().size());

  int price = 0;

  for (int i = 0; i < isize; ++i) {
    for (int j = 0; j < jsize; ++j) {
      if (map[i][j] == ' ') {
        continue;
      }

      const char type = map[i][j];

      std::queue<std::tuple<int, int>> queue;
      map[i][j] = '#';
      queue.push({ i, j });

      std::vector<std::tuple<int, int>> region;
      int perimeter = 0;

      while (!queue.empty()) {
        region.push_back(queue.front());

        auto [ curri, currj ] = queue.front();
        queue.pop();

        auto check_neighbor = [&](int ni, int nj) {
          char& neighbor = map[ni][nj];

          if (neighbor == type) {
            neighbor = '#';
            queue.push({ ni, nj });
          } else {
            if (neighbor != '#') {
              ++perimeter;
            }
          }
        };

        if (curri > 0) {
          check_neighbor(curri - 1, currj);
        } else {
          ++perimeter;
        }

        if (curri < isize - 1) {
          check_neighbor(curri + 1, currj);
        } else {
          ++perimeter;
        }

        if (currj > 0) {
          check_neighbor(curri, currj - 1);
        } else {
          ++perimeter;
        }

        if (currj < jsize - 1) {
          check_neighbor(curri, currj + 1);
        } else {
          ++perimeter;
        }
      }

      int area = int(region.size());

      for (auto [ curri, currj ] : region) {
        map[curri][currj] = ' ';
      }

      std::cout << type << ' ' << area << ' ' << perimeter << '\n';

      price += area * perimeter;
    }
  }

  std::cout << price << '\n';
}
