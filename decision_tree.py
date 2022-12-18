# -*- coding: utf-8 -*-
"""
Created on Thu Dec 15 15:01:45 2022

@author: user

"""


import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
data_red = pd.read_csv("winequality-red.csv", sep=";")
data_red.head()

print("There are {} rows and {} columns".format(data_red.shape[0], data_red.shape[1]))
data_red.isnull().sum()
plt.hist(data_red["quality"])
plt.show()
data_red["quality"].groupby(data_red["quality"]).count()
plt.figure(figsize=(10,8))
sns.heatmap(data_red.corr(), annot=True, cmap="PuOr")
plt.show()
data_red["good_quality"] = [0 if i<7 else 1 for i in data_red["quality"]]
data_red.head()
data_red["good_quality"].groupby(data_red["good_quality"]).count()
y = data_red["good_quality"]
X = data_red.drop(["good_quality", "quality"], axis=1)
from sklearn.preprocessing import MinMaxScaler
scaler = MinMaxScaler()
X_scaled = scaler.fit_transform(X)
from sklearn.model_selection import train_test_split
X_train, X_test, y_train, y_test = train_test_split(X_scaled, y, test_size=0.25, random_state=0)
print("Number of samples in training set:", X_train.shape[0])
print("Number of samples in testing set:", X_test.shape[0])
from sklearn.tree import DecisionTreeClassifier
model = DecisionTreeClassifier(random_state=0)
model.fit(X_train, y_train)
y_pred = model.predict(X_test)
from sklearn.metrics import accuracy_score
score = accuracy_score(y_pred, y_test)
print("Accuracy", score)
results_series = {"actual":y_test, "predicted":y_pred}
results = pd.DataFrame(results_series)
print("*** First 5 rows of results ***")
results.head()
s = {'col1':X.columns, 'col2':model.feature_importances_}
df = pd.DataFrame(s)
df_sorted = df.sort_values('col2')
plt.barh(df_sorted["col1"], df_sorted["col2"])
plt.show()