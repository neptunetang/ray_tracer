//
// Created by neptune on 21-04-20.
//

#ifndef BASIC_RAY_TRACER_RECTANGLE_H
#define BASIC_RAY_TRACER_RECTANGLE_H

#include "material.h"
#include "random.h"

class flip_face : public hitable {
public:
    explicit flip_face(hitable* p) : ptr(p) {}

    virtual bool is_hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
        if (!ptr->is_hit(r, t_min, t_max, rec))
            return false;

        rec.front = !rec.front;
        return true;
    }
    virtual vec3 random_start() const {
        return ptr->random_start();
    }

    virtual bool on(vec3 a) const {
        return ptr->on(a);
    }
    virtual ray random_ray() const{
        return ptr->random_ray();
    }

public:
    hitable* ptr;
};

class xy_rect : public hitable {
public:
    float p0, p1, q0, q1, k;
    material *mat;
    xy_rect(float _x0, float _x1, float _y0, float _y1, float _k, material *m):
            p0(_x0), p1(_x1), q0(_y0), q1(_y1),k(_k), mat(m){};
    virtual bool is_hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
    virtual vec3 random_start() const{
        return vec3(random_float(p0,p1),random_float(q0,q1), k);
    }
    virtual bool on(vec3 a) const {
        return (a.x() >= p0&&a.x()<=p1) && (a.y() >= q0&&a.y()<=q1) && a.z() == k;
    }
    virtual ray random_ray() const;
};

class xz_rect : public hitable {
public:
    float p0, p1, q0, q1, k;
    material *mat;
    xz_rect(float _x0, float _x1, float _z0, float _z1, float _k, material *m):
            p0(_x0), p1(_x1), q0(_z0), q1(_z1),k(_k), mat(m){};
    virtual bool is_hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
    virtual vec3 random_start() const{
        return vec3(random_float(p0,p1), k, random_float(q0,q1));
    }
    virtual bool on(vec3 a) const {
        return (a.x() >= p0&&a.x()<=p1) && (a.z() >= q0&&a.z()<=q1) && a.y() == k;
    }
    virtual ray random_ray() const;
};

class yz_rect : public hitable {
public:
    float p0, p1, q0, q1, k;
    material *mat;
    yz_rect(float _y0, float _y1, float _z0, float _z1, float _k, material *m):
            p0(_y0), p1(_y1), q0(_z0), q1(_z1),k(_k), mat(m){};
    virtual bool is_hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
    virtual vec3 random_start() const{
        return vec3(k, random_float(p0,p1),random_float(q0,q1));
    }
    virtual bool on(vec3 a) const {
        return (a.y() >= p0&&a.y()<=p1) && (a.z() >= q0&&a.z()<=q1) && a.x() == k;
    }
    virtual ray random_ray() const;
};



#endif //BASIC_RAY_TRACER_RECTANGLE_H
