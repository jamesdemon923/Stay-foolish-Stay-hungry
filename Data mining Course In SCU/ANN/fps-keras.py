"""
Author: Kevin Wu
Date: 2019/11/27
"""
import numpy as np
import mordred
from rdkit import Chem
from rdkit.Chem import AllChem
import keras
from keras.layers import *
from keras.optimizers import *
from keras.models import *
from keras.utils import *
from keras.losses import *


def getdata(file_path):
    with open(file_path) as f:
        data = f.readlines()
    smiles = [data[i].split('')[0] for i in range(len(data))]
    targets = [data[i].split("")[1] for i in range(len(data))]
    targets = np.array(targets)
    return smiles, targets

def get_fingerprints(smiles,type = 'Morgan'):
    fingerprints = []
    calculator = mordred.Calculator()
    if type == 'Morgan':
        for smile in smiles:
            mol = Chem.MolFromSmiles(smile)
            morgan_fp = AllChem.GetMorganFingerprintAsBitVect(mol,2,1024)
            fingerprints.append(morgan_fp)
        fingerprints = np.array(fingerprints)

    if type == 'Mordred':
        for smile in smiles:
            mol = Chem.MolFromSmiles(smile)
            mordred_fp = calculator(mol)
            fingerprints.append(mordred_fp)
        fingerprints = np.array(fingerprints)
    return  fingerprints


class ANN(object):
    # construct the networks
    def __init__(self):
        self.hidden_layers = hidden_layers
        self.hidden_out_units = hidden_out_units
        self.model = Sequential()

    def model_construct(self):
        for i in range(self.hidden_layers):
            self.model.add(Dense(self.hidden_out_units[i],activation='relu'))
        self.model.add(Dense(1))
        self.model.compile(Adam(),loss='mse')
        return self.model



if __name__ == '__main__':
    path = 'smiles.txt' # 这是你自己的数据
    hidden_layers = 3
    hidden_out_units = [100,100,100]
    batch_size = 128
    epoch = 100
    model = ANN()
    model = model.model_construct()
    smiles, lables = getdata(path)
    fingerprints = get_fingerprints(smiles)
    model.fit(fingerprints,lables,batch_size=batch_size,epoch =100,validation_split=0.2)

