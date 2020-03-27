#pragma once

namespace Space {

    template <typename ThisSpace, typename Implementation>
    class NormalizedXYVectorBase : public XYVectorBase<ThisSpace, Implementation>, public NormalizedVectorBase<ThisSpace, Implementation>
    {
        using XYVectorBaseInThisSpace = XYVectorBase<ThisSpace, Implementation>;
        using NormalizedXYVectorBaseInThisSpace = NormalizedXYVectorBase<ThisSpace, Implementation>;
        using NormalizedVectorBaseInThisSpace = NormalizedVectorBase<ThisSpace, Implementation>;

    public:

        NormalizedXYVectorBase() noexcept(false) : XYVectorBaseInThisSpace(), NormalizedVectorBaseInThisSpace() { }
        explicit NormalizedXYVectorBase(const Implementation& e) noexcept(false) : XYVectorBaseInThisSpace(e), NormalizedVectorBaseInThisSpace(e) { }
        explicit NormalizedXYVectorBase(const double x, const double y) noexcept(false) : XYVectorBaseInThisSpace(x, y), NormalizedVectorBaseInThisSpace(x, y, 0) {}
        NormalizedXYVectorBase(const std::initializer_list<double> l) noexcept(false) : XYVectorBaseInThisSpace(l), NormalizedVectorBaseInThisSpace(l) { }



    };
}
