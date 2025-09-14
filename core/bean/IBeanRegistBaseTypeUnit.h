#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/util/IJsonUtil.h"
#include "core/bean/IBeanTypeManage.h"
#include "core/bean/IBeanRegistBaseTypeUnit.h"

$PackageWebCoreBegin

template<typename T>
struct IBeanRegistBaseTypeUnit
{
    static void registType();

private:
//    static void registBean();

    static void registQList();
    static void registStdList();
    static void registQVector();
    static void registStdVector();

    // QMap
    static void registQStringQMap();
    static void registStdStringQMap();
    static void registIStringQMap();
    static void registQStringStdMap();
    static void registStdStringStdMap();
    static void registIStringStdMap();
};

template<typename T>
void IBeanRegistBaseTypeUnit<T>::registType()
{
//    registBean();     // this is invalid because we do not want to register int to beans!, but we regist  QList<int> as bean.
    registQList();
    registStdList();
    registQVector();
    registStdVector();

    registQStringQMap();
    registStdStringQMap();
    registIStringQMap();

    registQStringStdMap();
    registStdStringStdMap();
    registIStringStdMap();
}


template<typename T>
void IBeanRegistBaseTypeUnit<T>::registQList()
{
    auto name = "QList<" + IMetaUtil::getTypeName<T>() + ">";
    auto ids = IMetaUtil::registMetaType<QList<T>>({name});
    for(auto id : ids){
        IBeanTypeManage::instance().registBeanId(id);
        IBeanTypeManage::instance().registBeanFromJsonFun(id,[](void* ptr, const IJson& json)->bool{
            return IJsonUtil::fromJson(*static_cast<QList<T>*>(ptr), json);
        });
        IBeanTypeManage::instance().registBeanToJsonFun(id, [](void* ptr)->IJson{
            return IJsonUtil::toJson(*static_cast<QList<T>*>(ptr));
        });
    }
}

template<typename T>
void IBeanRegistBaseTypeUnit<T>::registStdList()
{
    auto name = "std::list<" + IMetaUtil::getTypeName<T>() + ">";
    auto ids = IMetaUtil::registMetaType< std::list<T> >({name});
    for(auto id : ids){
        IBeanTypeManage::instance().registBeanId(id);
        IBeanTypeManage::instance().registBeanFromJsonFun(id,[](void* ptr, const IJson& json)->bool{
            return IJsonUtil::fromJson(*static_cast< std::list<T>*>(ptr), json);
        });
        IBeanTypeManage::instance().registBeanToJsonFun(id, [](void* ptr)->IJson{
            return IJsonUtil::toJson(*static_cast< std::list<T>*>(ptr));
        });
    }
}

template<typename T>
void IBeanRegistBaseTypeUnit<T>::registQVector()
{
    auto name = "QVector<" + IMetaUtil::getTypeName<T>() + ">";
    auto ids = IMetaUtil::registMetaType<QVector<T>>({name});
    for(auto id : ids){
        IBeanTypeManage::instance().registBeanId(id);
        IBeanTypeManage::instance().registBeanFromJsonFun(id,[](void* ptr, const IJson& json)->bool{
            return IJsonUtil::fromJson(*static_cast<QVector<T>*>(ptr), json);
        });
        IBeanTypeManage::instance().registBeanToJsonFun(id, [](void* ptr)->IJson{
            return IJsonUtil::toJson(*static_cast<QVector<T>*>(ptr));
        });
    }
}

template<typename T>
void IBeanRegistBaseTypeUnit<T>::registStdVector()
{
    auto name = "std::vector<" + IMetaUtil::getTypeName<T>() + ">";
    auto ids = IMetaUtil::registMetaType<std::vector<T>>({name});
    for(auto id : ids){
        IBeanTypeManage::instance().registBeanId(id);
        IBeanTypeManage::instance().registBeanFromJsonFun(id,[](void* ptr, const IJson& json)->bool{
            return IJsonUtil::fromJson(*static_cast<std::vector<T>*>(ptr), json);
        });
        IBeanTypeManage::instance().registBeanToJsonFun(id, [](void* ptr)->IJson{
            return IJsonUtil::toJson(*static_cast<std::vector<T>*>(ptr));
        });
    }
}

