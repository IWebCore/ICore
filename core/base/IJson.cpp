#include <QString>
#include <json.hpp>

using IJson = nlohmann::json;

namespace nlohmann
{
template <>
struct adl_serializer<QString>
{
    static QString from_json(const IJson& j)
    {
        if(j.is_string()){
            return QString::fromStdString(j.template get<std::string>());
        }
        return QString::fromStdString(j.dump());
    }

    static void to_json(IJson& j, const QString& str)
    {
        j = str.toStdString();
    }
};
}
