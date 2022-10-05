#include "Vector3.h"

namespace neu
{
    const Vector3 Vector3::one{ 1, 1, 1 };
    const Vector3 Vector3::zero{ 0,0, 0 };
    const Vector3 Vector3::up{ 0,-1, 0 };
    const Vector3 Vector3::down{ 0,1, 0 };
    const Vector3 Vector3::left{ -1,0, 0 };
    const Vector3 Vector3::right{ 1, 0, 0 };

    std::istream& operator >> (std::istream& stream, Vector3& v)
    {
        std::string line;
        std::getline(stream, line);

        // { ##, ## }
        std::string xs = line.substr(line.find("{") + 1, line.find(",") - line.find("{") - 1);
        v.x = std::stof(xs);

        std::string ys = line.substr(line.find(","));
        v.y = std::stof(ys);

        std::string zs = line.substr(line.find(",") + 1, line.find("}") - line.find(",") - 1);
        v.z = std::stof(zs);

        return stream;
    }
}