//
// Created by MurphySL on 2020/10/23.
//

#include "weavess/component.h"
#include "SphereCentroid/SphereCentroid.h"

namespace weavess {

    void ComponentRefineEntryCentroid::EntryInner() {
        auto *center = new float[index->getBaseDim()];
        for (unsigned j = 0; j < index->getBaseDim(); j++) center[j] = 0;
        for (unsigned i = 0; i < index->getBaseLen(); i++) {
            for (unsigned j = 0; j < index->getBaseDim(); j++) {
                center[j] += index->getBaseData()[i * index->getBaseDim() + j];
            }
        }

        for (unsigned j = 0; j < index->getBaseDim(); j++) {
            center[j] /= index->getBaseLen();
        }

        std::vector<Index::Neighbor> tmp, pool;
        index->ep_ = rand() % index->getBaseLen();  // random initialize navigating point
        get_neighbors(center, tmp, pool);
        index->ep_ = tmp[0].id;

        std::cout << "ep_ " << index->ep_ << std::endl;
    }

    void ComponentRefineEntryCentroid::get_neighbors(const float *query, std::vector<Index::Neighbor> &retset,
                                                     std::vector<Index::Neighbor> &fullset) {
        unsigned L = index->L_refine;
        retset.resize(L + 1);
        std::vector<unsigned> init_ids(L);
        // initializer_->Search(query, nullptr, L, parameter, init_ids.data());
        boost::dynamic_bitset<> flags{index->getBaseLen(), 0};
        L = 0;
        for (unsigned i = 0; i < init_ids.size() && i < index->getFinalGraph()[index->ep_].size(); i++) {
            init_ids[i] = index->getFinalGraph()[index->ep_][i].id;
            flags[init_ids[i]] = true;
            L++;
        }
        while (L < init_ids.size()) {
            unsigned id = rand() % index->getBaseLen();
            if (flags[id]) continue;
            init_ids[L] = id;
            L++;
            flags[id] = true;
        }
        L = 0;
        for (unsigned i = 0; i < init_ids.size(); i++) {
            unsigned id = init_ids[i];
            if (id >= index->getBaseLen()) continue;
            float dist = index->getDist()->compare(index->getBaseData() + index->getBaseDim() * (size_t) id, query,
                                                   (unsigned) index->getBaseDim());
            retset[i] = Index::Neighbor(id, dist, true);
            //retset[i] = new Index::Node(id, dist, true, 0);
            // flags[id] = 1;
            L++;
        }
        std::sort(retset.begin(), retset.begin() + L);

        int k = 0;
        while (k < (int) L) {
            int nk = L;

            if (retset[k].flag) {
                retset[k].flag = false;
                unsigned n = retset[k].id;
                for (unsigned m = 0; m < index->getFinalGraph()[n].size(); ++m) {
                    unsigned id = index->getFinalGraph()[n][m].id;
                    if (flags[id]) continue;
                    flags[id] = true;

                    float dist = index->getDist()->compare(query,
                                                           index->getBaseData() + index->getBaseDim() * (size_t) id,
                                                           (unsigned) index->getBaseDim());
                    Index::Neighbor nn(id, dist, true);
                    fullset.push_back(nn);
                    if (dist >= retset[L - 1].distance) continue;
                    int r = Index::InsertIntoPool(retset.data(), L, nn);

                    if (L + 1 < retset.size()) ++L;
                    if (r < nk) nk = r;
                }
            }
            if (nk <= k)
                k = nk;
            else
                ++k;
        }
    }

    void ComponentRefineEntryCentroidSphere::EntryInner() {

        // convert raw data to Eigen matrix
        // calculate centroid of the data

        Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>> data(index->getBaseData(), index->getBaseLen(), index->getBaseDim());
        Eigen::VectorXf centroid = calcSphereCentroid(data, 10, 1e-6f, false);

        // convert Eigen vector to array of float
    
        auto centroid_ = new float[index->getBaseDim()];
        for (unsigned j = 0; j < index->getBaseDim(); j++) centroid_[j] = centroid(j);

        // use random navigating point (entry point) to find the nearest point of centroid
        // set the nearest point of centroid as final entry point
        std::vector<Index::Neighbor> tmp, pool;
        index->ep_ = rand() % index->getBaseLen();  // random initialize navigating point
        get_neighbors(centroid_, tmp, pool);
        index->ep_ = tmp[0].id;

        // search over the whole data set to find the nearest point of centroid
        // std::vector<Index::Neighbor> pool(index->getBaseLen());
        // for (unsigned i = 0; i < index->getBaseLen(); i++) {
        //     float dist = index->getDist()->compare(index->getBaseData() + index->getBaseDim() * (size_t) i, centroid_,
        //                                            (unsigned) index->getBaseDim());
        //     pool[i] = Index::Neighbor(i, dist, true);
        // }
        // std::sort(pool.begin(), pool.end());
        // index->ep_ = pool[0].id;

        std::cout << "ep_ " << index->ep_ << std::endl;
    }

