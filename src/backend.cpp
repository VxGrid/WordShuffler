#include "backend.h"

#include <algorithm>
#include <iterator>
#include <qwindowdefs.h>
#include <random>
#include <string>
#include <vector>

#include <QClipboard>
#include <QDebug>
#include <QGuiApplication>

Backend::Backend(QObject *parent)
    : QObject{parent}
{}


void Backend::processText(const QString &text)
{
    qDebug() << "Text from QML:" << text;
    std::vector<std::string> inSplit = splitString(text.toStdString());
    std::string out = shuffled(inSplit);
    setText(QString::fromStdString(out));
    copyToClipboard(text_);
    qDebug() << "Text out: " << text_;
}


void Backend::setText(const QString &text)
{
    if (text_ == text)
        return;

    text_ = text;
    emit textChanged();
}


QString Backend::text() const
{
    return text_;
}


void Backend::copyToClipboard(const QString &text)
{
    QClipboard *clipboard = QGuiApplication::clipboard();
    clipboard->setText(text);
}


std::vector<std::string> Backend::splitString(const std::string &str)
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

inline bool Backend::isNonCharacter(int ch)
{
    if (ch >= 48 && ch <= 57)
        return false;
    else if (ch >= 65 && ch <= 90)
        return false;
    else if (ch >= 97 && ch <= 122)
        return false;

    return true;
}

std::string Backend::shuffled(std::vector<std::string> &shuffledPieces)
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