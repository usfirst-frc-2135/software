namespace frc2135
{
    template<typename T>
    int sgn(T val)
    {
        return (T(0) < val) - (T(0) > val);
    }

} // namespace frc2135