    void ComponentRefineEntryCentroidSphere::get_neighbors(const float *query, std::vector<Index::Neighbor> &retset,
                                                     std::vector<Index::Neighbor> &fullset) {
        unsigned L = index->L_refine;
        retset.resize(L + 1);
        std::vector<unsigned> init_ids(L);
        // initializer_->Search(query, nullptr, L, parameter, init_ids.data());
        boost::dynamic_bitset<> flags{index->getBaseLen(), 0};
        L = 0;
        for (unsigned i = 0; i < init_ids.size() && i < index->getFinalGraph()[index->ep_].size(); i++) {
            init_ids[i] = index->getFinalGraph()[index->ep_][i].id;
            flags[init_ids[i]] = true;
            L++;
        }
        while (L < init_ids.size()) {
            unsigned id = rand() % index->getBaseLen();
            if (flags[id]) continue;
            init_ids[L] = id;
            L++;
            flags[id] = true;
        }
        L = 0;
        for (unsigned i = 0; i < init_ids.size(); i++) {
            unsigned id = init_ids[i];
            if (id >= index->getBaseLen()) continue;
            float dist = index->getDist()->compare(index->getBaseData() + index->getBaseDim() * (size_t) id, query,
                                                   (unsigned) index->getBaseDim());
            retset[i] = Index::Neighbor(id, dist, true);
            //retset[i] = new Index::Node(id, dist, true, 0);
            // flags[id] = 1;
            L++;
        }
        std::sort(retset.begin(), retset.begin() + L);

        int k = 0;
        while (k < (int) L) {
            int nk = L;

            if (retset[k].flag) {
                retset[k].flag = false;
                unsigned n = retset[k].id;
                for (unsigned m = 0; m < index->getFinalGraph()[n].size(); ++m) {
                    unsigned id = index->getFinalGraph()[n][m].id;
                    if (flags[id]) continue;
                    flags[id] = true;

                    float dist = index->getDist()->compare(query,
                                                           index->getBaseData() + index->getBaseDim() * (size_t) id,
                                                           (unsigned) index->getBaseDim());
                    Index::Neighbor nn(id, dist, true);
                    fullset.push_back(nn);
                    if (dist >= retset[L - 1].distance) continue;
                    int r = Index::InsertIntoPool(retset.data(), L, nn);

                    if (L + 1 < retset.size()) ++L;
                    if (r < nk) nk = r;
                }
            }
            if (nk <= k)
                k = nk;
            else
                ++k;
        }
    }

