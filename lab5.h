#ifndef PROGTASKSCPP_LAB5_H
#define PROGTASKSCPP_LAB5_H

#include <string>
#include <cmath>
#include <iostream>
#include <fstream>

class IGeoFig {
public:
    virtual double Square() const = 0;

    virtual double Perimeter() const = 0;
};

class CVector2D {
public:
    CVector2D &operator+=(CVector2D const &other);

    CVector2D &operator*=(double val);

    CVector2D &operator/=(double val);

    CVector2D &operator=(CVector2D const &other) = default;

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

class CCircle : public IBaseCObject, public IGeoFig, public IPrintable, public IDialogInitiable, public IPhysObject {
public:
    explicit CCircle(double rad = 0.0, CVector2D const &centre = {0.0, 0.0}, double mass = 0);

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

    CCircle &operator=(CCircle const &other) = default;

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

    void AddCircle(double rad, CVector2D const &centre, double mass = 0);

    void ShowCircles();

    double CiclesTotalSquare();

    double CirclesTotalPerimeter();

    double CirclesTotalMass();

    CVector2D CirclesMassCentre();

    size_t CircleTotalSize();

    void CirclesMassSort();

private:

    void CirclesMergeSort(int first, int last);

    void CirclesMerge(int first, int last, int middle);

    size_t size_;
    int head_;
    CCircle *arr_;
};

#endif //PROGTASKSCPP_LAB5_H
