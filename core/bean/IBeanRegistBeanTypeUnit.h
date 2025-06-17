#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/util/IJsonUtil.h"
#include "core/bean/IBeanTypeManage.h"
#include "core/bean/IBeanRegistBaseTypeUnit.h"

$PackageWebCoreBegin

template<typename T>
struct IBeanRegistBeanTypeUnit : public IBeanRegistBaseTypeUnit<T>
{
    static void registType();

private:
    static void registBean();
};

template<typename T>
void IBeanRegistBeanTypeUnit<T>::registType()
{
    registBean();
    IBeanRegistBaseTypeUnit<T>::registType();
}

template<typename T>
void IBeanRegistBeanTypeUnit<T>::registBean()
{   
    auto ids = IMetaUtil::registMetaType<T>();
    for(auto id : ids){
        IBeanTypeManage::instance().registBeanId(id);
        IBeanTypeManage::instance().registBeanFromJsonFun(id,[](void* ptr, const IJson& json)->bool{
            return IJsonUtil::fromJson(*static_cast<T*>(ptr), json);
        });
        IBeanTypeManage::instance().registBeanToJsonFun(id, [](void* ptr)->IJson{
            return IJsonUtil::toJson(*static_cast<T*>(ptr));
        });
    }
}

$PackageWebCoreEnd
