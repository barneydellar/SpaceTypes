# SpaceTypes

This is a C++ library for 3D points and vectors that are strongly typed on their coordinate space. It provides new types to wrap round an exsiting implementation, to ensures that vectors and points from different spaces cannot interact with each other. It is designed to catch these problems at compile-time, rather than at run time.

This is a header-only library. Simply #include "Space.h".
The library defines the namespace *Space*.

This library has only been tested using Visual Studio 2017 with C++17. The tests use Catch2.

## Licence

The library is licenced under the [Hippocratic License Version Number: 2.1.](LICENCE.md). See <https://firstdonoharm.dev> for more details.

## Summary

This namespace provides several templated types: Point, Vector and NormalizedVector. Optionally, XYPoint, XYVector and NormalizedXYVector are also available for a given space. Each point or vector lives in a Space. It is possible to convert points and vectors from space to another, in a type-safe way. Importantly, points and vectors can *only* interact with points and vectors from the same space. Attempting to add a vector from one space to a vector from another will result in a compilation error.

The library requires an existing implementation, which you will need to provide as a template argument. This implementation must be default contructible, and must have three doubles for x, y, and z as its first fields. The library also requires a Transform Manager which is able to convert the instances of the existing implementation from one Space to another.

The existing implementation of the 3D location or direction must implement the following API:

```cpp
class ExistingImplementation
{
public:
    ExistingImplementation();
private:
    double x;
    double y;
    double z;
    OtherThings ...
};
```

Or equally:

```cpp
class ExistingImplementation
{
public:
    ExistingImplementation();
    std::array<double, 3> m_values{};
    OtherThings ...
};
```

Once we have such an implementation, we also need units for the space:

```cpp
using NewSpaceUnits = double;
```

Alternatively, a strong type such as Jonathan Boccara's Named Type (https://github.com/joboccara/NamedType) can be used:

```cpp
using NewSpaceUnits = NamedType<double, struct NewSpaceUnitsTag>;
```

The units must be constructable from a double. They will be used to return the magnitude of a vector.

Once we have these and a unique identifer for the space in an enum called SpaceIDs:

```cpp
enum class SpaceIDs
{
    NewSpaceId
};
```

then a Space can be defined as follows:

```cpp
struct MySpace final : SpaceBase<MySpace, ExistingImplementation, XY::IsUsed, NewSpaceUnits> {
    static inline SpaceIDs id = SpaceIDs::NewSpaceId;
};
template <> const std::string SpaceTypeNameMap<MySpace>::name = "MySpace";
```

The XY parameter must be either XY::IsUsed or XY::IsNotUsed. It controls whether XY-only points and vectors are supported in this space.
They can be very useful for spaces such a Screen or View space, where you want to track coordinates on an XY-screen, and then convert them from there to a different space.

The *name* entry in the SpaceTypeNameMap will be used to serialize a point, vector or normalized vector.

Once this is done, then the space will have a Point, a Vector and a NormalizedVector defined for it, and optionally an XYPoint, an XYVector and a NormalizedXYVector.

## Creation

A point or vector can be declared like this:

```cpp
const YourSpace::Point p;
const MySpace::Vector v;
const MySpace::NormalizedVector nv;
```

A point or vector can be created from three doubles or values convertible to doubles.

```cpp
const YourSpace::Point p(1.1, 2.2, 3.3);
const MySpace::Vector v(1, 2, 3);
const MySpace::NormalizedVector nv(1, 0, 0);
```

A 2-dimensional point or vector can be created from two doubles or values convertible to doubles. The z-value will be set to zero.

```cpp
const YourSpace::XYPoint p(1.1, 2.2);
const MySpace::XYVector v(1, 2);
const MySpace::NormalizedXYVector v(1, 0);
```

Note that a NormalizedVector and a NormalisedXYVector will always have unit length, even if you create with non-unit values

```cpp
const YourSpace::NormalizedVector v(5, 0, 0); // v = {1, 0, 0}
const YourSpace::NormalizedXYVector v(5, 0); // v = {1, 0}

```

It is a runtime error to create a Normalized Vector with zero values.

Points or vectors can also be created for use in collections:

```cpp
std::vector<View::Point> vs{
    {1, 1, 1},
    {2, 2, 2}
};
```

## Adding vectors together

Vectors from the same space can be added together to produce a new vector:

```cpp
const MySpace::Vector v1(1, 2, 3);
const MySpace::Vector v2(4, 5, 6);
const auto sum = v1 + v2; // MySpace::Vector(5, 7, 9)
```

Vectors from the same space can be added together in place:

