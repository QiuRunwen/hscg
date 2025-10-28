#ifndef SPHERECENTROID_H
#define SPHERECENTROID_H

#include <Eigen/Dense>
#include <iostream>
#include <cmath>
// #include <cassert>

// Tolerance for floating‐point comparisons.
const float TOL = 1e-6f;

// Returns a rotation matrix R such that R * x = e_d, where e_d is the standard basis vector 
// with a 1 in the last coordinate.
Eigen::MatrixXf rotationMatrixXtoED(const Eigen::VectorXf &x, int d_of_ed = -1) {
    Eigen::VectorXf x_norm = x.normalized();
    int d = x_norm.size();
    if(d_of_ed < 0)
        d_of_ed = d - 1;
    Eigen::VectorXf ed = Eigen::VectorXf::Zero(d);
    ed[d_of_ed] = 1.0f;

    // if x is already e_d, no rotation is needed.
    if ((x_norm - ed).norm() < TOL)
        return Eigen::MatrixXf::Identity(d, d);

    bool need_to_flip = x_norm[d-1] < 0;
    Eigen::VectorXf x_mod = need_to_flip ? -x_norm : x_norm;

    // Form the Householder vector u = x + ed.
    Eigen::VectorXf u = x_mod + ed;
    float norm_u = u.norm();
    // If u is almost zero (i.e. x is nearly -ed), choose an arbitrary rotation.
    if (norm_u < 1e-10f) {
        Eigen::MatrixXf R = Eigen::MatrixXf::Identity(d, d);
        R(0, 0) = -1.0f;
        return R;
    }
    Eigen::VectorXf v = u / norm_u;
    Eigen::MatrixXf H = Eigen::MatrixXf::Identity(d, d) - 2.0f * v * v.transpose();
    Eigen::MatrixXf R = -H;
    if (need_to_flip)
        R = -R;
    return R;
}

// Returns a rotation matrix R such that R * e_d = x.
Eigen::MatrixXf rotationMatrixEDtoX(const Eigen::VectorXf &x) {
    int d = x.size();
    Eigen::VectorXf ed = Eigen::VectorXf::Zero(d);
    ed[d-1] = 1.0f;

    if ((x - ed).norm() < TOL)
        return Eigen::MatrixXf::Identity(d, d);
    if ((x + ed).norm() < TOL) {
        Eigen::MatrixXf R = Eigen::MatrixXf::Identity(d, d);
        R(0, 0) = -1.0f;
        R(d-1, d-1) = -1.0f;
        return R;
    }

    // Compute the rotation angle.
    float dot = std::min(1.0f, std::max(-1.0f, x[d-1]));
    float theta = std::acos(dot);
    float sin_theta = std::sin(theta);
    if (std::fabs(sin_theta) < 1e-8f)
        return Eigen::MatrixXf::Identity(d, d);

    // Compute unit vector w orthogonal to ed.
    Eigen::VectorXf w = (x - x[d-1] * ed) / sin_theta;

    Eigen::MatrixXf R = Eigen::MatrixXf::Identity(d, d);
    R += (std::cos(theta) - 1.0f) * (ed * ed.transpose() + w * w.transpose());
    R += std::sin(theta) * (w * ed.transpose() - ed * w.transpose());
    return R;
}

