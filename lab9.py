
import numpy as np

mass = np.array([1,1,2,2,2,3,4,4,4,5,6,7,7,7,8,9]) # массив
special, counts = np.unique(mass, return_counts=True) # считаем,сколько раз каждый элемент повторяется в массиве
twice = special[counts > 2] # находим числа, которые встречаются более двух раз
sumtwice = np.sum(twice) #считаем сумму
print(sumtwice)
