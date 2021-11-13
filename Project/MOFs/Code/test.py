if __name__ == '__main__':
    import pandas as pd
    file = pd.read_csv('data/data'+'3.csv')
    print(file['Henry Coef of propene'])
