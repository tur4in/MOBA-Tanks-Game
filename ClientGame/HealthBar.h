#pragma once

class CHealthBar
{
public:
    CHealthBar();
    ~CHealthBar();
    void Update(Vector2 parentPosition);
    size_t GetMaxHP() const;
    size_t GetCurrentHP() const;
    void SetMaxHP(size_t hp);
    void SetCurrentHP(size_t hp);
    virtual void TakeDamage(size_t damage);
    virtual void Heal(size_t heal);
    virtual bool IsAlive() const;
    virtual void Render();
    virtual void SetSize(Vector2 x);

private:
    Actor m_red;
    Actor m_blue;

    size_t m_currentHp;
    size_t m_maxHp;

    Vector2 m_sizeOfParent;
};