    void ComponentRefineEntryCentroidSphere2::EntryInner() {

        // convert raw data to Eigen matrix
        // calculate centroid of the data

        Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>> data(index->getBaseData(), index->getBaseLen(), index->getBaseDim());
        
        // Find a hyperplane to split the sphere into two hemi-sphere
        // Currently, random choose a hyper plane
        static std::default_random_engine e(0);
        static std::normal_distribution<float> normal_distr(0.0, 1.0);
        Eigen::VectorXf hyperplane = Eigen::VectorXf::Zero(index->getBaseDim()).unaryExpr([&](float x) { return normal_distr(e); });

        Eigen::VectorXi vec_if_gt_0 = ((data * hyperplane).array() > 0).cast<int>();
        std::vector<unsigned> ind_in_sphere1;
        std::vector<unsigned> ind_in_sphere2;
        for (unsigned i = 0; i < index->getBaseLen(); i++) {
            if (vec_if_gt_0(i) == 1) {
                ind_in_sphere1.push_back(i);
            } else {
                ind_in_sphere2.push_back(i);
            }
        }
        // debug
        std::cout << "hemi-sphere sizes: " << ind_in_sphere1.size() << " " << ind_in_sphere2.size() << std::endl;

        Eigen::VectorXf centroid1 = calcSphereCentroid(data(ind_in_sphere1, Eigen::all), 10, 1e-6f, false);
        Eigen::VectorXf centroid2 = calcSphereCentroid(data(ind_in_sphere2, Eigen::all), 10, 1e-6f, false);

        // convert Eigen vector to array of float
    
        auto centroid1_ = new float[index->getBaseDim()];
        auto centroid2_ = new float[index->getBaseDim()];
        for (unsigned j = 0; j < index->getBaseDim(); j++) {
            centroid1_[j] = centroid1(j);
            centroid2_[j] = centroid2(j);
        }

        index->eps_.resize(2);

        // search over the whole data set to find the nearest point of centroid
        std::vector<Index::Neighbor> pool1(index->getBaseLen());
        for (unsigned i = 0; i < index->getBaseLen(); i++) {
            float dist = index->getDist()->compare(index->getBaseData() + index->getBaseDim() * (size_t) i, centroid1_,
                                                   (unsigned) index->getBaseDim());
            pool1[i] = Index::Neighbor(i, dist, true);
        }
        std::sort(pool1.begin(), pool1.end());
        index->eps_[0] = pool1[0].id;

        std::vector<Index::Neighbor> pool2(index->getBaseLen());
        for (unsigned i = 0; i < index->getBaseLen(); i++) {
            float dist = index->getDist()->compare(index->getBaseData() + index->getBaseDim() * (size_t) i, centroid2_,
                                                   (unsigned) index->getBaseDim());
            pool2[i] = Index::Neighbor(i, dist, true);
        }
        std::sort(pool2.begin(), pool2.end());

        if (pool2[0].id != index->eps_[0]) {
            // not the same point as eps_[0]
            index->eps_[1] = pool2[0].id;
        }else {
            // find the second nearest point
            std::cout << "nn of centroid2_ is the same as centroid1_, find the second nearest point" << std::endl;
            index->eps_[1] = pool2[1].id;
        }

        std::cout << "eps_ " << index->eps_[0] << " " << index->eps_[1] << std::endl;
    }

    // TODO two entry points
    void ComponentRefineEntryCentroidSphere2::get_neighbors(const float *query, std::vector<Index::Neighbor> &retset,
                                                     std::vector<Index::Neighbor> &fullset) {
        unsigned L = index->L_refine;
        retset.resize(L + 1);
        std::vector<unsigned> init_ids(L);
        // initializer_->Search(query, nullptr, L, parameter, init_ids.data());
        boost::dynamic_bitset<> flags{index->getBaseLen(), 0};
        L = 0;
        for (unsigned i = 0; i < init_ids.size() && i < index->getFinalGraph()[index->ep_].size(); i++) {
            init_ids[i] = index->getFinalGraph()[index->ep_][i].id;
            flags[init_ids[i]] = true;
            L++;
        }
        while (L < init_ids.size()) {
            unsigned id = rand() % index->getBaseLen();
            if (flags[id]) continue;
            init_ids[L] = id;
            L++;
            flags[id] = true;
        }
        L = 0;
        for (unsigned i = 0; i < init_ids.size(); i++) {
            unsigned id = init_ids[i];
            if (id >= index->getBaseLen()) continue;
            float dist = index->getDist()->compare(index->getBaseData() + index->getBaseDim() * (size_t) id, query,
                                                   (unsigned) index->getBaseDim());
            retset[i] = Index::Neighbor(id, dist, true);
            //retset[i] = new Index::Node(id, dist, true, 0);
            // flags[id] = 1;
            L++;
        }
        std::sort(retset.begin(), retset.begin() + L);

        int k = 0;
        while (k < (int) L) {
            int nk = L;

            if (retset[k].flag) {
                retset[k].flag = false;
                unsigned n = retset[k].id;
                for (unsigned m = 0; m < index->getFinalGraph()[n].size(); ++m) {
                    unsigned id = index->getFinalGraph()[n][m].id;
                    if (flags[id]) continue;
                    flags[id] = true;

                    float dist = index->getDist()->compare(query,
                                                           index->getBaseData() + index->getBaseDim() * (size_t) id,
                                                           (unsigned) index->getBaseDim());
                    Index::Neighbor nn(id, dist, true);
                    fullset.push_back(nn);
                    if (dist >= retset[L - 1].distance) continue;
                    int r = Index::InsertIntoPool(retset.data(), L, nn);

                    if (L + 1 < retset.size()) ++L;
                    if (r < nk) nk = r;
                }
            }
            if (nk <= k)
                k = nk;
            else
                ++k;
        }
    }
}