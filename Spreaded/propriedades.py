from typing import Self


class Horario:
    def __init__(self, horas, minutos, segundos): #
        self._horas = horas
        self._minutos = minutos
        self._segundos = segundos

    @property
    def horas(self):
        print("\nHoras...", self._horas)
        return self._horas
    
    @horas.setter
    def horas(self, new_hora):
        print("\nAlterando hora...")
        self._horas += new_hora
        self._horas %= 24
        self._corrigir()
            
    @property
    def minutos(self):
        print("\nMinutos...", self._minutos)
        return self._minutos
    
    @minutos.setter
    def minutos(self, new_minuto):
        print("\nAlterando minuto...")
        self._minutos += new_minuto
        self._corrigir()
    
    @property
    def segundos(self):
        print("\nSegundo...", self._segundos)
        return self._segundos
    
    @segundos.setter
    def segundos(self, new_segundo):
        print("\nAlterando segundo...")
        self._segundos += new_segundo
        self._corrigir()


    def _corrigir(self):
        if self._segundos < 0:
            raise Exception("Segundos negativos")
        
        # minutos
        minutos = self._segundos // 60
        self._segundos %= 60
        self._minutos += minutos

        # horas
        horas = self._minutos // 60
        self._minutos %= 60
        self._horas += horas
        self._horas %= 24


hora = Horario(23, 00, 00)
print(f"\n{hora.horas}:{hora.minutos}:{hora.segundos}")

hora.minutos = 58
hora.segundos = 36

print(f"\n{hora.horas}:{hora.minutos}:{hora.segundos}")

hora.segundos = 24
hora.minutos = 1

print(f"\n{hora.horas}:{hora.minutos}:{hora.segundos}")

hora.horas = 3
print(f"\n{hora.horas}:{hora.minutos}:{hora.segundos}")

hora.horas = 23
print(f"\n{hora.horas}:{hora.minutos}:{hora.segundos}")

hora.horas = 23
hora.minutos = 58
hora.segundos = 145

print(f"\n{hora.horas}:{hora.minutos}:{hora.segundos}")

print()