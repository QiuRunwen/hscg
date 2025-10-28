//
// Created by MurphySL on 2020/10/23.
//

#include "weavess/component.h"

namespace weavess {

    // NO LIMIT GREEDY
    void
    ComponentCandidateNSG::CandidateInner(const unsigned query, const unsigned enter, boost::dynamic_bitset<> flags,
                                          std::vector<Index::SimpleNeighbor> &result) {
        auto L = index->getParam().get<unsigned>("L_refine");

        std::vector<unsigned> init_ids(L);
        std::vector<Index::Neighbor> retset;
        retset.resize(L + 1);

        L = 0;
        for (unsigned i = 0; i < init_ids.size() && i < index->getFinalGraph()[enter].size(); i++) {
            init_ids[i] = index->getFinalGraph()[enter][i].id;
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
        // unsinged -> SimpleNeighbor
        for (unsigned i = 0; i < init_ids.size(); i++) {
            unsigned id = init_ids[i];
            if (id >= index->getBaseLen()) continue;
            float dist = index->getDist()->compare(index->getBaseData() + index->getBaseDim() * id,
                                                   index->getBaseData() + index->getBaseDim() * query,
                                                   (unsigned) index->getBaseDim());

            retset[i] = Index::Neighbor(id, dist, true);
            result.emplace_back(Index::SimpleNeighbor(id, dist));

            L++;
        }
        std::sort(retset.begin(), retset.begin() + L);
        index->i++;

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

                    float dist = index->getDist()->compare(index->getBaseData() + index->getBaseDim() * query,
                                                           index->getBaseData() + index->getBaseDim() * (size_t) id,
                                                           (unsigned) index->getBaseDim());

                    Index::Neighbor nn(id, dist, true);
                    result.push_back(Index::SimpleNeighbor(id, dist));

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

        std::vector<Index::Neighbor>().swap(retset);
        std::vector<unsigned>().swap(init_ids);
    }

    // NO LIMIT GREEDY
    void
    ComponentCandidateNSGSphere2::CandidateInner(const unsigned query, unsigned enter, boost::dynamic_bitset<> flags,
                                          std::vector<Index::SimpleNeighbor> &result) {
        // enter is not used in this function
        // instead, index->eps_ is used as the entry point
        auto L = index->getParam().get<unsigned>("L_refine");

        std::vector<unsigned> init_ids(L);
        std::vector<Index::Neighbor> retset;
        retset.resize(L + 1);

        // 1. the two entry points
        // 2. the neighbor of first entry point
        // 3. the neighbor of second entry point
        // 4. random select
        init_ids[0] = index->eps_[0];
        init_ids[1] = index->eps_[1];
        flags[init_ids[0]] = true;
        flags[init_ids[1]] = true;   
        L = 2;
        for (auto ep_nn_id : index->getFinalGraph()[index->eps_[0]]) {
            if (L >= init_ids.size()) break;
            unsigned id = ep_nn_id.id;
            if (flags[id]) continue;
            init_ids[L] = id;
            flags[id] = true;
            L++;
        }
        for (auto ep_nn_id : index->getFinalGraph()[index->eps_[1]]) {
            if (L >= init_ids.size()) break;
            unsigned id = ep_nn_id.id;
            if (flags[id]) continue;
            init_ids[L] = id;
            flags[id] = true;
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
        // unsinged -> SimpleNeighbor
        for (unsigned i = 0; i < init_ids.size(); i++) {
            unsigned id = init_ids[i];
            if (id >= index->getBaseLen()) continue;
            float dist = index->getDist()->compare(index->getBaseData() + index->getBaseDim() * id,
                                                   index->getBaseData() + index->getBaseDim() * query,
                                                   (unsigned) index->getBaseDim());

            retset[i] = Index::Neighbor(id, dist, true);
            result.emplace_back(Index::SimpleNeighbor(id, dist));

            L++;
        }
        std::sort(retset.begin(), retset.begin() + L);
        index->i++;

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

                    float dist = index->getDist()->compare(index->getBaseData() + index->getBaseDim() * query,
                                                           index->getBaseData() + index->getBaseDim() * (size_t) id,
                                                           (unsigned) index->getBaseDim());

                    Index::Neighbor nn(id, dist, true);
                    result.push_back(Index::SimpleNeighbor(id, dist));

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

        std::vector<Index::Neighbor>().swap(retset);
        std::vector<unsigned>().swap(init_ids);
    }
    
    // add KNNG as seed comparing to NSG. Not working
    // void ComponentCandidateLSHCS::CandidateInner(const unsigned query, const unsigned enter, boost::dynamic_bitset<> flags,
    //     std::vector<Index::SimpleNeighbor> &result) {

    //     auto L = index->getParam().get<unsigned>("L_refine");

    //     std::vector<unsigned> init_ids(L);
    //     std::vector<Index::Neighbor> retset;
    //     retset.resize(L + 1);
        
    //     // 1. the enter node
    //     // 2. the neighbors of the query node
    //     // 3. the neighbors of the enter node
    //     // 4. the random nodes
    //     unsigned curr_i = 0;
    //     init_ids[curr_i++] = enter;
    //     for (unsigned i = 0; curr_i < init_ids.size() && i < index->getFinalGraph()[query].size(); i++) {
    //         init_ids[curr_i] = index->getFinalGraph()[query][i].id;
    //         flags[init_ids[curr_i]] = true;
    //         curr_i++;
    //     }
    //     for (unsigned i = 0; curr_i < init_ids.size() && i < index->getFinalGraph()[enter].size(); i++) {
    //         init_ids[curr_i] = index->getFinalGraph()[enter][i].id;
    //         flags[init_ids[curr_i]] = true;
    //         curr_i++;
    //     }
    //     while (curr_i < init_ids.size()) {
    //         unsigned id = rand() % index->getBaseLen();
    //         if (flags[id]) continue;
    //         init_ids[curr_i] = id;
    //         curr_i++;
    //         flags[id] = true;
    //     }

    //     L = 0;
    //     // unsinged -> SimpleNeighbor
    //     for (unsigned i = 0; i < init_ids.size(); i++) {
    //         unsigned id = init_ids[i];
    //         if (id >= index->getBaseLen()) continue;
    //         float dist = index->getDist()->compare(index->getBaseData() + index->getBaseDim() * id,
    //                         index->getBaseData() + index->getBaseDim() * query,
    //                         (unsigned) index->getBaseDim());

    //         retset[i] = Index::Neighbor(id, dist, true);
    //         result.emplace_back(Index::SimpleNeighbor(id, dist));

    //         L++;
    //     }
    //     std::sort(retset.begin(), retset.begin() + L);
    //     index->i++;

    //     int k = 0;
    //     while (k < (int) L) {
    //         int nk = L;
    //         if (retset[k].flag) {
    //             retset[k].flag = false;
    //             unsigned n = retset[k].id;
    //             for (unsigned m = 0; m < index->getFinalGraph()[n].size(); ++m) {

    //                 unsigned id = index->getFinalGraph()[n][m].id;

    //                 if (flags[id]) continue;
    //                 flags[id] = true;

    //                 float dist = index->getDist()->compare(index->getBaseData() + index->getBaseDim() * query,
    //                                         index->getBaseData() + index->getBaseDim() * (size_t) id,
    //                                         (unsigned) index->getBaseDim());

    //                 Index::Neighbor nn(id, dist, true);
    //                 result.push_back(Index::SimpleNeighbor(id, dist));

    //                 if (dist >= retset[L - 1].distance) continue;

    //                 int r = Index::InsertIntoPool(retset.data(), L, nn);

    //                 if (L + 1 < retset.size()) ++L;
    //                 if (r < nk) nk = r;
    //             }
    //         }
    //         if (nk <= k)
    //         k = nk;
    //         else
    //         ++k;
    //     }

    //     std::vector<Index::Neighbor>().swap(retset);
    //     std::vector<unsigned>().swap(init_ids);
    // }

    // Raw KNNG as Candidate
    void ComponentCandidateLSHCS::CandidateInner(const unsigned query, const unsigned enter, boost::dynamic_bitset<> flags,
        std::vector<Index::SimpleNeighbor> &result) {
        
        for (unsigned i = 0; i < index->getFinalGraph()[query].size(); i++) {
            unsigned id = index->getFinalGraph()[query][i].id;
            if (flags[id]) continue;
            flags[id] = true;
            float dist = index->getDist()->compare(index->getBaseData() + index->getBaseDim() * query,
                index->getBaseData() + index->getBaseDim() * id,
                index->getBaseDim());
            result.emplace_back(id, dist);
        }
    }


    // PROPAGATION 2
    void ComponentCandidatePropagation2::CandidateInner(const unsigned query, const unsigned enter,
                                                        boost::dynamic_bitset<> flags,
                                                        std::vector<Index::SimpleNeighbor> &pool) {
        flags[enter] = true;

        for (unsigned i = 0; i < index->getFinalGraph()[enter].size(); i++) {
            unsigned nid = index->getFinalGraph()[enter][i].id;
            for (unsigned nn = 0; nn < index->getFinalGraph()[nid].size(); nn++) {
                unsigned nnid = index->getFinalGraph()[nid][nn].id;
                if (flags[nnid]) continue;
                flags[nnid] = true;
                float dist = index->getDist()->compare(index->getBaseData() + index->getBaseDim() * query,
                                                       index->getBaseData() + index->getBaseDim() * nnid,
                                                       index->getBaseDim());
                pool.emplace_back(nnid, dist);
                if (pool.size() >= index->L_refine) break;
            }
            if (pool.size() >= index->L_refine) break;
        }
    }



    // SPTAG_BKT
    void ComponentCandidateSPTAG_BKT::BKTSearch(unsigned int query, Index::Heap &m_NGQueue,
                                                Index::Heap &m_SPTQueue, Index::OptHashPosVector &nodeCheckStatus,
                                                unsigned int &m_iNumberOfCheckedLeaves,
                                                unsigned int &m_iNumberOfTreeCheckedLeaves,
                                                int p_limits) {
        while (!m_SPTQueue.empty())
        {
            Index::HeapCell bcell = m_SPTQueue.pop();
            const Index::BKTNode& tnode = index->m_pBKTreeRoots[bcell.node];
            if (tnode.childStart < 0) {
                if (!nodeCheckStatus.CheckAndSet(tnode.centerid)) {
                    m_iNumberOfCheckedLeaves++;
                    m_NGQueue.insert(Index::HeapCell(tnode.centerid, bcell.distance));
                }
                if (m_iNumberOfCheckedLeaves >= p_limits) break;
            }
            else {
                if (!nodeCheckStatus.CheckAndSet(tnode.centerid)) {
                    m_NGQueue.insert(Index::HeapCell(tnode.centerid, bcell.distance));
                }
                for (int begin = tnode.childStart; begin < tnode.childEnd; begin++) {
                    int tmp = index->m_pBKTreeRoots[begin].centerid;
                    float dist = index->getDist()->compare(index->getBaseData() + index->getBaseDim() * query,
                                                           index->getBaseData() + index->getBaseDim() * tmp,
                                                           index->getBaseDim());
                    m_SPTQueue.insert(Index::HeapCell(begin, dist));
                }
            }
        }
    }

    void ComponentCandidateSPTAG_BKT::CandidateInner(unsigned int query, unsigned int enter,
                                                     boost::dynamic_bitset<> flags,
                                                     std::vector<Index::SimpleNeighbor> &result) {
        unsigned maxCheck = index->m_iMaxCheckForRefineGraph > index->m_iMaxCheck ? index->m_iMaxCheckForRefineGraph : index->m_iMaxCheck;
        unsigned m_iContinuousLimit = maxCheck / 64;
        const float MaxDist = (std::numeric_limits<float>::max)();

        unsigned m_iNumOfContinuousNoBetterPropagation = 0;
        unsigned m_iNumberOfCheckedLeaves = 0;
        unsigned m_iNumberOfTreeCheckedLeaves = 0;

        // Prioriy queue used for neighborhood graph
        Index::Heap m_NGQueue;
        m_NGQueue.Resize(maxCheck * 30);

        // Priority queue Used for Tree
        Index::Heap m_SPTQueue;
        m_SPTQueue.Resize(maxCheck * 10);

        Index::OptHashPosVector nodeCheckStatus;
        nodeCheckStatus.Init(maxCheck, index->m_iHashTableExp);
        nodeCheckStatus.CheckAndSet(query);

        Index::QueryResultSet p_query(index->L_refine);


        for (char i = 0; i < index->m_iTreeNumber; i++) {
            const Index::BKTNode& node = index->m_pBKTreeRoots[index->m_pTreeStart[i]];
            if (node.childStart < 0) {
                float dist = index->getDist()->compare(index->getBaseData() + index->getBaseDim() * query,
                                                       index->getBaseData() + index->getBaseDim() * node.centerid,
                                                       index->getBaseDim());
                m_SPTQueue.insert(Index::HeapCell(index->m_pTreeStart[i], dist));
            }
            else {
                for (int begin = node.childStart; begin < node.childEnd; begin++) {
                    int tmp = index->m_pBKTreeRoots[begin].centerid;
                    float dist = index->getDist()->compare(index->getBaseData() + index->getBaseDim() * query,
                                                           index->getBaseData() + index->getBaseDim() * tmp,
                                                           index->getBaseDim());
                    m_SPTQueue.insert(Index::HeapCell(begin, dist));
                }
            }
        }

        BKTSearch(query, m_NGQueue, m_SPTQueue, nodeCheckStatus, m_iNumberOfCheckedLeaves, m_iNumberOfTreeCheckedLeaves, index->m_iNumberOfInitialDynamicPivots);

        const unsigned checkPos = index->getFinalGraph()[0].size() - 1;
        while (!m_NGQueue.empty()) {
            Index::HeapCell gnode = m_NGQueue.pop();
            int tmpNode = gnode.node;
            std::vector<Index::SimpleNeighbor> node = index->getFinalGraph()[tmpNode];
            if (gnode.distance <= p_query.worstDist()) {
                int checkNode = node[checkPos].id;
                if (checkNode < -1) {
                    const Index::BKTNode& tnode = index->m_pBKTreeRoots[-2 - checkNode];
                    m_iNumOfContinuousNoBetterPropagation = 0;
                    p_query.AddPoint(tmpNode, gnode.distance);
                } else {
                    m_iNumOfContinuousNoBetterPropagation = 0;
                    p_query.AddPoint(tmpNode, gnode.distance);
                }
            } else {
                m_iNumOfContinuousNoBetterPropagation++;
                if (m_iNumOfContinuousNoBetterPropagation > m_iContinuousLimit || m_iNumberOfCheckedLeaves > maxCheck) {
                    p_query.SortResult();
                    for(int i = 0; i < p_query.GetResultNum(); i ++) {
                        if(p_query.GetResult(i)->Dist == MaxDist) break;
                        result.emplace_back(p_query.GetResult(i)->VID, p_query.GetResult(i)->Dist);
                    }
                    return;
                }
            }
            for (unsigned i = 0; i <= checkPos; i++) {
                int nn_index = node[i].id;
                if (nn_index < 0) break;
                if (nn_index >= index->getBaseLen()) break;
                if (nodeCheckStatus.CheckAndSet(nn_index)) continue;
                float distance2leaf = index->getDist()->compare(index->getBaseData() + index->getBaseDim() * query,
                                                                index->getBaseData() + index->getBaseDim() * nn_index,
                                                                index->getBaseDim());
                m_iNumberOfCheckedLeaves++;
                m_NGQueue.insert(Index::HeapCell(nn_index, distance2leaf));
            }
            if (m_NGQueue.Top().distance > m_SPTQueue.Top().distance) {
                BKTSearch(query, m_NGQueue, m_SPTQueue, nodeCheckStatus, m_iNumberOfCheckedLeaves, m_iNumberOfTreeCheckedLeaves, index->m_iNumberOfOtherDynamicPivots + m_iNumberOfCheckedLeaves);
            }
        }
        p_query.SortResult();
        for(int i = 0; i < p_query.GetResultNum(); i ++) {
            if(p_query.GetResult(i)->Dist == MaxDist) break;
            result.emplace_back(p_query.GetResult(i)->VID, p_query.GetResult(i)->Dist);
        }
    }



    // SPTAG_KDT
    void ComponentCandidateSPTAG_KDT::KDTSearch(unsigned int query, int node, Index::Heap &m_NGQueue,
                                                Index::Heap &m_SPTQueue, Index::OptHashPosVector &nodeCheckStatus,
                                                unsigned int &m_iNumberOfCheckedLeaves,
                                                unsigned int &m_iNumberOfTreeCheckedLeaves) {
        if (node < 0)
        {
            int tmp = -node - 1;
            if (tmp >= index->getBaseLen()) return;
            if (nodeCheckStatus.CheckAndSet(tmp)) return;

            ++m_iNumberOfTreeCheckedLeaves;
            ++m_iNumberOfCheckedLeaves;
            m_NGQueue.insert(Index::HeapCell(tmp, index->getDist()->compare(index->getBaseData() + index->getBaseDim() * query,
                                                                            index->getBaseData() + index->getBaseDim() * tmp,
                                                                            index->getBaseDim())));
            return;
        }

        auto& tnode = index->m_pKDTreeRoots[node];

        float distBound = 0;
        float diff = (index->getBaseData() + index->getBaseDim() * query)[tnode.split_dim] - tnode.split_value;
        float distanceBound = distBound + diff * diff;
        int otherChild, bestChild;
        if (diff < 0)
        {
            bestChild = tnode.left;
            otherChild = tnode.right;
        }
        else
        {
            otherChild = tnode.left;
            bestChild = tnode.right;
        }

        //std::cout << 3 << std::endl;

        m_SPTQueue.insert(Index::HeapCell(otherChild, distanceBound));
        KDTSearch(query, bestChild, m_NGQueue, m_SPTQueue, nodeCheckStatus, m_iNumberOfCheckedLeaves, m_iNumberOfTreeCheckedLeaves);
    }

    void ComponentCandidateSPTAG_KDT::CandidateInner(unsigned int query, unsigned int enter,
                                                     boost::dynamic_bitset<> flags,
                                                     std::vector<Index::SimpleNeighbor> &result) {
        unsigned m_iNumberOfCheckedLeaves = 0;
        unsigned m_iNumberOfTreeCheckedLeaves = 0;
        unsigned m_iNumOfContinuousNoBetterPropagation = 0;
        const float MaxDist = (std::numeric_limits<float>::max)();
        unsigned m_iThresholdOfNumberOfContinuousNoBetterPropagation = 3;
        unsigned m_iNumberOfInitialDynamicPivots = 50;
        unsigned maxCheck = index->m_iMaxCheckForRefineGraph > index->m_iMaxCheck ? index->m_iMaxCheckForRefineGraph : index->m_iMaxCheck;

        // Prioriy queue used for neighborhood graph
        Index::Heap m_NGQueue;
        m_NGQueue.Resize(maxCheck * 30);

        // Priority queue Used for Tree
        Index::Heap m_SPTQueue;
        m_SPTQueue.Resize(maxCheck * 10);

        Index::OptHashPosVector nodeCheckStatus;
        nodeCheckStatus.Init(maxCheck, index->m_iHashTableExp);
        nodeCheckStatus.CheckAndSet(query);

        Index::QueryResultSet p_query(index->L_refine + 1);
        //std::priority_queue<Index::SPTAGCloserFirst> res;

        for(int i = 0; i < index->m_iTreeNumber; i ++) {
            int node = index->m_pTreeStart[i];

            KDTSearch(query, node, m_NGQueue, m_SPTQueue, nodeCheckStatus, m_iNumberOfCheckedLeaves, m_iNumberOfTreeCheckedLeaves);
        }

        unsigned p_limits = m_iNumberOfInitialDynamicPivots;
        while (!m_SPTQueue.empty() && m_iNumberOfCheckedLeaves < p_limits)
        {
            auto& tcell = m_SPTQueue.pop();
            KDTSearch(query, tcell.node, m_NGQueue, m_SPTQueue, nodeCheckStatus, m_iNumberOfCheckedLeaves, m_iNumberOfTreeCheckedLeaves);
        }

        while (!m_NGQueue.empty()) {
            Index::HeapCell gnode = m_NGQueue.pop();
            std::vector<Index::SimpleNeighbor> node = index->getFinalGraph()[gnode.node];

            if (!p_query.AddPoint(gnode.node, gnode.distance) && m_iNumberOfCheckedLeaves > index->m_iMaxCheck) {
                p_query.SortResult();
                for(int i = 0; i < p_query.GetResultNum(); i ++) {
                    if(p_query.GetResult(i)->Dist == MaxDist) break;
                    result.emplace_back(p_query.GetResult(i)->VID, p_query.GetResult(i)->Dist);
                }
                return;
            }
            float upperBound = std::max(p_query.worstDist(), gnode.distance);
            bool bLocalOpt = true;
            for (unsigned i = 0; i < index->R_refine; i++) {
                int nn_index = node[i].id;
                // TODO why
                if (nn_index >= index->getBaseLen()) break;
                if (nn_index < 0) break;
                if (nodeCheckStatus.CheckAndSet(nn_index)) continue;
                float distance2leaf = index->getDist()->compare(index->getBaseData() + index->getBaseDim() * query,
                                                       index->getBaseData() + index->getBaseDim() * nn_index,
                                                       index->getBaseDim());
                if (distance2leaf <= upperBound) bLocalOpt = false;
                m_iNumberOfCheckedLeaves++;
                m_NGQueue.insert(Index::HeapCell(nn_index, distance2leaf));
            }
            if (bLocalOpt) m_iNumOfContinuousNoBetterPropagation++;
            else m_iNumOfContinuousNoBetterPropagation = 0;
            if (m_iNumOfContinuousNoBetterPropagation > m_iThresholdOfNumberOfContinuousNoBetterPropagation) {
                if (m_iNumberOfTreeCheckedLeaves <= m_iNumberOfCheckedLeaves / 10) {
                    auto& tcell = m_SPTQueue.pop();
                    KDTSearch(query, tcell.node, m_NGQueue, m_SPTQueue, nodeCheckStatus, m_iNumberOfCheckedLeaves, m_iNumberOfTreeCheckedLeaves);
                } else if (gnode.distance > p_query.worstDist()) {
                    break;
                }
            }
        }
        p_query.SortResult();
        for(int i = 0; i < p_query.GetResultNum(); i ++) {
            if(p_query.GetResult(i)->Dist == MaxDist) break;
            result.emplace_back(p_query.GetResult(i)->VID, p_query.GetResult(i)->Dist);
        }
    }
}