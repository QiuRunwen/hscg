## link1

<https://github.com/learnables/learn2learn/blob/db5cee3795490071282bbdfa81179ef732349196/learn2learn/vision/datasets/mini_imagenet.py#L37C34-L37C34>

```python
if self.mode == 'test':
	google_drive_file_id = '1wpmY-hmiJUUlRBkO9ZDCXAcIpHEFdOhD'
	dropbox_file_link = 'https://www.dropbox.com/s/ye9jeb5tyz0x01b/mini-imagenet-cache-test.pkl?dl=1'
	zenodo_file_link = 'https://zenodo.org/record/7978538/files/mini-imagenet-cache-test.pkl'
elif self.mode == 'train':
	google_drive_file_id = '1I3itTXpXxGV68olxM5roceUMG8itH9Xj'
	dropbox_file_link = 'https://www.dropbox.com/s/9g8c6w345s2ek03/mini-imagenet-cache-train.pkl?dl=1'
	zenodo_file_link = 'https://zenodo.org/record/7978538/files/mini-imagenet-cache-train.pkl'
elif self.mode == 'validation':
	google_drive_file_id = '1KY5e491bkLFqJDp0-UWou3463Mo8AOco'
	dropbox_file_link = 'https://www.dropbox.com/s/ip1b7se3gij3r1b/mini-imagenet-cache-validation.pkl?dl=1'
	zenodo_file_link = 'https://zenodo.org/record/7978538/files/mini-imagenet-cache-validation.pkl'
else:
	raise ValueError('Needs to be train, test or validation')
```
## link2

<https://raw.githubusercontent.com/NVIDIA/DeepLearningExamples/master/PyTorch/Classification/ConvNets/LOC_synset_mapping.json>
