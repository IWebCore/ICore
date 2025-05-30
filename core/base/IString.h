#pragma once

#include <QtCore>
//#include <QString>
//#include <QByteArray>
//#include <QList>
#include <string>
#include "core/base/IStringView.h"
#include "core/base/IResult.h"

#ifndef __I_STRING_GUARD__
#define __I_STRING_GUARD__

struct IString
{
private:
    enum class Type {
        IStringView, // default, and empty
        QByteArray,
        StdString,
    };

public:
    IString() = default;
    ~IString();

    IString(const IString& other);
    IString(IString&& other) noexcept;
    IString& operator=(const IString& other);
    IString& operator=(IString&& other) noexcept;

    IString(const IString*);
    IString(const std::string*);
    IString(const QByteArray*);

    IString(const char*);
    IString(const QByteArray& byteArray);
    IString(QByteArray&& byteArray) noexcept;
    IString(const std::string& stdString);
    IString(std::string&& stdString) noexcept;
    IString(const QString&) noexcept;
    IString(IStringView&& stringView);
    IString(const IStringView& stringView);

    IString& operator=(const IString*);
    IString& operator=(const QByteArray*);
    IString& operator=(const std::string*);

    IString& operator=(const char*);
    IString& operator=(const QString&);
    IString& operator=(const QByteArray& byteArray);
    IString& operator=(QByteArray&& byteArray) noexcept;
    IString& operator=(const std::string& stdString);
    IString& operator=(std::string&& stdString) noexcept;
    IString& operator=(IStringView&& stringView);
    IString& operator=(const IStringView& view);
    IString& operator=(std::nullptr_t);

    bool operator ==(const IString&) const;
    bool operator !=(const IString&) const;
    bool operator <(const IString&) const;

public:
    std::size_t length() const;
    std::size_t size() const;
    bool isSolid() const;
    bool isEmpty() const;
    IString& solidify();
    operator bool() const;
    operator IStringView() const;

public:
    template<typename T>
    IResult<T> value() const;

public:
    IStringViewList split(char) const;
    IStringViewList split(const IString&) const;
    bool startWith(const IString&) const;
    bool equal(const IString&) const;
    bool equalIgnoreCase(const IString&) const;
    bool containIgnoreCase(const IString&) const;

public:
    QString toQString() const;
    std::string toStdString() const;
    QByteArray toQByteArray() const;

private:
    void clear();
    void copyFrom(const IString& other);
    void moveFrom(IString&& other) noexcept;

private:
    Type m_type{Type::IStringView};
    void* m_data{};

public:
    IStringView m_view{};
};

using IStringList = QList<IString>;

Q_DECLARE_METATYPE(IString)

#endif
