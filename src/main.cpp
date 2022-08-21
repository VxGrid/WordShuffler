#include <algorithm>
#include <iostream>
#include <iterator>
#include <random>
#include <string>
#include <vector>

int main()
{
  std::string in{"Hallooooo zurück und als Rache werde ich jedes Wort welches ich schreibe wild durcheinander wirbeln ( ausser den ersten und letzten Buchstaben, sonst kann man es nicht mehr lesen )"};
  std::vector<std::string> inSplit;

  auto firstIt = std::begin(in);
  auto lastIt = firstIt--;
  while (firstIt != std::end(in))
  {
    lastIt = std::find(++firstIt, std::end(in), ' ');
    inSplit.emplace_back(std::string(firstIt, lastIt));
    firstIt = lastIt;
  }

  std::random_device rd;
  std::mt19937 g(rd());

  for (auto &str : inSplit)
  {

    if (str.size() < 4)
      continue;

    std::cout << "str is: " << str << " - ";
    std::shuffle(str.begin() + 1, str.end() - 1, g);
    std::cout << str << '\n';
  }

  for (const auto &str : inSplit)
  {
    std::cout << str << ' ';
  }
  std::cout << std::endl;

  return 0;
}
