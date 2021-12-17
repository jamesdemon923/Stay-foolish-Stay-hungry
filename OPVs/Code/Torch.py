"""
Author: Kevin Wu
Date: 2019/11/23

"""
import rdkit
import mordred
import numpy as np
from rdkit import Chem
from rdkit.Chem import AllChem
import torch.nn as nn
import torch
import torch.nn.functional as F
import torch.optim as optim


def getdata(file_path):
    with open(file_path) as f:
        data = f.readlines()
    smiles = [data[i].split('')[0] for i in range(len(data))]
    targets = [data[i].split("")[1] for i in range(len(data))]
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




class Fpnetwork(nn.Module):
    def __init__(self,input_units,hidden_units):
        super(Fpnetwork, self).__init__()
        self.hidden_layers = nn.Linear(input_units, hidden_units)
        self.activation = nn.ReLU()
        self.out_layer = nn.Linear(hidden_units,1)

    def forward(self, input):
        hidden = self.hidden_layers(input)
        out = self.out_layer(hidden)
        return out

class Train(object):
    def __init__(self,model):
        self.model = model

    def train(self,dataset):
        loss_tatal = 0
        for i in range(0,len(dataset),batch):
            np.random.shuffle(dataset)
            data_batch = dataset[i: i+batch]
            inputs, targets = data_batch
            predictions = self.model(inputs)
            loss = F.mse_loss(predictions,targets)
            optimer = optim.Adam(params=self.model.parameters())
            optimer.zero_grad()
            loss.backward()
            optimer.step()
            loss_tatal += loss
            return loss_tatal

if __name__ == '__main__':
    batch = 32
    ecpoch =100
    path = 'TrainData.txt' # 这是你自己的数据
    model = Fpnetwork(512,100)
    train = Train(model)

    smiles, lables = getdata(path)
    fingerprints = get_fingerprints(smiles)
    dataset = list(zip(fingerprints,lables))
    dataset = torch.Tensor(dataset)
    for i in range(ecpoch):
        loss_train = train.train(dataset=dataset)
        print(loss_train)

