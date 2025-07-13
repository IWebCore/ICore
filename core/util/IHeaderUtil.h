#if !defined(__MINGW32__) && !defined(__MINGW64__)
    #pragma once
#endif

#ifndef  __IWEBCORE_IHEADERUTIL_GUARD__
#define  __IWEBCORE_IHEADERUTIL_GUARD__

#include <QObject>
#include <QMetaObject>
#include <QtCore>
#if __has_include(<QtSql>)
    #include <QtSql>
#endif

#include <type_traits>
#include "core/util/IPackageUtil.h"
#include "core/base/IJson.h"
#include "core/base/IString.h"
#include "core/base/IStringViewStash.h"
#include "core/base/IStringView.h"
#include <asio.hpp>

#ifdef ENABLE_SSL
    #include <asio/ssl.hpp>
#endif

#endif