```cpp
MySpace::Vector v1(1, 2, 3);
const MySpace::Vector v2(4, 5, 6);
v1 += v2; // v1 = (5, 7, 9)
```

## Adding or subtracting vectors to or from points

Vectors can be added to a point from the same space to produce a new point:

```cpp
const MySpace::Vector v(1, 2, 3);
const MySpace::Point p1(4, 5, 6);
const auto p2 = p1 + v; // MySpace::Point(5, 7, 9)
```

Vectors can be added to a point from the same space in place:

```cpp
MySpace::Point p(4, 5, 6);
const MySpace::Vector v(1, 2, 3);
const auto p += v; // p = (5, 7, 9)
```

Vectors can be subtracted from a point from the same space to produce a new point:

```cpp
const MySpace::Vector v(1, 2, 3);
const MySpace::Point p1(4, 5, 6);
const auto p2 = p1 - v; // MySpace::Point(-3, -3, -3)
```

Vectors can be subtracted from a point from the same space in place:

```cpp
MySpace::Point p(4, 5, 6);
const MySpace::Vector v(1, 2, 3);
const auto p -= v; // p = (-3, -3, -3)
```

## Subtracting points

Points from the same space can be subtracted to produce the vector from one point to the other:

```cpp
const MySpace::Point p1(4, 5, 6);
const MySpace::Point p2(1, 2, 3);
const auto v = p1 - p2; // MySpace::Vector(3, 3, 3)
```

## Scaling

Vectors can be scaled to produce a new vector

```cpp
const MySpace::Vector v1(4, 5, 6);
const auto v2 = v1 * 2; // MySpace::Vector(8, 10, 12)
```

Vectors can be scaled in place

```cpp
MySpace::Vector v(4, 5, 6);
const auto v *= 2; // v = (8, 10, 12)
```

## XY Vectors and Points

If the space supports an XY plane, you can create XY vectors, points and normalized vectors. You can also convert a 3D point or vector to a 2D one by calling ToXY(). This simply removes the Z part of the vector or point.

```cpp
const MySpace::XYVector v(5, 0);
```

```cpp
const MySpace::Vector v_3d(1, 2, 3);
const auto v_xy = v_3d.ToXY(); // MySpace::XYVector(1, 2)
```

## Normalisation

You can get the normal form of a vector

```cpp
const MySpace::Vector v1(5, 0, 0);
const auto v2 = v1.Norm(); // MySpace::NormalizedVector(1, 0, 0)
```

In addition, you can construct a normalized vector as you would a normal vector, but the result will always be normalized:

```cpp
const MySpace::NormalizedVector v(5, 0, 0); // v = (1, 0, 0)
```

XY vectors can also be normalized:

```cpp
const MySpace::XYVector v1(5, 0);
const auto v2 = v1.Norm(); // MySpace::NormalizedXYVector(1, 0)
```

## Dot Product

You can get the dot product from two vectors in the same space

```cpp
const MySpace::Vector v1(1, 2, 3);
const MySpace::Vector v2(4, 5, 6);
const auto dot = v1.Dot(v2); // double dot = 4+10+18 = 32;
```

## Cross Product

You can get the cross product from two vectors in the same space

```cpp
const MySpace::Vector v1(1, 0, 0);
const MySpace::Vector v2(0, 1, 0);
const auto cross = v1.Cross(v2); // MySpace::Vector(0, 0, 1);
```

You can get the cross product from two vectors in the same space using the * operator:

```cpp
const MySpace::Vector v1(1, 0, 0);
const MySpace::Vector v2(0, 1, 0);
const auto cross = v1 * v2; // MySpace::Vector(0, 0, 1)
```

You can get the cross product from two vectors in the same space using the *= operator:

```cpp
MySpace::Vector v1(1, 0, 0);
const MySpace::Vector v2(0, 1, 0);
const auto v1 *= v2; // v1 = (0, 0, 1);
```

### Normalized Vectors

The cross-product of two normalized vectors is always a normalized vector:

```cpp
const MySpace::NormalizedVector v1(1, 0, 0);
const MySpace::NormalizedVector v2(0, 1, 0);
const auto cross = v1.Cross(v2); // MySpace::Normalized(0, 0, 1);
```

## Magnitude

You can get the magnitude of a vector. This will be in strongly typed units, e.g. MySpace is in NewSpaceUnits, YourSpace is in Pixels.

```cpp
const YourSpace::Vector v1(5, 0, 0);
const auto m = v1.Mag(); // m = 5 Millimetres
```

## Comparison

Vectors from the same space can be compared using == or !=. This will test each value with a tolerance of 1e-6.

```cpp
const MySpace::Vector v1(1, 0, 0);
const MySpace::Vector v2(0, 1, 0);
const auto b_equality = v1 == v2; // false
const auto b_inequality = v1 != v2; // true
```

