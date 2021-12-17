#!/usr/bin/env python
# coding: utf-8

# In[1]:


import numpy as np


# In[2]:


class Apriori:

    def __init__(self, min_support, min_confidence):
        self.min_support = min_support #最小支持度
        self.min_confidence = min_confidence # 最小置信度

    def count(self, filename='./apriori_data.csv'):
        self.total = 0 
        items = {}
        with open(filename) as f:
            for l in f:
                self.total += 1
                for i in l.strip().split(','):
                    if i in items:
                        items[i] += 1.
                    else:
                        items[i] = 1.
        self.items = {i:j/self.total for i,j in items.items() if j/self.total > self.min_support}
        self.item2id = {j:i for i,j in enumerate(self.items)}
        self.D = np.zeros((self.total, len(items)), dtype=bool)
        with open(filename) as f:
            for n,l in enumerate(f):
                for i in l.strip().split(','):
                    if i in self.items:
                        self.D[n, self.item2id[i]] = True
    def find_rules(self, filename='./apriori_data.csv'):
        self.count(filename)
        rules = [{(i,):j for i,j in self.items.items()}] 
        l = 0 

        while rules[-1]: 
            rules.append({})
            keys = sorted(rules[-2].keys()) 
            num = len(rules[-2])
            l += 1
            for i in range(num): 
                for j in range(i+1,num):
                    if keys[i][:l-1] == keys[j][:l-1]:
                        _ = keys[i] + (keys[j][l-1],)
                        _id = [self.item2id[k] for k in _]
                        support = 1. * sum(np.prod(self.D[:, _id], 1)) / self.total 
                        if support > self.min_support:
                            rules[-1][_] = support
        result = {}
        for n,relu in enumerate(rules[1:]): 
            for r,v in relu.items(): 
                for i,_ in enumerate(r): 
                    x = r[:i] + r[i+1:]
                    confidence = v / rules[n][x] 
                    if confidence > self.min_confidence: 
                        result[x+(r[i],)] = (confidence, v)

        return sorted(result.items(), key=lambda x: -x[1][0])


# In[3]:


from pprint import pprint
model = Apriori(0.01, 0.7)
pprint(model.find_rules('./apriori_data.csv'))


# In[ ]:




