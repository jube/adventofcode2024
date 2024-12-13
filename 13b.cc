#include <cassert>
#include <charconv>
#include <iostream>
#include <string>
#include <vector>

namespace {

  struct Input {
    long xA, yA;
    long xB, yB;
    long xP, yP;
  };

}

int main() {

  std::vector<Input> inputs;
  Input current = {};

  for (std::string line; std::getline(std::cin, line); ) {
    if (line.empty() || line == "\n") {
      continue;
    }

    if (line.substr(0, 9) == "Button A:") {
      auto x = line.find(',', 12);
      std::from_chars(line.data() + 12, line.data() + x, current.xA);
      std::from_chars(line.data() + x + 4, line.data() + line.size(), current.yA);
      // std::cout << "xA: " << current.xA << ' ' << "yA: " << current.yA << '\n';
    } else if (line.substr(0, 9) == "Button B:") {
      auto x = line.find(',', 12);
      std::from_chars(line.data() + 12, line.data() + x, current.xB);
      std::from_chars(line.data() + x + 4, line.data() + line.size(), current.yB);
      // std::cout << "xB: " << current.xB << ' ' << "yB: " << current.yB << '\n';
    } else {
      assert(line.substr(0, 6) == "Prize:");
      auto x = line.find(',', 9);
      std::from_chars(line.data() + 9, line.data() + x, current.xP);
      std::from_chars(line.data() + x + 4, line.data() + line.size(), current.yP);
      // std::cout << "xP: " << current.xP << ' ' << "yP: " << current.yP << '\n';

      inputs.push_back(current);
    }
  }

  long tokens = 0;

  for (auto input : inputs) {
    input.xP += 10000000000000;
    input.yP += 10000000000000;

    // https://en.wikipedia.org/wiki/Cramer%27s_rule#Explicit_formulas_for_small_systems
    long det = input.xA * input.yB - input.xB * input.yA;

    if (det == 0) {
      std::cout << "det = 0\n";
      continue;
    }

    long count_a = (input.xP * input.yB - input.xB * input.yP);

    if (count_a % det != 0) {
      std::cout << "count_a % det != 0\n";
      continue;
    }

    assert(count_a % det == 0);
    count_a /= det;

    long count_b = (input.xA * input.yP - input.xP * input.yA);

    if (count_b % det != 0) {
      std::cout << "count_b % det != 0\n";
      continue;
    }

    assert(count_b % det == 0);
    count_b /= det;

    if (count_a < 0 || count_b < 0) {
      std::cout << "outside range\n";
      continue;
    }

    std::cout << count_a << ' ' << count_b << '\n';

    tokens += 3 * count_a + count_b;
  }

  std::cout << tokens << '\n';
}