// Project data from the tangent hyperplane back to the sphere using the exponential map.
// Expects each row of 'data' to have its last coordinate equal to 1.
Eigen::MatrixXf tangentHyperplaneToSphereExponentialMap(const Eigen::MatrixXf &data, const Eigen::VectorXf &tangent_point) {
    int n = data.rows();
    int d = data.cols();
    Eigen::VectorXf tp = tangent_point;
    if (tp.size() == 0) {
        tp = Eigen::VectorXf::Zero(d);
        tp[d-1] = 1.0f;
    }

    Eigen::MatrixXf m_x_to_ed = rotationMatrixXtoED(tp);
    // Rotate data: note that we multiply by the transpose.
    Eigen::MatrixXf data_rot = data * m_x_to_ed.transpose();

    // Assert that the last column is 1 using vectorized check (for debugging)
    // (This might be omitted in a release build for speed.)
    // for (int i = 0; i < n; ++i) {
    //     assert(std::fabs(data_rot(i, d-1) - 1.0f) < TOL && "Last column should be 1 after rotation.");
    // }

    // Compute the Euclidean norm of the first d-1 columns for each row.
    Eigen::VectorXf dist2tp(n);
#pragma omp parallel for
    for (int i = 0; i < n; ++i) {
        dist2tp(i) = data_rot.block(i, 0, 1, d-1).norm();
    }
    // Eigen::VectorXf dist2tp = data_rot.block(0, 0, n, d-1).rowwise().norm();

    // Compute coefficient = sin(dist)/dist (with proper handling at dist=0).
    Eigen::VectorXf coeff(n);
#pragma omp parallel for
    for (int i = 0; i < n; ++i) {
        float r = dist2tp(i);
        coeff(i) = (std::fabs(r) > TOL) ? std::sin(r) / r : 1.0f;
    }

    // Build sphere_data: first d-1 columns scaled and last column as cos(dist)
    Eigen::MatrixXf sphere_data(n, d);
#pragma omp parallel for
    for (int i = 0; i < n; ++i) {
        sphere_data.block(i, 0, 1, d-1) = data_rot.block(i, 0, 1, d-1) * coeff(i);
        sphere_data(i, d-1) = std::cos(dist2tp(i));
    }

    Eigen::MatrixXf m_ed_to_x = rotationMatrixEDtoX(tp);
    Eigen::MatrixXf sphere_data_rot = sphere_data * m_ed_to_x.transpose();
    return sphere_data_rot;
}

// Project data from the sphere to the tangent hyperplane using the inverse exponential map.
Eigen::MatrixXf sphereToTangentHyperplaneInverseExpMap(const Eigen::MatrixXf &data, const Eigen::VectorXf &tangent_point) {
    int n = data.rows();
    int d = data.cols();
    Eigen::VectorXf tp = tangent_point;
    if (tp.size() == 0) {
        tp = Eigen::VectorXf::Zero(d);
        tp[d-1] = 1.0f;
    }

    Eigen::MatrixXf m_x_to_ed = rotationMatrixXtoED(tp);
    Eigen::MatrixXf data_rot = data * m_x_to_ed.transpose();

    // Normalize each row.
#pragma omp parallel for
    for (int i = 0; i < n; ++i) {
        float norm = data_rot.row(i).norm();
        if (norm > TOL)
            data_rot.row(i) /= norm;
    }
    // data_rot = data_rot.array().rowwise() / data_rot.rowwise().norm().array();

    // Compute spherical distance from the tangent point: arccos(last coordinate)
    Eigen::VectorXf dist2tp(n);
#pragma omp parallel for
    for (int i = 0; i < n; ++i) {
        float val = std::min(1.0f, std::max(-1.0f, data_rot(i, d-1)));
        dist2tp(i) = std::acos(val);
    }

    // Compute coefficient = dist/sin(dist) (with handling for small values)
    Eigen::VectorXf coeff(n);
#pragma omp parallel for
    for (int i = 0; i < n; ++i) {
        float r = dist2tp(i);
        coeff(i) = (std::fabs(std::sin(r)) > TOL) ? r / std::sin(r) : 1.0f;
    }

    // Multiply each row by coeff and set the last column to 1.
    Eigen::MatrixXf tangent_data = data_rot;
#pragma omp parallel for
    for (int i = 0; i < n; ++i) {
        tangent_data.row(i) *= coeff(i);
        tangent_data(i, d-1) = 1.0f;
    }

    Eigen::MatrixXf m_ed_to_x = rotationMatrixEDtoX(tp);
    tangent_data = tangent_data * m_ed_to_x.transpose();
    return tangent_data;
}

