#pragma once

#include <string_view>
#include <QString>
#include <QByteArray>
#include <QList>
#include "core/base/IResult.h"

#ifndef __I_STRING_VIEW_GUARD__
#define __I_STRING_VIEW_GUARD__

namespace asio
{
    class const_buffer;
}

class IStringViewList;
class IStringView : public std::string_view
{
public:
    IStringView() = default;
    constexpr IStringView& operator=(const IStringView&) noexcept = default;
    constexpr IStringView& operator=(IStringView&&) noexcept = default;
    explicit IStringView(const std::string& data);
    explicit IStringView(const QByteArray& data);
    explicit constexpr IStringView(std::string_view data);
    explicit constexpr IStringView(const char* data, std::size_t length);
    constexpr IStringView(const char* data);
    constexpr IStringView(const IStringView& data);

    operator QByteArray() const;
    bool operator ==(const char*) const;
    bool operator ==(IStringView) const;
    bool operator !=(IStringView) const;
    bool operator <(IStringView) const;

public:
    static uint qHash(const IStringView *obj, uint seed = 0);

public:
    QString toQString() const;
    std::string toStdString() const;
    QByteArray toQByteArray() const;
    asio::const_buffer toAsioBuffer() const;

public:
    IStringView substr(const size_type _Off, size_type _Count=std::string::npos) const;
    IStringView trimmed();
    IStringViewList split(char) const;
    IStringViewList split(IStringView) const;
    bool startWith(IStringView prefix) const;
    bool endWith(IStringView suffix) const;
    bool equalIgnoreCase(IStringView) const;
    bool containIgnoreCase(IStringView) const;
};


inline constexpr IStringView::IStringView(std::string_view data)
    : std::string_view(data)
{
}

inline constexpr IStringView::IStringView(const char *data)
    : std::string_view(data)
{
}

inline constexpr IStringView::IStringView(const char *data, std::size_t length)
    : std::string_view(data, length)
{
}

inline constexpr IStringView::IStringView(const IStringView& view)
    : std::string_view(static_cast<std::string_view>(view))
{
}

class IStringViewList : public QList<IStringView>
{
public:
    IStringViewList() = default;
    IStringViewList(QList<IStringView> data);

public:
    std::string join(IStringView);
};

#endif
