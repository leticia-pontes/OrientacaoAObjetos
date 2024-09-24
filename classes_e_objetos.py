from dataclasses import dataclass

# DEFINIÇÃO DA CLASSE E ATRIBUTOS

@dataclass # CLASSE DE DADOS
class Retangulo:
    largura: float
    comprimento: float

# INSTANCIANDO OBJETOS
a = Retangulo(5, 25)
b = Retangulo(10, 15)
c = Retangulo(8, 18)

# PARA ACESSAR UM ATRIBUTO, USAR PONTO
print(a.largura)
print(c.comprimento)