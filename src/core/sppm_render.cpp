//
// Created by tom20 on 2021/1/4.
//

#include "sppm_render.hpp"
#include "objects/group.hpp"

SPPMRender::SPPMRender(Scene *scene_, Image *image_, int n_rounds_, int n_photons_, int n_workers_, std::string cwd_) : BaseRender(scene_, image_) {
    camera = scene->getCamera();
    W = camera->getWidth(), H = camera->getHeight();

    // TODO: build object KD Tree
    object_group.build(scene->getObjects());

    hit_points.resize(W * H);
    for (int i = 0; i < W * H; i++)
        hit_points[i] = new HitPoint;
    // TODO: build hit point KD Tree
//    hit_point_group.build(hit_points);

    n_rounds = n_rounds_;
    n_photons = n_photons_;
    n_workers = n_workers_;

    cwd = cwd_;
}

SPPMRender::~SPPMRender() {
    for (auto hit_point : hit_points) {
        delete hit_point;
    }
}

void SPPMRender::render_step1(int r) {
    Vector3f weight_init = Vector3f(1.0);
    std::cout << "Round " << r << " :" << std::endl;
#pragma omp parallel for num_threads(n_workers) schedule(dynamic, 1)
    for (int i = 0; i < H * W; i++) {
        int x = i / H, y = i % H;
        int nx = 1, ny = 1, ix = r / ny % nx, iy = r % ny;
        double r1 = 2 * frandom();
        double dx = r1 < 1 ? sqrt(r1) - 1 : 1 - sqrt(2 - r1);
        double r2 = 2 * frandom();
        double dy = r2 < 1 ? sqrt(r2) - 1 : 1 - sqrt(2 - r2);
        assert(-1 <= dx && dx <= 1);
        assert(-1 <= dy && dy <= 1);
        double xx = x + 1.0 * ix / nx - 0.5 + dx / 2;
        double yy = y + 1.0 * iy / ny - 0.5 + dy / 2;
        Ray ray = camera->generateRay(Vector2f(xx, yy));
//            if (x == 0 && y == 0)
//                ray.getDirection().print(), ray.getOrigin().print();
        HitPoint *hit_point = hit_points[x * H + y];
        hit_point->invalidate();
        trace(1, ray, weight_init, hit_point);
    }
    hit_point_group.build(hit_points);
}
void SPPMRender::render_step2(int r) {
    int n_lights = scene->getLights().size();
    for (auto light_ptr: scene->getLights()) {
        assert(n_lights > 0);
        Vector3f light_weight = light_ptr->getPower();
#pragma omp parallel for num_threads(n_workers) schedule(dynamic, 1)
        for (int i = 0; i < n_photons / n_lights; i++) {
            Ray ray = light_ptr->generateRay();
//                light_weight.print();
            trace(1, ray, light_weight, nullptr);
        }
    }
}

void SPPMRender::render_save_img(int r) {
    if ((r < 10) || (r < 100 && r % 10 == 0) || (r < 1000 && r % 100 == 0) || (r % 500 == 0)) {
        for (int x = 0; x < W; x++) {
            for (int y = 0; y < H; y++) {
                HitPoint *hp = hit_points[x * H + y];
//                hp->flux.print();
                Vector3f color = hp->flux / (M_PI * hp->r2 * n_photons * (r + 1)) + hp->flux_light / (r + 1);
//                color.print();
                color = gamma_correction(clip(color, 0, 1), 1 / 2.2);
                image->SetPixel(x, y, color);
            }
        }
        image->SaveBMP((cwd + "/tmp/img-" + std::to_string(r) + ".bmp").c_str());
    }
}

void SPPMRender::render() {
    // init
    for (int x = 0; x < W; x++)
        for (int y = 0; y < H; y++)
            hit_points[x * H + y]->init();
    // loop
    auto st_time = std::chrono::high_resolution_clock::now();
    for (int r = 0; r < n_rounds; r++) {
        render_step1(r);
        std::cerr << "step1 time escape: " << 1e-9 * std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - st_time).count() << std::endl, st_time = std::chrono::high_resolution_clock::now();
        render_step2(r);
        std::cerr << "step2 time escape: " << 1e-9 * std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - st_time).count() << std::endl, st_time = std::chrono::high_resolution_clock::now();
        render_save_img(r);
        std::cerr << "step3 time escape: " << 1e-9 * std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - st_time).count() << std::endl, st_time = std::chrono::high_resolution_clock::now();
    }
}

