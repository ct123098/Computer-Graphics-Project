//
// Created by tom20 on 2020/12/21.
//

#ifndef RENDER_CONSTANT_HPP
#define RENDER_CONSTANT_HPP

#define MAX_DEPTH 10
#define ALPHA 0.75
#define INIT_R2 0.1
#define MAX_RADIUS 1000

// for cornell box
#define EPS 5e-5
#define EPS_INT 5e-5
#define EPS_HIT 1e-4
#define EPS_MOV 1e-4

#define N_WORKERS 64
#define N_ROUNDS 10
#define N_PHOTONS 1000000
//#define N_ROUNDS 2500
//#define N_PHOTONS 1000000

// 4K image
//#define N_ROUNDS 2500
//#define N_PHOTONS 10000000

//#define N_SAMPLES 1000
#define SAVE_FREQ 10

//#define IMG_WIDTH 80
//#define IMG_HEIGHT 60
//#define IMG_WIDTH 400
//#define IMG_HEIGHT 300
#define IMG_WIDTH 1024
#define IMG_HEIGHT 768
//#define IMG_WIDTH 2048
//#define IMG_HEIGHT 1536

//#define IMG_WIDTH 1280
//#define IMG_HEIGHT 720
//#define IMG_WIDTH 1920
//#define IMG_HEIGHT 1080
//#define IMG_WIDTH 3840
//#define IMG_HEIGHT 2160

//#define DEBUG(x)
//#define DEBUG2(x)
#define DEBUG(x) do { std::cerr << x << std::endl; } while (0)
#define DEBUG2(x) do { std::cerr << #x << ": " << x << std::endl; } while (0)

#endif //RENDER_CONSTANT_HPP
