#include "parameters.h"
#include <string.h>
#include <iostream>

void FANNG_PARA(std::string dataset, weavess::Parameters &parameters) {
    unsigned L, R;
    if (dataset == "nytimes") {
        L = 250, R = 90;    // nytimes
    }else if (dataset == "coco-t2i") {
        L = 130, R = 110;    // coco-t2i
    }else if (dataset == "coco-i2i"){
        L = 130, R = 110;    // coco-i2i
    }else if (dataset == "glove25") {
        L = 210, R = 70;    // glove25
    }else if (dataset == "text2image1m"){
        L = 110, R = 70;    // text2image1m
    }else if (dataset == "n100000_d128_cube"){
        L = 110, R = 90;    // n100000_d128_cube
    }else if (dataset == "miniimagenet-i2i"){
        L = 110, R = 90;    // miniimagenet-i2i
    }else if (dataset == "miniimagenet-t2i"){
        L = 110, R = 90;    // miniimagenet-t2i
    }else if (dataset == "n100000_d128_sphere"){
        L = 110, R = 90;    // n100000_d128_sphere
    }else if (dataset == "glove100"){
        L = 210, R = 70;    // glove100
    }else if (dataset == "miniimagenet-i2i_ed"){
        L = 110, R = 90;    // miniimagenet-i2i_ed
    }else if (dataset == "miniimagenet-t2i_ed"){
        L = 110, R = 90;    // miniimagenet-t2i_ed
    }else {
        std::cout << "dataset error!\n";
        exit(-1);
    }
    parameters.set<unsigned>("L", L);
    parameters.set<unsigned>("R_refine", R);
}

void KGRAPH_PARA(std::string dataset, weavess::Parameters &parameters) {
    unsigned K, L, Iter, S, R;
    if (dataset == "nytimes") {
        K = 40, L = 80, Iter = 6, S = 25, R = 100;  // kgraph
    }else if (dataset == "coco-t2i") {
        K = 50, L = 80, Iter = 7, S = 15, R = 100;  // kgraph
    }else if (dataset == "coco-i2i"){
        K = 50, L = 80, Iter = 7, S = 15, R = 100;  // kgraph
    }else if (dataset == "glove25") {
        K = 100, L = 150, Iter = 12, S = 35, R = 150;  // kgraph
    }else if (dataset == "text2image1m") {
        K = 90, L = 130, Iter = 12, S = 20, R = 50;  // kgraph
    }else if (dataset == "n100000_d128_cube") {
        K = 100, L = 130, Iter = 12, S = 20, R = 50;  // kgraph
    }else if (dataset == "miniimagenet-i2i") {
        K = 50, L = 80, Iter = 7, S = 15, R = 100;  // kgraph
    }else if (dataset == "miniimagenet-t2i") {
        K = 50, L = 80, Iter = 7, S = 15, R = 100;  // kgraph
    }else if (dataset == "n100000_d128_sphere") {
        K = 100, L = 130, Iter = 12, S = 20, R = 50;  // kgraph
    }else if (dataset == "glove100") {
        K = 100, L = 150, Iter = 12, S = 35, R = 150;  // kgraph
    }else if (dataset == "miniimagenet-i2i_ed") {
        K = 50, L = 80, Iter = 7, S = 15, R = 100;  // kgraph
    }else if (dataset == "miniimagenet-t2i_ed") {
        K = 50, L = 80, Iter = 7, S = 15, R = 100;  // kgraph
    }else {
        std::cout << "dataset error!\n";
        exit(-1);
    }
    parameters.set<unsigned>("K", K);
    parameters.set<unsigned>("L", L);
    parameters.set<unsigned>("ITER", Iter);
    parameters.set<unsigned>("S", S);
    parameters.set<unsigned>("R", R);
}

void NSG_PARA(std::string dataset, weavess::Parameters &parameters) {
    unsigned K, L, Iter, S, R, L_refine, R_refine, C;
    if (dataset == "nytimes") {
        K = 300, L = 320, Iter = 9, S = 25, R = 300, L_refine = 350, R_refine = 30, C = 400;   // nsg
    }else if (dataset == "coco-t2i") {
        K = 200, L = 200, Iter = 7, S = 25, R = 200, L_refine = 150, R_refine = 60, C = 600;  // nsg
    }else if (dataset == "coco-i2i"){
        K = 200, L = 200, Iter = 7, S = 25, R = 200, L_refine = 150, R_refine = 60, C = 600;  // nsg
    }else if (dataset == "glove25") {
        K = 400, L = 420, Iter = 12, S = 20, R = 300, L_refine = 150, R_refine = 90, C = 600;  // nsg
    }else if (dataset == "text2image1m") {
        K = 100, L = 120, Iter = 12, S = 25, R = 300, L_refine = 150, R_refine = 30, C = 400;   // nsg
    }else if (dataset == "n100000_d128_cube") {
        K = 200, L = 200, Iter = 15, S = 20, R = 50, L_refine = 100, R_refine = 80, C = 400;   // nsg 
    }else if (dataset == "miniimagenet-i2i") {
        K = 200, L = 200, Iter = 7, S = 25, R = 200, L_refine = 150, R_refine = 60, C = 600;  // nsg
    }else if (dataset == "miniimagenet-t2i") {
        K = 200, L = 200, Iter = 7, S = 20, R = 200, L_refine = 150, R_refine = 60, C = 600;  // nsg
    }else if (dataset == "n100000_d128_sphere") {
        K = 200, L = 200, Iter = 15, S = 20, R = 50, L_refine = 100, R_refine = 80, C = 400;   // nsg
    }else if (dataset == "glove100") {
        K = 400, L = 420, Iter = 12, S = 20, R = 300, L_refine = 150, R_refine = 90, C = 500;  // nsg
    }else if (dataset == "miniimagenet-i2i_ed") {
        K = 200, L = 200, Iter = 7, S = 25, R = 200, L_refine = 150, R_refine = 60, C = 600;  // nsg
    }else if (dataset == "miniimagenet-t2i_ed") {
        K = 200, L = 200, Iter = 7, S = 25, R = 200, L_refine = 150, R_refine = 60, C = 600;  // nsg
    }else {
        std::cout << "input dataset error!\n";
        exit(-1);
    }
    parameters.set<unsigned>("K", K);
    parameters.set<unsigned>("L", L);
    parameters.set<unsigned>("ITER", Iter);
    parameters.set<unsigned>("S", S);
    parameters.set<unsigned>("R", R);

    parameters.set<unsigned>("L_refine", L_refine);
    parameters.set<unsigned>("R_refine", R_refine);
    parameters.set<unsigned>("C_refine", C);
}


