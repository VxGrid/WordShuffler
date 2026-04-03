#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>

class Backend : public QObject
{
    Q_OBJECT Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
public:
    explicit Backend(QObject *parent = nullptr);

    Q_INVOKABLE void processText(const QString &text);

    void setText(const QString &text);

    QString text() const;

signals:
    void textChanged();

private:
    void copyToClipboard(const QString &text);

    std::vector<std::string> splitString(const std::string &str);

    inline bool isNonCharacter(int ch);

    std::string shuffled(std::vector<std::string> &shuffledPieces);

private:
    QString text_;
};

#endif // BACKEND_H
