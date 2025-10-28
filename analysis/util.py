import csv
import os
import struct
from pathlib import Path

import numpy as np
import scipy.spatial
from tqdm import tqdm


class SimilarityMeasure:
    def __init__(self, measure="cosine"):
        self.measure = measure
        if measure == "cosine":
            self.func_calc_sim = self._calc_cosine
            # self.is_sim_larger_close = True
            self.is_sim_satify_triang_ineq = False
        elif measure == "angular":
            self.func_calc_sim = self._calc_angle
            # self.is_sim_larger_close = False
            self.is_sim_satify_triang_ineq = True

        elif measure == "euclidean":
            self.func_calc_sim = self._calc_euclidean
            # self.is_sim_larger_close = False
            self.is_sim_satify_triang_ineq = True
        elif measure == "dot_product":
            self.func_calc_sim = self._calc_dot_product
            # self.is_sim_larger_close = True
            self.is_sim_satify_triang_ineq = False
        else:
            raise ValueError("Invalid similarity measure")

    def calc_sim(self, vec1: np.ndarray, vec2: np.ndarray) -> float:
        return self.func_calc_sim(vec1, vec2)

    def calc_sims(self, query: np.ndarray, data: np.ndarray) -> np.ndarray:
        """(n1,d), (n2,d)-> (n1,n2)"""

        if self.measure in ["cosine", "angular"]:
            one_minus_cos = scipy.spatial.distance.cdist(query, data, "cosine")
            # when there is a zero vector, the cosine similarity is nan
            # need to fill nan as 0 as it perpendicular to all vectors
            sim_matrix = 1 - one_minus_cos
            isnan = np.isnan(sim_matrix)
            if isnan.any():
                sim_matrix[isnan] = 0
                # check whether zero vector both in query and data
                zeroidx_in_query = np.arange(len(query))[isnan.all(axis=1)]
                zeroidx_in_data = np.arange(len(data))[isnan.all(axis=0)]
                if zeroidx_in_query.size > 0 and zeroidx_in_data.size > 0:
                    sim_matrix[zeroidx_in_query[:, None], zeroidx_in_data] = 1

            if self.measure == "angular":
                sim_matrix = -np.arccos(sim_matrix)
        elif self.measure == "euclidean":
            sim_matrix = -scipy.spatial.distance.cdist(query, data, "minkowski", p=2)
        elif self.measure == "dot_product":
            sim_matrix = scipy.spatial.distance.cdist(query, data, np.dot)
        else:
            raise ValueError("Invalid similarity measure")
        return sim_matrix

    def _calc_cosine(self, vec1: np.ndarray, vec2: np.ndarray) -> float:
        tmpnorm = np.linalg.norm(vec1) * np.linalg.norm(vec2)
        if tmpnorm == 0:
            return 0
        return np.dot(vec1, vec2) / tmpnorm

    def _calc_euclidean(self, vec1: np.ndarray, vec2: np.ndarray) -> float:
        return -np.linalg.norm(vec1 - vec2)

    def _calc_dot_product(self, vec1: np.ndarray, vec2: np.ndarray) -> float:
        return np.dot(vec1, vec2)

    def _calc_angle(self, vec1: np.ndarray, vec2: np.ndarray) -> float:
        return -np.arccos(self._calc_cosine(vec1, vec2))


def read_fbin(filename, start_idx=0, chunk_size=None):
    """Read *.fbin file that contains float32 vectors
    Args:
        :param filename (str): path to *.fbin file
        :param start_idx (int): start reading vectors from this index
        :param chunk_size (int): number of vectors to read.
                                 If None, read all vectors
    Returns:
        Array of float32 vectors (numpy.ndarray)
    """
    with open(filename, "rb") as f:
        nvecs, dim = np.fromfile(f, count=2, dtype=np.int32)
        nvecs = (nvecs - start_idx) if chunk_size is None else chunk_size
        arr = np.fromfile(
            f, count=nvecs * dim, dtype=np.float32, offset=start_idx * 4 * dim
        )
    return arr.reshape(nvecs, dim)


def read_ibin(filename, start_idx=0, chunk_size=None):
    """Read *.ibin file that contains int32 vectors
    Args:
        :param filename (str): path to *.ibin file
        :param start_idx (int): start reading vectors from this index
        :param chunk_size (int): number of vectors to read.
                                 If None, read all vectors
    Returns:
        Array of int32 vectors (numpy.ndarray)
    """
    with open(filename, "rb") as f:
        nvecs, dim = np.fromfile(f, count=2, dtype=np.int32)
        nvecs = (nvecs - start_idx) if chunk_size is None else chunk_size
        arr = np.fromfile(
            f, count=nvecs * dim, dtype=np.int32, offset=start_idx * 4 * dim
        )
    return arr.reshape(nvecs, dim)


def write_fbin(filename, vecs):
    """Write an array of float32 vectors to *.fbin file
    Args:s
        :param filename (str): path to *.fbin file
        :param vecs (numpy.ndarray): array of float32 vectors to write
    """
    assert len(vecs.shape) == 2, "Input array must have 2 dimensions"
    with open(filename, "wb") as f:
        nvecs, dim = vecs.shape
        f.write(struct.pack("<i", nvecs))
        f.write(struct.pack("<i", dim))
        vecs.astype("float32").flatten().tofile(f)


