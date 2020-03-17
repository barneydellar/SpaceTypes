#pragma once

namespace Space {

    template <typename Space, typename ExternalImplementation>
    class Vector : public Base<Space, ExternalImplementation>
    {
    public:
        using _base = Base<Space, ExternalImplementation>;
        using _base::_base;

        friend std::ostream& operator << (
            std::ostream& os,
            const Vector<Space, ExternalImplementation>& item
        ) {
            const auto space = SpaceTypeNameMap<Space>::name;
            os << space << "::Vector (" << item.X() << ", " << item.Y() << ", " << item.Z() << ")";
            return os;
        }
    };
}