void SPPMRender::trace(int depth, const Ray &ray, const Vector3f &weight, HitPoint *hp) {
    if (depth > MAX_DEPTH)
        return ;
    Hit hit;
    bool isIntersect = object_group.intersect(ray, hit, 0);
    if (!isIntersect)
        return ;
    if ((ray.getOrigin() + ray.getDirection() * hit.getT()).length() > MAX_RADIUS)
        return ;


    Material *mat = hit.getMaterial();
    Vector3f albedo = mat->get_diffuse_color(hit.getU(), hit.getV());
    double p_diffuse = mat->diffuse, p_specular = mat->specular, p_refraction = mat->refraction;
    assert(fcmp(p_diffuse + p_specular + p_refraction, 1.0) == 0);
    double action =  frandom();

//    Vector3f albedo = Vector3f(1.0);
    // russianRouletteProb
//    double P = Vector3f::dot(albedo, Vector3f(0.2126f, 0.7152f, 0.0722f));

    Vector3f X = ray.getOrigin() + ray.getDirection() * hit.getT();
    Vector3f NOut = hit.getNormal(), V = -ray.getDirection();
    Vector3f N = Vector3f::dot(NOut, V) >= 0 ? NOut : -NOut;
    double Vn = Vector3f::dot(V, N);
    Vector3f R = -V + 2.0 * Vn * N;
    assert(fcmp(R.length(), 1.0) == 0);

    if (fcmp(p_diffuse, 0.0) > 0 && action <= p_diffuse) {
        if (hp) {   // eye ray
            hp->pos = X;
            hp->dir = V;
            hp->mat = mat;
            hp->weight = weight; // FIXME I think the material is calculated twice?
            hp->flux_light += weight * 0.0; // emission
            hp->valid = true;
//            if (mat->getEmissionColor().squaredLength() > EPS)
//                hp->flux = hp->flux_light = 0;
            // FIXME: hp->dir, hp->norm ??
            // FIXME: mat == LIGHT ??
//            X.print();
        }
        else {
            // FIXME: pho_s
            // FIXME: hit point group
            hit_point_group.update(X, V, weight, hit);

            assert(fcmp(N.length(), 1.0) == 0);
            double phi = 2 * M_PI * frandom(), sinPhi = sin(phi), cosPhi = cos(phi);
            double r2 = frandom(), sinTheta = sqrt(r2), cosTheta = sqrt(1 - r2);
            Vector3f u = Vector3f::cross(fabs(N.x()) >= 0.5 ? Vector3f(0, 1, 0) : Vector3f(1, 0, 0), N).normalized();
            assert(fcmp(u.length(), 1.0) == 0);
            Vector3f v = Vector3f::cross(N, u);
            assert(fcmp(v.length(), 1.0) == 0);
            assert(fcmp(Vector3f::dot(N, v), 0.0) == 0);
            assert(fcmp(Vector3f::dot(N, u), 0.0) == 0);
            assert(fcmp(Vector3f::dot(u, v), 0.0) == 0);

            Vector3f D = u * sinTheta * sinPhi + v * sinTheta * cosPhi + N * cosTheta;
            assert(fcmp(Vector3f::dot(N, D), 0.0) >= 0);
            // FIXME: a <= rho_d then trace
            trace(depth + 1, Ray(X + D * EPS_MOV, D), weight * albedo, hp);
        }
        return ;
    }
    if (fcmp(p_specular, 0.0) > 0 && action <= p_diffuse + p_specular) {
        trace(depth + 1, Ray(X + EPS_MOV * R, R), weight * albedo, hp);
        return ;
    }
    if (fcmp(p_refraction, 0.0) > 0 && action <= p_diffuse + p_specular + p_refraction) {
//        double e1 = 1.0, e2 = 1.5, ratio = e2 / e1;
        double ior = mat->ior;
        bool into = Vector3f::dot(NOut, N) < 0;
        if (!into) ior = 1.0 / ior;
        double cosTheta2Sqr = 1 - ior * ior * (1.0 - Vn * Vn);
        if (cosTheta2Sqr < EPS_INT) {
            trace(depth + 1, Ray(X + R * EPS_MOV, R), weight * albedo, hp);
        }
        else {
            Vector3f Refr = -ior * V + (ior * Vn - sqrt(cosTheta2Sqr)) * N;
            if (fcmp(Refr.length(), 1.0) != 0) {
                std::cerr << Refr.length() << std::endl;
            }
            assert(fcmp(Refr.length(), 1.0) == 0);
            double R0 = (1 - ior) * (1 - ior) / ((1 + ior) * (1 + ior));
            double c = 1 - (into ? Vn : Vector3f::dot(-N, Refr));
            double Re = R0 + (1 - R0) * pow(c, 5.0);
            assert(fcmp(Re, 1.0) <= 0);
//            std::cerr << R0 << ' ' << c << ' ' << Re << std::endl;
//            std::cerr << Re << std::endl;
            if (frandom() < Re) {
                trace(depth + 1, Ray(X + R * EPS_MOV, R), weight * albedo, hp);
            }
            else {
                trace(depth + 1, Ray(X + Refr * EPS_MOV, Refr), weight * albedo, hp);
            }
        }
        return ;
    }
    assert(false); // not implemented yet !
}

HitPointGroup::HitPointGroup() : bucket(nullptr), bucket_rad(0), n_bucket(0) {
}

