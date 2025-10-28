import itertools
import json
import os
from pathlib import Path

import h5py
import numpy as np
import pandas as pd
from tqdm import tqdm


from util import (
    SimilarityMeasure,
    brutesearch,
    convert_vecs2bin,
    read_fbin,
    read_ibin,
    write_fbin,
    write_ibin,
)

DATA_ROOT = Path(__file__).parent.parent / "data"  # Path to the data directory


class Dataset:

    __slots__ = [
        "name",
        "base_path",
        "query_path",
        "ground_path",
        "measure",
        "kwargs",
        "base",
        "query",
        "ground",
    ]

    def __init__(
        self,
        name: str = None,
        base_path: str = None,
        query_path: str = None,
        ground_path: str = None,
        measure: str = None,
        **kwargs,
    ):
        self.name: str = name
        self.base_path: str = base_path
        self.query_path: str = query_path
        self.ground_path: str = ground_path
        self.measure: str = measure
        self.kwargs: dict = kwargs
        self.base, self.query, self.ground = self.load()

    def load(self) -> tuple[np.ndarray, np.ndarray, np.ndarray]:
        base = read_fbin(self.base_path)
        query = read_fbin(self.query_path)
        ground = read_ibin(self.ground_path)
        return base, query, ground

    def describe(self) -> dict:
        return {
            "name": self.name,
            "n_base": self.base.shape[0],
            "n_query": self.query.shape[0],
            "n_dim": self.base.shape[1],
            "n_ground_per_q": (
                self.ground.shape[1] if self.ground is not None else None
            ),
            "measure": self.measure,
            "kwargs": self.kwargs if self.kwargs else None,
        }

    def __repr__(self):
        desc_dict = self.describe()
        return f"{desc_dict['name']}({desc_dict['n_base']}x{desc_dict['n_dim']})"


class Uniform(Dataset):

    def __init__(self, name="Uniform", measure="cosine", on_sphere=True, **kwargs):
        """_summary_

        Args:
            name (str, optional): _description_. Defaults to "Uniform".
            measure (str, optional): _description_. Defaults to "cosine".
            seed (int, optional): _description_. Defaults to 0.
            n_base (int, optional): _description_. Defaults to 10000.
            n_dim (int, optional): _description_. Defaults to 128.
            n_query (int, optional): _description_. Defaults to n_base / 100.
            n_ground_per_q (int, optional): _description_. Defaults to 100.
        """
        self.on_sphere = on_sphere
        super().__init__(name=name, measure=measure, **kwargs)

    def load(self):
        if not self.kwargs:
            self.base_path = os.path.join(DATA_ROOT, "uniform", "base.fbin")
            self.query_path = os.path.join(DATA_ROOT, "uniform", "query.fbin")
            self.ground_path = os.path.join(DATA_ROOT, "uniform", "groundtruth.ibin")
            self.measure = "cosine"
            return super().load()

        measure = self.measure
        seed = self.kwargs.get("seed", 0)
        n_base = self.kwargs["n_base"]
        n_dim = self.kwargs["n_dim"]
        n_query = self.kwargs.get("n_query", int(n_base / 100))
        n_ground_per_q = self.kwargs.get("n_ground_per_q", None)

        rng = np.random.default_rng(seed)
        if self.on_sphere:
            # https://blog.csdn.net/codename_cys/article/details/122799384
            # https://kexue.fm/archives/7076
            base = rng.normal(0, 1, (n_base, n_dim))
            base /= np.linalg.norm(base, axis=1)[:, None]
            query = rng.normal(0, 1, (n_query, n_dim))
            query /= np.linalg.norm(query, axis=1)[:, None]
        else:
            base = rng.uniform(-1, 1, (n_base, n_dim))
            query = rng.uniform(-1, 1, (n_query, n_dim))
        if not (measure is None and n_ground_per_q is None):
            # ground = SimilarityMeasure(measure).calc_sims(query, base)
            # ground = np.argsort(ground, axis=1)[:, -n_ground_per_q:]
            ground = brutesearch(
                query, base, n_neighbor=n_ground_per_q, measure=measure
            )
        else:
            ground = None

        return base, query, ground


