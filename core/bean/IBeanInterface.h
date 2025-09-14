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
    virtual bool loadJson(const IJson &value, const IBeanTrait& = trait);
    static IResult<T> fromJson(const IJson& value, const IBeanTrait& = trait);

private:
    QStringList getRequiredFields() const;
    QVector<std::string> getAllFields() const;

protected:
    virtual void $task() override;
};


$IPackageBegin(detail)

    std::map<std::string, QMetaMethod> getMethodPair(const QMetaObject&);
    IJson convertData(const void*, const std::map<std::string, QMetaMethod>&);

    std::map<std::string, QMetaMethod> getRequiredMethodMap(const QMetaObject&);
    std::map<std::string, QMetaMethod> getOptionalMethodMap(const QMetaObject&);
    QMetaMethod getJsonValidatorMethod(const QMetaObject&);
    QVector<std::string> getFieldNames(const QMetaObject&);

    bool processLoadJson(const void* handle,
                         const IJson &value,
                         const IBeanTrait& beanTrait,
                         const std::map<std::string, QMetaMethod>& required,
                         const std::map<std::string, QMetaMethod>& optional,
                         const QVector<std::string>& fields,
                         const QMetaMethod& validator);


$IPackageEnd(detail)


template<typename T, bool enabled, IBeanTrait trait>
IJson IBeanInterface<T, enabled, trait>::toJson() const
{
    static const auto methodPair = detail::getMethodPair(T::staticMetaObject);
    return detail::convertData(this, methodPair);
}

template<typename T, bool enabled, IBeanTrait trait>
bool IBeanInterface<T, enabled, trait>::loadJson(const IJson &value, const IBeanTrait& beanTrait)
{
    static const auto requiredMethodPair = detail::getRequiredMethodMap(T::staticMetaObject);
    static const auto optionalMethodPair = detail::getOptionalMethodMap(T::staticMetaObject);
    static const auto jsonValidator = detail::getJsonValidatorMethod(T::staticMetaObject);
    static const auto allFields = detail::getFieldNames(T::staticMetaObject);

    return detail::processLoadJson(this, value, beanTrait, requiredMethodPair, optionalMethodPair, allFields, jsonValidator);
}

template<typename T, bool enabled, IBeanTrait trait>
IResult<T> IBeanInterface<T, enabled, trait>::fromJson(const IJson& value, const IBeanTrait& beanTrait)
{
    T t;
    if(t.loadJson(value, beanTrait)){
        return t;
    }
    return std::nullopt;
}

// template<typename T, bool enabled, IBeanTrait trait>
// const QMetaProperty& IBeanInterface<T, enabled, trait>::getMetaProperty(const QString& name) const
// {
//     static const auto& props = getMetaProperties();
//     for(const QMetaProperty& prop : props){
//         if(prop.name() == name){
//             return prop;
//         }
//     }

//     static QMetaProperty empty{};
//     return empty;
// }



// template<typename T, bool enabled, IBeanTrait trait>
// std::map<std::string, const QMetaMethod *> IBeanInterface<T, enabled, trait>::getRequiredMethodMap() const
// {
//     std::map<std::string, const QMetaMethod *> map;
//     const auto fields = getRequiredFields();
//     const auto& props = getMetaProperties();
//     for(const auto& prop : props){
//         if(fields.contains(prop.name())){
//             const auto& method = getMetaMethod("$" + QString(prop.name()) + "_fromJsonValue");
//             if(!method.isValid()){
//                 IBeanAbort::abortLoadJsonMethodNotExist(prop.name(), $ISourceLocation);
//             }
//             map[prop.name()] = &method;
//         }
//     }
//     return map;
// }

// template<typename T, bool enabled, IBeanTrait trait>
// std::map<std::string, const QMetaMethod *> IBeanInterface<T, enabled, trait>::getOptionalMethodMap() const
// {
//     std::map<std::string, const QMetaMethod *> map;
//     const auto fields = getRequiredFields();
//     const auto& props = getMetaProperties();
//     for(const auto& prop : props){
//         if(!fields.contains(prop.name())){
//             const auto& method = getMetaMethod("$" + QString(prop.name()) + "_fromJsonValue");
//             if(!method.isValid()){
//                 IBeanAbort::abortLoadJsonMethodNotExist(prop.name(), $ISourceLocation);
//             }
//             map[prop.name()] = &method;
//         }
//     }
//     return map;
// }

// template<typename T, bool enabled, IBeanTrait trait>
// const QMetaMethod& IBeanInterface<T, enabled, trait>::getJsonValidatorMethod() const
// {
//     const auto key = "$beanjsonvalidator__";
//     if(getMetaClassInfos().contains(key)){
//         const QMetaMethod& method = getMetaMethod(getMetaClassInfos()[key]);
//         if(!method.isValid()){
//             return method;
//         }

//         auto invalidCondition =
//                 method.returnType() != QMetaType::Bool ||
//                 method.parameterCount() != 1 ||
//                 method.parameterType(0) != qMetaTypeId<IJson>();
//         if(invalidCondition){
//             IBeanAbort::abortJsonValidatorSignatureInvalid($ISourceLocation);
//         }

//         return method;
//     }
//     static QMetaMethod method;
//     return method;
// }

template<typename T, bool enabled, IBeanTrait trait>
void IBeanInterface<T, enabled, trait>::$task()
{
    if constexpr (enabled){
        static std::once_flag flag;
        std::call_once(flag, [](){
            // IBeanRegistBeanTypeUnit<T>::registType();
        });
    }
}

$PackageWebCoreEnd
