#pragma once
class Mathf
{
public:
    static const float Epsilon;

    static bool Approximately(float, float);

private:
    Mathf()
    { }
};