class Glove100ED(Dataset):

    def __init__(self, name="Glove100", **kwargs):
        super().__init__(
            name,
            os.path.join(DATA_ROOT, "glove-100", "glove-100_base.fbin"),
            os.path.join(DATA_ROOT, "glove-100", "glove-100_query.fbin"),
            os.path.join(DATA_ROOT, "glove-100", "glove-100_groundtruth.ibin"),
            "euclidean",
            **kwargs,
        )


class Glove25(Dataset):

    def __init__(self, name="Glove25", **kwargs):
        super().__init__(
            name,
            os.path.join(DATA_ROOT, "glove25", "glove25_base.fbin"),
            os.path.join(DATA_ROOT, "glove25", "glove25_query.fbin"),
            os.path.join(DATA_ROOT, "glove25", "glove25_groundtruth.ibin"),
            "cosine",
            **kwargs,
        )


class NYTimes(Dataset):

    def __init__(self, name="NYTimes", **kwargs):
        super().__init__(
            name,
            os.path.join(DATA_ROOT, "nytimes", "nytimes_base.fbin"),
            os.path.join(DATA_ROOT, "nytimes", "nytimes_query.fbin"),
            os.path.join(DATA_ROOT, "nytimes", "nytimes_groundtruth.ibin"),
            "cosine",
            **kwargs,
        )

class Text2Image(Dataset):

    def __init__(self, name="Text2Image", **kwargs):
        super().__init__(
            name,
            os.path.join(DATA_ROOT, "Text-to-Image-1B", "base.1M.fbin"),
            os.path.join(DATA_ROOT, "Text-to-Image-1B", "query.public.100K.fbin"),
            os.path.join(DATA_ROOT, "Text-to-Image-1B", "groundtruth.public.100K.ibin"),
            "dot_product",
            **kwargs,
        )

class Text2Image1M(Dataset):

    def __init__(self, name="Text2Image1M", **kwargs):
        super().__init__(
            name,
            os.path.join(DATA_ROOT, "text2image1m", "text2image1m_base.fbin"),
            os.path.join(DATA_ROOT, "text2image1m", "text2image1m_query.fbin"),
            os.path.join(DATA_ROOT, "text2image1m", "text2image1m_groundtruth.ibin"),
            "cosine",
            **kwargs,
        )


class CocoI2I(Dataset):

    def __init__(self, name="CocoI2I", **kwargs):
        super().__init__(
            name,
            os.path.join(DATA_ROOT, "coco-i2i", "coco-i2i_base.fbin"),
            os.path.join(DATA_ROOT, "coco-i2i", "coco-i2i_query.fbin"),
            os.path.join(DATA_ROOT, "coco-i2i", "coco-i2i_groundtruth.ibin"),
            "cosine",
            **kwargs,
        )


class CocoT2I(Dataset):

    def __init__(self, name="CocoT2I", **kwargs):
        super().__init__(
            name,
            os.path.join(DATA_ROOT, "coco-t2i", "coco-t2i_base.fbin"),
            os.path.join(DATA_ROOT, "coco-t2i", "coco-t2i_query.fbin"),
            os.path.join(DATA_ROOT, "coco-t2i", "coco-t2i_groundtruth.ibin"),
            "cosine",
            **kwargs,
        )


class MiniImageNetT2I(Dataset):

    __slots__ = ["base_label", "query_label"]

    def __init__(self, name="MiniImageNetT2I", **kwargs):
        self.base_label = np.load(
            os.path.join(
                DATA_ROOT, "miniimagenet-t2i", "miniimagenet-t2i_baselabel.npy"
            )
        )
        self.query_label = np.load(
            os.path.join(
                DATA_ROOT, "miniimagenet-t2i", "miniimagenet-t2i_querylabel.npy"
            )
        )
        super().__init__(
            name,
            os.path.join(DATA_ROOT, "miniimagenet-t2i", "miniimagenet-t2i_base.fbin"),
            os.path.join(DATA_ROOT, "miniimagenet-t2i", "miniimagenet-t2i_query.fbin"),
            os.path.join(
                DATA_ROOT, "miniimagenet-t2i", "miniimagenet-t2i_groundtruth.ibin"
            ),
            "cosine",
            **kwargs,
        )