void NSG_SPHERE2_PARA(std::string dataset, weavess::Parameters &parameters) {
    unsigned K, L, Iter, S, R, L_refine, R_refine, C;
    if (dataset == "nytimes") {
        K = 300, L = 320, Iter = 9, S = 30, R = 200, L_refine = 350, R_refine = 30, C = 400;   // nsg
    }else if (dataset == "coco-t2i") {
        K = 200, L = 200, Iter = 7, S = 25, R = 200, L_refine = 150, R_refine = 60, C = 600;  // nsg
    }else if (dataset == "coco-i2i"){
        K = 200, L = 200, Iter = 7, S = 25, R = 200, L_refine = 150, R_refine = 60, C = 600;  // nsg
    }else if (dataset == "glove25") {
        K = 400, L = 420, Iter = 10, S = 20, R = 300, L_refine = 150, R_refine = 90, C = 600;  // nsg
    }else if (dataset == "text2image1m") {
        K = 100, L = 120, Iter = 12, S = 25, R = 300, L_refine = 150, R_refine = 35, C = 400;   // nsg
    }else if (dataset == "n100000_d128_cube") {
        K = 200, L = 200, Iter = 15, S = 20, R = 50, L_refine = 100, R_refine = 80, C = 400;   // nsg 
    }else if (dataset == "miniimagenet-i2i") {
        K = 200, L = 200, Iter = 7, S = 25, R = 200, L_refine = 150, R_refine = 60, C = 600;  // nsg
    }else if (dataset == "miniimagenet-t2i") {
        K = 200, L = 200, Iter = 7, S = 25, R = 200, L_refine = 150, R_refine = 60, C = 600;  // nsg
    }else if (dataset == "n100000_d128_sphere") {
        K = 200, L = 200, Iter = 15, S = 20, R = 50, L_refine = 100, R_refine = 80, C = 400;   // nsg
    }else if (dataset == "glove100") {
        K = 400, L = 420, Iter = 12, S = 25, R = 300, L_refine = 150, R_refine = 90, C = 600;  // nsg
    }else if (dataset == "miniimagenet-i2i_ed") {
        K = 200, L = 200, Iter = 7, S = 25, R = 200, L_refine = 150, R_refine = 60, C = 600;  // nsg
    }else if (dataset == "miniimagenet-t2i_ed") {
        K = 200, L = 200, Iter = 7, S = 25, R = 200, L_refine = 150, R_refine = 60, C = 600;  // nsg
    }else {
        std::cout << "input dataset error!\n";
        exit(-1);
    }
    parameters.set<unsigned>("K", K);
    parameters.set<unsigned>("L", L);
    parameters.set<unsigned>("ITER", Iter);
    parameters.set<unsigned>("S", S);
    parameters.set<unsigned>("R", R);

    parameters.set<unsigned>("L_refine", L_refine);
    parameters.set<unsigned>("R_refine", R_refine);
    parameters.set<unsigned>("C_refine", C);
}

void NSG_KDT_PARA(std::string dataset, weavess::Parameters &parameters) {
    unsigned nTrees, mLevel, K, L, Iter, S, R, L_refine, R_refine, C;
    if (dataset == "glove-100" || dataset == "glove-100_sample" || dataset == "glove-100_sample_cs") {
        nTrees = 8, mLevel = 8, K = 400, L = 420, Iter = 12, S = 20, R = 300, L_refine = 150, R_refine = 90, C = 600;   // nsg_kdt
    }else if (dataset == "nytimes") {
        nTrees = 4, mLevel = 8, K = 300, L = 320, Iter = 10, S = 15, R = 200, L_refine = 350, R_refine = 30, C = 400;   // nsg_kdt
    }else if (dataset == "coco-t2i") {
        nTrees = 4, mLevel = 8,K = 200, L = 200, Iter = 7, S = 25, R = 200, L_refine = 150, R_refine = 60, C = 600;  // nsg_kdt
    }else if (dataset == "coco-i2i"){
        nTrees = 4, mLevel = 8, K = 200, L = 200, Iter = 7, S = 25, R = 200, L_refine = 150, R_refine = 60, C = 600;  // nsg_kdt
    }else if (dataset == "glove25") {
        nTrees = 4, mLevel = 8, K = 400, L = 420, Iter = 12, S = 20, R = 300, L_refine = 150, R_refine = 90, C = 600;  // nsg_kdt
    }else if (dataset == "text2image1m") {
        nTrees = 4, mLevel = 8, K = 100, L = 120, Iter = 12, S = 25, R = 300, L_refine = 150, R_refine = 30, C = 400;   // nsg_kdt
    }else if (dataset == "n100000_d128_cube") {
        nTrees = 4, mLevel = 8, K = 200, L = 200, Iter = 15, S = 20, R = 50, L_refine = 100, R_refine = 80, C = 400;   // nsg_kdt 
    }else if (dataset == "miniimagenet-i2i") {
        nTrees = 4, mLevel = 8, K = 200, L = 200, Iter = 7, S = 25, R = 200, L_refine = 150, R_refine = 60, C = 600;  // nsg_kdt
    }else if (dataset == "miniimagenet-t2i") {
        nTrees = 4, mLevel = 8, K = 200, L = 200, Iter = 7, S = 25, R = 200, L_refine = 150, R_refine = 60, C = 600;  // nsg_kdt
    }else if (dataset == "n100000_d128_sphere") {
        nTrees = 4, mLevel = 8, K = 200, L = 200, Iter = 15, S = 20, R = 50, L_refine = 100, R_refine = 80, C = 400;   // nsg_kdt
    }else if (dataset == "glove100") {
        nTrees = 4, mLevel = 8, K = 400, L = 420, Iter = 12, S = 20, R = 300, L_refine = 150, R_refine = 90, C = 600;  // nsg_kdt
    }else if (dataset == "miniimagenet-i2i_ed") {
        nTrees = 4, mLevel = 8, K = 200, L = 200, Iter = 7, S = 25, R = 200, L_refine = 150, R_refine = 60, C = 600;  // nsg_kdt
    }else if (dataset == "miniimagenet-t2i_ed") {
        nTrees = 4, mLevel = 8, K = 200, L = 200, Iter = 7, S = 25, R = 200, L_refine = 150, R_refine = 60, C = 600;  // nsg_kdt
    }else {
        std::cout << "input dataset error!\n";
        exit(-1);
    }
    parameters.set<unsigned>("nTrees", nTrees);
    parameters.set<unsigned>("mLevel", mLevel);

    parameters.set<unsigned>("K", K);
    parameters.set<unsigned>("L", L);
    parameters.set<unsigned>("ITER", Iter);
    parameters.set<unsigned>("S", S);
    parameters.set<unsigned>("R", R);

    parameters.set<unsigned>("L_refine", L_refine);
    parameters.set<unsigned>("R_refine", R_refine);
    parameters.set<unsigned>("C_refine", C);
}

void NSG_KNNG_PARA(std::string dataset, weavess::Parameters &parameters) {
    unsigned K, L, Iter, S, R, L_refine, R_refine, C;
    float RATIO;
    if (dataset == "nytimes") {
        K = 300, L = 320, Iter = 10, S = 15, R = 200, L_refine = 350, R_refine = 30, C = 400, RATIO = 1.0f;   // nsg_knng
    }else if (dataset == "coco-t2i") {
        K = 200, L = 200, Iter = 7, S = 25, R = 200, L_refine = 150, R_refine = 60, C = 600, RATIO = 1.0f;  // nsg_knng
    }else if (dataset == "coco-i2i"){
        K = 200, L = 200, Iter = 7, S = 25, R = 200, L_refine = 150, R_refine = 60, C = 600, RATIO = 1.0f;  // nsg_knng
    }else if (dataset == "glove25") {
        K = 400, L = 420, Iter = 12, S = 20, R = 300, L_refine = 150, R_refine = 90, C = 600, RATIO = 1.0f;  // nsg_knng
    }else if (dataset == "text2image1m") {
        K = 100, L = 120, Iter = 12, S = 25, R = 300, L_refine = 150, R_refine = 30, C = 400, RATIO = 1.0f;   // nsg_knng
    }else if (dataset == "n100000_d128_cube") {
        K = 200, L = 200, Iter = 15, S = 20, R = 200, L_refine = 100, R_refine = 80, C = 400, RATIO = 1.0f;   // nsg_knng
    }else if (dataset == "miniimagenet-i2i") {
        K = 200, L = 200, Iter = 7, S = 25, R = 200, L_refine = 150, R_refine = 60, C = 600, RATIO = 1.0f;  // nsg_knng
    }else if (dataset == "miniimagenet-t2i") {
        K = 200, L = 200, Iter = 7, S = 25, R = 200, L_refine = 150, R_refine = 60, C = 600, RATIO = 1.0f;  // nsg_knng
    }else if (dataset == "n100000_d128_sphere") {
        K = 200, L = 200, Iter = 15, S = 20, R = 200, L_refine = 100, R_refine = 80, C = 400, RATIO = 1.0f;   // nsg_knng
    }else if (dataset == "glove100") {
        K = 400, L = 420, Iter = 12, S = 20, R = 300, L_refine = 150, R_refine = 90, C = 600, RATIO = 1.0f;  // nsg_knng
    }else if (dataset == "miniimagenet-i2i_ed") {
        K = 200, L = 200, Iter = 7, S = 25, R = 200, L_refine = 150, R_refine = 60, C = 600, RATIO = 1.0f;  // nsg_knng
    }else if (dataset == "miniimagenet-t2i_ed") {
        K = 200, L = 200, Iter = 7, S = 25, R = 200, L_refine = 150, R_refine = 60, C = 600, RATIO = 1.0f;  // nsg_knng
    }else {
        std::cout << "input dataset error!\n";
        exit(-1);
    }
    parameters.set<unsigned>("K", K);
    parameters.set<unsigned>("L", L);
    parameters.set<unsigned>("ITER", Iter);
    parameters.set<unsigned>("S", S);
    parameters.set<unsigned>("R", R);

    parameters.set<unsigned>("L_refine", L_refine);
    parameters.set<unsigned>("R_refine", R_refine);
    parameters.set<unsigned>("C_refine", C);

    parameters.set<float>("RATIO", RATIO);
}