template<typename T>
void IBeanRegistBaseTypeUnit<T>::registQStringQMap()
{
    auto name = "QMap<QString, " + IMetaUtil::getTypeName<T>() + ">";
    auto ids = IMetaUtil::registMetaType<QMap<QString, T>>({name});
    for(auto id : ids){
        IBeanTypeManage::instance().registBeanId(id);
        IBeanTypeManage::instance().registBeanFromJsonFun(id,[](void* ptr, const IJson& json)->bool{
            return IJsonUtil::fromJson(*static_cast<QMap<QString, T>*>(ptr), json);
        });
        IBeanTypeManage::instance().registBeanToJsonFun(id, [](void* ptr)->IJson{
            return IJsonUtil::toJson(*static_cast<QMap<QString, T>*>(ptr));
        });
    }
}

template<typename T>
void IBeanRegistBaseTypeUnit<T>::registStdStringQMap()
{
    auto name = "QMap<std::string, " + IMetaUtil::getTypeName<T>() + ">";
    auto ids = IMetaUtil::registMetaType<QMap<std::string, T>>({name});
    for(auto id : ids){
        IBeanTypeManage::instance().registBeanId(id);
        IBeanTypeManage::instance().registBeanFromJsonFun(id,[](void* ptr, const IJson& json)->bool{
            return IJsonUtil::fromJson(*static_cast<QMap<std::string, T>*>(ptr), json);
        });
        IBeanTypeManage::instance().registBeanToJsonFun(id, [](void* ptr)->IJson{
            return IJsonUtil::toJson(*static_cast<QMap<std::string, T>*>(ptr));
        });
    }
}

template<typename T>
void IBeanRegistBaseTypeUnit<T>::registIStringQMap()
{
    auto name = "QMap<IString, " + IMetaUtil::getTypeName<T>() + ">";
    auto ids = IMetaUtil::registMetaType<QMap<IString, T>>({name});
    for(auto id : ids){
        IBeanTypeManage::instance().registBeanId(id);
        IBeanTypeManage::instance().registBeanFromJsonFun(id,[](void* ptr, const IJson& json)->bool{
            return IJsonUtil::fromJson(*static_cast<QMap<IString, T>*>(ptr), json);
        });
        IBeanTypeManage::instance().registBeanToJsonFun(id, [](void* ptr)->IJson{
            return IJsonUtil::toJson(*static_cast<QMap<IString, T>*>(ptr));
        });
    }
}

template<typename T>
void IBeanRegistBaseTypeUnit<T>::registQStringStdMap()
{
    auto name = "std::map<QString, " + IMetaUtil::getTypeName<T>() + ">";
    auto ids = IMetaUtil::registMetaType<std::map<QString, T>>({name});
    for(auto id : ids){
        IBeanTypeManage::instance().registBeanId(id);
        IBeanTypeManage::instance().registBeanFromJsonFun(id,[](void* ptr, const IJson& json)->bool{
            return IJsonUtil::fromJson(*static_cast<std::map<QString, T>*>(ptr), json);
        });
        IBeanTypeManage::instance().registBeanToJsonFun(id, [](void* ptr)->IJson{
            return IJsonUtil::toJson(*static_cast<std::map<QString, T>*>(ptr));
        });
    }
}

template<typename T>
void IBeanRegistBaseTypeUnit<T>::registStdStringStdMap()
{
    auto name = "std::map<std::string, " + IMetaUtil::getTypeName<T>() + ">";
    auto ids = IMetaUtil::registMetaType<std::map<std::string, T>>({name});
    for(auto id : ids){
        IBeanTypeManage::instance().registBeanId(id);
        IBeanTypeManage::instance().registBeanFromJsonFun(id,[](void* ptr, const IJson& json)->bool{
            return IJsonUtil::fromJson(*static_cast<std::map<std::string, T>*>(ptr), json);
        });
        IBeanTypeManage::instance().registBeanToJsonFun(id, [](void* ptr)->IJson{
            return IJsonUtil::toJson(*static_cast<std::map<std::string, T>*>(ptr));
        });
    }
}

template<typename T>
void IBeanRegistBaseTypeUnit<T>::registIStringStdMap()
{
    auto name = "std::map<IString, " + IMetaUtil::getTypeName<T>() + ">";
    auto ids = IMetaUtil::registMetaType<std::map<IString, T>>({name});
    for(auto id : ids){
        IBeanTypeManage::instance().registBeanId(id);
        IBeanTypeManage::instance().registBeanFromJsonFun(id,[](void* ptr, const IJson& json)->bool{
            return IJsonUtil::fromJson(*static_cast<std::map<IString, T>*>(ptr), json);
        });
        IBeanTypeManage::instance().registBeanToJsonFun(id, [](void* ptr)->IJson{
            return IJsonUtil::toJson(*static_cast<std::map<IString, T>*>(ptr));
        });
    }
}

$PackageWebCoreEnd
