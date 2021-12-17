import pandas as pd


def xlsx_to_csv_pd(excel_filepath=''):
    data_xls = pd.read_excel(excel_filepath, sheet_name=None)  # 获取所有表
    path = excel_filepath[0:excel_filepath.rindex('/') + 1]
    count = 1
    for sheet in list(data_xls.keys()):  # 遍历每一张表,转换为csv
        csv_filepath = path + 'data' + str(count) + '.csv'
        data_xls[sheet].to_csv(csv_filepath, encoding='utf-8')
        count += 1


if __name__ == '__main__':
    xlsx_to_csv_pd('data/2000-all_data.xlsx')
