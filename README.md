# SpaceTypes

A C++ library for 3D points and vectors that are strongly typed on their coordinate space.

This library has only been tested using Visual Studio 2017 with C++17. The tests use Catch2.

This is a header-only library. Simply #include "Space.h".
The library defines the namespace *Space*.

## Licence

The library is licenced under the MIT licence (<https://opensource.org/licenses/MIT)>

## Summary

This namespace provides three templated types: Point, Vector and NormalizedVector. Each point or vector lives in a Space. It is possible to convert points and vectors from space to another.
Importantly, points and vectors can *only* interact with points and vectors from the same space.
Attempting to, say, add a vector from one space to a vector from another will result in a compilation error.

A Space can be defined as follows:

```cpp
using NewSpaceUnits = ...;

struct NewSpace final : Space::SpaceBase<NewSpace, NewSpaceUnits> {};
template <> const std::string SpaceTypeNameMap<Volume>::name = "NewSpace";
```

The units must be constructable from a double. It will be used to return the magnitude of a vector.
The entry in the SpaceTypeNameMap will be used to serialize a point, vector or normalized vector.

The *name* is used if and when a point or vector is serialised.  

## Creation

A point or vector can be created from three doubles.

```cpp
const ViewSpace::Point p(1, 2, 3);
const NewSpace::Vector v(1, 2, 3);
const NewSpace::NormalizedVector v(1, 0, 0);
```

A point or vector can be created from two doubles. The z-value will be set to zero.

```cpp
const ViewSpace::Point p(1, 2);
const NewSpace::Vector v(1, 2);
const NewSpace::NormalizedVector v(1, 0);
```

Note that a NormalizedVector will always have unit length, even if you create with non-unit values

```cpp
const ViewSpace::NormalizedVector v(5, 0, 0); // v = {1, 0, 0}
```

It is an error to create a NormalizedVector with zero values. 


## Adding

Vectors from the same space can be added together to produce a new vector:

```cpp
const NewSpace::Vector v1(1, 2, 3);
const NewSpace::Vector v2(4, 5, 6);
const auto sum = v1 + v2; // NewSpace::Vector(5, 7, 9)
```

Vectors from the same space can be added together in place:

```cpp
NewSpace::Vector v1(1, 2, 3);
const NewSpace::Vector v2(4, 5, 6);
v1 += v2; // v1 = (5, 7, 9)
```

Vectors can be added to a point from the same space can be added together to produce a new point:

```cpp
const NewSpace::Vector v(1, 2, 3);
const NewSpace::Point p1(4, 5, 6);
const auto p2 = p1 + v; // NewSpace::Point(5, 7, 9)
```

Vectors can be added to a point from the same space can be added together in place:

```cpp
NewSpace::Point p(4, 5, 6);
const NewSpace::Vector v(1, 2, 3);
const auto p += v; // p = (5, 7, 9)
```

## Subtracting

Points from the same space can be subtracted to produce a vector:

```cpp
const NewSpace::Point p1(4, 5, 6);
const NewSpace::Point p2(1, 2, 3);
const auto v = p1 - p2; // NewSpace::Vector(3, 3, 3)
```

## Scaling

Vectors can be scaled to produce a new vector

```cpp
const NewSpace::Vector v1(4, 5, 6);
const auto v2 = v1 * 2; // NewSpace::Vector(8, 10, 12)
```

Vectors can be scaled in place

```cpp
NewSpace::Vector v(4, 5, 6);
const auto v *= 2; // v = (8, 10, 12)
```

## Dot Product

You can get the dot product from two vectors in the same space

```cpp
const NewSpace::Vector v1(1, 2, 3);
const NewSpace::Vector v2(4, 5, 6);
const auto dot = v1.Dot(v2); // double dot = 4+10+18 = 32;
```

## Cross Product

You can get the cross product from two vectors in the same space

```cpp
const NewSpace::Vector v1(1, 0, 0);
const NewSpace::Vector v2(0, 1, 0);
const auto cross = v1.Cross(v2); // NewSpace::Vector(0, 0, 1);
```

You can get the cross product from two vectors in the same space using the * operator:

```cpp
const NewSpace::Vector v1(1, 0, 0);
const NewSpace::Vector v2(0, 1, 0);
const auto cross = v1 * v2; // NewSpace::Vector(0, 0, 1)
```

You can get the cross product from two vectors in the same space using the *= operator:

```cpp
NewSpace::Vector v1(1, 0, 0);
const NewSpace::Vector v2(0, 1, 0);
const auto v1 *= v2; // v1 = (0, 0, 1);
```

## Normalisation

You can get the normal form of a vector

```cpp
const NewSpace::Vector v1(5, 0, 0);
const auto v2 = v1.Norm(); // NewSpace::NormalizedVector(1, 0, 0)
```

In addition, you can construct a normalized vector as you would a normal vector, but the result will
always be normalized:

```cpp
const NewSpace::NormalizedVector v(5, 0, 0); // v = (1, 0, 0)
```

## Magnitude

You can get the magnitude of a vector. This will be in strongly typed units, e.g. NewSpace is in NewSpaceUnits, ViewSpace is in Pixels.

```cpp
const ViewSpace::Vector v1(5, 0, 0);
const auto m = v1.Mag(); // m = 5 Millimetres
```

## Comparison

Vectors from the same space can be compared using == or !=. Under the hood, this checks for approximate equality.

```cpp
const NewSpace::Vector v1(1, 0, 0);
const NewSpace::Vector v2(0, 1, 0);
const auto b_equality = v1 == v2; // false
const auto b_inequality = v1 != v2; // true
```

Points from the same space can be compared using == or !=. Under the hood, this checks for approximate equality.

```cpp
const NewSpace::Point p1(1, 0, 0);
const NewSpace::Point p2(0, 1, 0);
const auto b_equality = p1 == p2; // false
const auto b_inequality = p1 != p2; // true
```

## Conversion between spaces</H3>

Actual geometric transformations are outsourced to a transform manager. This needs to implement two method templates: Transform and Transform33.

Vectors from one space can be converted to another space. Under the hood, this makes a call to Transform33 on the TransformManager.

```cpp
const TransformManager tm;
const NewSpace::Vector v_new_space(1, 0, 0);
const auto v_view = v_new_space.ConvertTo<ViewSpace>(tm); // ViewSpace::Vector(x, y, z)
```

Points from one space can be converted to another space. Under the hood, this makes a call to Transform on the TransformManager.

```cpp
const TransformManager tm;
const NewSpace::Point p_new_space(1, 0, 0);
const auto p = p_view.ConvertTo<ViewSpace>(tm); // ViewSpace::Point(x, y, z)
```

### Example

Suppose we have two spaces defined, with units in *double*. Each has a static value identifying the type.

```cpp
enum class IDs
{
    FirstSpace,
    SecondSpace
};
struct FirstSpace final : SpaceBase<FirstSpace, double> {
    static inline constexpr SpaceIDs id = SpaceIDs::FirstSpace;
};
struct SecondSpace final : SpaceBase<SecondSpace, double> {
    static inline constexpr SpaceIDs id = SpaceIDs::SecondSpace;
};
```

We can then define a TransformManager as follows:

```cpp
class TransformManager final
{
public:
    template <typename From, typename To>
    std::array<double, 3> Transform33(
        std::array<double, 3>
    ) const noexcept {
        using namespace Space;
        if constexpr (From::id == SpaceIDs::FirstSpace) {
            return { 1, 2, 3 }; // Insert more useful logic here
        } else {
            return { -1, -2, -3 }; // Insert more useful logic here
        }
    }
    template <typename From, typename To>
    std::array<double, 3> Transform(
        std::array<double, 3>
    ) const noexcept {
        using namespace Space;
        if constexpr (From::id == SpaceIDs::FirstSpace) {
            return { 5, 6, 7 }; // Insert more useful logic here
        } else {
            return { -5, -6, -7 }; // Insert more useful logic here
        }
    }
};
```


## Access

There are several ways to access the underlying data:

### Random Access

The data from a point or vector can be accessed using square brackets. The only valid indices
are 0, 1, or 2. Any other value will cause a runtime throw.

```cpp
const NewSpace::Vector v(1, 2, 3); 
// v[0] == 1;
```

#### Named Access</H4>

The data from a point or vector can be accessed using the X(), Y() or Z() functions.

```cpp
const NewSpace::Vector v(1, 2, 3);
// v.Y() == 2;
```

### At Access

The data from a point or vector can be accessed using at(). The only valid indices are 0, 1 or 2.
Any other value will cause a compilation error.

```cpp
const NewSpace::Vector v(1, 2, 3);
//v.at<2>() == 3;
```

### Iteration

You can iterate over the values, and use STL algorithms on Points, Vectors and NormalizedVectors:

```cpp
NewSpace::Point p(2, 3, 4);

std::transform(
    p.cbegin(),
    p.cend(),
    p.begin(),
    [](const double d) {return d * 2; }
);
// p == NewSpace::Point(4, 6, 8);
```

## Serialisation

Points, Vectors and NormalisedVectors can be serialised:

```cpp
const NewSpace::Point p(2, 3, 4);
std::cout << p;
// Prints "NewSpace::Point (2, 3, 4)"
```