void NSG_LSHCS_PARA(std::string dataset, weavess::Parameters &parameters) {
    unsigned K, L, Iter, S, R, L_refine, R_refine, C, hash_t, hash_l;
    if (dataset == "nytimes") {
        K = 300, L = 320, Iter = 9, S = 25, R = 300, L_refine = 350, R_refine = 30, C = 400, hash_t = 20, hash_l = 10;   // nsg_lshcs
    }else if (dataset == "coco-t2i") {
        K = 200, L = 200, Iter = 7, S = 25, R = 200, L_refine = 150, R_refine = 60, C = 600, hash_t = 30, hash_l = 10;  // nsg_lshcs
    }else if (dataset == "coco-i2i"){
        K = 200, L = 200, Iter = 8, S = 30, R = 200, L_refine = 150, R_refine = 60, C = 600, hash_t = 30, hash_l = 10;  // nsg_lshcs
    }else if (dataset == "glove25") {
        K = 400, L = 420, Iter = 10, S = 30, R = 300, L_refine = 150, R_refine = 90, C = 600, hash_t = 30, hash_l = 10;  // nsg_lshcs
    }else if (dataset == "text2image1m") {
        K = 100, L = 120, Iter = 10, S = 25, R = 300, L_refine = 150, R_refine = 35, C = 400, hash_t = 20, hash_l = 5;   // nsg_lshcs
    }else if (dataset == "n100000_d128_cube") {
        K = 200, L = 200, Iter = 10, S = 25, R = 200, L_refine = 100, R_refine = 80, C = 400, hash_t = 30, hash_l = 10;   // nsg_lshcs
    }else if (dataset == "miniimagenet-i2i") {
        K = 200, L = 200, Iter = 7, S = 25, R = 200, L_refine = 150, R_refine = 60, C = 600, hash_t = 30, hash_l = 10;  // nsg_lshcs
    }else if (dataset == "miniimagenet-t2i") {
        K = 200, L = 200, Iter = 9, S = 25, R = 200, L_refine = 150, R_refine = 60, C = 600, hash_t = 30, hash_l = 10;  // nsg_lshcs
    }else if (dataset == "n100000_d128_sphere") {
        K = 200, L = 200, Iter = 10, S = 25, R = 200, L_refine = 100, R_refine = 80, C = 400, hash_t = 30, hash_l = 10;   // nsg_lshcs
    }else if (dataset == "glove100") {
        K = 400, L = 420, Iter = 12, S = 20, R = 300, L_refine = 150, R_refine = 90, C = 600, hash_t = 30, hash_l = 10;   // nsg_lshcs
    }else if (dataset == "miniimagenet-i2i_ed") {
        K = 200, L = 200, Iter = 7, S = 25, R = 200, L_refine = 150, R_refine = 60, C = 600, hash_t = 30, hash_l = 10;  // nsg_lshcs
    }else if (dataset == "miniimagenet-t2i_ed") {
        K = 200, L = 200, Iter = 9, S = 25, R = 200, L_refine = 150, R_refine = 60, C = 600, hash_t = 30, hash_l = 10;  // nsg_lshcs
    }else {
        std::cout << "input dataset error!\n";
        exit(-1);
    }
    parameters.set<unsigned>("K", K);
    parameters.set<unsigned>("L", L);
    parameters.set<unsigned>("ITER", Iter);
    parameters.set<unsigned>("S", S);
    parameters.set<unsigned>("R", R);

    parameters.set<unsigned>("L_refine", L_refine);
    parameters.set<unsigned>("R_refine", R_refine);
    parameters.set<unsigned>("C_refine", C);

    const bool UseColliCount = false;
    parameters.set<bool>("UseColliCount", UseColliCount);
    if (UseColliCount){
        parameters.set<unsigned>("hash_t", 2);
        parameters.set<unsigned>("hash_l", 10);
    }else{
        parameters.set<unsigned>("hash_t", hash_t);
        parameters.set<unsigned>("hash_l", hash_l);
    }
}

void NSG_LSH_SPHERE2_PARA(std::string dataset, weavess::Parameters &parameters) {
    unsigned K, L, Iter, S, R, L_refine, R_refine, C, hash_t, hash_l;
    if (dataset == "nytimes") {
        K = 300, L = 320, Iter = 9, S = 30, R = 200, L_refine = 350, R_refine = 30, C = 400, hash_t = 20, hash_l = 10;   // nsg_lshcs_sphere2
    }else if (dataset == "coco-t2i") {
        K = 200, L = 200, Iter = 5, S = 30, R = 200, L_refine = 150, R_refine = 60, C = 600, hash_t = 30, hash_l = 10;  // nsg_lshcs_sphere2
    }else if (dataset == "coco-i2i"){
        K = 200, L = 200, Iter = 8, S = 30, R = 200, L_refine = 150, R_refine = 60, C = 600, hash_t = 30, hash_l = 10;  // nsg_lshcs_sphere2
    }else if (dataset == "glove25") {
        K = 400, L = 420, Iter = 10, S = 30, R = 300, L_refine = 150, R_refine = 90, C = 600, hash_t = 20, hash_l = 5;  // nsg_lshcs_sphere2
    }else if (dataset == "text2image1m") {
        K = 100, L = 120, Iter = 7, S = 30, R = 300, L_refine = 150, R_refine = 30, C = 400, hash_t = 30, hash_l = 10;   // nsg_lshcs_sphere2
    }else if (dataset == "n100000_d128_cube") {
        K = 200, L = 200, Iter = 10, S = 25, R = 200, L_refine = 100, R_refine = 80, C = 400, hash_t = 30, hash_l = 10;   // nsg_lshcs_sphere2
    }else if (dataset == "miniimagenet-i2i") {
        K = 200, L = 200, Iter = 7, S = 25, R = 200, L_refine = 150, R_refine = 60, C = 600, hash_t = 20, hash_l = 10;  // nsg_lshcs_sphere2
    }else if (dataset == "miniimagenet-t2i") {
        K = 200, L = 200, Iter = 9, S = 25, R = 200, L_refine = 150, R_refine = 60, C = 600, hash_t = 30, hash_l = 10;  // nsg_lshcs_sphere2
    }else if (dataset == "n100000_d128_sphere") {
        K = 200, L = 200, Iter = 10, S = 25, R = 200, L_refine = 100, R_refine = 80, C = 400, hash_t = 30, hash_l = 10;   // nsg_lshcs_sphere2
    }else if (dataset == "glove100") {
        K = 400, L = 420, Iter = 12, S = 20, R = 300, L_refine = 150, R_refine = 90, C = 600, hash_t = 30, hash_l = 10;   // nsg_lshcs_sphere2
    }else if (dataset == "miniimagenet-i2i_ed") {
        K = 200, L = 200, Iter = 7, S = 25, R = 200, L_refine = 150, R_refine = 60, C = 600, hash_t = 30, hash_l = 10;  // nsg_lshcs_sphere2
    }else if (dataset == "miniimagenet-t2i_ed") {
        K = 200, L = 200, Iter = 9, S = 25, R = 200, L_refine = 150, R_refine = 60, C = 600, hash_t = 30, hash_l = 10;  // nsg_lshcs_sphere2
    }else {
        std::cout << "input dataset error!\n";
        exit(-1);
    }
    parameters.set<unsigned>("K", K);
    parameters.set<unsigned>("L", L);
    parameters.set<unsigned>("ITER", Iter);
    parameters.set<unsigned>("S", S);
    parameters.set<unsigned>("R", R);

    parameters.set<unsigned>("L_refine", L_refine);
    parameters.set<unsigned>("R_refine", R_refine);
    parameters.set<unsigned>("C_refine", C);

    const bool UseColliCount = false;
    parameters.set<bool>("UseColliCount", UseColliCount);
    if (UseColliCount){
        parameters.set<unsigned>("hash_t", 2);
        parameters.set<unsigned>("hash_l", 10);
    }else{
        parameters.set<unsigned>("hash_t", hash_t);
        parameters.set<unsigned>("hash_l", hash_l);
    }
}

