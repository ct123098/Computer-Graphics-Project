#ifndef MESH_H
#define MESH_H

#include <vector>
#include "../core/object3d.hpp"
#include "triangle.hpp"
#include "Vector2f.h"
#include "Vector3f.h"


class Mesh : public Object3D {

public:
    Mesh(const char *filename, const Matrix4f &trans, Material *m);
    Mesh(const char *filename, double dx = 0.0, double dy = 0.0, double dz = 0.0, double sx = 1.0, double sy = 1.0, double sz = 1.0, Material *m = nullptr);

    ~Mesh() override;

    struct TriangleIndex {
        TriangleIndex() {
            x[0] = 0; x[1] = 0; x[2] = 0;
        }
        int &operator[](const int i) { return x[i]; }
        // By Computer Graphics convention, counterclockwise winding is front face
        int x[3]{};
    };

//    std::vector<Vector3f> v;
//    std::vector<Vector3f> vn;
//    std::vector<Vector2f> vt;
//    std::vector<TriangleIndex> faces_idx;
    std::vector<Material*> materials;
    std::vector<Triangle*> faces;
    bool intersect(const Ray &r, Hit &h, double tmin) override;
    void get_all_faces(std::vector<Object3D*> &objects) override;

private:

    // Normal can be used for light estimation
//    void computeNormal();
//    void computeTransform(const Matrix4f &m);
};

#endif
