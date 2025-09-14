#include "IBeanInterface.h"

$PackageWebCoreBegin

namespace detail
{
    QMetaMethod getMetaMethod(const QMetaObject& meta, const QString &name);

    QVector<std::string> getFieldNames(const QMetaObject &meta);

    QStringList getRequiredFields(const QMetaObject& meta)
    {
        QStringList fields;
        const QString prefix = "$beanfieldrequired_";
        const auto& infos = IMetaUtil::getMetaClassInfoMap(meta);
        for(const auto& info : infos.keys()){
            if(info.startsWith(prefix)){
                fields.append(infos[info]);
            }
        }
        return fields;
    }

    std::map<std::string, QMetaMethod> getRequiredMethodMap(const QMetaObject &meta)
    {
        std::map<std::string, QMetaMethod> map;
        const auto fields = detail::getRequiredFields(meta);
        const auto& props = IMetaUtil::getMetaProperties(meta);
        for(const auto& prop : props){
            if(fields.contains(prop.name())){
                const auto& method = detail::getMetaMethod(meta, "$" + QString(prop.name()) + "_fromJsonValue");
                if(!method.isValid()){
                    IBeanAbort::abortLoadJsonMethodNotExist(prop.name(), $ISourceLocation);
                }
                map[prop.name()] = method;
            }
        }
        return map;
    }

    std::map<std::string, QMetaMethod> getOptionalMethodMap(const QMetaObject &meta)
    {
        std::map<std::string, QMetaMethod> map;
        const auto fields = detail::getRequiredFields(meta);
        const auto& props = IMetaUtil::getMetaProperties(meta);
        for(const auto& prop : props){
            if(!fields.contains(prop.name())){
                const auto& method = detail::getMetaMethod(meta, "$" + QString(prop.name()) + "_fromJsonValue");
                if(!method.isValid()){
                    IBeanAbort::abortLoadJsonMethodNotExist(prop.name(), $ISourceLocation);
                }
                map[prop.name()] = method;
            }
        }
        return map;
    }

    QMetaMethod getJsonValidatorMethod(const QMetaObject &meta)
    {
        const auto key = "$beanjsonvalidator__";
        auto infos = IMetaUtil::getMetaClassInfoMap(meta);
        if(infos.contains(key)){
            const QMetaMethod& method = detail::getMetaMethod(meta, infos[key]);
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
        return {};
    }

}

std::map<std::string, QMetaMethod> detail::getMethodPair(const QMetaObject &meta)
{
    std::map<std::string, QMetaMethod> methodPair;
    auto props = IMetaUtil::getMetaProperties(meta);
    for(const auto& prop : props){
        const auto& method = detail::getMetaMethod(meta, "$" + QString(prop.name()) + "_toJsonValue");
        if(!method.isValid()){
            IBeanAbort::abortToJsonMethodNotExist(prop.name(), $ISourceLocation);
        }
        methodPair[prop.name()] = method;
    }
    return methodPair;
}


IJson detail::convertData(const void * handle, const std::map<std::string, QMetaMethod> &methodPair)
{
    IJson obj = IJson::object();
    for(const auto& [key, method] : methodPair){
        IJson json;
        method.invokeOnGadget(const_cast<void*>(handle), Q_RETURN_ARG(IJson, json));
        obj[key] = std::move(json);
    }
    return obj;
}


bool processLoadJson(const void *handle,
                     const IJson &value,
                     const IBeanTrait &beanTrait,
                     const std::map<std::string, QMetaMethod>& required,
                     const std::map<std::string, QMetaMethod>& optional,
                     const QVector<std::string>& allFields,
                     const QMetaMethod &validator)
{


    if(!value.is_object()) {
        return false;
    }

    bool ok;
    if(validator.isValid()){
        validator.invokeOnGadget(const_cast<void*>(handle),Q_RETURN_ARG(bool, ok), Q_ARG(IJson, value));
        if(!ok){
            return false;
        }
    }

    for(const auto& [key, method] : required){
        if(!value.contains(key)){
            return false;
        }
        method.invokeOnGadget(const_cast<void*>(handle),Q_RETURN_ARG(bool, ok), Q_ARG(IJson, value[key]));
        if(!ok){
            return false;
        }
    }

    for(const auto& [key, method] : optional){
        if(value.contains(key)){
            method.invokeOnGadget(const_cast<void*>(handle),Q_RETURN_ARG(bool, ok), Q_ARG(IJson, value[key]));
            if(!ok){
                return false;
            }
        }else if(beanTrait != IBeanTrait::Tolerance){
            return false;
        }
    }

    if(beanTrait == IBeanTrait::Full){
        for(const auto&val : value.items()){
            if(!allFields.contains(val.key())){
                return false;
            }
        }
    }

    return true;
}
// below

QMetaMethod detail::getMetaMethod(const QMetaObject& meta, const QString &name)
{
    const auto& methods = IMetaUtil::getMetaMethods(meta);
    for(const QMetaMethod& method : methods){
        if(method.name() == name){
            return method;
        }
    }

    // TODO: qFatal here
    return {};
}

QVector<std::string> detail::getFieldNames(const QMetaObject &meta)
{
    QVector<std::string> fields;
    const auto& props = IMetaUtil::getMetaProperties(meta);
    for(const auto& prop : props){
        fields.append(prop.name());
    }
    return fields;
}

$PackageWebCoreEnd
