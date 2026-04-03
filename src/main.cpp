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

inline bool isNonCharacter(int ch)
{
    if (ch >= 48 && ch <= 57)
        return false;
    else if (ch >= 65 && ch <= 90)
        return false;
    else if (ch >= 97 && ch <= 122)
        return false;

    return true;
}

std::string shuffled(std::vector<std::string> &shuffledPieces)
{
    static std::random_device rd;
    static std::mt19937 g(rd());
    static constexpr size_t minCharacters{4};

    for (auto &str : shuffledPieces)
    {
        if (str.size() < minCharacters)
            continue;

        int shuffleStart{1}, shuffleEnd{1};

        if (isNonCharacter(str[0]))
            ++shuffleStart;

        if (isNonCharacter(str.back()))
            ++shuffleEnd;

        if (str.size() + 2 - shuffleStart - shuffleEnd < minCharacters)
            continue;

        std::shuffle(str.begin() + shuffleStart, str.end() - shuffleEnd, g);
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

void printHelp()
{
    std::cout <<
        "This application shuffles every word internally - except the first and last character.\n\n";
    std::cout << "-h | --help:\t\t\t Prints this help and exits\n";
    std::cout << "-t | --translate [\"text\"]:\t Shuffles only [text] and exits\n";
    std::cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
}


int main(int argc, char* argv[])
{
    bool eternityMode{true};
    std::string inStr{};

    for (int args = 1; args < argc; ++args)
    {
        if (std::string(argv[args]) == "-h" || std::string(argv[args]) == "--help")
        {
            printHelp();
            return EXIT_SUCCESS;
        }

        if (std::string(argv[args]) == "-t" || std::string(argv[args]) == "--translate")
        {
            // Translation mode - only run once.
            eternityMode = false;

            if (argc < args + 1)
            {
                printHelp();
                return EXIT_FAILURE;
            }

            inStr = std::string(argv[args + 1]);
        }
    }

    if (eternityMode)
        std::cout << "Insert the sentence you like to character shuffle:\n";

    do
    {
        if (eternityMode)
            std::getline(std::cin, inStr);

        std::vector<std::string> inSplit = splitString(inStr);
        std::string out = shuffled(inSplit);
        std::cout << '\r' << out << '\n';
        inStr.clear();
    }
    while (eternityMode);

    /*
        /// Test code
        // Test string
        std::string in{"1, 12, 123, 1234, 12345, 123456, 1234567, 12345678, 123456789, .1, .12, .123, .1234, .12345, .123456, .1234567, .12345678, .123456789,"};
        std::cout << in << '\n';
        std::vector<std::string> inSplit = splitString(in);
        std::string out = shuffled(inSplit);
        std::cout << out << '\n';
    */
    return EXIT_SUCCESS;
}
