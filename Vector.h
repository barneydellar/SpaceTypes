#include "BaseImpl.h"
#include "NormalizedVector.h"

namespace Space::detail {

    //--------------------------------------------------------------------------------------------

    template <typename Space>
    class Vector final : public ModifiableBaseImpl<Space>
    {
        friend class Space::NormalizedVector;
        friend class Space::Point;
        using _base = ModifiableBaseImpl<Space>;

    public:

        explicit Vector(const std::array<double, 3> value) : _base(value) {}
        explicit Vector(const double x, const double y, const double z) : _base(x, y, z) {}
        explicit Vector(const double x, const double y) : _base(x, y) {}
        explicit Vector(const typename Space::NormalizedVector nv) : _base(nv.X(), nv.Y(), nv.Z()) {}

        //------------------------------------------------------------------------------------

        bool operator == (const typename Space::Vector& other) const {
            return std::equal(_base::m_values.cbegin(), _base::m_values.cend(), other.m_values.cbegin());
        }
        bool operator == (const typename Space::NormalizedVector& other) const {
            return std::equal(_base::m_values.cbegin(), _base::m_values.cend(), other.m_values.cbegin());
        }
        template <typename WrongSpace>
        StaticAssert::invalid_equality operator == (const NormalizedVector<WrongSpace>&) const {
            return StaticAssert::invalid_equality{};
        }
        template <typename WrongSpace>
        StaticAssert::invalid_equality operator == (const Vector<WrongSpace>&) const {
            return StaticAssert::invalid_equality{};
        }
        template <typename AnySpace>
        StaticAssert::invalid_point_vector_equality operator == (const Point<AnySpace>&) const {
            return StaticAssert::invalid_point_vector_equality{};
        }

        //------------------------------------------------------------------------------------

        bool operator != (const typename Space::Vector& other) const {
            return !(operator==(other));
        }
        bool operator != (const typename Space::NormalizedVector& other) const {
            return !(operator==(other));
        }
        template <typename WrongSpace>
        StaticAssert::invalid_equality operator != (const Vector<WrongSpace>&) const {
            return StaticAssert::invalid_equality{};
        }
        template <typename WrongSpace>
        StaticAssert::invalid_equality operator != (const NormalizedVector<WrongSpace>&) const {
            return StaticAssert::invalid_equality{};
        }
        template <typename AnySpace>
        StaticAssert::invalid_point_vector_equality operator != (const Point<AnySpace>&) const {
            return StaticAssert::invalid_point_vector_equality{};
        }

        //-------------------------------------------------------------------------------------

        template <typename OtherSpace, typename TransformManager>
        typename OtherSpace::Vector ConvertTo(const TransformManager& transform_manager) const {
            return typename OtherSpace::Vector(transform_manager.template Transform33<Space, OtherSpace>(_base::m_values));
        }

        //------------------------------------------------------------------------------------

        // Operators
        typename Space::Vector operator*(const double& d) const {
            return Space::Vector(_base::ScaleArray(_base::m_values, d));
        }
        typename Space::Vector& operator*=(const double& d) {
            _base::m_values = _base::ScaleArray(_base::m_values, d);
            return *this;
        }

        typename Space::Vector operator*(const typename Space::Vector& rhs) const {
            return this->Cross(rhs);
        }
        template <typename WrongSpace>
        StaticAssert::invalid_vector_cross operator*(const Vector<WrongSpace>&) const {
            return StaticAssert::invalid_vector_cross{};
        }

        typename Space::Vector operator*=(const typename Space::Vector& rhs) {
            return *this = this->Cross(rhs);
        }
        template <typename WrongSpace>
        StaticAssert::invalid_vector_cross operator*=(const Vector<WrongSpace>&) const {
            return StaticAssert::invalid_vector_cross{};
        }

        //-------------------------------------------------------------------------------------

        typename Space::Vector operator+(const typename Space::Vector& rhs) const {
            return Space::Vector(_base::SumArrays(_base::m_values, rhs.m_values));
        }
        typename Space::Vector operator+(const typename Space::NormalizedVector& rhs) const {
            return Space::Vector(_base::SumArrays(_base::m_values, rhs.m_values));
        }
        template <typename WrongSpace>
        StaticAssert::invalid_vector_to_vector_addition operator+(const Vector<WrongSpace>&) const {
            return StaticAssert::invalid_vector_to_vector_addition{};
        }
        template <typename WrongSpace>
        StaticAssert::invalid_vector_to_vector_addition operator+(const NormalizedVector<WrongSpace>&) const {
            return StaticAssert::invalid_vector_to_vector_addition{};
        }
        template <typename AnySpace>
        StaticAssert::invalid_point_to_vector_addition operator+(const Point<AnySpace>&) const {
            return StaticAssert::invalid_point_to_vector_addition{};
        }

        //-------------------------------------------------------------------------------------

        typename Space::Vector operator+=(const typename Space::Vector& rhs) {
            _base::m_values = _base::SumArrays(_base::m_values, rhs.m_values);
            return *this;
        }
        typename Space::Vector operator+=(const typename Space::NormalizedVector& rhs) {
            _base::m_values = _base::SumArrays(_base::m_values, rhs.m_values);
            return *this;
        }
        template <typename WrongSpace>
        StaticAssert::invalid_vector_to_vector_addition operator += (const Vector<WrongSpace>&) const {
            return StaticAssert::invalid_vector_to_vector_addition{};
        }
        template <typename WrongSpace>
        StaticAssert::invalid_vector_to_vector_addition operator += (const NormalizedVector<WrongSpace>&) const {
            return StaticAssert::invalid_vector_to_vector_addition{};
        }

        //-------------------------------------------------------------------------------------

        typename Space::Unit Mag() const {
            return Space::Unit{ _base::MagHelper() };
        }

        double Mag_double() const {
            return _base::MagHelper();
        }

        typename Space::NormalizedVector Norm() const {
            return Space::NormalizedVector(_base::m_values);
        }

        double Dot(const typename Space::Vector& other) const {
            return _base::DotArrays(_base::m_values, other.m_values);
        }
        double Dot(const typename Space::NormalizedVector& other) const {
            return _base::DotArrays(_base::m_values, other.m_values);
        }
        template <typename WrongSpace>
        StaticAssert::invalid_vector_dot Dot(const Vector<WrongSpace>&) const {
            return StaticAssert::invalid_vector_dot{};
        }
        template <typename WrongSpace>
        StaticAssert::invalid_vector_dot Dot(const NormalizedVector<WrongSpace>&) const {
            return StaticAssert::invalid_vector_dot{};
        }

        typename Space::Vector Cross(const typename Space::Vector& other) const {
            return Space::Vector(_base::CrossArrays(_base::m_values, other.m_values));
        }
        template <typename WrongSpace>
        StaticAssert::invalid_vector_cross Cross(const Vector<WrongSpace>&) const {
            return StaticAssert::invalid_vector_cross{};
        }
    };

    template <typename Space>
    std::ostream& operator << (
        std::ostream& os,
        const Vector<Space>& item
    ) {
        const auto space = SpaceTypeNameMap<Space>::name;
        os << space << "::Vector (" << item.X() << ", " << item.Y() << ", " << item.Z() << ")";
        return os;
    }
}
