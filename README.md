# Hemi-Sphere Centroids Graph (HSCG)

Efficient Approximate Nearest Neighbor Search in Cosine Similarity. The source code of the SIGMOD 2026 paper `Efficient Approximate Nearest Neighbor Search via Hemi-Sphere Centroids Graph` https://doi.org/10.1145/3769786

## Project Structure

```
analysis/ # python code. data processing.
model/ # the embedding model
data/
  coco-i2i/ # Raw dataset
  ...
  sample/ # sample from raw dataset
include/ # c++ header files
  Eigen/
  SphereCentroid/
  weavess/
src/ # c++ source code. Different components of ANNS algorithms.
test/ # c++ source code. Experiment of ANNS algorihtms on different datasets.
```

## Environment

Linux

### Python

3.12.7

```bash
pip install -r ./requirements.txt
```

### C++

library

- [Boost](https://www.boost.org/)=1.74.0
- [Eigen](https://eigen.tuxfamily.org/index.php?title=Main_Page)=3.4.0

```bash
sudo apt-get update
sudo apt-get install libboost-all-dev
```

Eigen already exists in `include/`

## Step1: data preparation

1. Download the datasets according to the instruction in each subfolder. e.g. `data/coco-i2i/readme.txt`
2. Preprocess the datasets using `analysis/data.py`, including unifying the format of data, getting the ground true nearest neighbors under different similarity, and the generation of synthetic data.
3. Sample the datasets using `analysis/data.py` for hyperparameter tuning and debug.

## Step2: hyperparameter tuning

1. Change the data path to the path of sample dataset in `test/main.cpp`

2. Change the hyperparameters in `include/weavess/exp_data.h`

3. Run the c++ code. 
   ```bash
   mkdir build
   cd build
   cmake ..
   make -j
   ./test/main nsg_lsh_sphere2 coco-i2i build
   ./test/main nsg_lsh_sphere2 coco-i2i search
   ```

## Step3: indexing and searching

1. Change the data path to the path of full dataset in `test/main.cpp`

2. Change the hyperparameters in `include/weavess/exp_data.h`

3. Run the c++ code. 
   ```bash
   mkdir build
   cd build
   cmake ..
   make -j
   ./test/main nsg_lsh_sphere2 coco-i2i build
   ./test/main nsg_lsh_sphere2 coco-i2i search
   ./test/main nsg_lsh_sphere2 coco-i2i info
   ```

## Citation

If you find this code useful in your research, please cite our paper:

```bib
@article{qiu2025efficient,
  title = {Efficient {{Approximate Nearest Neighbor Search}} via {{Hemi-Sphere Centroids Graph}}},
  author = {Qiu, Runwen and Tang, Jing},
  year = {2025},
  month = dec,
  journal = {Proc. ACM Manag. Data},
  volume = {3},
  number = {6},
  pages = {321:1-321:26},
  doi = {10.1145/3769786},
  langid = {english}
}
```

## Acknowledgements

This repository contains code that was inspired by or derived from the following projects:

- [WEAVESS](https://github.com/Lsyhprum/WEAVESS)
- [nsg](https://github.com/ZJULearning/nsg)

