#pragma once
/**************************************************************************************************

    Copyright (C) 2018 Canon Medical Systems Corporation. All rights reserved.

**************************************************************************************************/

/*!
\namespace Space

<H3> Summary: </H3>

This namespace provides three templated types: Point, Vector and NormalizedVector. Each point or vector lives in a 
Space. It is possible to convert points and vectors from space to another.

A Space can be defined as follows:
\code
    using NewSpaceUnits = ...;

    struct NewSpace final : Space::SpaceBase<NewSpace, NewSpaceUnits> {};
    template <> const std::string SpaceTypeNameMap<Volume>::name = "NewSpace";
\endcode

The units must be constructable from a double. It will be used to return the magnitude of a vector.
The entry in the SpaceTypeNameMap will be used to serialize a point, vector or normalized vector.

<H3> Creation: </H3>

A point or vector can be created from three doubles.

\code
const View::Point p(1, 2, 3);
const Patient::Vector v(1, 2, 3);
const Image::NormalizedVector v(1, 0, 0);
\endcode

A point or vector can be created from two doubles. The z-value will be set to zero.

\code
const View::Point p(1, 2);
const Patient::Vector v(1, 2);
const Image::NormalizedVector v(1, 0);
\endcode

Note that a NormalizedVector will always have unit length, even if you create with non-unit values

\code
const Image::NormalizedVector v(5, 0, 0); // v = {1, 0, 0}
\endcode


<H3> Adding: </H3>

Vectors from the same space can be added together to produce a new vector:

\code
const Patient::Vector v1(1, 2, 3);
const Patient::Vector v2(4, 5, 6);
auto sum = v1 + v2; // Patient::Vector(5, 7, 9) 
\endcode

Vectors from the same space can be added together in place:

\code
Patient::Vector v1(1, 2, 3);
const Patient::Vector v2(4, 5, 6);
v1 += v2; // v1 = (5, 7, 9)
\endcode


Vectors can be added to a point from the same space can be added together to produce a new point:

\code
const Patient::Vector v(1, 2, 3);
const Patient::Point p1(4, 5, 6);
auto p2 = p1 + v; // Patient::Point(5, 7, 9)
\endcode

Vectors can be added to a point from the same space can be added together in place:

\code
const Patient::Point p(4, 5, 6);
const Patient::Vector v(1, 2, 3);
auto p += v; // p = (5, 7, 9)
\endcode


<H3> Subtracting: </H3>

Points from the same space can be subtracted to produce a vector:

\code
const Patient::Point p1(4, 5, 6);
const Patient::Point p2(1, 2, 3);
auto v = p1 - p2; // Patient::Vector(3, 3, 3)
\endcode

<H3> Scaling: </H3>

Vectors can be scaled to produce a new vector

\code
const Patient::Vector v1(4, 5, 6);
auto v2 = v1 * 2; // Patient::Vector(8, 10, 12)
\endcode

Vectors can be scaled in place

\code
const Patient::Vector v(4, 5, 6);
auto v *= 2; // v = (8, 10, 12)
\endcode

<H3> Dot Product: </H3>

You can get the dot product from two vectors in the same space

\code
const Patient::Vector v1(1, 2, 3);
const Patient::Vector v2(4, 5, 6);
auto dot = v1.Dot(v2); // double dot = 4+10+18 = 32;
\endcode

<H3> Cross Product: </H3>

You can get the cross product from two vectors in the same space

\code
const Patient::Vector v1(1, 0, 0);
const Patient::Vector v2(0, 1, 0);
auto cross = v1.Cross(v2); // Patient::Vector(0, 0, 1);
\endcode

You can get the cross product from two vectors in the same space using the * operator:

\code
const Patient::Vector v1(1, 0, 0);
const Patient::Vector v2(0, 1, 0);
auto cross = v1 * v2; // Patient::Vector(0, 0, 1);
\endcode

You can get the cross product from two vectors in the same space using the *= operator:

\code
const Patient::Vector v1(1, 0, 0);
const Patient::Vector v2(0, 1, 0);
auto v1 *= v2; // v1 = (0, 0, 1);
\endcode

<H3> Normalisation: </H3>

You can get the normal form of a vector

\code
const Patient::Vector v1(5, 0, 0);
const Patient::NormalizedVector v2 = v1.Norm(); // Patient::Vector(1, 0, 0)
\endcode

In addition, you can construct a normalized vector as you would a normal vector, but the result will
always be normalized:

\code
const Patient::NormalizedVector v(5, 0, 0);
// v1 = (1, 0, 0)
\endcode


<H3> Magnitude: </H3>

You can get the magnitude of a vector. This will be in strongly typed units, e.g. Patient Space
is in millimetres, View Space is in Pixels.

\code
const Patient::Vector v1(5, 0, 0);
const auto m = v1.Mag(); // m = 5 Millimetres
\endcode

<H3> Comparison </H3>

Vectors from the same space can be compared using == or !=. Under the hood, this checks
for approximate equality.

\code
const Patient::Vector v1(1, 0, 0);
const Patient::Vector v2(0, 1, 0);
auto b_equality = v1 == v2; // false
auto b_inequality = v1 != v2; // true
\endcode

Points from the same space can be compared using == or !=. Under the hood, this checks
for approximate equality.

\code
const Patient::Point p1(1, 0, 0);
const Patient::Point p2(0, 1, 0);
auto b_equality = p1 == p2; // false
auto b_inequality = p1 != p2; // true
\endcode

<H3> Conversion between spaces</H3>

Vectors from one space can be converted to another space. Under the hood, this uses a Transform33.

\code
TransformManager tm;
const Patient::Vector v_patient(1, 0, 0);
auto v = v_patient.ConvertTo<Image>(tm); // Image::Vector(x, y, z)
\endcode

Points from one space can be converted to another space. Under the hood, this uses a Transform.

\code
TransformManager tm;
const Patient::Point p_patient(1, 0, 0);
auto p = p_patient.ConvertTo<Image>(tm); // Image::Point(x, y, z)
\endcode
i
<H3> Access </H3>

There are several ways to access the underlying data:

<H4> Random Access </H4>

The data from a point or vector can be accessed using square brackets. The only valid indices
are 0, 1, or 2. Any other value will cause a runtime throw.

\code
const Image::Vector v(1, 2, 3);
v[0] == 1;
\endcode

<H4> Named Access</H4>

The data from a point or vector can be accessed using the X(), Y() or Z() functions.

\code
const Image::Vector v(1, 2, 3);
v.Y() == 2;
\endcode

<H4> At Access </H4>

The data from a point or vector can be accessed using at(). The only valid indices are 0, 1 or 2.
Any other value will cause a compilation error.

\code
const Image::Vector v(1, 2, 3);
v.at<2>() == 3;
\endcode

<H4> Iteration </H4>

You can iterate over the values, and use STL algorithms on Points, Vectors and NormalizedVectors:

\code
View::Point p(2, 3, 4);

std::transform(
    p.cbegin(),
    p.cend(),
    p.begin(),
    [](const double d) {return d * 2; }
);
p == View::Point(4, 6, 8);
\endcode


*************************************************************************************************/

#include "Point.h"
#include "Vector.h"
#include "NormalizedVector.h"

namespace Space {

    //--------------------------------------------------------------------------------------------

    template <typename SpaceName, typename Units>
    struct SpaceBase {
        using Point = detail::Point<SpaceName>;
        using Vector = detail::Vector<SpaceName>;
        using NormalizedVector = detail::NormalizedVector<SpaceName>;
        using Unit = Units;
    };
}

