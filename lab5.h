#ifndef PROGTASKSCPP_LAB5_H
#define PROGTASKSCPP_LAB5_H

#include <string>
#include <cmath>
#include <iostream>

class IGeoFig {
public:
    virtual double Square() const = 0;

    virtual double Perimeter() const = 0;
};

class CVector2D {
public:
    double x, y;
};

class IPhysObject {
public:
    virtual double Mass() const = 0;

    virtual void SetMass(double val) = 0;

    virtual CVector2D Position() const = 0;

    virtual void SetPosition(const CVector2D &vect) = 0;

    virtual bool operator==(const IPhysObject &ob) const = 0;

    virtual bool operator!=(const IPhysObject &ob) const = 0;

    virtual bool operator<(const IPhysObject &ob) const = 0;

    virtual bool operator>(const IPhysObject &ob) const = 0;

    virtual bool operator<=(const IPhysObject &ob) const = 0;

    virtual bool operator>=(const IPhysObject &ob) const = 0;
};

class IPrintable {
public:
    virtual void Draw() const = 0;
};

class IDialogInitiable {
    virtual void InitFromDialog() = 0;
};

class IBaseCObject {
public:
    virtual const char *ClassName() const = 0;

    virtual void SetClassName(std::string name) = 0;

    virtual size_t Size() const = 0;
};

class CCircle : IBaseCObject, IGeoFig, IPrintable, IDialogInitiable, IPhysObject {
public:
    explicit CCircle(double rad = 0.0, CVector2D const &centre = {0.0, 0.0});

    size_t Size() const override;

    const char *ClassName() const override;

    void SetClassName(std::string name) override;

    void InitFromDialog() override;

    void SetRad(double rad);

    double Mass() const override;

    void SetMass(double val) override;

    CVector2D Position() const override;

    void SetPosition(const CVector2D &vect) override;

    void Draw() const override;

    double Square() const override;

    double Perimeter() const override;

    bool operator==(const IPhysObject &ob) const override;

    bool operator!=(const IPhysObject &ob) const override;

    bool operator<(const IPhysObject &ob) const override;

    bool operator>(const IPhysObject &ob) const override;

    bool operator<=(const IPhysObject &ob) const override;

    bool operator>=(const IPhysObject &ob) const override;


private:
    std::string name_;
    size_t size_;

    double rad_;
    CVector2D centre_;
    double mass_;
};

class CCircleSystem {
public:
    CCircleSystem() :
            size_(10),
            head_(0),
            arr_(new CCircle[10]) {}

    void AddCircle(double rad, CVector2D const &centre, double mass = 0) {
        if (head_ >= size_ * 0.7) {
            CCircle * tmp = new CCircle[floor(size_ * 1.)];
            for (int i = 0; i < size_; ++i)
                tmp[i] = arr_[i];
            delete[] arr_;
        }

        arr_[head_].SetPosition(centre);
        arr_[head_].SetRad(rad);
        arr_[head_].SetMass(mass);

        ++head_;
    }

private:
    size_t size_;
    int head_;
    CCircle * arr_;
};

#endif //PROGTASKSCPP_LAB5_H
