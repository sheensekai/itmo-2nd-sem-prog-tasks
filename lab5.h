#ifndef PROGTASKSCPP_LAB5_H
#define PROGTASKSCPP_LAB5_H

#include <string>
#include <cmath>
#include <iostream>

class IGeoFig {
public:
    virtual double Square() = 0;

    virtual double Perimeter() = 0;
};

class CVector2D {
public:
    double x, y;
};

class IPhysObject {
public:
    virtual double Mass() = 0;

    virtual CVector2D Position() = 0;

    virtual bool operator==(const IPhysObject &ob) const = 0;

    virtual bool operator<(const IPhysObject &ob) const = 0;
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
    CCircle(double rad, CVector2D const &centre);

    CCircle();

    const char *ClassName() const override;

    size_t Size() const override;

    void SetClassName(std::string name) override;

    void InitFromDialog() override;

    void Draw() const override;

    double Square() override;

    double Perimeter() override;


private:
    std::string name_;
    size_t size_;

    double rad_;
    CVector2D centre_;
};

#endif //PROGTASKSCPP_LAB5_H
