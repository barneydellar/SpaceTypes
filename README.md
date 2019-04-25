# SpaceTypes

A C++ library for 3D points and vectors that are strongly typed on their coordinate space.

This is a header-only library. Simply #include "Space.h".
The library defines the namespace *Space*.

## Licence

The library is licenced under the MIT licence (https://opensource.org/licenses/MIT)

## The *Space* namespace

### Summary

This namespace provides three templated types: Point, Vector and NormalizedVector. Each point or vector lives in a 
Space. It is possible to convert points and vectors from space to another.

A Space can be defined as follows:

```cpp
    using NewSpaceUnits = ...;

    struct NewSpace final : Space::SpaceBase<NewSpace, NewSpaceUnits> {};
    template <> const std::string SpaceTypeNameMap<Volume>::name = "NewSpace";
```

The units must be constructable from a double. It will be used to return the magnitude of a vector.
The entry in the SpaceTypeNameMap will be used to serialize a point, vector or normalized vector.

### Creation

A point or vector can be created from three doubles.

```cpp
const View::Point p(1, 2, 3);
const Patient::Vector v(1, 2, 3);
const Image::NormalizedVector v(1, 0, 0);
```

A point or vector can be created from two doubles. The z-value will be set to zero.

```cpp
const View::Point p(1, 2);
const Patient::Vector v(1, 2);
const Image::NormalizedVector v(1, 0);
```

Note that a NormalizedVector will always have unit length, even if you create with non-unit values

```cpp
const Image::NormalizedVector v(5, 0, 0); // v = {1, 0, 0}
```


### Adding

Vectors from the same space can be added together to produce a new vector:

```cpp
const Patient::Vector v1(1, 2, 3);
const Patient::Vector v2(4, 5, 6);
auto sum = v1 + v2; // Patient::Vector(5, 7, 9)
```

Vectors from the same space can be added together in place:

```cpp
Patient::Vector v1(1, 2, 3);
const Patient::Vector v2(4, 5, 6);
v1 += v2; // v1 = (5, 7, 9)
```


Vectors can be added to a point from the same space can be added together to produce a new point:

```cpp
const Patient::Vector v(1, 2, 3);
const Patient::Point p1(4, 5, 6);
auto p2 = p1 + v; // Patient::Point(5, 7, 9)
```

Vectors can be added to a point from the same space can be added together in place:

```cpp
const Patient::Point p(4, 5, 6);
const Patient::Vector v(1, 2, 3);
auto p += v; // p = (5, 7, 9)
```


### Subtracting

Points from the same space can be subtracted to produce a vector:

```cpp
const Patient::Point p1(4, 5, 6);
const Patient::Point p2(1, 2, 3);
auto v = p1 - p2; // Patient::Vector(3, 3, 3)
```

### Scaling

Vectors can be scaled to produce a new vector

```cpp
const Patient::Vector v1(4, 5, 6);
auto v2 = v1 * 2; // Patient::Vector(8, 10, 12)
```

Vectors can be scaled in place

```cpp
const Patient::Vector v(4, 5, 6);
auto v *= 2; // v = (8, 10, 12)
```

### Dot Product

You can get the dot product from two vectors in the same space

```cpp
const Patient::Vector v1(1, 2, 3);
const Patient::Vector v2(4, 5, 6);
auto dot = v1.Dot(v2); // double dot = 4+10+18 = 32;
```

### Cross Product

You can get the cross product from two vectors in the same space

```cpp
const Patient::Vector v1(1, 0, 0);
const Patient::Vector v2(0, 1, 0);
auto cross = v1.Cross(v2); // Patient::Vector(0, 0, 1);
```

You can get the cross product from two vectors in the same space using the * operator:

```cpp
const Patient::Vector v1(1, 0, 0);
const Patient::Vector v2(0, 1, 0);
auto cross = v1 * v2; // Patient::Vector(0, 0, 1)
```

You can get the cross product from two vectors in the same space using the *= operator:

```cpp
const Patient::Vector v1(1, 0, 0);
const Patient::Vector v2(0, 1, 0);
auto v1 *= v2; // v1 = (0, 0, 1);
```

### Normalisation

You can get the normal form of a vector

```cpp
const Patient::Vector v1(5, 0, 0);
const Patient::NormalizedVector v2 = v1.Norm(); // Patient::Vector(1, 0, 0)
```

In addition, you can construct a normalized vector as you would a normal vector, but the result will
always be normalized:

```cpp
const Patient::NormalizedVector v(5, 0, 0);
// v1 = (1, 0, 0)
```

### Magnitude

You can get the magnitude of a vector. This will be in strongly typed units, e.g. Patient Space
is in millimetres, View Space is in Pixels.

```cpp
const Patient::Vector v1(5, 0, 0);
const auto m = v1.Mag(); // m = 5 Millimetres
```

### Comparison

Vectors from the same space can be compared using == or !=. Under the hood, this checks
for approximate equality.

```cpp
const Patient::Vector v1(1, 0, 0);
const Patient::Vector v2(0, 1, 0);
auto b_equality = v1 == v2; // false
auto b_inequality = v1 != v2; // true
```

Points from the same space can be compared using == or !=. Under the hood, this checks
for approximate equality.

```cpp
const Patient::Point p1(1, 0, 0);
const Patient::Point p2(0, 1, 0);
auto b_equality = p1 == p2; // false
auto b_inequality = p1 != p2; // true
```

### Conversion between spaces</H3>

Vectors from one space can be converted to another space. Under the hood, this uses a Transform33.

```cpp
TransformManager tm;
const Patient::Vector v_patient(1, 0, 0);
auto v = v_patient.ConvertTo<Image>(tm); // Image::Vector(x, y, z)
```

Points from one space can be converted to another space. Under the hood, this uses a Transform.

```cpp
TransformManager tm;
const Patient::Point p_patient(1, 0, 0);
auto p = p_patient.ConvertTo<Image>(tm); // Image::Point(x, y, z)
```

### Access

There are several ways to access the underlying data:

#### Random Access

The data from a point or vector can be accessed using square brackets. The only valid indices
are 0, 1, or 2. Any other value will cause a runtime throw.

```cpp
const Image::Vector v(1, 2, 3);
v[0] == 1;
```

#### Named Access</H4>

The data from a point or vector can be accessed using the X(), Y() or Z() functions.

```cpp
const Image::Vector v(1, 2, 3);
v.Y() == 2;
```

#### At Access

The data from a point or vector can be accessed using at(). The only valid indices are 0, 1 or 2.
Any other value will cause a compilation error.

```cpp
const Image::Vector v(1, 2, 3);
v.at<2>() == 3;
```

#### Iteration

You can iterate over the values, and use STL algorithms on Points, Vectors and NormalizedVectors:

```cpp
View::Point p(2, 3, 4);

std::transform(
    p.cbegin(),
    p.cend(),
    p.begin(),
    [](const double d) {return d * 2; }
);
p == View::Point(4, 6, 8);
```