class MiniImageNetI2I(Dataset):

    __slots__ = ["base_label", "query_label"]

    def __init__(self, name="MiniImageNetI2I", **kwargs):
        self.base_label = np.load(
            os.path.join(
                DATA_ROOT, "miniimagenet-i2i", "miniimagenet-i2i_baselabel.npy"
            )
        )
        self.query_label = np.load(
            os.path.join(
                DATA_ROOT, "miniimagenet-i2i", "miniimagenet-i2i_querylabel.npy"
            )
        )
        super().__init__(
            name,
            os.path.join(DATA_ROOT, "miniimagenet-i2i", "miniimagenet-i2i_base.fbin"),
            os.path.join(DATA_ROOT, "miniimagenet-i2i", "miniimagenet-i2i_query.fbin"),
            os.path.join(
                DATA_ROOT, "miniimagenet-i2i", "miniimagenet-i2i_groundtruth.ibin"
            ),
            "cosine",
            **kwargs,
        )


class MiniImageNetT2IED(Dataset):

    __slots__ = ["base_label", "query_label"]

    def __init__(self, name="MiniImageNetT2IED", **kwargs):
        self.base_label = np.load(
            os.path.join(
                DATA_ROOT, "miniimagenet-t2i_ed", "miniimagenet-t2i_ed_baselabel.npy"
            )
        )
        self.query_label = np.load(
            os.path.join(
                DATA_ROOT, "miniimagenet-t2i_ed", "miniimagenet-t2i_ed_querylabel.npy"
            )
        )
        super().__init__(
            name,
            os.path.join(
                DATA_ROOT, "miniimagenet-t2i_ed", "miniimagenet-t2i_ed_base.fbin"
            ),
            os.path.join(
                DATA_ROOT, "miniimagenet-t2i_ed", "miniimagenet-t2i_ed_query.fbin"
            ),
            os.path.join(
                DATA_ROOT, "miniimagenet-t2i_ed", "miniimagenet-t2i_ed_groundtruth.ibin"
            ),
            "euclidean",
            **kwargs,
        )


class MiniImageNetI2IED(Dataset):

    __slots__ = ["base_label", "query_label"]

    def __init__(self, name="MiniImageNetI2IED", **kwargs):
        self.base_label = np.load(
            os.path.join(
                DATA_ROOT, "miniimagenet-i2i_ed", "miniimagenet-i2i_ed_baselabel.npy"
            )
        )
        self.query_label = np.load(
            os.path.join(
                DATA_ROOT, "miniimagenet-i2i_ed", "miniimagenet-i2i_ed_querylabel.npy"
            )
        )
        super().__init__(
            name,
            os.path.join(
                DATA_ROOT, "miniimagenet-i2i_ed", "miniimagenet-i2i_ed_base.fbin"
            ),
            os.path.join(
                DATA_ROOT, "miniimagenet-i2i_ed", "miniimagenet-i2i_ed_query.fbin"
            ),
            os.path.join(
                DATA_ROOT, "miniimagenet-i2i_ed", "miniimagenet-i2i_ed_groundtruth.ibin"
            ),
            "euclidean",
            **kwargs,
        )


class N100000D128Sphere(Dataset):

    def __init__(self, name="n100000_d128_sphere", **kwargs):
        super().__init__(
            name,
            os.path.join(
                DATA_ROOT, "n100000_d128_sphere", "n100000_d128_sphere_base.fbin"
            ),
            os.path.join(
                DATA_ROOT, "n100000_d128_sphere", "n100000_d128_sphere_query.fbin"
            ),
            os.path.join(
                DATA_ROOT, "n100000_d128_sphere", "n100000_d128_sphere_groundtruth.ibin"
            ),
            "cosine",
            **kwargs,
        )


class N100000D128Cube(Dataset):

    def __init__(self, name="n100000_d128_cube", **kwargs):
        super().__init__(
            name,
            os.path.join(DATA_ROOT, "n100000_d128_cube", "n100000_d128_cube_base.fbin"),
            os.path.join(
                DATA_ROOT, "n100000_d128_cube", "n100000_d128_cube_query.fbin"
            ),
            os.path.join(
                DATA_ROOT, "n100000_d128_cube", "n100000_d128_cube_groundtruth.ibin"
            ),
            "cosine",
            **kwargs,
        )


class Glove100(Dataset):

    def __init__(self, name="Glove100", **kwargs):
        super().__init__(
            name,
            os.path.join(DATA_ROOT, "glove100", "glove100_base.fbin"),
            os.path.join(DATA_ROOT, "glove100", "glove100_query.fbin"),
            os.path.join(DATA_ROOT, "glove100", "glove100_groundtruth.ibin"),
            "cosine",
            **kwargs,
        )