void NSG_LSHCS_NONNDES_PARA(std::string dataset, weavess::Parameters &parameters) {
    unsigned L, S, L_refine, R_refine, C, hash_t, hash_l;
    if (dataset == "glove-100" || dataset == "glove-100_sample" || dataset == "glove-100_sample_cs") {
        L = 420, S = 400, L_refine = 150, R_refine = 90, C = 600, hash_t = 30, hash_l = 10;   // nsg_lshcs
    }else if (dataset == "nytimes") {
        L = 320, S = 300, L_refine = 350, R_refine = 30, C = 400, hash_t = 30, hash_l = 10;   // nsg_lshcs
    }else if (dataset == "coco-t2i") {
        L = 200, S = 200, L_refine = 150, R_refine = 60, C = 600, hash_t = 30, hash_l = 10;  // nsg_lshcs
    }else if (dataset == "coco-i2i"){
        L = 200, S = 200, L_refine = 150, R_refine = 60, C = 600, hash_t = 30, hash_l = 10;  // nsg_lshcs
    }else if (dataset == "glove25") {
        L = 420, S = 400, L_refine = 150, R_refine = 90, C = 600, hash_t = 30, hash_l = 10;  // nsg_lshcs
    }else if (dataset == "text2image1m") {
        L = 120, S = 100,  L_refine = 150, R_refine = 30, C = 400, hash_t = 30, hash_l = 10;   // nsg_lshcs
    }else if (dataset == "n100000_d128_cube") {
        L = 200, S = 200, L_refine = 100, R_refine = 80, C = 400, hash_t = 30, hash_l = 10;   // nsg_lshcs
    }else if (dataset == "miniimagenet-i2i") {
        L = 200, S = 200, L_refine = 150, R_refine = 60, C = 600, hash_t = 30, hash_l = 10;  // nsg_lshcs
    }else if (dataset == "miniimagenet-t2i") {
        L = 200, S = 200, L_refine = 150, R_refine = 60, C = 600, hash_t = 30, hash_l = 10;  // nsg_lshcs
    }else if (dataset == "n100000_d128_sphere") {
        L = 200, S = 200, L_refine = 100, R_refine = 80, C = 400, hash_t = 30, hash_l = 10;   // nsg_lshcs
    }else if (dataset == "glove100") {
        L = 420, S = 400, L_refine = 150, R_refine = 90, C = 600, hash_t = 30, hash_l = 10;   // nsg_lshcs
    }else if (dataset == "miniimagenet-i2i_ed") {
        L = 200, S = 200, L_refine = 150, R_refine = 60, C = 600, hash_t = 30, hash_l = 10;  // nsg_lshcs
    }else if (dataset == "miniimagenet-t2i_ed") {
        L = 200, S = 200, L_refine = 150, R_refine = 60, C = 600, hash_t = 30, hash_l = 10;  // nsg_lshcs
    }else {
        std::cout << "input dataset error!\n";
        exit(-1);
    }
    // parameters.set<unsigned>("K", K);
    // parameters.set<unsigned>("L", L);
    // parameters.set<unsigned>("ITER", Iter);
    parameters.set<unsigned>("S", S);
    // parameters.set<unsigned>("R", R);

    parameters.set<unsigned>("L_refine", L_refine);
    parameters.set<unsigned>("R_refine", R_refine);
    parameters.set<unsigned>("C_refine", C);

    const bool UseColliCount = false;
    parameters.set<bool>("UseColliCount", UseColliCount);
    if (UseColliCount){
        parameters.set<unsigned>("hash_t", 2);
        parameters.set<unsigned>("hash_l", 10);
    }else{
        parameters.set<unsigned>("hash_t", hash_t);
        parameters.set<unsigned>("hash_l", hash_l);
    }
}

void SSG_PARA(std::string dataset, weavess::Parameters &parameters) {
    unsigned K, L, Iter, S, R, L_refine, R_refine;
    if (dataset == "nytimes") {
        K = 400, L = 420, Iter = 6, S = 20, R = 300, L_refine = 250, R_refine = 20;   // ssg
    }else if (dataset == "coco-t2i") {
        K = 100, L = 110, Iter = 7, S = 20, R = 300, L_refine = 300, R_refine = 30;   // ssg
    }else if (dataset == "coco-i2i"){
        K = 100, L = 110, Iter = 7, S = 20, R = 300, L_refine = 300, R_refine = 30;   // ssg
    }else if (dataset == "glove25") {
        K = 300, L = 320, Iter = 12, S = 10, R = 200, L_refine = 150, R_refine = 30;   // ssg
    }else if (dataset == "text2image1m") {
        K = 400, L = 420, Iter = 12, S = 20, R = 100, L_refine = 50, R_refine = 20;   // ssg
    }else if (dataset == "n100000_d128_cube") {
        K = 200, L = 210, Iter = 15, S = 20, R = 200, L_refine = 100, R_refine = 80;   // ssg
    }else if (dataset == "miniimagenet-i2i") {
        K = 100, L = 110, Iter = 7, S = 20, R = 300, L_refine = 300, R_refine = 30;   // ssg
    }else if (dataset == "miniimagenet-t2i") {
        K = 100, L = 110, Iter = 7, S = 20, R = 300, L_refine = 300, R_refine = 30;   // ssg
    }else if (dataset == "n100000_d128_sphere") {
        K = 200, L = 210, Iter = 15, S = 20, R = 200, L_refine = 100, R_refine = 80;   // ssg
    }else if (dataset == "glove100") {
        K = 300, L = 320, Iter = 12, S = 10, R = 200, L_refine = 150, R_refine = 30;   // ssg
    }else if (dataset == "miniimagenet-i2i_ed") {
        K = 100, L = 110, Iter = 7, S = 20, R = 300, L_refine = 300, R_refine = 30;   // ssg
    }else if (dataset == "miniimagenet-t2i_ed") {
        K = 100, L = 110, Iter = 7, S = 20, R = 300, L_refine = 300, R_refine = 30;   // ssg
    }else {
        std::cout << "input dataset error!\n";
        exit(-1);
    }
    parameters.set<unsigned>("K", K);
    parameters.set<unsigned>("L", L);
    parameters.set<unsigned>("ITER", Iter);
    parameters.set<unsigned>("S", S);
    parameters.set<unsigned>("R", R);

    parameters.set<unsigned>("L_refine", L_refine);
    parameters.set<unsigned>("R_refine", R_refine);
    parameters.set<float>("A", 60);
    parameters.set<unsigned>("n_try", 10);
}

