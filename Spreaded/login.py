from dataclasses import dataclass
from getpass import getpass
from hashlib import sha256

@dataclass
class Usuario:
    nome: str
    senha: str

nome = input("Digite o nome: ")
senha = sha256(getpass("Digite a senha: ").encode()).hexdigest()

user = Usuario(nome, senha)

print(user)