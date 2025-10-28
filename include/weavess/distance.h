//
// Created by Murph on 2020/8/14.
//

#ifndef WEAVESS_DISTANCE_H
#define WEAVESS_DISTANCE_H

// #define USING_EUCLIDEAN

namespace weavess {
    class Distance {
    public:
        template<typename T>

#ifdef USING_EUCLIDEAN
        /* L2 distance */
        T compare(const T *a, const T *b, unsigned length) const {
            T result = 0;

            float diff0, diff1, diff2, diff3;
            const T *last = a + length;
            const T *unroll_group = last - 3;

            /* Process 4 items with each loop for efficiency. */
            while (a < unroll_group) {
                diff0 = a[0] - b[0];
                diff1 = a[1] - b[1];
                diff2 = a[2] - b[2];
                diff3 = a[3] - b[3];
                result += diff0 * diff0 + diff1 * diff1 + diff2 * diff2 + diff3 * diff3;
                a += 4;
                b += 4;
            }
            /* Process last 0-3 pixels.  Not needed for standard vector lengths. */
            while (a < last) {
                diff0 = *a++ - *b++;
                result += diff0 * diff0;
            }

            return result;
        }
#else
        /* cosine similarity */
        T compare(const T *a, const T *b, unsigned length) const {
            T result = 0;

            float dot = 0;
            float normA = 0;
            float normB = 0;

            const T *last = a + length;
            const T *unroll_group = last - 3;

            /* Process 4 items with each loop for efficiency. */
            while (a < unroll_group) {
                dot += a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3];
                normA += a[0] * a[0] + a[1] * a[1] + a[2] * a[2] + a[3] * a[3];
                normB += b[0] * b[0] + b[1] * b[1] + b[2] * b[2] + b[3] * b[3];
                a += 4;
                b += 4;
            }

            /* Process last 0-3 pixels.  Not needed for standard vector lengths. */
            while (a < last) {
                dot += *a * *b;
                normA += *a * *a;
                normB += *b * *b;
                a++;
                b++;
            }

            
            // if (normA == 0 || normB == 0) {
            //     return 0;
            // }            
            // return dot / (sqrt(normA) * sqrt(normB));

            // for compatibility with the original code
            // make `distance = 1 - CosineSimilarity`
            if (normA == 0 || normB == 0) {
                return 1;
            }
            return 1 - dot / (sqrt(normA) * sqrt(normB)); 
        }
#endif

        bool calc_angle_if_lt_90(const float *a, const float *b, const unsigned length) const {
            float dot = 0;
            const float *last = a + length;
            const float *unroll_group = last - 3;

            // Process 4 items with each loop for efficiency.
            while (a < unroll_group) {
                dot += a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3];
                a += 4;
                b += 4;
            }
            // Process last 0-3 pixels.  Not needed for standard vector lengths.
            while (a < last) {
                dot += *a++ * *b++;
            }

            return dot > 0;

        }
    };
}

#endif //WEAVESS_DISTANCE_H