void DPG_PARA(std::string dataset, weavess::Parameters &parameters) {
    unsigned K, L, Iter, S, R;
    if (dataset == "nytimes") {
        K = 100, L = 100, Iter = 6, S = 20, R = 300;   // nytimes
    }else if (dataset == "coco-t2i") {
        K = 100, L = 100, Iter = 7, S = 20, R = 200;   // coco-t2i
    }else if (dataset == "coco-i2i"){
        K = 100, L = 100, Iter = 7, S = 20, R = 200;   // coco-i2i
    }else if (dataset == "glove25") {
        K = 100, L = 100, Iter = 12, S = 20, R = 100;   // glove25
    }else if (dataset == "text2image1m") {
        K = 90, L = 130, Iter = 12, S = 20, R = 50;   // text2image1m
    }else if (dataset == "n100000_d128_cube") {
        K = 100, L = 100, Iter = 12, S = 20, R = 50;   // n100000_d128_cube
    }else if (dataset == "miniimagenet-i2i") {
        K = 100, L = 100, Iter = 7, S = 20, R = 200;   // miniimagenet-i2i
    }else if (dataset == "miniimagenet-t2i") {
        K = 100, L = 100, Iter = 7, S = 20, R = 200;   // miniimagenet-t2i
    }else if (dataset == "n100000_d128_sphere") {
        K = 100, L = 100, Iter = 12, S = 20, R = 50;   // n100000_d128_sphere
    }else if (dataset == "glove100") {
        K = 100, L = 130, Iter = 12, S = 20, R = 100;   // glove100
    }else if (dataset == "miniimagenet-i2i_ed") {
        K = 100, L = 100, Iter = 7, S = 20, R = 200;   // miniimagenet-i2i_ed
    }else if (dataset == "miniimagenet-t2i_ed") {
        K = 100, L = 100, Iter = 7, S = 20, R = 200;   // miniimagenet-t2i_ed
    }else {
        std::cout << "input dataset error!\n";
        exit(-1);
    }
    parameters.set<unsigned>("K", K);
    parameters.set<unsigned>("L", L);
    parameters.set<unsigned>("ITER", Iter);
    parameters.set<unsigned>("S", S);
    parameters.set<unsigned>("R", R);
}

void VAMANA_PARA(std::string dataset, weavess::Parameters &parameters) {
    unsigned L, R;
    if (dataset == "nytimes") {
        L = 60, R = 30;    // nytimes
    }else if (dataset == "coco-t2i") {
        L = 140, R = 110;    // coco-t2i
    }else if (dataset == "coco-i2i"){
        L = 140, R = 110;    // coco-i2i
    }else if (dataset == "glove25") {
        L = 120, R = 110;    // glove25
    }else if (dataset == "text2image1m") {
        L = 70, R = 50;    // text2image1m
    }else if (dataset == "n100000_d128_cube") {
        L = 80, R = 70;    // n100000_d128_cube
    }else if (dataset == "miniimagenet-i2i") {
        L = 140, R = 110;    // miniimagenet-i2i
    }else if (dataset == "miniimagenet-t2i") {
        L = 140, R = 110;    // miniimagenet-t2i
    }else if (dataset == "n100000_d128_sphere") {
        L = 80, R = 70;    // n100000_d128_sphere
    }else if (dataset == "glove100") {
        L = 120, R = 110;    // glove100
    }else if (dataset == "miniimagenet-i2i_ed") {
        L = 140, R = 110;    // miniimagenet-i2i_ed
    }else if (dataset == "miniimagenet-t2i_ed") {
        L = 140, R = 110;    // miniimagenet-t2i_ed
    }else {
        std::cout << "dataset error!\n";
        exit(-1);
    }
    parameters.set<unsigned>("L", R);
    parameters.set<unsigned>("L_refine", L);
    parameters.set<unsigned>("R_refine", R);
}

void EFANNA_PARA(std::string dataset, weavess::Parameters &parameters) {
    unsigned nTrees, mLevel, K, L, Iter, S, R;
    if (dataset == "nytimes") {
        nTrees = 4, mLevel = 8, K = 40, L = 50, Iter = 7, S = 10, R = 150;    // nytimes
    }else if (dataset == "coco-t2i") {
        nTrees = 4, mLevel = 8, K = 40, L = 140, Iter = 5, S = 35, R = 150;    // coco-t2i
    }else if (dataset == "coco-i2i"){
        nTrees = 4, mLevel = 8, K = 40, L = 140, Iter = 5, S = 35, R = 150;    // coco-i2i
    }else if (dataset == "glove25") {
        nTrees = 8, mLevel = 8, K = 100, L = 170, Iter = 7, S = 10, R = 100;    // glove25
    }else if (dataset == "text2image1m") {
        nTrees = 8, mLevel = 8, K = 60, L = 70, Iter = 10, S = 15, R = 150;    // text2image1m
    }else if (dataset == "n100000_d128_cube") {
        nTrees = 4, mLevel = 8, K = 40, L = 40, Iter = 7, S = 25, R = 150;    // n100000_d128_cube
    }else if (dataset == "miniimagenet-i2i") {
        nTrees = 4, mLevel = 8, K = 40, L = 140, Iter = 5, S = 35, R = 150;    // miniimagenet-i2i
    }else if (dataset == "miniimagenet-t2i") {
        nTrees = 4, mLevel = 8, K = 40, L = 140, Iter = 5, S = 35, R = 150;    // miniimagenet-t2i
    }else if (dataset == "n100000_d128_sphere") {
        nTrees = 4, mLevel = 8, K = 100, L = 160, Iter = 7, S = 15, R = 100;    // n100000_d128_sphere
    }else if (dataset == "glove100") {
        nTrees = 8, mLevel = 8, K = 100, L = 170, Iter = 7, S = 10, R = 100;    // glove100
    }else if (dataset == "miniimagenet-i2i_ed") {
        nTrees = 4, mLevel = 8, K = 40, L = 140, Iter = 5, S = 35, R = 150;    // miniimagenet-i2i_ed
    }else if (dataset == "miniimagenet-t2i_ed") {
        nTrees = 4, mLevel = 8, K = 40, L = 140, Iter = 5, S = 35, R = 150;    // miniimagenet-t2i_ed
    }else {
        std::cout << "dataset error!\n";
        exit(-1);
    }
    parameters.set<unsigned>("nTrees", nTrees);
    parameters.set<unsigned>("mLevel", mLevel);
    parameters.set<unsigned>("K", K);
    parameters.set<unsigned>("L", L);
    parameters.set<unsigned>("ITER", Iter);
    parameters.set<unsigned>("S", S);
    parameters.set<unsigned>("R", R);
}

void NSW_PARA(std::string dataset, weavess::Parameters &parameters) {
    unsigned max_m0, ef_construction;
    if (dataset == "nytimes") {
        max_m0 = 30, ef_construction = 400;    // nytimes
    }else if (dataset == "coco-t2i") {
        max_m0 = 80, ef_construction = 600;    // coco-t2i
    }else if (dataset == "coco-i2i"){
        max_m0 = 80, ef_construction = 600;    // coco-i2i
    }else if (dataset == "glove25") {
        max_m0 = 80, ef_construction = 100;    // glove25
    }else if (dataset == "text2image1m") {
        max_m0 = 40, ef_construction = 300;    // text2image1m
    }else if (dataset == "n100000_d128_cube") {
        max_m0 = 80, ef_construction = 1000;    // n100000_d128_cube
    }else if (dataset == "miniimagenet-i2i") {
        max_m0 = 80, ef_construction = 600;    // miniimagenet-i2i
    }else if (dataset == "miniimagenet-t2i") {
        max_m0 = 80, ef_construction = 600;    // miniimagenet-t2i
    }else if (dataset == "n100000_d128_sphere") {
        max_m0 = 100, ef_construction = 400;    // n100000_d128_sphere
    }else if (dataset == "glove100") {
        max_m0 = 80, ef_construction = 100;    // glove100
    }else if (dataset == "miniimagenet-i2i_ed") {
        max_m0 = 80, ef_construction = 600;    // miniimagenet-i2i_ed
    }else if (dataset == "miniimagenet-t2i_ed") {
        max_m0 = 80, ef_construction = 600;    // miniimagenet-t2i_ed
    }else {
        std::cout << "dataset error!\n";
        exit(-1);
    }
    parameters.set<unsigned>("NN", max_m0);
    parameters.set<unsigned>("ef_construction", ef_construction);
}

