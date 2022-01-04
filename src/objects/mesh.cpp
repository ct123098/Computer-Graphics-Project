#include "mesh.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <utility>
#include <sstream>

#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc

#include "lib/tiny_obj_loader.h"

#include "utils.hpp"


// transforms a 3D point using a matrix, returning a 3D point
static Vector3f transformPoint(const Matrix4f &mat, const Vector3f &point) {
    return (mat * Vector4f(point, 1)).xyz();
}

// transform a 3D directino using a matrix, returning a direction
static Vector3f transformDirection(const Matrix4f &mat, const Vector3f &dir) {
    return (mat * Vector4f(dir, 0)).xyz();
}

bool Mesh::intersect(const Ray &r, Hit &h, double tmin) {
    assert(false); // this is abandoned.
//    // Optional: Change this brute force method into a faster one.
//    bool result = false;
//    for (int triId = 0; triId < (int) t.size(); ++triId) {
//        TriangleIndex &triIndex = t[triId];
//        Triangle triangle(v[triIndex[0]],
//                          v[triIndex[1]], v[triIndex[2]], material);
//        triangle.normal = n[triId];
//        result |= triangle.intersect(r, h, tmin);
//    }
//    return result;
}

void Mesh::get_all_faces(std::vector<Object3D *> &objects) {
    objects.insert(objects.end(), faces.begin(), faces.end());
}

Mesh::Mesh(const char *filename, const Matrix4f &trans, Material *material_) {

    std::string inputfile = filename;
    tinyobj::ObjReaderConfig reader_config;
    reader_config.mtl_search_path = "mesh/"; // Path to material files
    tinyobj::ObjReader reader;

    if (!reader.ParseFromFile(inputfile, reader_config)) {
        if (!reader.Error().empty()) {
            std::cerr << "TinyObjReader: " << reader.Error();
        }
        exit(1);
    }

    if (!reader.Warning().empty()) {
        std::cout << "TinyObjReader: " << reader.Warning();
    }


    auto &attrib = reader.GetAttrib();
    auto &shapes = reader.GetShapes();
    auto &obj_materials = reader.GetMaterials();

    auto &vertices = attrib.vertices;
    auto &normals = attrib.normals;
    auto &texcoords = attrib.texcoords;

    for (auto &obj_mat : obj_materials) {
        Material *mat = new Material(1.0, 0.0, 0.0,
                                     Vector3f(obj_mat.diffuse[0], obj_mat.diffuse[1], obj_mat.diffuse[2]),
                                     Vector3f(obj_mat.specular[0], obj_mat.specular[1], obj_mat.specular[2]),
                                     obj_mat.shininess, obj_mat.ior, obj_mat.diffuse_texname);
        switch (obj_mat.illum) {
            case 3: mat->diffuse = 0.8, mat->specular = 0.2, mat->refraction = 0.0; break;
            default: break;
        }
        materials.push_back(mat);
    }


// Loop over shapes
    for (size_t s = 0; s < shapes.size(); s++) {
        // Loop over faces(polygon)
        size_t index_offset = 0;
        for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
            size_t fv = shapes[s].mesh.num_face_vertices[f];
            assert(fv == 3);
            // Loop over vertices in the face.
            Vector3f v[3] = {}, vn[3] = {};
            Vector2f vt[3] = {};
            int nflag = 0, tflag = 0;
            for (size_t i = 0; i < fv; i++) {
                // access to vertex
                tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + i];
                int vidx = idx.vertex_index;
                int nidx = idx.normal_index;
                int tidx = idx.texcoord_index;
                assert((int)vertices.size() > 3 * vidx + 2);
                v[i] = Vector3f(vertices[3 * vidx + 0], vertices[3 * vidx + 1], vertices[3 * vidx + 2]);
                v[i] = transformPoint(trans, v[i]);
//                std::cerr << f << std::endl;
//                std::cerr << nidx << ' ' << tidx << std::endl;
//                std::cerr << normals.size() << ' ' << texcoords.size() << std::endl;
                if (nidx >= 0) {
                    assert((int)normals.size() > 3 * nidx + 2);
                    vn[i] = Vector3f(normals[3 * nidx + 0], normals[3 * nidx + 1], normals[3 * nidx + 2]);
                    vn[i] = transformDirection(trans, vn[i]);
                    nflag += 1;
                }
                if (tidx >= 0) {
                    assert((int)texcoords.size() > 2 * tidx + 1);
                    vt[i] = Vector2f(texcoords[2 * tidx + 0], texcoords[2 * tidx + 1]);
                    tflag += 1;
                }
            }
            index_offset += fv;

            // per-face material
            int midx = shapes[s].mesh.material_ids[f];
//            std::cerr << materials.size() << std::endl;
//            std::cerr << midx << std::endl;
            assert((int)materials.size() > midx);
//            std::cerr << "face : " << f << ' ' << nflag << ' ' << tflag << endl;
            Material *mat = material_ ? material_ : materials[midx];
            Triangle *tri = nullptr;
            if (nflag == 0 && tflag == 0) {
                tri = new Triangle(v, mat);
            }
            else if (nflag == 3 && tflag == 0) {
                tri = new Triangle(v, vn, mat);
            }
            else if (nflag == 3 && tflag == 3) {
                tri = new Triangle(v, vn, vt, mat);
            }
            else {
                assert(false); // not implemented yet!
            }
            faces.push_back(tri);
        }
    }

    for (auto tri_ptr : faces) {
        mx = max(mx, tri_ptr->mx);
        mn = max(mn, tri_ptr->mn);
//        tri_ptr->v[0].print(), tri_ptr->v[1].print(), tri_ptr->v[2].print();
//        tri_ptr->vn[0].print(), tri_ptr->vn[1].print(), tri_ptr->vn[2].print();
//        std::cout << std::endl;
    }

//    computeNormal();
//    computeTransform(trans);
//
//    mn = 1e10, mx = -1e10;
//    for (auto &vi : v) {
//        mn = min(mn, vi);
//        mx = max(mx, vi);
//    }
//    for (auto ti : t) {
//        auto obj = new Triangle(v[ti.x[0]], v[ti.x[1]], v[ti.x[2]], material);
//        faces.push_back(obj);
//    }
}

//void Mesh::computeTransform(const Matrix4f &m) {
//    for (auto &point : v) {
//        point = transformPoint(m, point);
//    }
//    for (auto &normal : n) {
//        normal = transformDirection(m, normal);
//    }
////    for (auto point : v) {
////        point.print();
////    }
////    printf("\n");
//}

Mesh::Mesh(const char *filename, double dx, double dy, double dz, double sx, double sy, double sz, Material *m) :
        Mesh(filename, Matrix4f::translation(dx, dy, dz) * Matrix4f::scaling(sx, sy, sz), m) {

}

Mesh::~Mesh() {
    for (auto face_ptr : faces) {
        delete face_ptr;
    }
    for (auto mat_ptr : materials) {
        delete mat_ptr;
    }
}