Points from the same space can be compared using == or !=.

```cpp
const MySpace::Point p1(1, 0, 0);
const MySpace::Point p2(0, 1, 0);
const auto b_equality = p1 == p2; // false
const auto b_inequality = p1 != p2; // true
```

## Conversion between spaces

Actual geometric transformations are outsourced to a transform manager. This needs to implement two method templates: TransformPoint and TransformVector. Both of these methods receive an ExistingImplementation, and must also return an ExistingImplementation.

Vectors from one space can be converted to another space. Under the hood, this makes a call to TransformVector on the TransformManager.

```cpp
const TransformManager tm;
const MySpace::Vector v_new_space(1, 0, 0);
const auto v_view = v_new_space.ConvertTo<YourSpace>(tm); // YourSpace::Vector(x, y, z)
```

Points from one space can be converted to another space. Under the hood, this makes a call to TransformPoint on the TransformManager.

```cpp
const TransformManager tm;
const MySpace::Point p_new_space(1, 0, 0);
const auto p = p_view.ConvertTo<YourSpace>(tm); // YourSpace::Point(x, y, z)
```

### Example Transform Manager

Suppose we have two spaces defined, with units in *double*. Each has a static value identifying the type.

```cpp
enum class SpaceIDs
{
    FirstSpace,
    SecondSpace
};
struct FirstSpace final : SpaceBase<FirstSpace, ExistingImplementation, double> {
    static inline SpaceIDs id = SpaceIDs::FirstSpace;
};
struct SecondSpace final : SpaceBase<SecondSpace, ExistingImplementation, double> {
    static inline SpaceIDs id = SpaceIDs::SecondSpace;
};
```

We can then define a TransformManager as follows:

```cpp
class TransformManager final
{
public:
    template <typename From, typename To>
    ExistingImplementation TransformVector(
        ExistingImplementation
    ) const noexcept {
        using namespace Space;
        if (From::id == SpaceIDs::FirstSpace && To::id == SpaceIDs::SecondSpace) {
            // Insert actual conversion code here
        }
        // etc
    }
    template <typename From, typename To>
    ExistingImplementation TransformPoint(
        ExistingImplementation
    ) const noexcept {
        using namespace Space;
        if (From::id == SpaceIDs::FirstSpace && To::id == SpaceIDs::SecondSpace) {
            // Insert actual conversion code here
        }
        // etc
    }
};
```

## Access

There are several ways to access the underlying data:

### Random Access

The data from a point or vector can be accessed using square brackets. The only valid indices are 0, 1, or 2. Any other value will cause a runtime throw.

```cpp
const MySpace::Vector v(1, 2, 3);
// v[0] == 1;
```

#### Named Element Modification

The data from a point or vector can be modified using the SetX(), SetY() or SetZ() functions.

```cpp
MySpace::Vector v(1, 2, 3);
v.SetX((5); // v == {5, 2, 3};
```

#### Named Element Access

The data from a point or vector can be accessed using the X(), Y() or Z() functions.

```cpp
const MySpace::Vector v(1, 2, 3);
// v.Y() == 2;
```

### At Access

The data from a point or vector can be accessed using at(). The only valid indices are 0, 1 or 2. Any other value will cause a compilation error.

```cpp
const MySpace::Vector v(1, 2, 3);
//v.at<2>() == 3;
```

### Iteration

You can iterate over the values, and use STL algorithms on Points, Vectors and NormalizedVectors:

```cpp
MySpace::Point p(2, 3, 4);

std::transform(
    p.cbegin(),
    p.cend(),
    p.begin(),
    [](const double d) {return d * 2; }
);
// p == MySpace::Point(4, 6, 8);
```

Non-normalized vectors and points also support non-const access via _base::begin() and _base::end().

## Serialisation

Points, Vectors and NormalisedVectors can be serialised:

```cpp
const MySpace::Point p(2, 3, 4);
std::cout << p;
// Prints "MySpace::Point (2, 3, 4)"
```

## Compile-time errors

A key feature of this library is that it is a compile-time error to make points or vectors from different spaces interact with eachother. The library also has human-readable errors, so if you try and add a vector from one space to a point from another space, for example, you get the following compiler error:

```
You can't do anything with vectors or points from different spaces.
```

Similarly, if you try and add two Points together, you get the following compiler error:

```
It is not valid to add points together.
```

These checks can be disabled by defining the following Macro:

```cpp
#define IGNORE_SPACE_STATIC_ASSERT
```

This is usful if you want the extra checks available in a Debug build for example, but disabled in a Release build.
