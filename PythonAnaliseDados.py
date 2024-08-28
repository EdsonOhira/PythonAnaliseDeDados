import numpy as np
import matplotlib.pyplot as plt
from sklearn.linear_model import LinearRegression

# Valores de x e y
x = np.array([202.8, 202.4, 201.8, 201.7, 201.7, 201.1, 201, 200.9, 200.5, 200.4, 200.4, 200.3, 200])
y = np.array([13, 15, 13, 18, 18, 14, 15, 15, 15, 14, 12, 15, 16])

# Criando um gráfico de dispersão
plt.scatter(x, y, label='Dados')

# Ajustando uma regressão linear aos dados
model = LinearRegression()
x = x.reshape(-1, 1)  # Redimensionar x para funcionar com Scikit-Learn
model.fit(x, y)
y_pred = model.predict(x)

# Obtendo os coeficientes da regressão linear
coeficiente_angular = model.coef_[0]
coeficiente_linear = model.intercept_

# Imprimindo os coeficientes
print(f"Coeficiente Angular: {coeficiente_angular}")
print(f"Coeficiente Linear: {coeficiente_linear}")

# Criando um gráfico da regressão linear
plt.plot(x, y_pred, color='red', linewidth=2, label='Regressão Linear')

# Configurando legendas e rótulos
plt.xlabel('X')
plt.ylabel('Y')
plt.legend()
plt.title('Gráfico de Dispersão e Regressão Linear')

# Exibindo o gráfico
plt.show()
