#include "IApplicationManage.h"
#include "core/application/IApplicationWare.h"
// #include "core/application/IAsioContext.h"
// #include <QCoreApplication>

$PackageWebCoreBegin

IApplicationWare* iApp = nullptr;

$PackageWebCoreEnd

// namespace detail
// {
//     std::int64_t getQtTime();
// }

// IApplicationManage::IApplicationManage()
// {
// }

// QString IApplicationManage::applicationName() const
// {
//     if(m_applicationWare){
//         return m_applicationWare->applicationName();
//     }
//     return qApp->applicationName();
// }

// QString IApplicationManage::applicationPath() const
// {
//     if(m_applicationWare){
//         return m_applicationWare->applicationPath();
//     }
//     return qApp->applicationFilePath();
// }

// QString IApplicationManage::workingDirectory() const
// {
//     return QDir::currentPath();
// }

// QStringList IApplicationManage::arguments() const
// {
//     if(m_applicationWare){
//         return m_applicationWare->arguments();
//     }
//     return qApp->arguments();
// }

// IHandle IApplicationManage::startTimer(std::chrono::milliseconds duration, Task task)
// {
//     return IAsioContext::instance().startTimer(duration, task);
// }

// void IApplicationManage::stopTimer(IHandle id)
// {
//     IAsioContext::instance().stopTimer(id);
// }

// int64_t IApplicationManage::time() const
// {
//     // if(m_applicationWare){
//     //     return m_applicationWare->time();
//     // }

//     // return detail::getQtTime();
// }

// void IApplicationManage::registerApplicationWare(IApplicationWare *ware)
// {
//     if(m_applicationWare){
//         qFatal("application already registered, you can not register application any more");
//     }

//     m_applicationWare = ware;
// }


// std::int64_t detail::getQtTime()
// {
//     static std::int64_t s_time{std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock().now().time_since_epoch()).count()};
//     static std::once_flag flag;
//     std::call_once(flag, [](){
//         static QTimer timer;
//         QObject::disconnect(&timer, nullptr, nullptr, nullptr);
//         QObject::connect(&timer, &QTimer::timeout, [](){
//             s_time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock().now().time_since_epoch()).count();
//         });
//         timer.setTimerType(Qt::TimerType::PreciseTimer);
//         timer.start(1000);
//     });

//     return s_time ++;
// }

void IApplicationManage::registerAppFuns(const QString &name, AppFun fun)
{
    m_appFuns[name] = fun;
}

IApplicationManage::AppFun IApplicationManage::getAppFunction(const QString & name)
{
    if(m_appFuns.contains(name)){
        return m_appFuns[name];
    }
    return nullptr;
}


