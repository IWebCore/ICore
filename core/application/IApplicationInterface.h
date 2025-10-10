#pragma once

#include "IApplicationWare.h"
#include "core/task/unit/ITaskInstantUnit.h"
#include "IApplicationManage.h"
#include "core/unit/ISoloUnit.h"

template<typename T, bool enabled=true>
class IApplicationInterface : public IApplicationWare, public ITaskInstantUnit<T, true> //, ISoloUnit<T>
{
public:
    IApplicationInterface() = default;

public:
    virtual void $task() override;
};

template<typename T, bool enabled>
void IApplicationInterface<T, enabled>::$task()
{
    if constexpr (enabled){
        IApplicationManage::instance().registerAppFuns(applicationType(), [&](int argc, const char** argv) -> IApplicationWare*{
            return invoke(argc, argv);
        });
    }
}


















// #pragma once

// #include "core/util/IHeaderUtil.h"
// #include "core/task/ITaskManage.h"
// #include "core/application/IApplicationWare.h"
// #include "core/application/IAsioContext.h"

// $PackageWebCoreBegin

// template<typename T>
// class IApplicationInterface : public IApplicationWare
// {
//     friend class IAsioApplicationTimerTask;
// public:
//     IApplicationInterface(int argc, char** argv);

// public:
//     static T& instance();

// public:
//     virtual QString applicationName() const final;
//     virtual QString applicationPath() const final;
//     virtual QString workingDirectory() const final;
//     virtual QStringList arguments() const final;
//     virtual std::int64_t time() const final;

// public:
//     virtual int run() = 0;

// protected:
//     void init();

// protected:
//     static T* m_instance;
//     std::atomic_int64_t m_time;
//     QStringList m_arguments;
// };

// template<typename T>
// T* IApplicationInterface<T>::m_instance = nullptr;

// template<typename T>
// IApplicationInterface<T>::IApplicationInterface(int argc, char **argv)
// {
//     IApplicationInterface::m_time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock().now().time_since_epoch()).count();
//     IAsioContext::startTimer(std::chrono::seconds(1), [&](){
//         IApplicationInterface::m_time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock().now().time_since_epoch()).count();
//     });

//     for(int i=0; i<argc; i++){
//         m_arguments.append(QString::fromLocal8Bit(argv[i]));
//     }
// }

// template<typename T>
// T& IApplicationInterface<T>::instance()
// {
//     return *m_instance;
// }

// template<typename T>
// QString IApplicationInterface<T>::applicationName() const
// {
//     QString path = m_arguments.first();
//     return path.replace("\\", "/").split("/").last();
// }

// template<typename T>
// QString IApplicationInterface<T>::applicationPath() const
// {
//     return QFileInfo(m_arguments.first()).absolutePath();
// }

// template<typename T>
// QString IApplicationInterface<T>::workingDirectory() const
// {
//     return QDir::currentPath();
// }

// template<typename T>
// QStringList IApplicationInterface<T>::arguments() const
// {
//     return instance().m_arguments;
// }

// template<typename T>
// int64_t IApplicationInterface<T>::time() const
// {
//     return instance().m_time ++;
// }

// template<typename T>
// void IApplicationInterface<T>::init()
// {
//     m_instance = dynamic_cast<T*>(this);
//     return ITaskManage::run();
// }

// $PackageWebCoreEnd