void HCNNG_PARA(std::string dataset, weavess::Parameters &parameters) {
    unsigned num_cl;
    if (dataset == "nytimes") {
        num_cl = 80;    // nytimes
    }else if (dataset == "coco-t2i") {
        num_cl = 100;    // coco-t2i
    }else if (dataset == "coco-i2i"){
        num_cl = 100;    // coco-i2i
    }else if (dataset == "glove25") {
        num_cl = 100;    // glove25
    }else if (dataset == "text2image1m") {
        num_cl = 90;    // text2image1m
    }else if (dataset == "n100000_d128_cube") {
        num_cl = 100;    // n100000_d128_cube
    }else if (dataset == "miniimagenet-i2i") {
        num_cl = 100;    // miniimagenet-i2i
    }else if (dataset == "miniimagenet-t2i") {
        num_cl = 100;    // miniimagenet-t2i
    }else if (dataset == "n100000_d128_sphere") {
        num_cl = 100;    // n100000_d128_sphere
    }else if (dataset == "glove100") {
        num_cl = 100;    // glove100
    }else if (dataset == "miniimagenet-i2i_ed") {
        num_cl = 100;    // miniimagenet-i2i_ed
    }else if (dataset == "miniimagenet-t2i_ed") {
        num_cl = 100;    // miniimagenet-t2i_ed
    }else {
        std::cout << "dataset error!\n";
        exit(-1);
    }
    parameters.set<unsigned>("num_cl", num_cl);
    parameters.set<unsigned>("K", 10);
    parameters.set<unsigned>("nTrees", 10);
    parameters.set<unsigned>("mLevel", 1);
}

void SPTAG_KDT_PARA(std::string dataset, weavess::Parameters &parameters) {
    unsigned KDT_Number, TPT_Number, TPT_leaf_size, scale, CEF;
    if (dataset == "nytimes") {
        KDT_Number = 1, TPT_Number = 16, TPT_leaf_size = 500, scale = 8, CEF = 500;    // nytimes
    }else if (dataset == "coco-t2i") {
        KDT_Number = 4, TPT_Number = 16, TPT_leaf_size = 500, scale = 8, CEF = 1500;    // coco-t2i
    }else if (dataset == "coco-i2i"){
        KDT_Number = 4, TPT_Number = 16, TPT_leaf_size = 500, scale = 8, CEF = 1500;    // coco-i2i
    }else if (dataset == "glove25") {
        KDT_Number = 4, TPT_Number = 32, TPT_leaf_size = 1000, scale = 2, CEF = 1500;    // glove25
    }else if (dataset == "text2image1m") {
        KDT_Number = 1, TPT_Number = 16, TPT_leaf_size = 500, scale = 8, CEF = 500;    // text2image1m
    }else if (dataset == "n100000_d128_cube") {
        KDT_Number = 4, TPT_Number = 16, TPT_leaf_size = 1500, scale = 2, CEF = 1500;    // n100000_d128_cube
    }else if (dataset == "miniimagenet-i2i") {
        KDT_Number = 4, TPT_Number = 16, TPT_leaf_size = 500, scale = 8, CEF = 1500;    // miniimagenet-i2i
    }else if (dataset == "miniimagenet-t2i") {
        KDT_Number = 4, TPT_Number = 16, TPT_leaf_size = 500, scale = 8, CEF = 1500;    // miniimagenet-t2i
    }else if (dataset == "n100000_d128_sphere") {
        KDT_Number = 4, TPT_Number = 16, TPT_leaf_size = 1500, scale = 2, CEF = 1500;    // n100000_d128_sphere
    }else if (dataset == "glove100") {
        KDT_Number = 4, TPT_Number = 32, TPT_leaf_size = 1000, scale = 2, CEF = 1500;    // glove100
    }else if (dataset == "miniimagenet-i2i_ed") {
        KDT_Number = 4, TPT_Number = 16, TPT_leaf_size = 500, scale = 8, CEF = 1500;    // miniimagenet-i2i_ed
    }else if (dataset == "miniimagenet-t2i_ed") {
        KDT_Number = 4, TPT_Number = 16, TPT_leaf_size = 500, scale = 8, CEF = 1500;    // miniimagenet-t2i_ed
    }else {
        std::cout << "dataset error!\n";
        exit(-1);
    }
    parameters.set<unsigned>("KDTNumber", KDT_Number);
    parameters.set<unsigned>("TPTNumber", TPT_Number);
    parameters.set<unsigned>("TPTLeafSize", TPT_leaf_size);
    parameters.set<unsigned>("NeighborhoodSize", 32);
    parameters.set<unsigned>("GraphNeighborhoodScale", scale);
    parameters.set<unsigned>("CEF", CEF);
    parameters.set<unsigned>("numOfThreads", parameters.get<unsigned>("n_threads"));
}

void SPTAG_BKT_PARA(std::string dataset, weavess::Parameters &parameters) {
    unsigned BKT_Number, BKT_kmeans_k, TPT_Number, TPT_leaf_size, scale, CEF;
    if (dataset == "nytimes") {
        BKT_Number = 4, BKT_kmeans_k = 64, TPT_Number = 16, TPT_leaf_size = 1000, scale = 2, CEF = 500;    // nytimes
    }else if (dataset == "coco-t2i") {
        BKT_Number = 1, BKT_kmeans_k = 16, TPT_Number = 16, TPT_leaf_size = 1500, scale = 2, CEF = 500;    // coco-t2i
    }else if (dataset == "coco-i2i"){
        BKT_Number = 1, BKT_kmeans_k = 16, TPT_Number = 16, TPT_leaf_size = 1500, scale = 2, CEF = 500;    // coco-i2i
    }else if (dataset == "glove25") {
        BKT_Number = 4, BKT_kmeans_k = 16, TPT_Number = 16, TPT_leaf_size = 500, scale = 2, CEF = 500;    // glove25
    }else if (dataset == "text2image1m") {
        BKT_Number = 1, BKT_kmeans_k = 16, TPT_Number = 16, TPT_leaf_size = 500, scale = 2, CEF = 500;    // text2image1m
    }else if (dataset == "n100000_d128_cube") {
        BKT_Number = 4, BKT_kmeans_k = 16, TPT_Number = 32, TPT_leaf_size = 500, scale = 2, CEF = 500;    // n100000_d128_cube
    }else if (dataset == "miniimagenet-i2i") {
        BKT_Number = 1, BKT_kmeans_k = 16, TPT_Number = 16, TPT_leaf_size = 1500, scale = 2, CEF = 500;    // miniimagenet-i2i
    }else if (dataset == "miniimagenet-t2i") {
        BKT_Number = 1, BKT_kmeans_k = 16, TPT_Number = 16, TPT_leaf_size = 1500, scale = 2, CEF = 500;    // miniimagenet-t2i
    }else if (dataset == "n100000_d128_sphere") {
        BKT_Number = 4, BKT_kmeans_k = 16, TPT_Number = 32, TPT_leaf_size = 500, scale = 2, CEF = 500;    // n100000_d128_sphere
    }else if (dataset == "glove100") {
        BKT_Number = 4, BKT_kmeans_k = 16, TPT_Number = 16, TPT_leaf_size = 500, scale = 2, CEF = 500;    // glove100
    }else if (dataset == "miniimagenet-i2i_ed") {
        BKT_Number = 1, BKT_kmeans_k = 16, TPT_Number = 16, TPT_leaf_size = 1500, scale = 2, CEF = 500;    // miniimagenet-i2i_ed
    }else if (dataset == "miniimagenet-t2i_ed") {
        BKT_Number = 1, BKT_kmeans_k = 16, TPT_Number = 16, TPT_leaf_size = 1500, scale = 2, CEF = 500;    // miniimagenet-t2i_ed
    }else {
        std::cout << "dataset error!\n";
        exit(-1);
    }
    parameters.set<unsigned>("BKTNumber", BKT_Number);
    parameters.set<unsigned>("BKTKMeansK", BKT_kmeans_k);
    parameters.set<unsigned>("TPTNumber", TPT_Number);
    parameters.set<unsigned>("TPTLeafSize", TPT_leaf_size);
    parameters.set<unsigned>("NeighborhoodSize", 32);
    parameters.set<unsigned>("GraphNeighborhoodScale", scale);
    parameters.set<unsigned>("CEF", CEF);
    parameters.set<unsigned>("numOfThreads", parameters.get<unsigned>("n_threads"));
}

