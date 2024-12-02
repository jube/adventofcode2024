#include <cassert>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

int main() {

  std::vector<std::vector<int>> reports;

  for (std::string line; std::getline(std::cin, line); ) {
    if (line.empty() || line == "\n") {
      continue;
    }

    std::vector<int> report;

    std::istringstream is(line);
    int level;

    while (is >> level) {
      report.push_back(level);
    }

    reports.push_back(std::move(report));
  }

  auto count = std::count_if(reports.begin(), reports.end(), [&](const std::vector<int>& report) {

    auto is_good = [](const std::vector<int>& report) {
      std::vector<int> differences;
      std::adjacent_difference(report.begin(), report.end(), std::back_inserter(differences));
      differences.erase(differences.begin());

      return (std::is_sorted(report.begin(), report.end(), std::less<int>()) || std::is_sorted(report.begin(), report.end(), std::greater<int>()))
      && std::all_of(differences.begin(), differences.end(), [](int difference) { return 1 <= std::abs(difference) && std::abs(difference) <= 3; });
    };

    if (is_good(report)) {
      return true;
    }

    for (std::size_t i = 0; i < report.size(); ++i) {
      auto copy = report;
      copy.erase(copy.begin() + i);

      if (is_good(copy)) {
        return true;
      }
    }

    return false;
  });

  std::cout << count << '\n';
}
