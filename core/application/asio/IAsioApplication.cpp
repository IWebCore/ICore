#if __has_include(<asio.hpp>)

#include "IAsioApplication.h"

#include "IAsioApplication.h"
#include "core/application/asio/IAsioContext.h"
#include "core/application/asio/IAsioContext.h"
#include "core/application/IApplicationManage.h"
#include "core/config/IContextImport.h"
#include "core/task/ITaskManage.h"

#ifdef _WIN32
#include <windows.h>
#endif

$PackageWebCoreBegin

IAsioApplication::IAsioApplication()
{

}

QString IAsioApplication::applicationName() const
{
    return qApp->applicationName();
}

QString IAsioApplication::applicationPath() const
{
    return qApp->applicationFilePath();
}

QString IAsioApplication::workingDirectory() const
{
    return QDir::currentPath();
}

QStringList IAsioApplication::arguments() const
{
    return qApp->arguments();
}

IHandle IAsioApplication::startTimer(std::chrono::milliseconds duration, TaskType task)
{
    return IAsioContext::startTimer(duration, task);
}

void IAsioApplication::stopTimer(IHandle handle)
{
    return IAsioContext::stopTimer(handle);
}

void IAsioApplication::post(TaskType task)
{
    IAsioContext::post(task);
}

int64_t IAsioApplication::time()
{
    return ++m_time;
}

int IAsioApplication::exec()
{
    if(!m_threadCount){
        $ContextInt count{"/system/threadCount", static_cast<int>(std::thread::hardware_concurrency() * 2)};
        m_threadCount = *count;
    }
    IAsioContext::instance().run(m_threadCount);

    return 0;
}

QString IAsioApplication::applicationType() const
{
    return "asio";
}

IApplicationWare* IAsioApplication::invoke(int argc, char ** argv)
{
    static QCoreApplication qCoreApp(argc, argv);
    ITaskManage::run();
    return this;
}

void IAsioApplication::$task()
{
    IApplicationManage::instance().registerAppFuns(applicationType(), [&](int argc, char** argv) -> IApplicationWare*{
        return invoke(argc, argv);
    });

    m_time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock().now().time_since_epoch()).count();
    IAsioContext::startTimer(std::chrono::seconds(1), [&](){
        m_time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock().now().time_since_epoch()).count();
    });
}

$PackageWebCoreEnd

#endif

// #if __has_include(<asio.hpp>)

// #include "IAsioApplication.h"
// #include "core/application/IAsioContext.h"
// #include "core/application/IApplicationManage.h"
// #include "core/config/IContextImport.h"

// #include <iostream>
// #ifdef _WIN32
// #include <windows.h>
// #endif

// $PackageWebCoreBegin

// namespace detail
// {
// class SignalHandler
// {
// public:
//     SignalHandler();

// private:
//     asio::signal_set signals_;
// };

// #ifdef _WIN32
// static BOOL WINAPI ConsoleCtrlHandler(DWORD ctrlType) {
//     if (ctrlType == CTRL_C_EVENT) {
//         std::cout << "Ctrl+C detected, stopping io_context." << std::endl;
//         IAsioContext::instance().getContext().stop();
//         return TRUE;
//     }
//     return FALSE;
// }
// #endif

// SignalHandler::SignalHandler() : signals_(IAsioContext::instance().getContext())
// {
// #ifdef _WIN32
//     SetConsoleCtrlHandler(ConsoleCtrlHandler, TRUE);
// #else
//     // TODO: check in linux!!!
// //    signals_.add(SIGINT);
// //    signals_.add(SIGTERM);
// //    signals_.async_wait([this](const asio::error_code& error, int signal_number) {
// //        if (!error) {
// //            std::cout << "Signal received: " << signal_number << ". Stopping io_context." << std::endl;
// //            io_context_ptr_->stop();
// //            handle_stop();
// //        }
// //    });
// #endif
// }

// }

// IAsioApplication::IAsioApplication(int argc, char **argv)
//     : IApplicationInterface(argc, argv)
// {
//     static QCoreApplication app(argc, argv);
//     // IApplicationManage::instance().registerApplicationWare(this);

//     Q_UNUSED(app)

//     init();
// }

// void IAsioApplication::setThreadCount(int threadCount)
// {
//     m_threadCount = threadCount;
// }

// int IAsioApplication::run()
// {
//     detail::SignalHandler signal_handler;

//     if(!m_threadCount){
//         $ContextInt count{"/system/threadCount", static_cast<int>(std::thread::hardware_concurrency() * 2)};
//         m_threadCount = *count;
//     }
//     IAsioContext::instance().run(m_threadCount);

//     return 0;
// }

// $PackageWebCoreEnd

// #endif

