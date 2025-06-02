#include "IString.h"
//#include <charconv.hpp>
//#include <charconv>
#include <string_view>
#include <QtCore>

namespace detail
{
    template <typename T>
    T string_view_to(const IStringView& str, bool& ok);
}

#define STRING_VIEW_CREATE(Class)                                   \
template<>                                                          \
IResult< Class > IString::value< Class >() const                    \
{                                                                   \
    bool ok;                                                        \
    auto value = detail::string_view_to< Class >(m_view, ok);       \
    if(ok){                                                         \
        return value;                                               \
    }                                                               \
    return std::nullopt;                                            \
}

STRING_VIEW_CREATE(ushort)
STRING_VIEW_CREATE(short)
STRING_VIEW_CREATE(uint)
STRING_VIEW_CREATE(int)
STRING_VIEW_CREATE(unsigned long)
STRING_VIEW_CREATE(long)
STRING_VIEW_CREATE(unsigned long long)
STRING_VIEW_CREATE(long long)
STRING_VIEW_CREATE(float)
STRING_VIEW_CREATE(double)
#undef STRING_VIEW_CREATE

template<>
IResult<bool> IString::value<bool>() const
{
    if(m_view == "true"){
        return true;
    }
    if(m_view == "false"){
        return false;
    }
    return std::nullopt;
}

template<>
IResult<unsigned char> IString::value<unsigned char>() const
{
    bool ok;
    auto value = detail::string_view_to<unsigned short>(m_view, ok);
    if(ok && value > std::numeric_limits<unsigned char>::max()){
        return std::nullopt;
    }
    return static_cast<unsigned char>(value);
}

template<>
IResult<signed char> IString::value<signed char>() const
{
    bool ok;
    auto value = detail::string_view_to<short>(m_view, ok);
    if(ok && (value > std::numeric_limits<signed char>::max() || value < std::numeric_limits<signed char>::min())){
        return std::nullopt;
    }
    return static_cast<signed char>(value);
}

template<>
IResult<QString> IString::value<QString>() const
{
    return toQString();
}

template<>
IResult<QByteArray> IString::value<QByteArray>() const
{
    return toQByteArray();
}

template<>
IResult<std::string> IString::value<std::string>() const
{
    return toStdString();
}

template<>
IResult<IString> IString::value<IString>() const
{
    return *this;
}

template<>
IResult<IStringView> IString::value<IStringView>() const
{
    return this->m_view;
}

template<>
IResult<QDate> IString::value<QDate>() const
{
    auto date = QVariant(this->m_view.toQString()).toDate();
    if(date.isValid()){
        return date;
    }
    return std::nullopt;
}

template<>
IResult<QTime> IString::value<QTime>() const
{
    auto time = QVariant(this->m_view.toQString()).toTime();
    if(time.isValid()){
        return time;
    }
    return std::nullopt;
}

template<>
IResult<QDateTime> IString::value<QDateTime>() const
{
    auto time = QVariant(this->m_view.toQString()).toDateTime();
    if(time.isValid()){
        return time;
    }
    return std::nullopt;
}

// I deprecated std::from_chars because mingw do not support it.
// it will be update latter
template <typename T>
T detail::string_view_to(const IStringView& str, bool& ok)
{
    ok = true;
    try{
        if constexpr (std::is_same_v<T, double>){
            return std::stod(std::string(str));
        }
        if constexpr (std::is_same_v<T, float>){
            return std::stof(std::string(str));
        }
        if constexpr (std::is_signed_v<T>){
            auto value = std::stoll(std::string(str));
            if(value > std::numeric_limits<T>::max() || value < std::numeric_limits<T>::min()){
                ok = false;
                return {};
            }
            return value;
        }
        if constexpr (! std::is_signed_v<T>){
            auto value = std::stoull(std::string(str));
            if(value > std::numeric_limits<T>::max() || value < std::numeric_limits<T>::min()){
                ok = false;
                return {};
            }
            return value;
        }
    }catch(...){
        ok = false;
        return {};
    }

    qFatal("heere");
    ok = false;
    return {};

//    if (str.empty()) {
//        ok = false;
//        return {};
//    }

//    T result{};
//    auto val = std::from_chars(str.data(), str.data()+str.length(), result);
//    if (val.ec != std::errc()) {
//        ok = false;
//        return {};
//    }
//    ok = true;
//    return result;
}

