#pragma once

#include "IBeanAbort.h"
#include "IBeanTypeManage.h"
#include "IBeanPreProcessor.h"
#include "IBeanRegistBeanTypeUnit.h"
#include "core/base/IResult.h"
#include "core/util/IMetaUtil.h"
#include "core/unit/ITraceUnit.h"
#include "core/task/unit/ITaskInstantUnit.h"

$PackageWebCoreBegin

enum IBeanTrait
{
    Tolerance,
    Exact,
    Full
};

template<typename T, bool enabled = true, IBeanTrait trait = IBeanTrait::Tolerance>
class IBeanInterface : public ITaskInstantUnit<T, enabled>, protected IBeanRegistBeanTypeUnit<T>
{
public:
    IBeanInterface() = default;
    virtual ~IBeanInterface() = default;

public:
    virtual IJson toJson() const;
    virtual bool loadJson(const IJson &value, IBeanTrait = trait);
    static IResult<T> fromJson(const IJson& value, IBeanTrait = trait);

private:
    int getMetaTypeId() const;
    const QVector<QMetaMethod>& getMetaMethods() const;
    const QMap<QString, QString>& getMetaClassInfos() const;
    const QVector<QMetaProperty>& getMetaProperties() const;
    const QMetaProperty& getMetaProperty(const QString& name) const;
    const QMetaMethod& getMetaMethod(const QString &name) const;

private:
    QStringList getRequiredFields() const;
    QVector<std::string> getAllFields() const;
    std::map<std::string, const QMetaMethod*> getRequiredMethodMap() const;
    std::map<std::string, const QMetaMethod*> getOptionalMethodMap() const;
    const QMetaMethod& getJsonValidatorMethod() const;


protected:
    virtual void $task() override;
};

template<typename T, bool enabled, IBeanTrait trait>
IJson IBeanInterface<T, enabled, trait>::toJson() const
{
    static std::map<const char*, const QMetaMethod*> methodPair;
    static std::once_flag flag;
    std::call_once(flag, [this](){
        const auto& props = getMetaProperties();
        for(const auto& prop : props){
            const auto& method = getMetaMethod("$" + QString(prop.name()) + "_toJsonValue");
            if(!method.isValid()){
                IBeanAbort::abortToJsonMethodNotExist(prop.name(), $ISourceLocation);
            }
            methodPair[prop.name()] = &method;
        }
    });

    IJson obj = IJson::object();
    for(const auto& [key, method] : methodPair){
        IJson json;
        method->invokeOnGadget(const_cast<void*>(static_cast<const void*>(this)), Q_RETURN_ARG(IJson, json));
        obj[key] = std::move(json);
    }
    return obj;
}

template<typename T, bool enabled, IBeanTrait trait>
bool IBeanInterface<T, enabled, trait>::loadJson(const IJson &value, IBeanTrait beanTrait)
{
    static const auto optionalMethodPair = getOptionalMethodMap();
    static const auto requiredMethodPair = getRequiredMethodMap();
    static const QMetaMethod& jsonValidator = getJsonValidatorMethod();

    if(!value.is_object()) {
        return false;
    }

    bool ok;
    if(jsonValidator.isValid()){
        jsonValidator.invokeOnGadget(const_cast<void*>(static_cast<const void*>(this)),Q_RETURN_ARG(bool, ok), Q_ARG(IJson, value));
        if(!ok){
            return false;
        }
    }

    for(const auto& [key, method] : requiredMethodPair){
        if(!value.contains(key)){
            return false;
        }
        method->invokeOnGadget(const_cast<void*>(static_cast<const void*>(this)),Q_RETURN_ARG(bool, ok), Q_ARG(IJson, value[key]));
        if(!ok){
            return false;
        }
    }

    for(const auto& [key, method] : optionalMethodPair){
        if(value.contains(key)){
            method->invokeOnGadget(const_cast<void*>(static_cast<const void*>(this)),Q_RETURN_ARG(bool, ok), Q_ARG(IJson, value[key]));
            if(!ok){
                return false;
            }
        }else if(beanTrait != IBeanTrait::Tolerance){
            return false;
        }
    }

    if(beanTrait == IBeanTrait::Full){
        static const auto fields = getAllFields();
        for(const auto&val : value.items()){
            if(!fields.contains(val.key())){
                return false;
            }
        }
    }

    return true;
}

template<typename T, bool enabled, IBeanTrait trait>
IResult<T> IBeanInterface<T, enabled, trait>::fromJson(const IJson& value, IBeanTrait beanTrait)
{
    T t;
    if(t.loadJson(value, beanTrait)){
        return t;
    }
    return std::nullopt;
}

template<typename T, bool enabled, IBeanTrait trait>
int IBeanInterface<T, enabled, trait>::getMetaTypeId() const
{
    static int id = qMetaTypeId<T>();
    return id;
}

