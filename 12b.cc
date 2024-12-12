#include <cassert>
#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <tuple>
#include <vector>

namespace {

  int count_sides_h(std::vector<std::tuple<int, int>>& neighbors) {
    std::sort(neighbors.begin(), neighbors.end(), [](const std::tuple<int, int>& lhs, const std::tuple<int, int>& rhs) {
      return lhs < rhs;
    });

    auto [ i, j ] = neighbors.front();
    int count = 1;

    for (std::size_t k = 1; k < neighbors.size(); ++k) {
      auto [ curri, currj ] = neighbors[k];

      if (curri == i && currj == j + 1) {
        j = currj;
      } else {
        ++count;
        i = curri;
        j = currj;
      }
    }

    return count;
  }

  int count_sides_v(std::vector<std::tuple<int, int>>& neighbors) {
    std::sort(neighbors.begin(), neighbors.end(), [](const std::tuple<int, int>& lhs, const std::tuple<int, int>& rhs) {
      return std::tie(std::get<1>(lhs), std::get<0>(lhs)) < std::tie(std::get<1>(rhs), std::get<0>(rhs));
    });

    auto [ i, j ] = neighbors.front();
    int count = 1;

    for (std::size_t k = 1; k < neighbors.size(); ++k) {
      auto [ curri, currj ] = neighbors[k];

      if (currj == j && curri == i + 1) {
        i = curri;
      } else {
        ++count;
        i = curri;
        j = currj;
      }
    }

    return count;
  }

}

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

      std::vector<std::tuple<int, int>> top;
      std::vector<std::tuple<int, int>> down;
      std::vector<std::tuple<int, int>> left;
      std::vector<std::tuple<int, int>> right;

      while (!queue.empty()) {
        region.push_back(queue.front());

        auto [ curri, currj ] = queue.front();
        queue.pop();

        auto check_neighbor = [&](int ni, int nj, std::vector<std::tuple<int, int>>& neighbors) {
          char& neighbor = map[ni][nj];

          if (neighbor == type) {
            neighbor = '#';
            queue.push({ ni, nj });
          } else {
            if (neighbor != '#') {
              neighbors.emplace_back(ni, nj);
            }
          }
        };

        if (curri > 0) {
          check_neighbor(curri - 1, currj, top);
        } else {
          top.emplace_back(curri - 1, currj);
        }

        if (curri < isize - 1) {
          check_neighbor(curri + 1, currj, down);
        } else {
          down.emplace_back(curri + 1, currj);
        }

        if (currj > 0) {
          check_neighbor(curri, currj - 1, left);
        } else {
          left.emplace_back(curri, currj - 1);
        }

        if (currj < jsize - 1) {
          check_neighbor(curri, currj + 1, right);
        } else {
          right.emplace_back(curri, currj + 1);
        }
      }

      int area = int(region.size());


      for (auto [ curri, currj ] : region) {
        map[curri][currj] = ' ';
      }

      int sides = count_sides_h(top) + count_sides_h(down) + count_sides_v(left) + count_sides_v(right);

      std::cout << type << ' ' << area << ' ' << sides << '\n';

      price += area * sides;
    }
  }

  std::cout << price << '\n';
}