DATASETS_CLS = [
    # Uniform,
    Glove100ED,
    Glove25,
    Glove100,
    NYTimes,
    Text2Image1M,
    CocoI2I,
    CocoT2I,
    MiniImageNetI2I,
    MiniImageNetT2I,
    N100000D128Sphere,
    N100000D128Cube,
]


def desc_all():

    progress_bar = tqdm(total=len(DATASETS_CLS))
    descs = []
    for cls in DATASETS_CLS:
        dataset: Dataset = cls()
        descs.append(dataset.describe())
        progress_bar.set_description(dataset.name)
        progress_bar.update(1)

    progress_bar.close()

    df = pd.DataFrame(descs)
    df.sort_values(by=["measure", "n_base", "n_query"], inplace=True)
    df.to_csv(os.path.join(DATA_ROOT, "dataset_desc.csv"), index=False)
    print(df)


def convert2cosine():
    """Convert non-cosine-based dataset to cosine-similarity-based data"""

    for cls in [MiniImageNetI2IED, MiniImageNetT2IED, Text2Image]:
        ds: Dataset = cls()
        if ds.measure == "cosine":
            continue
        new_dir_name = ds.name.lower() + "_cs"
        new_dir = os.path.join(DATA_ROOT, new_dir_name)
        if not os.path.exists(new_dir):
            os.makedirs(new_dir)
        write_fbin(os.path.join(new_dir, f"{new_dir_name}_base.fbin"), ds.base)
        write_fbin(os.path.join(new_dir, f"{new_dir_name}_query.fbin"), ds.query)
        ground = brutesearch(
            ds.query, ds.base, n_neighbor=ds.ground.shape[1], measure="cosine"
        )
        write_ibin(os.path.join(new_dir, f"{new_dir_name}_groundtruth.ibin"), ground)
        print(f"Converted {ds.name} to cosine similarity")


def hdf5_to_bin():
    """Convert hdf5 dataset to binary format"""
    filepaths = [
        r"coco-i2i\coco-i2i-512-angular.hdf5",
        r"coco-t2i\coco-t2i-512-angular.hdf5",
        r"glove25\glove-25-angular.hdf5",
        r"glove100\glove-100-angular.hdf5",
        r"nytimes\nytimes-256-angular.hdf5",
    ]
    filespaths = [os.path.join(DATA_ROOT, fp) for fp in filepaths]

    for fp in filespaths:
        dir_path = os.path.dirname(fp)
        ds_name = os.path.basename(dir_path)
        with h5py.File(fp, "r") as f:
            base = np.array(f["train"], dtype=np.float32)
            query = np.array(f["test"], dtype=np.float32)
            ground = np.array(f["neighbors"], dtype=np.int32)
            # dist = np.array(f["distances"], dtype=np.float32)
            # write_fbin(os.path.join(dir_path, f"{ds_name}_base.fbin"), base)
            # write_fbin(os.path.join(dir_path, f"{ds_name}_query.fbin"), query)
            # write_ibin(os.path.join(dir_path, f"{ds_name}_groundtruth.ibin"), ground)

            tmpd = dict(f.attrs.items())
            for k, v in tmpd.items():
                if isinstance(v, (np.int64, np.int32)):
                    tmpd[k] = int(v)
                elif isinstance(v, (np.float64, np.float32)):
                    tmpd[k] = float(v)
            tmpd.update(
                {
                    "n_base": base.shape[0],
                    "n_query": query.shape[0],
                    "n_dim": base.shape[1],
                    "n_ground_per_q": ground.shape[1],
                    "measure": "cosine",
                }
            )
            with open(
                os.path.join(dir_path, f"{ds_name}_meta.json"), "w", encoding="utf8"
            ) as jsonf:
                json.dump(tmpd, jsonf)

            print(f"Converted {ds_name} to binary format")


