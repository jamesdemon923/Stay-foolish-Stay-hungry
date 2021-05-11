str = input("请输入要查询的作品名称:\n")
release_year_dict = {"Thriller": "1982",
                     "Back in Black": "1980",
                     "The Dark Side of the Moon": "1973",
                     "The Bodyguard": "1992",
                     "Bat Out of Hell": "1977",
                     "Their Greatest Hits (1971-1975)": "1976",
                     "Saturday Night Fever": "1977",
                     "Rumours": "1977"}
years = release_year_dict[str]
print('该作品的年份为:\n'+ years)