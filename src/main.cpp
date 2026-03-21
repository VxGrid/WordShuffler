#include <algorithm>
#include <iostream>
#include <iterator>
#include <random>
#include <string>
#include <vector>

std::vector<std::string> splitString(const std::string str)
{
    /// FIXME: Split strings special characters, like ,./( not with it
    std::vector<std::string> inSplit;
    auto firstIt = std::begin(str);
    auto lastIt = firstIt--;

    while (firstIt != std::end(str))
    {
        lastIt = std::find(++firstIt, std::end(str), ' ');
        inSplit.emplace_back(std::string(firstIt, lastIt));
        firstIt = lastIt;
    }

    return inSplit;
}

std::string shuffled(std::vector<std::string> &shuffledPieces)
{
    std::random_device rd;
    std::mt19937 g(rd());

    for (auto &str : shuffledPieces)
    {
        if (str.size() < 4)
            continue;

        //std::cout << "str is: " << str << " - ";
        std::shuffle(str.begin() + 1, str.end() - 1, g);
        //std::cout << str << '\n';
    }

    std::string out;

    for (auto &str : shuffledPieces)
    {
        out += str;
        out += ' ';
    }

    out.pop_back();
    return out;
}


int main(int argc, char* argv[])
{
    /// TODO: If user inserts text directly as command, just adapt this and return
    if (argc == 2)
    {
    }

    /// TODO: Write this all as a cin inifinity loop, until pogram gets interrupted
    std::string in{"Hallooooo zurück und als Rache werde ich jedes Wort welches ich schreibe wild durcheinander wirbeln ( ausser den ersten und letzten Buchstaben, sonst kann man es nicht mehr lesen )"};
    std::vector<std::string> inSplit = splitString(in);
    std::string out = shuffled(inSplit);
    std::cout << out << '\n';
    return 0;
}
