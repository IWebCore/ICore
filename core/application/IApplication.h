#pragma once

#include "core/task/ITaskManage.h"
#include "IApplicationManage.h"
#include "IApplicationAnnomacro.h"
#include <asio.hpp>

#if __has_include(<asio.hpp>)
    #include "IAsioApplication.h"
#else
    using IApplication = QCoreApplication;
#endif
