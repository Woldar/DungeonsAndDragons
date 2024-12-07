#pragma once

class EffectTarget {
public:
    virtual void dealDamage(int amount) = 0;
    virtual void addArmor(int amount) = 0;
    virtual ~EffectTarget() = default;
};