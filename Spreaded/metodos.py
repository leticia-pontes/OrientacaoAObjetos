from dataclasses import dataclass
from typing import Self

# Correcao

@dataclass
class horario:
    _horas: int = 0
    _minutos: int = 0
    _segundos: int = 0

    def _corrigir(self):
        if self._segundos < 0:
            raise Exception("Segundos negativos")
        minutos = self._segundos // 60
        self._segundos %= 60
        self._minutos += minutos
        horas = self._minutos // 60
        self._minutos %= 60
        self.add_horas(horas)
        
    def add_segundos(self, segundos: int) -> Self:
        self._segundos += segundos
        self._corrigir()
        return self

    def add_minutos(self, minutos: int) -> Self:
        self._minutos += minutos
        self._corrigir()
        return self
    
    def add_horas(self, horas: int) -> Self:
        self._horas += horas
        self._horas %= 24
        return self

hora_atual = horario(23, 00, 00)
print("\nHora atual: ", hora_atual)

hora_atual.add_minutos(58)
hora_atual.add_segundos(36)

print("\nAdicionou 58 minutos e 36 segundos: ", hora_atual)

hora_atual.add_segundos(60 * 60 * 3)

print("\nAdicionou 85 segundos: ", hora_atual)

print()