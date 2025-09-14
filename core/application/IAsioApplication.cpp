#if __has_include(<asio.hpp>)

#include "IAsioApplication.h"
#include "core/application/IAsioContext.h"
#include "core/application/IApplicationManage.h"
#include "core/config/IContextImport.h"

#include <iostream>
#ifdef _WIN32
#include <windows.h>
#endif

$PackageWebCoreBegin

namespace detail
{
class SignalHandler
{
public:
    SignalHandler();

private:
    asio::signal_set signals_;
};

#ifdef _WIN32
static BOOL WINAPI ConsoleCtrlHandler(DWORD ctrlType) {
    if (ctrlType == CTRL_C_EVENT) {
        std::cout << "Ctrl+C detected, stopping io_context." << std::endl;
        IAsioContext::instance().getContext().stop();
        return TRUE;
    }
    return FALSE;
}
#endif

SignalHandler::SignalHandler() : signals_(IAsioContext::instance().getContext())
{
#ifdef _WIN32
    SetConsoleCtrlHandler(ConsoleCtrlHandler, TRUE);
#else
    // TODO: check in linux!!!
//    signals_.add(SIGINT);
//    signals_.add(SIGTERM);
//    signals_.async_wait([this](const asio::error_code& error, int signal_number) {
//        if (!error) {
//            std::cout << "Signal received: " << signal_number << ". Stopping io_context." << std::endl;
//            io_context_ptr_->stop();
//            handle_stop();
//        }
//    });
#endif
}

}

IAsioApplication::IAsioApplication(int argc, char **argv)
    : IApplicationInterface(argc, argv)
{
    static QCoreApplication app(argc, argv);
    IApplicationManage::instance().registerApplicationWare(this);

    Q_UNUSED(app)

    init();
}

void IAsioApplication::setThreadCount(int threadCount)
{
    m_threadCount = threadCount;
}

int IAsioApplication::run()
{
    detail::SignalHandler signal_handler;

    if(!m_threadCount){
        $ContextInt count{"/system/threadCount", static_cast<int>(std::thread::hardware_concurrency() * 2)};
        m_threadCount = *count;
    }
    IAsioContext::instance().run(m_threadCount);

    return 0;
}

$PackageWebCoreEnd

#endif
