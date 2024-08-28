def calcular_media(valores):
    soma = sum(valores)
    media = soma / len(valores)
    return media

def calcular_mediana(valores):
    valores_ordenados = sorted(valores)
    n = len(valores_ordenados)
    print(valores_ordenados)
    
    if n % 2 == 0:
        mediana = (valores_ordenados[n // 2 - 1] + valores_ordenados[n // 2]) / 2
    else:
        mediana = valores_ordenados[n // 2]
    
    return mediana

def calcular_variancia_populacional(valores):
    media = calcular_media(valores)
    soma_diferencas_quadradas = sum((x - media) ** 2 for x in valores)
    variancia = soma_diferencas_quadradas / len(valores)
    return variancia

def calcular_variancia_amostral(valores):
    media = calcular_media(valores)
    soma_diferencas_quadradas = sum((x - media) ** 2 for x in valores)
    n = len(valores)
    variancia = soma_diferencas_quadradas /(n-1)
    return variancia

def calcular_desvio_padrao_populacional(valores):
    variancia_populacional = calcular_variancia_populacional(valores)
    desvio_padrao = variancia_populacional ** 0.5
    return desvio_padrao

def calcular_desvio_padrao_amostral(valores):
    variancia_amostral = calcular_variancia_amostral(valores)
    desvio_padrao = variancia_amostral ** 0.5
    return desvio_padrao

def calcular_coeficiente_variacao_populacional(valores):
    media = calcular_media(valores)
    desvio_padrao = calcular_desvio_padrao_populacional(valores)
    coef_variacao = (desvio_padrao / media)
    coef_variacao_porc = (desvio_padrao / media) * 100
    return coef_variacao, coef_variacao_porc

def calcular_coeficiente_variacao_amostral(valores):
    media = calcular_media(valores)
    desvio_padrao = calcular_desvio_padrao_amostral(valores)
    coef_variacao = (desvio_padrao / media)
    coef_variacao_porc = (desvio_padrao / media) * 100
    return coef_variacao, coef_variacao_porc

def calcular_quartis(valores):
    valores_ordenados = sorted(valores)
    n = len(valores_ordenados)
    
    q1_index = (n + 1) // 4
    q3_index = 3 * ((n + 1) // 4)
    
    q1 = valores_ordenados[q1_index - 1]
    q3 = valores_ordenados[q3_index - 1]
    
    return q1, q3

# Função principal
'''
valores = []
total_numeros = int(input("Insira o total de números: "))

for i in range(total_numeros):
    numero = float(input(f"Insira o número {i+1}: "))
    valores.append(numero)
'''

valores = [47.3, 12.8, 63.5, 29.1, 54.7, 18.2, 37.6, 82.4, 66.9, 41.2, 95.8, 23.7, 57.1, 34.6, 25.1, 1]


while True:
    print("\nOpções:")
    print("1 - Calcular Média")
    print("2 - Calcular Mediana")
    print("3 - Calcular Variância")
    print("4 - Calcular Desvio Padrão")
    print("5 - Calcular Coeficiente de Variação")
    print("6 - Calcular Quartis")
    print("0 - Sair")
    
    opcao = input("Escolha uma opção: ")
    
    if opcao == "1":
        media = calcular_media(valores)
        print(f"A média é: {media}")
    elif opcao == "2":
        mediana = calcular_mediana(valores)
        print(f"A mediana é: {mediana}")
    elif opcao == "3":
        variancia_populacional_resultado = calcular_variancia_populacional(valores)
        print(f"A variância populacional é: {variancia_populacional_resultado}")
        variancia_amostral_resultado = calcular_variancia_amostral(valores)
        print(f"A variância populacional é: {variancia_amostral_resultado}")
    elif opcao == "4":
        desvio_padrao_populacional_resultado = calcular_desvio_padrao_populacional(valores)
        print(f"O desvio padrão populacional é: {desvio_padrao_populacional_resultado}")
        desvio_padrao_amostral_resultado = calcular_desvio_padrao_amostral(valores)     
        print(f"O desvio padrão amostral é: {desvio_padrao_amostral_resultado}")
    elif opcao == "5":
        coef_variacao_populacional_resultado = calcular_coeficiente_variacao_populacional(valores)
        print(f"O coeficiente de variação populacional é: {coef_variacao_populacional_resultado}%")
        coef_variacao_amostral_resultado = calcular_coeficiente_variacao_amostral(valores)
        print(f"O coeficiente de variação populacional é: {coef_variacao_amostral_resultado}% ")
    elif opcao == "6":
        q1, q3 = calcular_quartis(valores)
        print(f"O primeiro quartil (Q1) é: {q1}")
        print(f"O terceiro quartil (Q3) é: {q3}")
    elif opcao == "0":
        break
    else:
        print("Opção inválida. Tente novamente.")