def sample4paramtune(base_num=10000, query_num=100, seed=0):
    """Sample a subset of the dataset for parameter tuning"""
    for cls in tqdm(
        [
            Glove25,
            Glove100,
            NYTimes,
            Text2Image1M,
            CocoI2I,
            CocoT2I,
            MiniImageNetI2I,
            MiniImageNetT2I,
        ]
    ):
        rng = np.random.default_rng(seed)
        ds: Dataset = cls()
        base = ds.base[rng.choice(ds.base.shape[0], base_num, replace=False)]
        query = ds.query[rng.choice(ds.query.shape[0], query_num, replace=False)]

        # e.g.
        # "D:/phd/VDB/data/nytimes/nytimes_base.fbin" -> "D:/phd/VDB/data/sample/nytimes/nytimes_base.fbin"
        raw_base_path = Path(ds.base_path)
        raw_dir_name = raw_base_path.parent.name
        new_dir = raw_base_path.parent.parent / "sample" / raw_dir_name
        if os.path.exists(new_dir):
            print(f"{new_dir} already exists. Skip sampling")
            continue
        os.makedirs(new_dir)
        ground = brutesearch(
            query, base, n_neighbor=ds.ground.shape[1], measure=ds.measure
        )

        write_fbin(os.path.join(new_dir, f"{raw_dir_name}_base.fbin"), base)
        write_fbin(os.path.join(new_dir, f"{raw_dir_name}_query.fbin"), query)
        write_ibin(os.path.join(new_dir, f"{raw_dir_name}_groundtruth.ibin"), ground)


# def gen_miniimagenet_ds():
#     from analy_downstream import get_embeddings, read_miniimagenet
#     emb_model = "clip-ViT-L-14"
#     use_emb_cache = True
#     use_searchresult_cache = True
#     train_images, train_labels, test_images, test_labels, d_label_text = (
#         read_miniimagenet()
#     )

#     test_labeltext = np.array([d_label_text[label] for label in test_labels])
#     base_img, query_img, query_text = get_embeddings(
#         emb_model, train_images, test_images, test_labeltext, use_cache=use_emb_cache
#     )

#     _, q_txt_unique_idx = np.unique(query_text, axis=0, return_index=True)
#     q_txt_unique_idx.sort()
#     query_text = query_text[q_txt_unique_idx]

#     query_img_label = test_labels
#     query_text_label = test_labels[q_txt_unique_idx]

#     for (query_type, query, query_label), sim_measure in itertools.product(
#         (("i2i", query_img, query_img_label), ("t2i", query_text, query_text_label)),
#         ("cosine", "euclidean"),
#     ):
#         name_suffix = query_type
#         name_suffix += "" if sim_measure == "cosine" else "_ed"
#         ground = brutesearch(query, base_img, n_neighbor=100, measure=sim_measure)

#         dir_name = f"miniimagenet-{name_suffix}"
#         os.makedirs(os.path.join(DATA_ROOT, dir_name), exist_ok=True)

#         write_fbin(os.path.join(DATA_ROOT, dir_name, f"{dir_name}_base.fbin"), base_img)
#         write_fbin(os.path.join(DATA_ROOT, dir_name, f"{dir_name}_query.fbin"), query)
#         write_ibin(
#             os.path.join(DATA_ROOT, dir_name, f"{dir_name}_groundtruth.ibin"), ground
#         )
#         np.save(
#             os.path.join(DATA_ROOT, dir_name, f"{dir_name}_baselabel"), train_labels
#         )
#         np.save(
#             os.path.join(DATA_ROOT, dir_name, f"{dir_name}_querylabel"), query_label
#         )
#         print(
#             f"Generated {dir_name}. {base_img.shape}, {query.shape}, ({ground.shape})"
#         )


def gen_uniform():
    for on_sphere in (True, False):
        ds = Uniform(
            n_base=100000,
            n_dim=128,
            measure="cosine",
            n_query=10000,
            n_ground_per_q=100,
            on_sphere=on_sphere,
            seed=0,
        )
        suffix = "sphere" if on_sphere else "cube"
        name = f"n100000_d128_{suffix}"
        os.makedirs(os.path.join(DATA_ROOT, name), exist_ok=True)
        write_fbin(os.path.join(DATA_ROOT, name, f"{name}_base.fbin"), ds.base)
        write_fbin(os.path.join(DATA_ROOT, name, f"{name}_query.fbin"), ds.query)
        write_ibin(
            os.path.join(DATA_ROOT, name, f"{name}_groundtruth.ibin"),
            ds.ground,
        )
        print("Generated ", name)


if __name__ == "__main__":

    # gen_uniform()

    # desc_all()

    # gen_miniimagenet_ds()

    sample4paramtune()

    # hdf5_to_bin()
    # convert2cosine()

    # test()