void HNSW_PARA(std::string dataset, weavess::Parameters &parameters) {
    unsigned max_m, max_m0, ef_construction;
    if (dataset == "nytimes") {
        max_m = 10, max_m0 = 40, ef_construction = 200;
    }else if (dataset == "coco-t2i") {
        max_m = 50, max_m0 = 80, ef_construction = 900;
    }else if (dataset == "coco-i2i"){
        max_m = 50, max_m0 = 80, ef_construction = 900;
    }else if (dataset == "glove25") {
        max_m = 50, max_m0 = 60, ef_construction = 700;
    }else if (dataset == "text2image1m") {
        max_m = 40, max_m0 = 50, ef_construction = 800;
    }else if (dataset == "n100000_d128_cube") {
        max_m = 90, max_m0 = 100, ef_construction = 900;
    }else if (dataset == "miniimagenet-i2i") {
        max_m = 50, max_m0 = 80, ef_construction = 900;
    }else if (dataset == "miniimagenet-t2i") {
        max_m = 50, max_m0 = 80, ef_construction = 900;
    }else if (dataset == "n100000_d128_sphere") {
        max_m = 100, max_m0 = 100, ef_construction = 900;
    }else if (dataset == "glove100") {
        max_m = 50, max_m0 = 60, ef_construction = 700;
    }else if (dataset == "miniimagenet-i2i_ed") {
        max_m = 50, max_m0 = 80, ef_construction = 900;
    }else if (dataset == "miniimagenet-t2i_ed") {
        max_m = 50, max_m0 = 80, ef_construction = 900;
    }else {
        std::cout << "dataset error!\n";
        exit(-1);
    }
    parameters.set<unsigned>("max_m", max_m);
    parameters.set<unsigned>("max_m0", max_m0);
    parameters.set<unsigned>("ef_construction", ef_construction);
    parameters.set<int>("mult", -1);
}

void IEH_PARA(std::string dataset, weavess::Parameters &parameters) {
    std::string index_path = parameters.get<std::string>("index_path");
    std::string LSHtable_path(index_path);
    std::string LSHfunc_path(index_path);

    LSHtable_path.append("LSHtable_" + dataset + ".txt");
    LSHfunc_path.append("LSHfunc_" + dataset + ".txt");

    parameters.set<std::string>("train", parameters.get<std::string>("base_path"));
    parameters.set<std::string>("test", parameters.get<std::string>("query_path"));
    parameters.set<std::string>("func", LSHfunc_path);
    parameters.set<std::string>("basecode", LSHtable_path);
    parameters.set<std::string>("knntable", parameters.get<std::string>("graph_file"));

    // parameters.set<unsigned>("expand", 10);
    parameters.set<unsigned>("iterlimit", 3);
}

void PANNG_PARA(std::string dataset, weavess::Parameters &parameters) {
    unsigned K, L;
    if (dataset == "nytimes") {
        K = 40, L = 60;    // nytimes
    }else if (dataset == "coco-t2i") {
        K = 40, L = 40;    // coco-t2i
    }else if (dataset == "coco-i2i"){
        K = 40, L = 40;    // coco-i2i
    }else if (dataset == "glove25") {
        K = 40, L = 40;    // glove25
    }else if (dataset == "text2image1m") {
        K = 40, L = 50;    // text2image1m
    }else if (dataset == "n100000_d128_cube") {
        K = 50, L = 90;    // n100000_d128_cube
    }else if (dataset == "miniimagenet-i2i") {
        K = 40, L = 40;    // miniimagenet-i2i
    }else if (dataset == "miniimagenet-t2i") {
        K = 40, L = 40;    // miniimagenet-t2i
    }else if (dataset == "n100000_d128_sphere") {
        K = 50, L = 90;    // n100000_d128_sphere
    }else if (dataset == "glove100") {
        K = 40, L = 40;    // glove100
    }else if (dataset == "miniimagenet-i2i_ed") {
        K = 40, L = 40;    // miniimagenet-i2i_ed
    }else if (dataset == "miniimagenet-t2i_ed") {
        K = 40, L = 40;    // miniimagenet-t2i_ed
    }else {
        std::cout << "dataset error!\n";
        exit(-1);
    }
    parameters.set<unsigned>("NN", K);          // K
    parameters.set<unsigned>("ef_construction", L);        //L
}

void ONNG_PARA(std::string dataset, weavess::Parameters &parameters) {
    unsigned K, L, numOfOutgoingEdges, numOfIngoingEdges;
    if (dataset == "nytimes") {
        K = 100, L = 120, numOfOutgoingEdges = 10, numOfIngoingEdges = 100;    // nytimes
    }else if (dataset == "coco-t2i") {
        K = 100, L = 100, numOfOutgoingEdges = 10, numOfIngoingEdges = 100;    // coco-t2i
    }else if (dataset == "coco-i2i"){
        K = 100, L = 100, numOfOutgoingEdges = 10, numOfIngoingEdges = 100;    // coco-i2i
    }else if (dataset == "glove25") {
        K = 400, L = 430, numOfOutgoingEdges = 80, numOfIngoingEdges = 100;    // glove25
    }else if (dataset == "text2image1m") {
        K = 100, L = 110, numOfOutgoingEdges = 10, numOfIngoingEdges = 100;    // text2image1m
    }else if (dataset == "n100000_d128_cube") {
        K = 100, L = 100, numOfOutgoingEdges = 20, numOfIngoingEdges = 100;    // n100000_d128_cube
    }else if (dataset == "miniimagenet-i2i") {
        K = 100, L = 100, numOfOutgoingEdges = 10, numOfIngoingEdges = 100;    // miniimagenet-i2i
    }else if (dataset == "miniimagenet-t2i") {
        K = 100, L = 100, numOfOutgoingEdges = 10, numOfIngoingEdges = 100;    // miniimagenet-t2i
    }else if (dataset == "n100000_d128_sphere") {
        K = 100, L = 100, numOfOutgoingEdges = 20, numOfIngoingEdges = 100;    // n100000_d128_sphere
    }else if (dataset == "glove100") {
        K = 400, L = 430, numOfOutgoingEdges = 80, numOfIngoingEdges = 100;    // glove100
    }else if (dataset == "miniimagenet-i2i_ed") {
        K = 100, L = 100, numOfOutgoingEdges = 10, numOfIngoingEdges = 100;    // miniimagenet-i2i_ed
    }else if (dataset == "miniimagenet-t2i_ed") {
        K = 100, L = 100, numOfOutgoingEdges = 10, numOfIngoingEdges = 100;    // miniimagenet-t2i_ed
    }else {
        std::cout << "dataset error!\n";
        exit(-1);
    }
    parameters.set<unsigned>("NN", K);          // K
    parameters.set<unsigned>("ef_construction", L);        //L
    parameters.set<unsigned>("numOfOutgoingEdges", numOfOutgoingEdges);
    parameters.set<unsigned>("numOfIncomingEdges", numOfIngoingEdges);
    parameters.set<unsigned>("numOfQueries", 200);
    parameters.set<unsigned>("numOfResultantObjects", 20);
}