// Compute the angular distance between two unit vectors.
float angularDist(const Eigen::VectorXf &x, const Eigen::VectorXf &y) {
    float dot = x.dot(y);
    dot = std::min(1.0f, std::max(-1.0f, dot));
    return std::acos(dot);
}

// Calculate the quadratic loss between each data point and the centroid.
float calcDistQuadraticLoss(const Eigen::MatrixXf &data, const Eigen::VectorXf &centroid) {
    int n = data.rows();
    float loss = 0.0f;
    for (int i = 0; i < n; ++i) {
        loss += std::pow(angularDist(data.row(i), centroid), 2);
    }
    return 0.5f * loss;
}

// ------------------------------------------------------------------------
// Logarithm Map on the unit hypersphere for a single point.
// Given base point q (unit vector) and a point p on the sphere,
// compute the tangent vector at q pointing toward p.
Eigen::VectorXf log_map(const Eigen::VectorXf &q, const Eigen::VectorXf &p, double tol=1e-10) {
    // Compute the dot product and clamp it between -1 and 1 for numerical stability.
    double dot = q.dot(p);
    dot = std::max(-1.0, std::min(1.0, dot));

    // Compute the geodesic distance (angle) between q and p.
    double theta = std::acos(dot);

    // For very small angles, return the zero vector.
    if (std::fabs(theta) < tol)
        return Eigen::VectorXf::Zero(q.size());

    // Compute the scaling factor
    double factor = theta / std::sin(theta);

    // Compute and return the tangent vector at q.
    return factor * (p - std::cos(theta) * q);
}

// Overload of log_map for multiple points provided as rows of a matrix.
Eigen::MatrixXf log_map(const Eigen::VectorXf &q, const Eigen::MatrixXf &P, double tol=1e-10) {
    int nPoints = P.rows();
    int dim = P.cols();
    Eigen::MatrixXf V(nPoints, dim);

#pragma omp parallel for
    for (int i = 0; i < nPoints; ++i) {
        // Extract i-th point as a vector.
        Eigen::VectorXf p = P.row(i).transpose();
        V.row(i) = log_map(q, p, tol).transpose();
    }
    return V;
}

// ------------------------------------------------------------------------
// Exponential Map on the unit hypersphere for a single tangent vector.
// Given base point q (unit vector) and a tangent vector v at q,
// map it back onto the sphere.
Eigen::VectorXf exp_map(const Eigen::VectorXf &q, const Eigen::VectorXf &v, double tol=1e-10) {
    double norm_v = v.norm();
    
    // If the tangent vector is nearly zero, return q.
    if (norm_v < tol)
        return q;
    
    return std::cos(norm_v) * q + std::sin(norm_v) * (v / norm_v);
}

// Overload of exp_map for multiple tangent vectors provided as rows of a matrix.
Eigen::MatrixXf exp_map(const Eigen::VectorXf &q, const Eigen::MatrixXf &V, double tol=1e-10) {
    int nPoints = V.rows();
    int dim = V.cols();
    Eigen::MatrixXf P(nPoints, dim);

#pragma omp parallel for
    for (int i = 0; i < nPoints; ++i) {
        Eigen::VectorXf v = V.row(i).transpose();
        P.row(i) = exp_map(q, v, tol).transpose();
    }
    return P;
}

