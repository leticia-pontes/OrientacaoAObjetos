from dataclasses import dataclass
#from typing import Self
import math

@dataclass
class Retangulo:
    largura: float
    comprimento: float

    def calcular_area(self) -> float:
        return self.largura * self.comprimento
    
        '''
        def escalar(self, valor: float) -> Self: # Retorna mesmo tipo da classe atual
            self.largura *= valor
            self.comprimento *= valor
            return self

        def escalado(self, valor: float) -> Self:
            return Retangulo(
                largura=self.largura*valor,
                comprimento=self.comprimento*valor
            )
        '''
        '''
        @staticmethod
        def from_input():
            largura = float(input('Digite a largura:\n'))
            comprimento = float(input('Digite o comprimento:\n'))
            return Retangulo(largura, comprimento) # Necessita retornar o nome da classe
        '''
    
    @classmethod
    def from_input(cls):
        largura = float(input('Digite a largura:\n'))
        comprimento = float(input('Digite o comprimento:\n'))
        return cls(largura, comprimento) # Retorna o nome do atributo passado (cls)
    
@dataclass
class Circulo:
    raio: float

    def calcular_area(self) -> float:
        return self.raio ** 2 * math.pi
    
    @staticmethod
    def from_input():
        raio = float(input("\nDigite o raio:\n"))
        return Circulo(raio)

    
@dataclass
class Quadrado:
    lado: float

    def calcular_area(self) -> float:
        return self.lado ** 2
    
    @staticmethod
    def from_input():
        lado = float(input("\nDigite o lado:\n"))
        return Quadrado(lado)
    
retangulo = Retangulo(25, 13.2)
circulo = Circulo(5.3)
quadrado = Quadrado(4.8)

area_retangulo = retangulo.calcular_area()
area_circulo = circulo.calcular_area()
area_quadrado = quadrado.calcular_area()

print(f"{area_retangulo:.2f} {area_circulo:.2f} {area_quadrado:.2f}")

retangulo_input = Retangulo.from_input()
print(retangulo_input)
print(retangulo_input.calcular_area())

circulo_input = Circulo.from_input()
print(circulo_input)
print(f"{circulo_input.calcular_area():.2f}")

quadrado_input = Quadrado.from_input()
print(quadrado_input)
print(quadrado_input.calcular_area())