void HitPointGroup::build(std::vector<HitPoint *> hit_points) {
//    double st_time = clock();
    Vector3f mn = 1e100, mx = -1e100;
    double rad2 = -1e100;
    for (auto hp_ptr : hit_points) {
        if (hp_ptr->valid) {
            assert(Vector3f(-1e10) <= hp_ptr->pos && hp_ptr->pos <= Vector3f(1e10));
//            if(!(Vector3f(-1000) <= hp_ptr->pos && hp_ptr->pos <= Vector3f(1000)))
//                hp_ptr->pos.print();
            mn = min(mn, hp_ptr->pos), mx = max(mx, hp_ptr->pos);
            rad2 = std::max(rad2, hp_ptr->r2);
        }
    }
    mn.print();
    mx.print();
    Vector3f sz = mx - mn;
    // heuristic for init_r (from smallppm)
    double rad = 0.0;
    if (rad2 < 0) {
        rad = 2.0 * ((sz.x() + sz.y() + sz.z()) / 3) / (sqrt(hit_points.size()));
        rad = std::min(rad, INIT_R2);
        for (auto hp_ptr : hit_points) {
            assert(hp_ptr->n == 0);
            hp_ptr->r2 = rad * rad;
        }
    }
    else
        rad = sqrt(rad2);
    for (auto hp_ptr : hit_points) {
        mn = min(mn, hp_ptr->pos - Vector3f(rad)), mx = max(mx, hp_ptr->pos + Vector3f(rad));
    }
    std::cerr << "max rad: " << rad << std::endl;
//    exit(0);
    init_hash_table(std::min(MAX_BUCKET_NUM, 2 * (int)hit_points.size()), 2 * rad);
//    std::cerr << "bucket num: " << n_bucket << std::endl;
    for (auto hp_ptr : hit_points) {
        if (hp_ptr->valid) {
            Vector3f bmin = (hp_ptr->pos - Vector3f(rad)) / bucket_rad, bmax = (hp_ptr->pos + Vector3f(rad)) / bucket_rad;
            assert(fabs(bmin.x()) < 1e9 && fabs(bmin.y()) < 1e9 && fabs(bmin.z()) < 1e9);
            assert(fabs(bmax.x()) < 1e9 && fabs(bmax.y()) < 1e9 && fabs(bmax.z()) < 1e9);
            for (int ix = floor(bmin.x()); ix <= (int)floor(bmax.x()); ix++)
                for (int iy = floor(bmin.y()); iy <= (int)floor(bmax.y()); iy++)
                    for (int iz = floor(bmin.z()); iz <= (int)floor(bmax.z()); iz++) {
                        int idx = hash(ix, iy, iz);
                        bucket[idx].push_back(hp_ptr);
                    }
        }
    }
//    std::cerr << "build hashtable success, time escape: " << (clock() - st_time) * 1e-9 << std::endl, st_time = clock();
}
int HitPointGroup::hash(const Vector3f &X) {
    Vector3f tmp = X / bucket_rad;
    return hash(floor(tmp.x()), floor(tmp.y()), floor(tmp.z()));
}
int HitPointGroup::hash(int ix, int iy, int iz) {
    int ret = (int)((((unsigned int)ix*73856093)^((unsigned int)iy*19349663)^((unsigned int)iz*83492791)) % n_bucket);
    assert(0 <= ret && ret < n_bucket);
    return ret;
}

void HitPointGroup::update(const Vector3f &X, const Vector3f &V, const Vector3f &weight, const Hit &hit) {
    int total_cnt = 0, hit_cnt = 0, update_cnt = 0;
    int idx = hash(X);
    for (auto hp : bucket[idx]) {
        total_cnt += 1;
        hit_cnt += ((X - hp->pos).squaredLength() <= hp->r2);
        if (hp->valid && (X - hp->pos).squaredLength() <= hp->r2) {
            update_cnt += 1;
            // FIXME: if material is BSDF
            // FIXME: modify this to phong model
            Material *mat = hit.getMaterial();
            Vector3f rho = weight * (mat->get_diffuse_color(hit.getU(), hit.getV())
                    + mat->specular_color * pow(clip(Vector3f::dot(hp->dir, V), 0.0, 1.0), mat->phong_s));
//            Vector3f rho = weight * mat->get_diffuse_color(hit.getU(), hit.getV());
            hp->update(rho);
//            std::cerr << weight.x() << ", " << weight.y() << ", " << weight.z() << "; ";
//            std::cerr << hp->mat->getDiffuseColor().x() << ", " << hp->mat->getDiffuseColor().y() << ", " << hp->mat->getDiffuseColor().z() << "; ";
        }
    }
//    if (total_cnt > 0)
//        std::cerr << 1.0 * hit_cnt / total_cnt << std::endl;
//    if (update_cnt) {
//        std::cerr << " : " << update_cnt << ", " << valid_cnt;
//        std::cerr << std::endl;
//    }
}

void HitPointGroup::init_hash_table(int n, double bucket_rad_) {
    assert(n <= MAX_BUCKET_NUM);
    assert(0 <= bucket_rad && bucket_rad <= 1e100);
//    std::cerr << bucket << std::endl;
    delete[] bucket;
    bucket = new std::vector<HitPoint*> [n];
    n_bucket = n;
    bucket_rad = bucket_rad_;
}