// Compute the spherical centroid of the data iteratively.
Eigen::VectorXf calcSphereCentroid(Eigen::MatrixXf data, int n_iter = 10, float eps = 1e-6f, bool verbose = false) {
    int n = data.rows();
    int d = data.cols();

    // Normalize data points to lie on the unit sphere.
#pragma omp parallel for
    for (int i = 0; i < n; ++i) {
        float norm = data.row(i).norm();
        if (norm > TOL)
            data.row(i) /= norm;
    }
    // data = data.array().rowwise() / data.rowwise().norm().array();

    // Initialize centroid as the mean of the data points, then normalize.
    Eigen::VectorXf centroid = data.colwise().mean();
    centroid.normalize();

    if (verbose) {
        float loss = calcDistQuadraticLoss(data, centroid);
        std::cout << "Initial centroid: " << centroid.transpose() << "\n"
                  << "loss: " << loss << std::endl;
    }

    for (int i = 0; i < n_iter; ++i) {
        // Eigen::MatrixXf data_on_plane = sphereToTangentHyperplaneInverseExpMap(data, centroid);.
        // Eigen::VectorXf centroid_on_plane = data_on_plane.colwise().mean();
        // Eigen::VectorXf diff = centroid_on_plane - centroid;

        // Wrap centroid_on_plane (a 1xd row vector) into a 1-row matrix.
        // Eigen::MatrixXf cp_mat(1, d);
        // cp_mat.row(0) = centroid_on_plane.transpose();
        // centroid = tangentHyperplaneToSphereExponentialMap(cp_mat, centroid).row(0).transpose();

        // float norm_of_diff = diff.norm();

        Eigen::MatrixXf data_on_plane = log_map(centroid, data); // tangent point is at the origin
        Eigen::VectorXf centroid_on_plane = data_on_plane.colwise().mean();
        centroid = exp_map(centroid, centroid_on_plane);
        float norm_of_diff = centroid_on_plane.norm(); // since tangent point (last centroid) is at the origin

        if (verbose) {
            float loss = calcDistQuadraticLoss(data, centroid);
            std::cout << "===Iter " << i << "\n"
                    //   << "c_on_plane: " << centroid_on_plane.transpose() << "\n"
                    //   << "c: " << centroid.transpose() << "\n"
                      << "norm_of_diff:" << norm_of_diff << "\n"
                      << "loss:" << loss << std::endl;
        }
        if (norm_of_diff < eps)
            break;
    }
    
    if (verbose) {
        std::cout << "Final centroid: " << centroid.transpose() << std::endl;
    }

    return centroid;
}

#endif // SPHERECENTROID_H

// int main() {
//     // Example usage:
//     // Suppose we have 5 points in 3D (each row is a point)
//     // Eigen::MatrixXf data(5, 3);
//     // data << 0.0f, 0.0f, 1.0f,
//     //         0.1f, 0.0f, 0.995f,
//     //         -0.1f, 0.05f, 0.99f,
//     //         0.05f, -0.1f, 0.995f,
//     //         -0.05f, -0.05f, 0.997f;
    
//     // final should be 0.659346  0.75184
//     // Eigen::MatrixXf data(4, 2);
//     // data << 0.0f, 1.0f,
//     //         1.0f, 0.0f, 
//     //         sqrt(2.0f) / 2.0f, sqrt(2.0f) / 2.0f,
//     //         1.0f / 2.0f, sqrt(3.0f) / 2.0f;

//     Eigen::MatrixXf data(8, 3);
//     data << 0.67388316f, -0.800516f,   -0.62422205f,
//      0.41960099f,  0.48394943f, -2.01119974f,
//      0.13259279f, -1.19713667f, -0.66089308f,
//     -1.84669367f, -2.39599538f,  0.52988928f,
//     -0.63532810f, -0.13938167f,  0.61042593f,
//      0.97274296f, -1.04815435f, -0.13111393f,
//     -0.03713117f,  0.68440949f, -0.81099645f,
//      1.06857131f,  0.45117844f, -0.81628281f;
    
//     // Ensure data rows are normalized to the sphere.
//     for (int i = 0; i < data.rows(); ++i)
//         data.row(i).normalize();

//     Eigen::VectorXf centroid = calcSphereCentroid(data, 20, 1e-6f, true);
//     std::cout << "Final centroid: " << centroid.transpose() << std::endl;
    
//     return 0;
// }