def write_ibin(filename, vecs):
    """Write an array of int32 vectors to *.ibin file
    Args:
        :param filename (str): path to *.ibin file
        :param vecs (numpy.ndarray): array of int32 vectors to write
    """
    assert len(vecs.shape) == 2, "Input array must have 2 dimensions"
    with open(filename, "wb") as f:
        nvecs, dim = vecs.shape
        f.write(struct.pack("<i", nvecs))
        f.write(struct.pack("<i", dim))
        vecs.astype("int32").flatten().tofile(f)


def read_fvecs(filename):
    """Read *.fvecs file that contains float32 vectors
    Args:
        :param filename (str): path to *.fvecs file
    Returns:
        Array of float32 vectors (numpy.ndarray)
    """

    with open(filename, "rb") as f:
        dim = np.fromfile(f, count=1, dtype=np.int32)[0]
        line_size = 4 + dim * 4  # 1 int (4 bytes) + d floats (4 bytes each)

        # Get the total number of vectors
        f.seek(0, 2)  # Move to the end of the file
        total_bytes = f.tell()
        nvecs = total_bytes // line_size

        # Read vectors
        f.seek(0)
        # each line is `n_dim, v1, v2, ..., vn_dim`
        vecs = np.fromfile(f, count=nvecs * (1 + dim), dtype=np.float32)

    return vecs.reshape(nvecs, dim + 1)[:, 1:]


def read_ivecs(filename):
    """Read *.ivecs file that contains int32 vectors
    Args:
        :param filename (str): path to *.ivecs file
    Returns:
        Array of int32 vectors (numpy.ndarray)
    """

    with open(filename, "rb") as f:
        dim = np.fromfile(f, count=1, dtype=np.int32)[0]
        line_size = 4 + dim * 4  # 1 int (4 bytes) + d ints (4 bytes each)

        # Get the total number of vectors
        f.seek(0, 2)  # Move to the end of the file
        total_bytes = f.tell()
        nvecs = total_bytes // line_size

        # Read vectors
        f.seek(0)
        # each line is `n_dim, v1, v2, ..., vn_dim`
        vecs = np.fromfile(f, count=nvecs * (1 + dim), dtype=np.int32)

    return vecs.reshape(nvecs, dim + 1)[:, 1:]


def convert_vecs2bin(dir_name: str):
    """Convert all *.fvecs and *.ivecs files in a directory to *.fbin and *.ibin files.

    They are both binary files that contain float32 and int32 vectors respectively.
    But in *.fvecs: each line is `n_dim, v1, v2, ..., vn_dim`.
    in .fbin: first line is `n_vecs, n_dim` then `n_vecs` lines of `v1, v2, ..., vn_dim`.

    Args:
        dir_name (str): path to the directory that contains *.fvecs and *.ivecs files
    """

    for file_name in os.listdir(dir_name):
        raw_path = os.path.join(dir_name, file_name)
        if file_name.endswith(".fvecs"):
            vecs = read_fvecs(raw_path)
            output_path = os.path.join(dir_name, file_name.replace(".fvecs", ".fbin"))
            write_fbin(output_path, vecs)
        elif file_name.endswith(".ivecs"):
            vecs = read_ivecs(raw_path)
            output_path = os.path.join(dir_name, file_name.replace(".ivecs", ".ibin"))
            write_ibin(output_path, vecs)
        else:
            continue
        print(f"Converted {raw_path} to {output_path}")


def append_dicts_to_csv(file_path: str | Path, data_dicts: list[dict]):
    """Append dicts to csv file. If the file is empty, write header using the keys of data_dicts.
    if the file is not empty, the first line of the file must be the header.
    and the keys of data_dicts must be the same as the header in the file.
    e.g. data_dicts=[{"a": 1, "b": 2}, {"a": 3, "b": 4}] and the header is ["a", "b"]
    """
    if not data_dicts:
        return  # Return if the list is empty

    # Create the file and directory if not exist
    file_path = Path(file_path)
    file_path.parent.mkdir(parents=True, exist_ok=True)
    with open(file_path, "a+", newline="", encoding="utf-8") as csv_file:
        if csv_file.tell() == 0:
            # The file is empty, write header
            fieldnames = data_dicts[0].keys()
            writer = csv.DictWriter(csv_file, fieldnames=fieldnames)
            writer.writeheader()
        else:
            # The file is not empty, get the header first and then write
            csv_file.seek(0)  # Move the cursor to the start of the file
            fieldnames = csv.DictReader(csv_file).fieldnames  # Read the header
            csv_file.seek(0, 2)  # Move the cursor to the end of the file
            writer = csv.DictWriter(csv_file, fieldnames=fieldnames)
        writer.writerows(data_dicts)


def brutesearch(query: np.ndarray, data: np.ndarray, n_neighbor: int, measure="cosine"):
    """Brute force search for KNN"""
    assert (
        len(query.shape) == 2
        and len(data.shape) == 2
        and query.shape[1] == data.shape[1]
    )

    def _search(query, data, n_neighbor, measure):
        sim_measure = SimilarityMeasure(measure)
        sim_matrix = sim_measure.calc_sims(query, data)
        ground = np.argsort(sim_matrix, axis=1)[:, ::-1][:, :n_neighbor].astype(np.int32)
        return ground

    if query.shape[0] * data.shape[0] <= 1e9:
        return _search(query, data, n_neighbor, measure)

    # Large query and data, split query into chunks
    n_chunks = query.shape[0] // 64 + 1
    chunks = np.array_split(query, n_chunks)
    ground = [_search(chunk, data, n_neighbor, measure) for chunk in tqdm(chunks)]

    return np.vstack(ground)
