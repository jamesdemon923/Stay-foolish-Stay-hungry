#!/usr/bin/env python
# coding: utf-8

# In[1]:


import pandas as pd
import numpy as np
from rdkit.Chem import Draw
from collections import defaultdict
import os
import pickle
import sys
import networkx as nx
from rdkit import Chem
import matplotlib.pyplot as plt

#定义一些函数用于获取分子片段池和提取分子特征
def create_atoms(mol):
    """Create a list of atom (e.g., hydrogen and oxygen) IDs
    considering the aromaticity."""
    atoms = [a.GetSymbol() for a in mol.GetAtoms()]#取出一个分子中的所有原子，不区分重复，不区分是否存在芳香性
    for a in mol.GetAromaticAtoms():
        i = a.GetIdx()
        atoms[i] = (atoms[i], 'aromatic')#这里通过索引把atoms中所有芳香原子特殊标注出来
    atoms = [atom_dict[a] for a in atoms]#atom_dict[a]很强大，如a在atom_dict返回value值，如不在将a与len(atom_dict)形成的k-v对添加到atom_dict并返回value值
    return np.array(atoms)#这里返回的是每个原子在atom_dict中对应的value

def create_ijbonddict(mol):
    """Create a dictionary, which each key is a node ID
    and each value is the tuples of its neighboring node
    and bond (e.g., single and double) IDs."""
    i_jbond_dict = defaultdict(lambda: [])
    for b in mol.GetBonds():#对分子中的每一个化学键进行分析
        i, j = b.GetBeginAtomIdx(), b.GetEndAtomIdx()#找出每一个键的起止原子
        bond = bond_dict[str(b.GetBondType())]#记录键的类型（单，双，三，芳）至bond_dict，并返回对应的value值
        i_jbond_dict[i].append((j, bond))
        i_jbond_dict[j].append((i, bond))#分别以ij为起始原子（中心原子），记录他们与哪个原子（原子在smiles中的index）形成了什么键（bond_dict中对应value）
    return i_jbond_dict#返回的是每个原子（以smiles中index表示）的成键情况字典

def extract_fingerprints(atoms, i_jbond_dict, radius):
    """Extract the r-radius subgraphs (i.e., fingerprints)
    from a molecular graph using Weisfeiler-Lehman algorithm."""

    if (len(atoms) == 1) or (radius == 0):
        fingerprints = [fingerprint_dict[a] for a in atoms]
    else:
        nodes = atoms
        i_jedge_dict = i_jbond_dict
        for _ in range(radius):

            """Update each node ID considering its neighboring nodes and edges
            (i.e., r-radius subgraphs or fingerprints)."""
            fingerprints = []
            for i, j_edge in i_jedge_dict.items():
                neighbors = [(nodes[j], edge) for j, edge in j_edge]
                fingerprint = (nodes[i], tuple(sorted(neighbors)))
                fingerprints.append(fingerprint_dict[fingerprint])
            nodes = fingerprints

            """Also update each edge ID considering two nodes
            on its both sides."""
            _i_jedge_dict = defaultdict(lambda: [])
            for i, j_edge in i_jedge_dict.items():
                for j, edge in j_edge:
                    both_side = tuple(sorted((nodes[i], nodes[j])))
                    edge = edge_dict[(both_side, edge)]
                    _i_jedge_dict[i].append((j, edge))
            i_jedge_dict = _i_jedge_dict#统计了片段类型，主要反映中心原子（atom_dict中index）与相连原子（atom_dict中index）形成什么键（bond_dict中index）

    return np.array(fingerprints)#这里返回的指纹是按smiles的index排列的fingerprint_dict中对应片段的value

def create_mol_graph(mol):
    """
    create a molecular graph with networkx
    :param mol:
    :return:
    """
    i_jbond = []
    mol_graph = nx.Graph()
    for bond in mol.GetBonds():
        i,j  = bond.GetBeginAtomIdx(), bond.GetEndAtomIdx()
        i_jbond.append((i,j))
        mol_graph.add_edge(i,j)
    return mol_graph#将分子转化为图，返回分子图

def create_bfs_graph(graph):
    """
    Traversing Graphs with Boarding First searching method
    """
    bfs_graph = nx.bfs_tree(graph,source=0)#把smiles的index按照bfs搜索路径进行排序
    bfs_nodes = list(bfs_graph)
    return bfs_nodes#返回的是bfs顺序的smiles的index

def new_sequence_fingerprint(nodes_sequence,fingerprint):
    """
    Generating new fingerprint
    """
    new_sequence_fingerprint = []
    for node in nodes_sequence:
        new_sequence_fingerprint.append(fingerprint[node])
    new_sequence_fingerprint = np.array(new_sequence_fingerprint)
    return new_sequence_fingerprint#按bfs顺序在fingerprint中分别取出对应的片段（fingerprint_dic的value）


# In[ ]:


from collections import defaultdict
from rdkit import Chem
"""开始处理数据，这里的目标有两个：
    1.得到一个字典结构，其中每一种片段key能够有一个对应的值value——fingerprint_dict(用于后续调用nn.embedding)
    2.得到每一个分子中所有片段按bfs排序的结果——fp_list,及对应的pce值——pce_list"""
f = open("F:/Jupyter Notebook/materials genes/data/moldata.txt","r")
cal_data = f.read()
f.close()
cal_data = cal_data.strip().split('\n')#strip()在字符串的首尾删除()包含的字符,split()按()中的字符进行切分,最终data为list形式

cal_fp_list, cal_pce_list = [], []
atom_dict = defaultdict(lambda: len(atom_dict))
bond_dict = defaultdict(lambda: len(bond_dict))
fingerprint_dict = defaultdict(lambda: len(fingerprint_dict))
edge_dict = defaultdict(lambda: len(edge_dict))

