#ifndef GROUP_H
#define GROUP_H


#include <iostream>
#include <vector>
#include "core/object3d.hpp"
#include "core/ray.hpp"
#include "core/hit.hpp"


//// Implement Group - add data structure to store a list of Object*
//class Group : public Object3D {
//
//public:
//
//    Group() {
//
//    }
//
//    explicit Group (int num_objects) {
//        vec.resize(num_objects);
//    }
//
//    ~Group() override {
//
//    }
//
//    bool intersect(const Ray &r, Hit &h, double tmin) override {
//        bool ret = false;
//        for (auto obj : vec) {
//            if (obj != nullptr) {
//                bool res = obj->intersect(r, h, tmin);
//                ret |= res;
//            }
//        }
//        return ret;
//    }
//
//    void addObject(int index, Object3D *obj) {
//        vec[index] = obj;
//    }
//
//    void appendObject(Object3D *obj) {
//        vec.push_back(obj);
//    }
//    std::vector<Object3D*> &getObjects() {
//        return vec;
//    }
//
//    int getGroupSize() {
//        return vec.size();
//    }
//
//private:
//    std::vector<Object3D*> vec;
//};

class ObjectGroup {
public:
    ObjectGroup() = default;
    void build(const std::vector<Object3D*> &group);
    bool intersect(const Ray &r, Hit &h, double tmin);

private:
    struct KDTreeNode {
        std::vector<Object3D*> objs;
        Vector3f mn, mx;
        KDTreeNode *lc, *rc;
    };
    KDTreeNode *root = nullptr;
    std::vector<Object3D*> objects;

    KDTreeNode *build_tree(int l, int r, int d);
    bool intersect_tree(KDTreeNode *now, const Ray &r, Hit &h);

    static double estimated_distance(const Vector3f &mn, const Vector3f &mx, const Ray &r);
    static bool cmp(Object3D *a, Object3D *b);
    static int D;
};

#endif
