#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/task/ITaskManage.h"
#include "core/application/IAsioContext.h"
//#include <filesystem>

$PackageWebCoreBegin

template<typename T>
class IApplicationInterface
{
    friend class IAsioApplicationTimerTask;
public:
    IApplicationInterface(int argc, char** argv);

public:
    static T& instance();
    QString applicationPath();
    QString workingDirectory();
    QString appName();
    const QStringList& arguments();
    static int64_t time();

public:
    virtual int run() = 0;

protected:
    void init();

protected:
    static T* m_instance;
    std::atomic_int64_t m_time;
    QStringList m_arguments;
};

template<typename T>
T* IApplicationInterface<T>::m_instance = nullptr;

template<typename T>
IApplicationInterface<T>::IApplicationInterface(int argc, char **argv)
{
    IApplicationInterface::m_time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock().now().time_since_epoch()).count();
    IAsioContext::startTimer(std::chrono::seconds(1), [&](){
        IApplicationInterface::m_time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock().now().time_since_epoch()).count();
    });

    for(int i=0; i<argc; i++){
        m_arguments.append(QString::fromLocal8Bit(argv[i]));
    }
}

template<typename T>
T& IApplicationInterface<T>::instance()
{
    return *m_instance;
}

template<typename T>
QString IApplicationInterface<T>::applicationPath()
{
    return QFileInfo(m_arguments.first()).absolutePath();
}

template<typename T>
QString IApplicationInterface<T>::workingDirectory()
{
    return QDir::currentPath();
//    std::filesystem::path cwd = std::filesystem::current_path();
//    return QString::fromStdString(cwd.string());
}

template<typename T>
QString IApplicationInterface<T>::appName()
{
    QString path = m_arguments.first();
    return path.replace("\\", "/").split("/").last();
}

template<typename T>
const QStringList& IApplicationInterface<T>::arguments()
{
    return instance().m_arguments;
}

template<typename T>
int64_t IApplicationInterface<T>::time()
{
    return instance().m_time ++;
}

template<typename T>
void IApplicationInterface<T>::init()
{
    m_instance = dynamic_cast<T*>(this);
    return ITaskManage::run();
}

$PackageWebCoreEnd