void KDRG_PARA(std::string dataset, weavess::Parameters &parameters) {
    unsigned K = 50;
    parameters.set<unsigned>("S", K);
    parameters.set<unsigned>("R_refine", K);
}

void set_data_path(std::string dataset, weavess::Parameters &parameters) {
    // dataset root path
    std::string dataset_root = parameters.get<std::string>("dataset_root");
    std::string base_path(dataset_root);
    std::string query_path(dataset_root);
    std::string ground_path(dataset_root);
    if (dataset == "nytimes") {
        base_path.append(R"(nytimes/nytimes_base.fbin)");
        query_path.append(R"(nytimes/nytimes_query.fbin)");
        ground_path.append(R"(nytimes/nytimes_groundtruth.ibin)");
    }else if (dataset == "coco-t2i"){
        base_path.append(R"(coco-t2i/coco-t2i_base.fbin)");
        query_path.append(R"(coco-t2i/coco-t2i_query.fbin)");
        ground_path.append(R"(coco-t2i/coco-t2i_groundtruth.ibin)");
    }else if (dataset == "coco-i2i"){
        base_path.append(R"(coco-i2i/coco-i2i_base.fbin)");
        query_path.append(R"(coco-i2i/coco-i2i_query.fbin)");
        ground_path.append(R"(coco-i2i/coco-i2i_groundtruth.ibin)");
    }else if (dataset == "glove25"){
        base_path.append(R"(glove25/glove25_base.fbin)");
        query_path.append(R"(glove25/glove25_query.fbin)");
        ground_path.append(R"(glove25/glove25_groundtruth.ibin)");
    }else if (dataset == "text2image1m") {
        base_path.append(R"(text2image1m/text2image1m_base.fbin)");
        query_path.append(R"(text2image1m/text2image1m_query.fbin)");
        ground_path.append(R"(text2image1m/text2image1m_groundtruth.ibin)");
    }else if (dataset == "n100000_d128_cube") {
        base_path.append(R"(n100000_d128_cube/n100000_d128_cube_base.fbin)");
        query_path.append(R"(n100000_d128_cube/n100000_d128_cube_query.fbin)");
        ground_path.append(R"(n100000_d128_cube/n100000_d128_cube_groundtruth.ibin)");
    }else if (dataset == "miniimagenet-i2i") {
        base_path.append(R"(miniimagenet-i2i/miniimagenet-i2i_base.fbin)");
        query_path.append(R"(miniimagenet-i2i/miniimagenet-i2i_query.fbin)");
        ground_path.append(R"(miniimagenet-i2i/miniimagenet-i2i_groundtruth.ibin)");
    }else if (dataset == "miniimagenet-t2i") {
        base_path.append(R"(miniimagenet-t2i/miniimagenet-t2i_base.fbin)");
        query_path.append(R"(miniimagenet-t2i/miniimagenet-t2i_query.fbin)");
        ground_path.append(R"(miniimagenet-t2i/miniimagenet-t2i_groundtruth.ibin)");
    }else if (dataset == "n100000_d128_sphere"){
        base_path.append(R"(n100000_d128_sphere/n100000_d128_sphere_base.fbin)");
        query_path.append(R"(n100000_d128_sphere/n100000_d128_sphere_query.fbin)");
        ground_path.append(R"(n100000_d128_sphere/n100000_d128_sphere_groundtruth.ibin)");
    }else if (dataset == "glove100"){
        base_path.append(R"(glove100/glove100_base.fbin)");
        query_path.append(R"(glove100/glove100_query.fbin)");
        ground_path.append(R"(glove100/glove100_groundtruth.ibin)");
    }else if (dataset == "miniimagenet-t2i_ed") {
        base_path.append(R"(miniimagenet-t2i_ed/miniimagenet-t2i_ed_base.fbin)");
        query_path.append(R"(miniimagenet-t2i_ed/miniimagenet-t2i_ed_query.fbin)");
        ground_path.append(R"(miniimagenet-t2i_ed/miniimagenet-t2i_ed_groundtruth.ibin)");
    }else if (dataset == "miniimagenet-i2i_ed") {
        base_path.append(R"(miniimagenet-i2i_ed/miniimagenet-i2i_ed_base.fbin)");
        query_path.append(R"(miniimagenet-i2i_ed/miniimagenet-i2i_ed_query.fbin)");
        ground_path.append(R"(miniimagenet-i2i_ed/miniimagenet-i2i_ed_groundtruth.ibin)");
    }else {
        std::cout << "dataset input error!\n";
        exit(-1);
    }
    parameters.set<std::string>("base_path", base_path);
    parameters.set<std::string>("query_path", query_path);
    parameters.set<std::string>("ground_path", ground_path);
}

void set_para(std::string alg, std::string dataset, weavess::Parameters &parameters) {
    
    set_data_path(dataset, parameters);
    if (parameters.get<std::string>("exc_type") != "build") {
        return;
    }
    if (alg == "linearscan"){
        // do nothing
    }else if (alg == "fanng") {
        FANNG_PARA(dataset, parameters);
    }else if (alg == "kgraph") {
        KGRAPH_PARA(dataset, parameters);
    }else if (alg == "nsg") {
        NSG_PARA(dataset, parameters);
    }else if (alg == "nsg_sphere2") {
        NSG_SPHERE2_PARA(dataset, parameters);
    }else if (alg == "nsg_knng") {
        NSG_KNNG_PARA(dataset, parameters);
    }else if (alg == "nsg_f") {
        NSG_PARA(dataset, parameters); // TODO
    }else if (alg == "nsg_lshcs") {
        NSG_LSHCS_PARA(dataset, parameters);
    }else if (alg == "nsg_lshcs_nonndes") {
        NSG_LSHCS_NONNDES_PARA(dataset, parameters);
    }else if (alg == "nsg_kdt") {
        NSG_KDT_PARA(dataset, parameters);
    }else if (alg == "nsg_lsh_sphere2") {
        NSG_LSH_SPHERE2_PARA(dataset, parameters);
    }else if (alg == "ssg") {
        SSG_PARA(dataset, parameters);
    }else if (alg == "dpg") {
        DPG_PARA(dataset, parameters);
    }else if (alg == "vamana") {
        VAMANA_PARA(dataset, parameters);
    }else if (alg == "efanna") {
        EFANNA_PARA(dataset, parameters);
    }else if (alg == "nsw") {
        NSW_PARA(dataset, parameters);
    }else if (alg == "hcnng") {
        HCNNG_PARA(dataset, parameters);
    }else if (alg == "sptag_kdt") {
        SPTAG_KDT_PARA(dataset, parameters);
    }else if (alg == "sptag_bkt") {
        SPTAG_BKT_PARA(dataset, parameters);
    }else if (alg == "hnsw") {
        HNSW_PARA(dataset, parameters);
    }else if (alg == "ieh") {
        IEH_PARA(dataset, parameters);
    }else if (alg == "panng") {
        PANNG_PARA(dataset, parameters);
    }else if (alg == "onng") {
        ONNG_PARA(dataset, parameters);
    }else if (alg == "kdrg") {
        KDRG_PARA(dataset, parameters);
    }
    else {
        std::cout << "algorithm input error!\n";
        exit(-1);
    }
}