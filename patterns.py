from dataclasses import dataclass, field
from abc import ABC, abstractmethod
from typing import List, Callable, Iterable, Iterator
from io import StringIO
import random
import time


# Acaba virando uma classe Deus
class Product:
    name: str

    @classmethod
    def create_liquid(cls, name: str, quantity: float) -> 'Product':
        return Liquid(name=name, quantity=quantity)

    @classmethod
    def create_solid(cls, name: str, quantity: int) -> 'Product':
        return Solid(name=name, quantity=quantity)
        

@dataclass
class Liquid(Product):
    name: str
    quantity: float

@dataclass
class Solid(Product):
    name: str
    quantity: int


p = Product.create_liquid('Leite', 1.)


# Observer
@dataclass
class Sensor:
    value: float
    # field: cria método fábrica pro dataclass usar
    listeners: List['SensorListener'] = field(default_factory=list)

    def set_value(self, value: float):
        old_value = self.value
        self.value = value

        if old_value != value:
            for listener in self.listeners:
                listener.on_change(self)

    def add_listener(self, listener: 'SensorListener'):
        self.listeners.append(listener)


class SensorListener(ABC):

    @abstractmethod
    def on_change(self, sensor: Sensor):
        raise NotImplementedError()

class SerialSensorListener(SensorListener):

    @abstractmethod
    def on_change(self, sensor: Sensor):
        print("Sou o SerialSensorListener >>> ", sensor)

    @classmethod
    def adapt_fn(cls, fn: Callable[[Sensor], None]) -> 'SensorListener':
        return LambdaAdapterSensorListener(fn)

@dataclass
class LambdaAdapterSensorListener(SensorListener):

    fn: Callable[[Sensor], None]

    def on_change(self, sensor: Sensor):
        return self.fn(sensor)
    

@dataclass
class FileSensorListener(SensorListener):
    output: StringIO

    def on_change(self, sensor: Sensor):
        print(sensor, file=self.output)


# sensor_temp = Sensor(None)
# sensor_temp.add_listener(FileSensorListener(open('sensor.txt', 'w+')))
# sensor_temp.add_listener(LambdaAdapterSensorListener(print))
# sensor_temp.add_listener(LambdaAdapterSensorListener(lambda sensor: print('Lambda >>>', sensor)))

# sensor_temp.set_value(25)
# sensor_temp.set_value(32)


# Iterator
# retorna o elemento em si
class IteratorList:

    def __init__(self, lista) -> None:
        self.index = 0
        self.lista = lista

    def next(self):
        atual = self.index
        self.index += 1
        if self.index > len(self.lista):
            raise StopIteration()
        return self.lista[atual]

    def __iter__(self):
        return self

    def __next__(self):
        return self.next()


def outro_exemplo():
    yield 1
    yield 2
    yield 3


def my_range(inicial, final) -> Iterable[int]:
    lista = []
    atual = inicial
    while atual < final:
        yield atual # YUDI
        atual += 1
    

# it = iter(outro_exemplo())
# print(next(it))
# print('------------')
# print(next(it))
# print('------------')
# print(next(it))
# print('------------')
# print(next(it))



# print(outro_exemplo())
# print(list(outro_exemplo()))

# print(my_range(0, 10))

# for i in my_range(0, 10):
#     print (i)
    




# with open('sensor.txt') as input:
#     content = input.read()
#     print(type(content))
#     print(content)


# Iterator
# lista = ['a', 'b', 'c', 'd', 'e']

# iterator = IteratorList(lista)

# # python 2: printa números de 0 a 9
# print(range(0, 10))

# print(list(range(0, 10)))


# Estouro de memória
# print(list(range(0, 99999999999999999999999)))


# for i in iterator:
#     print(i)


# while True:
#     item = iterator.next()
#     print(item)



class SensorLento:

    def ler(self):
        while True:
            yield random.random()
            time.sleep(0.5)

sensor = SensorLento()

for (_,valor) in zip(range(10), sensor.ler()):
    print(_, valor)