template<typename T, bool enabled, IBeanTrait trait>
const QVector<QMetaMethod>& IBeanInterface<T, enabled, trait>::getMetaMethods() const
{
    static const auto& methods =  IMetaUtil::getMetaMethods(T::staticMetaObject);
    return methods;
}

template<typename T, bool enabled, IBeanTrait trait>
const QMap<QString, QString>& IBeanInterface<T, enabled, trait>::getMetaClassInfos() const
{
    static const auto& clsInfos = IMetaUtil::getMetaClassInfoMap(T::staticMetaObject);
    return clsInfos;
}

template<typename T, bool enabled, IBeanTrait trait>
const QVector<QMetaProperty>& IBeanInterface<T, enabled, trait>::getMetaProperties() const
{
    static const auto& properties = IMetaUtil::getMetaProperties(T::staticMetaObject);
    return properties;
}

template<typename T, bool enabled, IBeanTrait trait>
const QMetaProperty& IBeanInterface<T, enabled, trait>::getMetaProperty(const QString& name) const
{
    static const auto& props = getMetaProperties();
    for(const QMetaProperty& prop : props){
        if(prop.name() == name){
            return prop;
        }
    }

    static QMetaProperty empty{};
    return empty;
}

template<typename T, bool enabled, IBeanTrait trait>
const QMetaMethod& IBeanInterface<T, enabled, trait>::getMetaMethod(const QString &name) const
{
    static const auto& methods = getMetaMethods();
    for(const QMetaMethod& method : methods){
        if(method.name() == name){
            return method;
        }
    }

    static QMetaMethod s_emptyMethod{};
    return s_emptyMethod;
}

template<typename T, bool enabled, IBeanTrait trait>
QStringList IBeanInterface<T, enabled, trait>::getRequiredFields() const
{
    QStringList fields;
    const QString prefix = "$beanfieldrequired_";
    const auto& infos = getMetaClassInfos();
    for(const auto& info : infos.keys()){
        if(info.startsWith(prefix)){
            fields.append(infos[info]);
        }
    }
    return fields;
}

template<typename T, bool enabled, IBeanTrait trait>
QVector<std::string> IBeanInterface<T, enabled, trait>::getAllFields() const
{
    QVector<std::string> fields;
    const auto& props = getMetaProperties();
    for(const auto& prop : props){
        fields.append(prop.name());
    }
    return fields;
}

template<typename T, bool enabled, IBeanTrait trait>
std::map<std::string, const QMetaMethod *> IBeanInterface<T, enabled, trait>::getRequiredMethodMap() const
{
    std::map<std::string, const QMetaMethod *> map;
    const auto fields = getRequiredFields();
    const auto& props = getMetaProperties();
    for(const auto& prop : props){
        if(fields.contains(prop.name())){
            const auto& method = getMetaMethod("$" + QString(prop.name()) + "_fromJsonValue");
            if(!method.isValid()){
                IBeanAbort::abortLoadJsonMethodNotExist(prop.name(), $ISourceLocation);
            }
            map[prop.name()] = &method;
        }
    }
    return map;
}

template<typename T, bool enabled, IBeanTrait trait>
std::map<std::string, const QMetaMethod *> IBeanInterface<T, enabled, trait>::getOptionalMethodMap() const
{
    std::map<std::string, const QMetaMethod *> map;
    const auto fields = getRequiredFields();
    const auto& props = getMetaProperties();
    for(const auto& prop : props){
        if(!fields.contains(prop.name())){
            const auto& method = getMetaMethod("$" + QString(prop.name()) + "_fromJsonValue");
            if(!method.isValid()){
                IBeanAbort::abortLoadJsonMethodNotExist(prop.name(), $ISourceLocation);
            }
            map[prop.name()] = &method;
        }
    }
    return map;
}

template<typename T, bool enabled, IBeanTrait trait>
const QMetaMethod& IBeanInterface<T, enabled, trait>::getJsonValidatorMethod() const
{
    const auto key = "$beanjsonvalidator__";
    if(getMetaClassInfos().contains(key)){
        const QMetaMethod& method = getMetaMethod(getMetaClassInfos()[key]);
        if(!method.isValid()){
            return method;
        }

        auto invalidCondition =
                method.returnType() != QMetaType::Bool ||
                method.parameterCount() != 1 ||
                method.parameterType(0) != qMetaTypeId<IJson>();
        if(invalidCondition){
            IBeanAbort::abortJsonValidatorSignatureInvalid($ISourceLocation);
        }

        return method;
    }
    static QMetaMethod method;
    return method;
}

template<typename T, bool enabled, IBeanTrait trait>
void IBeanInterface<T, enabled, trait>::$task()
{
    if constexpr (enabled){
        static std::once_flag flag;
        std::call_once(flag, [](){
            IBeanRegistBeanTypeUnit<T>::registType();
        });
    }
}

$PackageWebCoreEnd
