//
// Created by tom20 on 2021/1/5.
//

#include "objects/group.hpp"
#include <algorithm>

int ObjectGroup::D = 0;

void ObjectGroup::build(const std::vector<Object3D*> &group) {
    objects.clear();
    for (auto obj_ptr : group) {
        obj_ptr->get_all_faces(objects);
    }
    std::cerr << "num of face: " << objects.size() << std::endl;
    root = build_tree(0, objects.size(), 0);
}

bool ObjectGroup::intersect(const Ray &r, Hit &h, double tmin) {
//        bool ret = false;
//        for (auto obj : objects) {
//            bool res = obj->intersect(r, h, tmin);
//            ret |= res;
//        }
//    return ret;
//    double st_clock = clock();
    assert(fcmp(tmin, 0.0) == 0);
    bool ret = intersect_tree(root, r, h);
//    double ed_clock = clock();
//    std::cerr << "kd-tree query: " <<  1e3 * (ed_clock - st_clock) / CLOCKS_PER_SEC << "ms" << std::endl;
    return ret;
}

ObjectGroup::KDTreeNode* ObjectGroup::build_tree(int l, int r, int d) {
//    std::cerr << "build tree: " << l << ' ' << r << " | "; //
    const int N_OBJS_PER_LEAF = 8;
    auto *now = new KDTreeNode;
    now->lc = now->rc = nullptr;
    now->mn = 1e10, now->mx = -1e10;
    for (int i = l; i < r; i++) {
        now->mn = min(now->mn, objects[i]->mn);
        now->mx = max(now->mx, objects[i]->mx);
    }
//    std::cerr << now->mn.x() << ' ' << now->mx.x() << std::endl;
    if (r - l <= N_OBJS_PER_LEAF) {
        now->objs = std::vector<Object3D*>(objects.begin() + l, objects.begin() + r);
        return now;
    }
    int mid = (l + r) / 2;
    D = d;
    std::nth_element(objects.begin() + l, objects.begin() + mid, objects.begin() + r, cmp);
    now->lc = build_tree(l, mid + 1, (d + 1) % 3);
    now->rc = build_tree(mid + 1, r, (d + 1) % 3);
    return now;
}

double ObjectGroup::estimated_distance(const Vector3f &mn, const Vector3f &mx, const Ray &r) {
    Vector3f o = r.getOrigin(), d = r.getDirection();
    if (mn <= o && o <= mx)  // the ray origin is in the box
        return -1e100;
    double ret = -1e100;
    if (fabs(d.x()) > EPS)
        ret = std::max(ret, (double)std::min((mn.x() - o.x()) / d.x(), (mx.x() - o.x()) / d.x()));
    if (fabs(d.y()) > EPS)
        ret = std::max(ret, (double)std::min((mn.y() - o.y()) / d.y(), (mx.y() - o.y()) / d.y()));
    if (fabs(d.z()) > EPS)
        ret = std::max(ret, (double)std::min((mn.z() - o.z()) / d.z(), (mx.z() - o.z()) / d.z()));
    if (ret < -EPS || ret > 1e10)
        return 1e100;
    assert(-EPS <= ret && ret <= 1e10);
    Vector3f p = o + ret * d;
    if (!(mn - Vector3f(EPS) <= p && p <= mx + Vector3f(EPS)))
        return 1e100;
    return ret;
}

bool ObjectGroup::intersect_tree(ObjectGroup::KDTreeNode *now, const Ray &r, Hit &h) {
    bool ret = false;
    for (auto obj_ptr : now->objs) {
        ret |= obj_ptr->intersect(r, h, 0);
    }
    if (!now->lc || !now->rc)
        return ret;
    double ldis = estimated_distance(now->lc->mn, now->lc->mx, r);
    double rdis = estimated_distance(now->rc->mn, now->rc->mx, r);
//    ret |= intersect_tree(now->lc, r, h);
//    ret |= intersect_tree(now->rc, r, h);
//    return ret;
    if (ldis < rdis) {
        if (ldis < h.getT()) ret |= intersect_tree(now->lc, r, h);
        if (rdis < h.getT()) ret |= intersect_tree(now->rc, r, h);
    }
    else {
        if (rdis < h.getT()) ret |= intersect_tree(now->rc, r, h);
        if (ldis < h.getT()) ret |= intersect_tree(now->lc, r, h);
    }
    return ret;
}

bool ObjectGroup::cmp(Object3D *a, Object3D *b) {
    if (D == 0)
        return a->mx.x() != b->mx.x() ? a->mx.x() < b->mx.x() : a->mn.x() < a->mn.x();
    else if (D == 1)
        return a->mx.y() != b->mx.y() ? a->mx.y() < b->mx.y() : a->mn.y() < a->mn.y();
    else if (D == 2)
        return a->mx.z() != b->mx.z() ? a->mx.z() < b->mx.z() : a->mn.z() < a->mn.z();
    assert(false);
}