for i, mol in enumerate(cal_data):
    smiles, pce = mol.strip().split(), mol.strip().split()
    smiles = Chem.MolFromSmiles(smiles)
    atoms = create_atoms(smiles)
    i_jbond_dict = create_ijbonddict(smiles)
    fingerprint = extract_fingerprints(atoms,i_jbond_dict,1)
    graph = create_mol_graph(smiles)
    atom_sequence = create_bfs_graph(graph)#bfs顺序的smiles的index
    new_fingerprint = new_sequence_fingerprint(atom_sequence, fingerprint)
    cal_fp_list.append(new_fingerprint)
    cal_pce_list.append([float(pce)])
    
    print("{}/{}".format(i+1, len(cal_data)))
print(atom_dict)

#训练前的数据准备，固定每个分子的片段长度
fragment_num = len(fingerprint_dict)#片段种类数
# print("碎片种类数:{}".format(fragment_num))

atom_number = []
for fp in cal_fp_list:
    atom_number.append(len(fp))
mol_len = max(atom_number)
# print("分子含片段数:({},{})".format(min(atom_number),mol_len))

#对pce值进行标准化处理
cal_pce_list = np.array(cal_pce_list)
mean, std = np.mean(cal_pce_list), np.std(cal_pce_list)
cal_pce_list = np.array((cal_pce_list - mean) / std)
cal_pce_list = cal_pce_list.tolist()

# 补齐分子，使其长度一致
cal_nfp_list = []
for fp in cal_fp_list:
    if len(fp) < mol_len + 1:
        nfp = np.append(fp, (mol_len + 1 - len(fp)) * ([fragment_num + 1]))
        cal_nfp_list.append(nfp)


# In[ ]:


from sklearn.metrics import r2_score
from sklearn.metrics import mean_squared_error
import torch
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim
import torch.utils.data as Data
from torch.autograd import Variable


class LSTM(nn.Module):
    def __init__(self):
        super(LSTM, self).__init__()
        self.embedding = nn.Embedding(fragment_num+2, embedding_dim, padding_idx=fragment_num+1)
        self.lstm = nn.LSTM(input_size=embedding_dim, hidden_size=hidden_dim, num_layers=3, batch_first=True, bidirectional=True, dropout=0.1)
        self.dropout = nn.Dropout(0.5)
        self.output = nn.Linear(mol_len*hidden_dim*2,1)
        
    def forward(self, nfp_list):
        embedding_fp = self.embedding(nfp_list)
        #[batch, mol_len, embedding_dim]
        out, (hidden, cell) = self.lstm(embedding_fp)
        #output[batch, mol_len, hidden_dim*2], hidden,cell[batch, num_layer*2, hidden_dim]
        output = out.reshape(len(batch_x), mol_len*hidden_dim*2)
        pre_pce = self.output(output)
        #[batch,1]
        return pre_pce


# In[ ]:


#训练网络
device = torch.device('cuda')

mol_len = 99
embedding_dim = 64
hidden_dim = 128
batch = 32
iteration = 100
# da_model = get_da_model().to(device)
model = LSTM().to(device)
loss_function = nn.MSELoss()
optimizer = torch.optim.Adam(model.parameters(), lr=0.001)

#划分训练集与测试集
from sklearn.model_selection import train_test_split
train_x,test_x, train_y, test_y = train_test_split(cal_nfp_list,
                                                   cal_pce_list,
                                                   test_size = 0.2,
                                                   random_state = 1234)

train_dataset = Data.TensorDataset(torch.tensor(train_x, dtype=torch.long), torch.tensor(train_y, dtype=torch.float))
train_loader = Data.DataLoader(
    dataset=train_dataset,  # torch TensorDataset format
    batch_size=batch,  # mini batch size
    shuffle=True,  #  
    num_workers = 8 # 多线程读数据
)

test_dataset = Data.TensorDataset(torch.tensor(test_x, dtype=torch.long), torch.tensor(test_y, dtype=torch.float))
test_loader = Data.DataLoader(
    dataset=test_dataset,  # torch TensorDataset format
    batch_size=batch,  # mini batch size
    shuffle=True,  #  
    num_workers = 8 # 多线程读数据
)

#数据读取完毕，神经网络开始构建
for epoch in range(1, iteration):
    train_exp = []
    train_pre = []
    test_exp = []
    test_pre = []
    for step, data in enumerate(train_loader):
        batch_x, batch_y = data
        batch_x = batch_x.to(device)
        batch_y = batch_y.to(device)
        model.zero_grad()
        pce_pred = model(batch_x)
        loss = loss_function(pce_pred,batch_y)
        loss.backward()
        optimizer.step()
        train_exp.append(batch_y.to('cpu').data.numpy())
        train_pre.append(pce_pred.to('cpu').data.numpy())

    train_exp = np.vstack(train_exp)
    train_pre = np.vstack(train_pre)
    train_mse = mean_squared_error(train_exp,train_pre)
    
    with torch.no_grad():
        for step, data in enumerate(test_loader):
            batch_x, batch_y = data
            batch_x = batch_x.to(device)
            batch_y = batch_y.to(device)
            pce_pred = model(batch_x)
            test_exp.append(batch_y.to('cpu').data.numpy())
            test_pre.append(pce_pred.to('cpu').data.numpy())
    test_exp = np.vstack(test_exp)
    test_pre = np.vstack(test_pre)
    test_mse = mean_squared_error(test_exp,test_pre)
    r2 = r2_score(test_exp,test_pre)
    print('epoch = {},train_mse = {},test_mse = {},r2 = {}'.format(epoch, train_mse, test_mse, r2))

